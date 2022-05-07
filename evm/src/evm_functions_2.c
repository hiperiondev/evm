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

#include <stdint.h>

#include "evm.h"

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
