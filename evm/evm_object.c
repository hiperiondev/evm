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
#include <stdlib.h>

#include "evm.h"
#include "qhashtbl.h"

#define NIL_AS_ZERO  1  // treat nil as zero

obj_id_t obj_next;

////////////// vm object functions //////////////

obj_id_t object_next_id(void) {
    if (obj_next.id == 0xFFFFFFFF) {
        // TODO: implement - if id space full -> search deallocated ids free
    } else {
        obj_next.id++;
    }

    return obj_next;
}

uint8_t object_get_type(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint8_t object_set(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint64_t object_get_any_int(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint8_t object_test_zero(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint8_t object_persist(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint8_t object_retain(evm_t *evm, obj_id_t id) {
    // TODO: implement
    return RC_OK;
}

uint8_t object_convert(evm_t *evm, obj_id_t id, uint8_t to_type) {
    if (to_type == VT_NULL || object_get_type(evm, id) == to_type)
        return RC_OK;

    // TODO: implement
    return RC_OK;
}

#define ARG_ID(x)  if (!arg) { \
                       x = arg; \
                   } else { \
                       x = VM_POP(evm, d); \
                   }

uint8_t object_op(evm_t *evm, uint8_t type, uint8_t operation, uint8_t arg) {
    uint8_t ret = RC_OK;
    obj_id_t o;

    switch (operation) {

        case OBJ_CREATE:
            object_t *obj;
            for (int n = 0; n < arg; n++) {
                obj = malloc(sizeof(object_t));
                obj->type = type;
                o = object_next_id();
                VM_PUSH(evm,d, o.id, 1);
                ret = evm->object->put(evm->object, o.c, obj, sizeof(object_t*)) ? RC_OK : RC_OBJECT_ERROR;
                if (ret == RC_OBJECT_ERROR)
                    break;
            }
            break;

        case OBJ_DELETE:
            for (int n = 0; n < arg; n++) {
                o.id = VM_POP(evm, d);
                ret = evm->object->remove(evm->object, o.c) ? RC_OK : RC_OBJECT_ERROR;
                if (ret == RC_OBJECT_ERROR)
                    break;
            }
            break;

        case OBJ_TO_T:
            ARG_ID(o.id);
            object_convert(evm, o, type);
            // TODO: implement
            break;

        case OBJ_FROM_T:
            ARG_ID(o.id);
            object_convert(evm, o, type);
            // TODO: implement
            break;

        case OBJ_TO_A:
            ARG_ID(o.id);
            object_convert(evm, o, type);
            // TODO: implement
            break;

        case OBJ_FROM_A:
            ARG_ID(o.id);
            object_convert(evm, o, type);
            // TODO: implement
            break;
    }

    return ret;
}
