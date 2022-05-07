/*
 * Copyright 2022 Emiliano Gonzalez LU3VEA (egonzalez . hiperion @ gmail . com))
 * * Project Site:  https://github.com/hiperiondev/evm *
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

#include "evm.h"

uint16_t stk_nop(evm_t *evm) {
    return VM_T(evm);
}

uint16_t stk_scn(evm_t *evm) {
    return VM_N(evm);
}

uint16_t stk_trs(evm_t *evm) {
    uint8_t type;
    uint16_t res = evm_pop(evm, RSTK, &type);
    evm_push(evm, res, LIT, DSTK, 0);
    return VM_R(evm);
}

uint16_t stk_dds(evm_t *evm) {
    return evm->_dp;
}

uint16_t stk_drs(evm_t *evm) {
    return evm->_rp;
}

uint16_t stk_ssp(evm_t *evm) {
    uint8_t type;
    uint16_t res = evm_pop(evm, DSTK, &type);
    evm->_dp = res;
    return VM_T(evm);
}

uint16_t stk_srp(evm_t *evm) {
    uint8_t type;
    uint16_t res = evm_pop(evm, DSTK, &type);
    evm->_rp = res;
    return VM_T(evm);
}

uint16_t stk_rto(evm_t *evm) { // TODO: implement
    return VM_T(evm);
}

uint16_t stk_rtt(evm_t *evm) {
    uint8_t type;
    uint16_t reg = evm_pop(evm, DSTK, &type);
    if (reg > evm->reg_size)
        return RC_REG_UNKNOWN;

    evm_push(evm, evm->reg[reg], LIT, DSTK, 0);

    return VM_T(evm);
}

uint16_t stk_ttr(evm_t *evm) {
    uint8_t type;
    uint32_t val = evm_pop(evm, DSTK, &type);
    uint16_t reg = evm_pop(evm, DSTK, &type);
    if (reg > evm->reg_size)
        return RC_REG_UNKNOWN;

    evm->reg[reg] = val;

    return VM_T(evm);
}

uint16_t stk_swp(evm_t *evm) {
    uint16_t tmp = VM_N(evm);
    VM_N (evm) = VM_T(evm);
    return tmp;
}

uint16_t stk_rtr(evm_t *evm) {
    uint8_t type;
    uint16_t reg_from = evm_pop(evm, DSTK, &type);
    uint16_t reg_to = evm_pop(evm, DSTK, &type);
    if (reg_from > evm->reg_size || reg_to > evm->reg_size)
        return RC_REG_UNKNOWN;

    evm->reg[reg_to] = evm->reg[reg_from];

    return VM_T(evm);
}

uint16_t stk_ict(evm_t *evm) {
    return ++VM_T(evm);
}

uint16_t stk_dct(evm_t *evm) {
    return --VM_T(evm);
}

uint16_t stk_aic(evm_t *evm) {
    ++VM_A(evm);
    return VM_T(evm);
}

uint16_t stk_att(evm_t *evm) {
    evm_push(evm, VM_A(evm), LIT, DSTK, 0);
    return VM_T(evm);
}

uint16_t (*stk_fun[])(evm_t *evm) = {
    stk_nop,
    stk_scn,
    stk_trs,
    stk_dds,
    stk_drs,
    stk_ssp,
    stk_srp,
    stk_rto,
    stk_rtt,
    stk_ttr,
    stk_swp,
    stk_rtr,
    stk_ict,
    stk_dct,
    stk_aic,
    stk_att
};



