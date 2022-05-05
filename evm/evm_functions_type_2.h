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

#ifndef FUNCTIONS_TYPE_2_H_
#define FUNCTIONS_TYPE_2_H_

#include "evm_object.h"
#include "evm.h"

enum vm_func_2 {
    FUNC_T2_00 = 0x00, //
    FUNC_T2_01 = 0x01, //
    FUNC_T2_02 = 0x02, //
    FUNC_T2_03 = 0x03, //
    FUNC_T2_04 = 0x04, //
    FUNC_T2_05 = 0x05, //
    FUNC_T2_06 = 0x06, //
    FUNC_T2_07 = 0x07, //
    FUNC_T2_08 = 0x08, //
    FUNC_T2_09 = 0x09, //
    FUNC_T2_0a = 0x0a, //
    FUNC_T2_0b = 0x0b, //
    FUNC_T2_0c = 0x0c, //
    FUNC_T2_0d = 0x0d, //
    FUNC_T2_0e = 0x0e, //
    FUNC_T2_0f = 0x0f, //
    FUNC_T2_10 = 0x10, //
    FUNC_T2_11 = 0x11, //
    FUNC_T2_12 = 0x12, //
    FUNC_T2_13 = 0x13, //
    FUNC_T2_14 = 0x14, //
    FUNC_T2_15 = 0x15, //
    FUNC_T2_16 = 0x16, //
    FUNC_T2_17 = 0x17, //
    FUNC_T2_18 = 0x18, //
    FUNC_T2_19 = 0x19, //
    FUNC_T2_1a = 0x1a, //
    FUNC_T2_1b = 0x1b, //
    FUNC_T2_1c = 0x1c, //
    FUNC_T2_1d = 0x1d, //
    FUNC_T2_1e = 0x1e, //
    FUNC_T2_1f = 0x1f, //
    FUNC_T2_20 = 0x20, //
    FUNC_T2_21 = 0x21, //
    FUNC_T2_22 = 0x22, //
    FUNC_T2_23 = 0x23, //
    FUNC_T2_24 = 0x24, //
    FUNC_T2_25 = 0x25, //
    FUNC_T2_26 = 0x26, //
    FUNC_T2_27 = 0x27, //
    FUNC_T2_28 = 0x28, //
    FUNC_T2_29 = 0x29, //
    FUNC_T2_2a = 0x2a, //
    FUNC_T2_2b = 0x2b, //
    FUNC_T2_2c = 0x2c, //
    FUNC_T2_2d = 0x2d, //
    FUNC_T2_2e = 0x2e, //
    FUNC_T2_2f = 0x2f, //
    FUNC_T2_30 = 0x30, //
    FUNC_T2_31 = 0x31, //
    FUNC_T2_32 = 0x32, //
    FUNC_T2_33 = 0x33, //
    FUNC_T2_34 = 0x34, //
    FUNC_T2_35 = 0x35, //
    FUNC_T2_36 = 0x36, //
    FUNC_T2_37 = 0x37, //
    FUNC_T2_38 = 0x38, //
    FUNC_T2_39 = 0x39, //
    FUNC_T2_3a = 0x3a, //
    FUNC_T2_3b = 0x3b, //
    FUNC_T2_3c = 0x3c, //
    FUNC_T2_3d = 0x3d, //
    FUNC_T2_3e = 0x3e, //
    FUNC_T2_3f = 0x3f, //
};

// placeholder
uint16_t func_t2_nop(evm_t *vm, uint16_t args) {
    return VM_T(vm);
}

uint16_t (*t2_fun[])(evm_t *vm, uint16_t args) = {
    func_t2_nop, // 0x00
    func_t2_nop, // 0x01
    func_t2_nop, // 0x02
    func_t2_nop, // 0x03
    func_t2_nop, // 0x04
    func_t2_nop, // 0x05
    func_t2_nop, // 0x06
    func_t2_nop, // 0x07
    func_t2_nop, // 0x08
    func_t2_nop, // 0x09
    func_t2_nop, // 0x0a
    func_t2_nop, // 0x0b
    func_t2_nop, // 0x0c
    func_t2_nop, // 0x0d
    func_t2_nop, // 0x0e
    func_t2_nop, // 0x0f
    func_t2_nop, // 0x10
    func_t2_nop, // 0x11
    func_t2_nop, // 0x12
    func_t2_nop, // 0x13
    func_t2_nop, // 0x14
    func_t2_nop, // 0x15
    func_t2_nop, // 0x16
    func_t2_nop, // 0x17
    func_t2_nop, // 0x18
    func_t2_nop, // 0x19
    func_t2_nop, // 0x1a
    func_t2_nop, // 0x1b
    func_t2_nop, // 0x1c
    func_t2_nop, // 0x1d
    func_t2_nop, // 0x1e
    func_t2_nop, // 0x1f
    func_t2_nop, // 0x20
    func_t2_nop, // 0x21
    func_t2_nop, // 0x22
    func_t2_nop, // 0x23
    func_t2_nop, // 0x24
    func_t2_nop, // 0x25
    func_t2_nop, // 0x26
    func_t2_nop, // 0x27
    func_t2_nop, // 0x28
    func_t2_nop, // 0x29
    func_t2_nop, // 0x2a
    func_t2_nop, // 0x2b
    func_t2_nop, // 0x2c
    func_t2_nop, // 0x2d
    func_t2_nop, // 0x2e
    func_t2_nop, // 0x2f
    func_t2_nop, // 0x30
    func_t2_nop, // 0x31
    func_t2_nop, // 0x32
    func_t2_nop, // 0x33
    func_t2_nop, // 0x34
    func_t2_nop, // 0x35
    func_t2_nop, // 0x36
    func_t2_nop, // 0x37
    func_t2_nop, // 0x38
    func_t2_nop, // 0x39
    func_t2_nop, // 0x3a
    func_t2_nop, // 0x3b
    func_t2_nop, // 0x3c
    func_t2_nop, // 0x3d
    func_t2_nop, // 0x3e
    func_t2_nop, // 0x3f
};

#endif /* FUNCTIONS_TYPE_2_H_ */
