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
#include <stdio.h>

#include "evm.h"

#define RSTK 0
#define DSTK 1
#define LITL 1
#define OBJC 0

#define TEST(str, idx, a,b)  if(a == b) { \
                                 printf ("   \e[32m[OK]\e[0m "); \
                             } else { \
                                 printf ("\e[31m[ERROR]\e[0m "); \
                             } \
                             printf ("\e[93m[TEST %02d: " #str "]\e[0m (expect: 0x%"PRIx64" / result: 0x%"PRIx64")\n", idx, b, a);
#define LABEL_TEST(str)      printf("\e[94m[-- " #str " --]\e[0m\n");

uint8_t evm_test_number(void) {
    evm_t *evm;
    uint64_t result;
    uint64_t number;
    uint64_t res = 0;
    uint8_t tst = 1, type;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////
    LABEL_TEST(TEST NUMBER [LITERAL/OBJECT]);

    number = 0xAA;
    res = evm_push(evm, number, LITL, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([literal] size DSTK, tst++, result, res);
    result = evm_pop(evm, DSTK, &type);
    TEST([literal] on DSTK, tst++, result, number);

    number = 0xAAAA;
    res = evm_push(evm, number, LITL, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([literal] size DSTK, tst++, result, res);
    result = evm_pop(evm, DSTK, &type);
    TEST([literal] on DSTK, tst++, result, number);

    number = 0xAAAAAA;
    res = evm_push(evm, number, LITL, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([literal] size DSTK, tst++, result, res);
    result = evm_pop(evm, DSTK, &type);
    TEST([literal] on DSTK, tst++, result, number);

    number = 0xAAAAAAAA;
    res = evm_push(evm, number, LITL, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([literal] size DSTK, tst++, result, res)
    result = evm_pop(evm, DSTK, &type);
    TEST([literal] on DSTK, tst++, result, number);

    number = 0xAAAAAAAAAAAAAAAA;
    res = evm_push(evm, number, LITL, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([literal] size DSTK, tst++, result, res)
    result = evm_pop(evm, DSTK, &type);
    TEST([literal] on DSTK, tst++, result, number);

    number = 0xAAAAAAAAAAAAAAAA;
    res = evm_push(evm, number, OBJC, DSTK, 1);
    result = evm_stack_value_size(evm, DSTK);
    TEST([object] size DSTK, tst++, result, res);
    result = evm_pop(evm, DSTK, &type);
    TEST([object] on DSTK, tst++, result, number);

    number = 0xAAAAAAAAAAAAAAAA;
    res = evm_push(evm, number, OBJC, RSTK, 1);
    result = evm_stack_value_size(evm, RSTK);
    TEST([object] size DSTK, tst++, result, res);
    result = evm_pop(evm, RSTK, &type);
    TEST([object] on RSTK, tst++, result, number);

    //////////////////////
    evm_deinit(&evm);

    LABEL_TEST(END NUMBER [LITERAL/OBJECT]);

    return 0;
}

uint8_t evm_test_branch(void) {
    evm_t *evm;
    uint64_t val;
    uint16_t op;
    uint8_t ret, type, tst = 1;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////

    LABEL_TEST(TEST OP BRANCH);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMP_ABS, 0x07FF);
    ret = evm_step(evm, op);
    TEST([branch] JMP_ABS rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMP_ABS, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x07FF);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMP_IND, 0x0700);
    VM_A(evm) = 0x5;
    ret = evm_step(evm, op);
    TEST([branch] JMP_IND fw rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMP_IND fw, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x0705);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMP_IND, 0x0705);
    VM_A(evm) = -0x5;
    ret = evm_step(evm, op);
    TEST([branch] JMP_IND bk rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMP_IND bk, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x0700);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMZ_ABS, 0x07FF);
    evm_push(evm, 0x0, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JMZ_ABS lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMZ_ABS lit, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x07FF);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMZ_ABS, 0x07FF);
    evm_push(evm, 0xAAAAAAAAAAAAAAAA, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JMZ_ABS lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMZ_ABS lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x1);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMZ_IND, 0x0700);
    VM_A(evm) = 0x5;
    evm_push(evm, 0x0, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JMZ_IND lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMZ_IND lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x705);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JMZ_IND, 0x0700);
    VM_A(evm) = 0x05;
    evm_push(evm, 0xAAAAAAAAAAAAAAAA, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JMZ_IND lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JMZ_IND lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x1);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JNZ_ABS, 0x0700);
    VM_A(evm) = 0x5;
    evm_push(evm, 0x0, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JNZ_ABS lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JNZ_ABS lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x1);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JNZ_ABS, 0x0700);
    VM_A(evm) = 0x05;
    evm_push(evm, 0xAAAAAAAAAAAAAAAA, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JNZ_ABS lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JNZ_ABS lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x700);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JNZ_IND, 0x0700);
    VM_A(evm) = 0x5;
    evm_push(evm, 0x0, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JNZ_IND lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JNZ_IND lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x1);

    VM_PC(evm) = 0;
    op = OP_BRANCH(JNZ_IND, 0x0700);
    VM_A(evm) = 0x05;
    evm_push(evm, 0xAAAAAAAAAAAAAAAA, LITL, DSTK, 0);
    ret = evm_step(evm, op);
    TEST([branch] JNZ_IND lit rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] JNZ_IND lit, tst++, (uint64_t )VM_PC(evm), (uint64_t )0x705);

    VM_PC(evm) = 0x100;
    op = OP_BRANCH(CLL_ABS, 0x07FF);
    ret = evm_step(evm, op);
    val = evm_pop(evm, RSTK, &type);
    TEST([branch] CLL_ABS rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] CLL_ABS, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x07FF);
    TEST([branch] CLL_ABS rstk, tst++, (uint64_t )val, (uint64_t )0x102);
    TEST([branch] CLL_ABS rstk type, tst++, (uint64_t )type, (uint64_t )LIT);

    VM_PC(evm) = 0x100;
    op = OP_BRANCH(CLL_IND, 0x0700);
    VM_A(evm) = 0x5;
    ret = evm_step(evm, op);
    val = evm_pop(evm, RSTK, &type);
    TEST([branch] CLL_IND rc, tst++, (uint64_t )ret, (uint64_t )0);
    TEST([branch] CLL_IND, tst++, (uint64_t)VM_PC(evm), (uint64_t )0x0705);
    TEST([branch] CLL_IND rstk, tst++, (uint64_t )val, (uint64_t )0x102);
    TEST([branch] CLL_IND rstk type, tst++, (uint64_t )type, (uint64_t )LIT);

    LABEL_TEST(END OP BRANCH);

    //////////////////////
    evm_deinit(&evm);
    return 0;
}

uint8_t evm_test_stack(void) {
    evm_t *evm;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////

    LABEL_TEST(TEST OP STACK);



    LABEL_TEST(END OP STACK);

    //////////////////////
    evm_deinit(&evm);
    return 0;
}

uint8_t evm_test_object(void) {
    evm_t *evm;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////

    LABEL_TEST(TEST OP OBJECT);



    LABEL_TEST(END OP OBJECT);

    //////////////////////
    evm_deinit(&evm);
    return 0;
}

uint8_t evm_test_data_types(void) {
    evm_t *evm;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////

    LABEL_TEST(TEST DATA TYPES);



    LABEL_TEST(END DATA TYPES);

    //////////////////////
    evm_deinit(&evm);
    return 0;
}

uint8_t evm_test_function(void) {
    evm_t *evm;

    evm_init(&evm, 100, 100, 100, 100);
    //////////////////////

    LABEL_TEST(TEST OP FUNCTION);



    LABEL_TEST(END OP FUNCTION);

    //////////////////////
    evm_deinit(&evm);
    return 0;
}

int main(void) {
    evm_test_number();
    evm_test_branch();
    evm_test_stack();
    evm_test_object();
    evm_test_data_types();
    evm_test_function();

    return 0;
}