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

/////////////////////////////////////////////////////////////////////////////////////
/*
## Instruction Set Encoding

        +---------------------------------------------------------------+
        | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        +---------------------------------------------------------------+
        | 1 | 0 | c |                 LITERAL                           | c=0 -> continue until c=1 (64 bits)
        +---------------------------------------------------------------+
        | 1 | 1 |        TYPE       | operation |        argument       | OBJECT (operation: create, delete, to T, from T, to register, from register, to A, from A)
        +---------------------------------------------------------------+
        | 0 | 0 |   TYPE    |        BRANCH / CALL argument             |
        +---------------------------------------------------------------+
        | 0 | 1 | TYPE  |        FUNCTION       |        ARG QTY        |  FUNCTIONS
        +---------------------------------------------------------------+
        | 0 | 1 | 1 | 1 |      OP       |T2N|T2R|N2T|R2P|  RS   |  DS   |  STACK
        +---------------------------------------------------------------+
        | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        +---------------------------------------------------------------+

        STACK
        +---------------------------------------------------------------+
        | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
        +---------------------------------------------------------------+
        | 0 | c | 0 |                    LITERAL                        |  c=1 -> continue until c=0
        +---------------------------------------------------------------+
        | 1 | c | 0 |                   OBJECT ID                       |
        +---------------------------------------------------------------+

T   : Top of data stack
N   : Next on data stack
PC  : Program Counter

T2N : Move T to N
T2R : Move T to top of return stack
N2T : Move the new value of T (or D) to N
R2P : Move top of return stack to PC

RSTACK and DSTACK :
00 =  0
01 = +1
10 = -1

DSTACK:
11 = --A

RSTACK
11 = Move T to A

NOTE: if both used first move then decrement

 OBJECT operation:
        create: arg = qty objects to create. ids to dstack
        delete: arg = qty objects to delete. ids from dstack
          to T: arg > 0 -> id = arg. id. arg = 0 id from T
        from T: arg > 0 -> id = arg. arg = 0 id from N
   to register: arg > 0 -> id = arg. arg = 0 id from T. register id from N
 from register: arg > 0 -> id = arg. arg = 0 id from T. register id from N
          to A: arg > 0 -> id = arg. arg = 0 id from T
        from A: arg > 0 -> id = arg. arg = 0 id from T

NOTE: before any operation try to convert to type

 */
/////////////////////////////////////////////////////////////////////////////////////

#ifndef EVM_H_
#define EVM_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <time.h>

#include "qhashtbl.h"

