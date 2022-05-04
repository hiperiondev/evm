/*
 * Copyright 2022 Emiliano Gonzalez LU3VEA (egonzalez . hiperion @ gmail . com))
 * * Project Site:  *
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "evm.h"
#include "evm_functions_type_0.h"
#include "evm_functions_type_1.h"
#include "evm_functions_type_2.h"
#include "evm_stack.h"
#include "evm_object.h"

//#define CHECK_PC 1  // check if PC under/overrun

//////////////////////////////////////////////////////////////

uint8_t evm_push(evm_t *evm, uint64_t val, bool lit, bool stk, int8_t stkp_inc) {
    uint16_t vtp;
    uint8_t len = 5, ret = 1;
    uint16_t pfx_cnt = (lit ? PFX_LIT_CNT : PFX_OBJ_CNT);
    uint16_t pfx_end = (lit ? PFX_LIT_END : PFX_OBJ_END);
    uint64_t mask = 0x0000000000000FFF;

    if (!(val & 0xFFFFFFFFFFFFF000)) {
           vtp = val | pfx_end;
           goto end;
       }

    while (!(val & (mask << (12 * len))) && len > 0) {
        --len;
    }

    ret = len + 1;
    for (; len > 0; --len) {
        vtp = ((val & (mask << (12 * len))) >> (12 * len)) | (len == ret - 1 ? pfx_end : pfx_cnt);
        if (stk) {
            VM_PUSH(evm, d, vtp, stkp_inc);
        } else {
            VM_PUSH(evm, r, vtp, stkp_inc);
        }
    }
    vtp = (val & mask) | pfx_cnt;

    end:
    if (stk) {
        VM_PUSH(evm, d, vtp, stkp_inc);
    } else {
        VM_PUSH(evm, r, vtp, stkp_inc);
    }

    return ret;
}

uint64_t evm_pop(evm_t *evm, bool stk, uint8_t *type) {
    uint8_t cnt = 0;
    uint64_t stk_val = 0;
    uint64_t value = 0;

    if (stk) {
        *type = VM_T_TYPE(evm);
        while ((VM_T_TYPE(evm) == LIT_CNT) | (VM_T_TYPE(evm) == OBJ_CNT)) {
            stk_val = VM_POP(evm, d) & 0x1FFF;
            value |= stk_val << (12 * cnt++);
        }
        stk_val = VM_POP(evm, d) & 0x1FFF;
        value |= stk_val << (12 * cnt);

    } else {
        *type = VM_R_TYPE(evm);
        while ((VM_R_TYPE(evm) == LIT_CNT) | (VM_R_TYPE(evm) == OBJ_CNT)) {
            stk_val = VM_POP(evm, r) & 0x1FFF;
            value |= stk_val << (12 * cnt++);
        }
        stk_val = VM_POP(evm, r) & 0x1FFF;
        value |= stk_val << (12 * cnt);
    }

    return value;
}

uint8_t evm_stack_value_size(evm_t *evm, bool stk) {
    uint8_t cnt = 0;
    if (stk) {
        while ((VM_STK_TYPE(evm, d, cnt) == LIT_CNT) || (VM_STK_TYPE(evm, d, cnt) == OBJ_CNT))
            cnt++;
    } else {
        while ((VM_STK_TYPE(evm, r, cnt) == LIT_CNT) || (VM_STK_TYPE(evm, r, cnt) == OBJ_CNT))
            cnt++;
    }
    return cnt + 1;
}

uint8_t evm_check_zero(evm_t *evm) {
    uint8_t type;
    uint64_t stack_value = evm_pop(evm, DSTK, &type);
    switch (VM_T_TYPE(evm)) {
        case LIT_CNT:
        case LIT_END:
            return (stack_value == 0);
            break;
        case OBJ_CNT:
        case OBJ_END:
            obj_id_t obj;
            obj.id = stack_value;
            return object_test_zero(evm, obj);
            break;
    }
    return RC_OK;
}

uint8_t evm_init(evm_t **evm, uint32_t dsize, uint32_t rsize, uint32_t regsize, uint32_t progsize) {

    obj_next.id = 0;

    (*evm) = malloc(sizeof(evm_t));
    if ((*evm) == NULL)
        return -1;

    (*evm)->_dp = 0;
    (*evm)->_rp = 0;
    (*evm)->pc = 0;
    (*evm)->irq_addr = 0;
    (*evm)->status = 0;
    (*evm)->A = 0;

    (*evm)->reg = malloc(regsize * sizeof(uint32_t));
    if ((*evm)->reg == NULL)
        return RC_ERROR;
    (*evm)->reg_size = regsize;

    (*evm)->_ds = malloc(dsize * sizeof(uint16_t));
    if ((*evm)->_ds == NULL)
        return RC_ERROR;
    (*evm)->_rs = malloc(rsize * sizeof(uint16_t));
    if ((*evm)->_rs == NULL)
        return RC_ERROR;
    (*evm)->ds_size = dsize;
    (*evm)->rs_size = rsize;

    (*evm)->program = malloc(progsize * sizeof(uint16_t));
    (*evm)->prog_size = progsize;

    if(((*evm)->object = qhashtbl(0, QHASHTBL_THREADSAFE)) == NULL)
        return RC_ERROR;

    return RC_OK;
}

uint8_t evm_deinit(evm_t **evm) {
    free((*evm)->reg);
    free((*evm)->_ds);
    free((*evm)->_rs);
    free((*evm)->program);
    qhashtbl_free((*evm)->object);
    free((*evm));

    return 0;
}

uint8_t evm_step(evm_t *evm, uint16_t word) {
    static const int8_t delta[] = { 0, 1, -1, 0 };

    VM_PC(evm)++;

#ifdef CHECK_PC
    if ((VM_PC < 0) ||(VM_PC > evm->prog_size))
        return RC_PC_UND_OVR;
#endif

    // irq
    if ((evm->status & ST_IRQ) && !(evm->status & ST_IMK)) {
#ifdef CHECK_PC
        if ((VM_PC + 1 > evm->prog_size) || (evm->irq_addr > evm->prog_size))
            return RC_PC_UND_OVR;
#endif
        evm_push(evm, VM_PC(evm) + 1, LIT, RSTK, 1);
        VM_PC(evm) = evm->irq_addr;
        evm->status &= ~ST_IRQ;
        evm->status |= ST_IMK;
        return RC_IRQ;
    }

    switch (OP(word)) {

        case LITERL:
            VM_T(evm) = word;
            return RC_OK;
            break;

        case OBJECT:
        	return object_op(evm, OBJ_TYPE(word), OBJ_OPERATION(word), OBJ_ARGUMENT(word));
            break;

        case BRCCLL:
            switch (BRC_CLL_TYPE(word)) {
                case JMP_ABS:
                    VM_PC(evm) = BRC_CLL_ADDR(word);
                    return RC_OK;
                    break;

                case JMP_IND:
                    VM_PC(evm) = BRC_CLL_ADDR(word) + VM_A(evm);
                    return RC_OK;
                    break;

                case JMZ_ABS:
                    if (evm_check_zero(evm))
                        VM_PC(evm) = BRC_CLL_ADDR(word);
                    return RC_OK;
                    break;

                case JMZ_IND:
                    if (evm_check_zero(evm))
                        VM_PC(evm) = BRC_CLL_ADDR(word) + VM_A(evm);
                    return RC_OK;
                    break;

                case JNZ_ABS:
                    if (!evm_check_zero(evm))
                        VM_PC(evm) = BRC_CLL_ADDR(word);
                    return RC_OK;
                    break;

                case JNZ_IND:
                    if (!evm_check_zero(evm))
                        VM_PC(evm) = BRC_CLL_ADDR(word) + VM_A(evm);
                    return RC_OK;
                    break;

                case CLL_ABS:
                    evm_push(evm, VM_PC(evm) + 1, LIT, RSTK, 1);
                    VM_PC(evm) = BRC_CLL_ADDR(word);
                    return RC_OK;
                    break;

                case CLL_IND:
                    evm_push(evm, VM_PC(evm) + 1, LIT, RSTK, 1);
                    VM_PC(evm) = BRC_CLL_ADDR(word) + VM_A(evm);
                    return RC_OK;
                    break;
            }
            break;

        case FUNSTK:
            switch (FUN_OP(word)) {

                case FUN_0:
                    return (*t0_fun[FUN_OP(word)])(evm, FUN_ARGQTY(word));
                    break;

                case FUN_1:
                    return (*t1_fun[FUN_OP(word)])(evm, FUN_ARGQTY(word));
                    break;

                case FUN_2:
                    return (*t2_fun[FUN_OP(word)])(evm, FUN_ARGQTY(word));
                    break;

                case STACK:
                    uint16_t res = VM_T(evm);
                    uint8_t stk_v;
                    uint8_t type;

                    if (STK_R2P(word))
                        VM_PC(evm) = evm_pop(evm, DSTK, &type);

                    res = (*stk_fun[STK_OP(word)])(evm);

                    stk_v = evm_stack_value_size(evm, DSTK);
                    if (stk_v < 0)
                        VM_STK_PNT(evm, d) += delta[STK_DS(word)] * stk_v;
                    else
                        VM_STK_PNT(evm, d) += delta[STK_DS(word)];

                    stk_v = evm_stack_value_size(evm, RSTK);
                    if (stk_v < 0)
                        VM_STK_PNT(evm, r) += delta[STK_RS(word)] * stk_v;
                    else
                        VM_STK_PNT(evm, r) += delta[STK_RS(word)];

                    if (STK_T2N(word)) {
                        VM_N(evm) = VM_T(evm);
                    }
                    if (STK_T2R(word)) {
                        VM_R(evm) = VM_T(evm);
                    }
                    if (STK_N2T(word)) {
                        VM_T(evm) = VM_N(evm);
                    } else {
                        VM_T(evm) = res;
                    }

                    if (STK_RS(word) == 0x03)
                        VM_A(evm) = VM_T(evm);
                    if (STK_DS(word) == 0x03)
                        --VM_A(evm);

                    return RC_OK;
                    break;
            }
            break;

        default:
            return RC_OP_UNKNOWN;
    }

    return RC_OK;
}
