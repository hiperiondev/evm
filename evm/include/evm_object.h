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

#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdint.h>

#include "evm.h"

extern obj_id_t obj_next;

obj_id_t object_next_id(void);
uint64_t object_get_any_int(evm_t *evm, obj_id_t id);
 uint8_t object_get_type(evm_t *evm, obj_id_t id);
 uint8_t object_test_zero(evm_t *evm, obj_id_t id);
 uint8_t object_persist(evm_t *evm, obj_id_t id);
 uint8_t object_retain(evm_t *evm, obj_id_t id);
 uint8_t object_op(evm_t *evm, uint8_t type, uint8_t operation, uint8_t arg);

#endif /* OBJECT_H_ */