#ifdef DEBUG
#if DEBUG == 1
#define DBG_PRINT(fmt, args...)  \
       fprintf(stderr, "" fmt, ##args)
#endif
#if DEBUG == 2
#define DBG_PRINT(fmt, args...)  \
       fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, __LINE__, __FUNCTION__, ##args)
#endif
#else
#define DBG_PRINT(fmt, args...)
#endif

#define EP(x) [x] = #x  // enum print

// data types
typedef enum {
    VT_NULL    = 0x00,  //
    VT_BOOL    = 0x01,  // bool
    VT_SINT    = 0x02,  // int8_t
    VT_INT     = 0x03,  // int16_t
    VT_DINT    = 0x04,  // int32_t
    VT_LINT    = 0x05,  // int64_t
    VT_USINT   = 0x06,  // uint8_t
    VT_UINT    = 0x07,  // uint16_t
    VT_UDINT   = 0x08,  // uint32_t
    VT_ULINT   = 0x09,  // uint64_t
    VT_REAL    = 0x0a,  // float
    VT_LREAL   = 0x0b,  // double
    VT_TIME    = 0x0c,  // time_t
    VT_DATE    = 0x0d,  // date_t
    VT_TOD     = 0x0e,  // tod_t
    VT_DT      = 0x0f,  // dat_t
    VT_STRING  = 0x10,  // char
    VT_WSTRING = 0x11,  // wchar_t
    VT_POINTER = 0x12,  // pointer_t
    VT_TABLE   = 0x13,  // table_t
    VT_USER    = 0x14,  // user_t
	VT_NDEF_15 = 0x15,  // not defined
    VT_NDEF_16 = 0x16,  // not defined
    VT_NDEF_17 = 0x17,  // not defined
    VT_NDEF_18 = 0x18,  // not defined
    VT_NDEF_19 = 0x19,  // not defined
    VT_NDEF_1A = 0x1a,  // not defined
    VT_NDEF_1B = 0x1b,  // not defined
    VT_NDEF_1C = 0x1c,  // not defined
    VT_NDEF_1D = 0x1d,  // not defined
    VT_NDEF_1E = 0x1e,  // not defined
	VT_NIL     = 0x1f,  // nil
} vartype_t;

typedef enum {
	TT_MARK    = 0x00,
	TT_NORMAL  = 0x01,
	TT_PERSIST = 0x02,
	TT_RETAIN  = 0x03,
} tt_t;

typedef union {
    struct {
         uint8_t day;
         uint8_t month;
        uint16_t year;
    } date;
        uint32_t dw_date;
} date_t;

typedef union {
    struct {
        uint8_t csec;
        uint8_t sec;
        uint8_t min;
        uint8_t hour;
    } tod;
       uint32_t dw_tod;
} tod_t;

typedef struct {
    struct {
         tod_t tod;
        date_t date;
    } dat;
      uint64_t dw_dat;
} dat_t;

typedef uint64_t pointer_t;

typedef struct {
	    void *data;
	uint64_t value;
} user_t;

typedef struct {
	    bool wstring;
	uint32_t len;
	uint32_t hash;
	union {
		   char *str;
		wchar_t *wstr;
	};
} string_t;

typedef struct {
      uint64_t len;
          void *table;
} table_t;

typedef struct {
        vartype_t type;
             tt_t tt;
    union {
             bool boolean;
           int8_t sint;
          int16_t intg;
          int32_t dint;
          int64_t lint;
          uint8_t usint;
         uint16_t uint;
         uint32_t udint;
         uint64_t ulint;
            float real;
           double lreal;
           time_t time;
           date_t date;
            tod_t tod;
            dat_t dt;
         string_t *string;
         uint64_t pointer;
          table_t table;
           user_t user;
         uint16_t *code;
    };
} object_t;

typedef union obj_id {
        char c[4];
    uint32_t id;
} obj_id_t;

typedef struct {
      uint16_t _dp;          // data stack pointer
      uint16_t _rp;          // return stack pointer
      uint32_t pc;           // program counter
      uint32_t irq_addr;     // irq address
       uint8_t status;       // status register
       int64_t A;            // A register
      uint32_t *reg;         // register vector (max 64)
       uint8_t reg_size;     // register size
      uint16_t *program;     // program vector
      uint16_t *_rs;         // return stack vector
      uint16_t *_ds;         // data stack vector
      uint32_t ds_size;      // data stack size
      uint32_t rs_size;      // return stack size
      uint32_t prog_size;    // program memory size
      object_t *result;      // operation result place
    qhashtbl_t *object;      // objects hash table
} evm_t;

//////////////////////////////////////////
#define OP(x)                    (x >> 14)

#define LIT(x)                   (x & 0x3FFF)
#define LIT_PREFX(x)             ((x & 0x2000) << 1)
#define LIT_VAL(x)               (x & 0x1FFF)

#define OBJ_TYPE(x)              ((x & 0x3E00) >> 9)
#define OBJ_OPERATION(x)         (x & 0x01C0)
#define OBJ_ARGUMENT(x)          (x & 0x003F)

#define BRC_CLL_TYPE(x)          (x >> 11)
#define BRC_CLL_ADDR(x)          (x & 0x07FF)

#define FUN_TYPE(x)              ((x & 0x3000) >> 12)
#define FUN_OP(x)                ((x & 0x03F0) >> 4)
#define FUN_ARGQTY(x)            (x & 0x000F)

#define STK_OP(x)                ((x & 0x0F00) >> 8)
#define STK_DS(x)                (x & 0x0003)
#define STK_RS(x)                ((x >> 2) & 0x0003)
#define STK_T2N(x)               (x & 0x80)
#define STK_T2R(x)               (x & 0x40)
#define STK_N2T(x)               (x & 0x20)
#define STK_R2P(x)               (x & 0x10)

#define ANY_NUM(x)               (x > 0x0a)
#define ANY_DATE(x)              (x == VT_DATE || x == VT_TOD || x == VT_DT)
#define ANY_BIT(x)               (x == VT_BOOL || x == VT_UINT || x == VT_UDINT || x == VT_ULINT)
#define ANY_REAL(x)              (x == VT_REAL || x == VT_LREAL)
#define ANY_INT(x)               (x == VT_UINT || x == VT_UDINT || x == VT_ULINT || x == VT_SINT || x == VT_INT || x == VT_DINT || x == VT_LINT)
#define ANY_STRING(x)            (x == VT_STRING || x == VT_WSTRING)
#define ANY_ELEMENTARY(x)        (ANY_BIT(x) || ANY_NUM(x) || ANY_DATE(x) || ANY_STRING(x) || x == VT_TIME)

#define GET_BIT(v, b)            ((v >> b) & 1)
#define SET_BIT(v, b)            (v | (1 << b))
#define CLR_BIT(v, b)            (v & ~(1 << b))

#define VM_NEXT_PRG(vm)          (vm->program[++vm->pc])
#define VM_RETR_PRG(vm,x)        (vm->program[x])

#define VM_T_R(vm,stk)           (vm->_##stk##s[VM_STK_PNT(vm,stk)])
#define VM_STK_PNT(vm,stk)       vm->_##stk##p
#define VM_POP(vm,stk)           (vm->_##stk##s[VM_STK_PNT(vm,stk)--])
#define VM_PUSH(vm,stk, x, inc)  vm->_##stk##s[VM_STK_PNT(vm,stk)] = x;VM_STK_PNT(vm,stk) += inc;
#define VM_DROP(vm,stk)          (--vm->_##stk##p)

#define VM_PC(vm)                (vm->pc)
#define VM_T(vm)                 (VM_T_R(vm,d))
#define VM_N(vm)                 (vm->_ds[vm->_dp - 1])
#define VM_R(vm)                 (VM_T_R(vm,r))
#define VM_A(vm)                 (vm->A)

#define VM_STK_X_VALUE(vm,stk,x) (vm->_##stk[x] & 0xC000)

#define VM_T_TYPE(vm)            (VM_T(vm) >> 14)
#define VM_N_TYPE(vm)            (vm->_ds[vm->_dp - 1] >> 14)
#define VM_R_TYPE(vm)            (vm->_rs[vm->_rp] >> 14)
#define VM_STK_TYPE(vm,stk, p)   (vm->_##stk##s[VM_STK_PNT(vm,stk) - p] >> 14)

#define VM_T_VALUE(vm)           (VM_T(vm) & 0xC000)
#define VM_N_VALUE(vm)           (vm->_ds[vm->_dp - 1] & 0xC000)
#define VM_STK_VALUE(vm,stk, p)  (vm->_##stk[VM_STK_PNT(vm,stk) - p] & 0xC000)

#define VM_REG(vm,x)             (vm->reg[x])

//////////////////////////////////////////

#define OP_BRANCH(type, arg)                ((type << 11) | arg)
#define OP_LITERAL(cont, value)             (0x8000 | (cont << 14) | value)
#define OP_FUN (type, fun, arg)             (0x4000 | (type << 12) |(fun << 6) | arg)
#define OP_OBJECT (type, op, arg)           (0xC000 | (type << 8) | (op << 6) | arg)
#define OP_STK(op, tn, tr, nt, rp, rs, ds)  (0x7000 | (op  << 8) |(tn << 7) | (tr << 6) | (nt << 5) | (rp << 4) | (rs << 2)| ds)

//////////////////////////////////////////
enum op_type {
	BRCCLL = 0x00,
	FUNSTK = 0x01,
	LITERL = 0x02,
	OBJECT = 0x03,
};

enum abs_branch_type {
	JMP_ABS = 0x00,
	JMP_IND = 0x01,
	JMZ_ABS = 0x02,
	JMZ_IND = 0x03,
	JNZ_ABS = 0x04,
	JNZ_IND = 0x05,
	CLL_ABS = 0x06,
	CLL_IND = 0x07
};

enum fun_type {
    FUN_0 = 0x0,
    FUN_1 = 0x1,
    FUN_2 = 0x2,
    STACK = 0x3
};

enum obj_operation {
    OBJ_CREATE = 0x00,
    OBJ_DELETE = 0x01,
    OBJ_TO_T   = 0x02,
    OBJ_FROM_T = 0x03,
    OBJ_TO_A   = 0x04,
    OBJ_FROM_A = 0x05
};

enum stk_opts {
    STK_F_T2N = 0x80,  // move T to N
    STK_F_T2R = 0x40,  // move T to R
    STK_F_N2T = 0x20,  // move N to T
    STK_F_R2P = 0x10   // move R to PC
};

enum stk_type {
    LIT_END = 0x00,
    LIT_CNT = 0x01,
    OBJ_END = 0x02,
    OBJ_CNT = 0x03
};

enum stk_prfx {
    PFX_LIT_END = 0x0000,
    PFX_LIT_CNT = 0x4000,
    PFX_OBJ_END = 0x8000,
    PFX_OBJ_CNT = 0xc000
};

enum num_type {
    OBJ = 0x0,
    LIT = 0x1
};

enum stk {
    RSTK = 0x0,
    DSTK = 0x1
};

// status
enum vm_status {
    ST_IRQ  = 0x01, // interrupt
    ST_IMK  = 0x02, // interrupt mask
 // ST_XXXX = 0x04, // not defined
 // ST_XXXX = 0x08, // not defined
 // ST_XXXX = 0x10, // not defined
 // ST_XXXX = 0x20, // not defined
 // ST_XXXX = 0x40, // not defined
 // ST_XXXX = 0x80, // not defined
};


// return condition
enum vm_rc {
    RC_OK             = 0x00, // ok
    RC_DS_UNDER_FLOW  = 0x01, // data stack underflow
    RC_DS_OVER_FLOW   = 0x02, // data stack overflow
    RC_RS_OVER_FLOW   = 0x03, // return stack overflow
    RC_RS_UNDER_FLOW  = 0x04, // return stack underflow
    RC_PC_UND_OVR     = 0x05, // program counter under/overflow
    RC_OP_UNKNOWN     = 0x06, // operator unknown
    RC_MEM_OVERFLOW   = 0x07, // out of memory access
    RC_IRQ            = 0x08, // irq execute
    RC_REG_UNKNOWN    = 0x09, // unknown register
    RC_OBJECT_ERROR   = 0x0a, // object not exist, not allowed type or not more heap space
    RC_OBJECT_CONVERT = 0x0b, // object can't be converted or truncated
    /////////////////////////
    RC_ERROR          = 0xfe, // generic error
    RC_BYE            = 0xff  // exit
};

//////////////////////////////////////////
// vm functions
 uint8_t evm_init(evm_t **evm, uint32_t dsize, uint32_t rsize, uint32_t regsize, uint32_t progsize);
 uint8_t evm_deinit(evm_t **evm);
 uint8_t evm_step(evm_t *evm, uint16_t word);
 uint8_t evm_push(evm_t *evm, uint64_t val, bool lit, bool stk, int8_t inc);
uint64_t evm_pop(evm_t *evm, bool stk, uint8_t *type, uint8_t *err);
 uint8_t evm_stack_value_size(evm_t *vm, bool stk);
 uint8_t evm_check_zero(evm_t *vm, bool stack, uint8_t *err);
    void evm_print_stack(evm_t *evm, bool stk, uint16_t qty);

#endif /* VM_H_ */
