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

#ifndef STACK_H_
#define STACK_H_

#include "evm.h"

enum vm_stack {
    STK_NOP = 0x00, // t
    STK_SCN = 0x01, // n
    STK_TRS = 0x02, // r->t
    STK_DDS = 0x03, // depth of data stack (double literal)
    STK_DRS = 0x04, // depth of return stack (double literal)
    STK_SSP = 0x05, // set data stack depth (double literal)
    STK_SRP = 0x06, // set return stack depth (double literal)
    STK_RTO = 0x07, // result to object(t)
    STK_RTT = 0x08, // reg(t)->t
    STK_TTR = 0x09, // t->reg(n)
    STK_SWP = 0x0a, // swap
    STK_RTR = 0x0b, // reg(t)->reg(n)
    STK_ICT = 0x0c, // ++t
    STK_DCT = 0x0d, // --t
    STK_AIC = 0x0e, // ++A
    STK_ATT = 0x0e, // A->t
};

uint16_t stk_nop(evm_t *vm) {
    return VM_T(vm);
}

uint16_t stk_scn(evm_t *vm) {
    return VM_N(vm);
}

uint16_t stk_trs(evm_t *vm) {
    return VM_R(vm);
}

uint16_t stk_dds(evm_t *vm) {
    return vm->_dp;
}

uint16_t stk_drs(evm_t *vm) {
    return vm->_rp;
}

uint16_t stk_ssp(evm_t *vm) {
	uint16_t res = VM_POP(vm, d);
	vm->_dp = res;
	return VM_T(vm);
}

uint16_t stk_srp(evm_t *vm) {
	uint16_t res = VM_POP(vm, r);
	vm->_rp = res;
	return VM_T(vm);
}

uint16_t stk_rto(evm_t *vm) {
    return VM_T(vm);
}

uint16_t stk_rtt(evm_t *vm) {
    return VM_T(vm);
}

uint16_t stk_ttr(evm_t *vm) {
    return vm->_ds[VM_POP(vm, d)];
}

uint16_t stk_swp(evm_t *vm) {
    uint16_t tmp = VM_N(vm);
    VM_N(vm) = VM_T(vm);
    return tmp;
}

uint16_t stk_rtr(evm_t *vm) {
    uint16_t tmp = vm->_ds[vm->_dp -2];
    vm->_ds[vm->_dp -2] = VM_N(vm);
    VM_N(vm) = VM_T(vm);
    return tmp;
}

uint16_t stk_ict(evm_t *vm) {
    return ++VM_T(vm);
}

uint16_t stk_dct(evm_t *vm) {
    return --VM_T(vm);
}

uint16_t stk_aic(evm_t *vm) {
    ++VM_A(vm);
    return VM_T(vm);
}

uint16_t stk_att(evm_t *vm) {
    return VM_A(vm);
}

uint16_t (*stk_fun[])(evm_t *vm) = {
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

#endif /* STACK_H_ */
