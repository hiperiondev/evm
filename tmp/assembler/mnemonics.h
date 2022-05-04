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

#ifndef MNEMONICS_H_
#define MNEMONICS_H_

const char *MNCS_STACK[] = {
    EP(STK_NOP),
    EP(STK_SCN),
    EP(STK_TRS),
    EP(STK_DDS),
    EP(STK_DRS),
    EP(STK_SSP),
    EP(STK_SRP),
    EP(STK_NNN),
    EP(STK_RTT),
    EP(STK_TTR),
    EP(STK_SWP),
    EP(STK_RTR),
    EP(STK_ICT),
    EP(STK_DCT),
    EP(STK_AIC),
    EP(STK_ATT)
};

const char *MNCS_FT0[] = {
    EP(FUNC_T0_00),
    EP(FUNC_T0_01),
    EP(FUNC_T0_02),
    EP(FUNC_T0_03),
    EP(FUNC_T0_04),
    EP(FUNC_T0_05),
    EP(FUNC_T0_06),
    EP(FUNC_T0_07),
    EP(FUNC_T0_08),
    EP(FUNC_T0_09),
    EP(FUNC_T0_0a),
    EP(FUNC_T0_0b),
    EP(FUNC_T0_0c),
    EP(FUNC_T0_0d),
    EP(FUNC_T0_0e),
    EP(FUNC_T0_0f),
    EP(FUNC_T0_10),
    EP(FUNC_T0_11),
    EP(FUNC_T0_12),
    EP(FUNC_T0_13),
    EP(FUNC_T0_14),
    EP(FUNC_T0_15),
    EP(FUNC_T0_16),
    EP(FUNC_T0_17),
    EP(FUNC_T0_18),
    EP(FUNC_T0_19),
    EP(FUNC_T0_1a),
    EP(FUNC_T0_1b),
    EP(FUNC_T0_1c),
    EP(FUNC_T0_1d),
    EP(FUNC_T0_1e),
    EP(FUNC_T0_1f),
    EP(FUNC_T0_20),
    EP(FUNC_T0_21),
    EP(FUNC_T0_22),
    EP(FUNC_T0_23),
    EP(FUNC_T0_24),
    EP(FUNC_T0_25),
    EP(FUNC_T0_26),
    EP(FUNC_T0_27),
    EP(FUNC_T0_28),
    EP(FUNC_T0_29),
    EP(FUNC_T0_2a),
    EP(FUNC_T0_2b),
    EP(FUNC_T0_2c),
    EP(FUNC_T0_2d),
    EP(FUNC_T0_2e),
    EP(FUNC_T0_2f),
    EP(FUNC_T0_30),
    EP(FUNC_T0_31),
    EP(FUNC_T0_32),
    EP(FUNC_T0_33),
    EP(FUNC_T0_34),
    EP(FUNC_T0_35),
    EP(FUNC_T0_36),
    EP(FUNC_T0_37),
    EP(FUNC_T0_38),
    EP(FUNC_T0_39),
    EP(FUNC_T0_3a),
    EP(FUNC_T0_3b),
    EP(FUNC_T0_3c),
    EP(FUNC_T0_3d),
    EP(FUNC_T0_3e),
    EP(FUNC_T0_3f)
};

const char *MNCS_FT1[] = {
    EP(FUNC_T1_00),
    EP(FUNC_T1_01),
    EP(FUNC_T1_02),
    EP(FUNC_T1_03),
    EP(FUNC_T1_04),
    EP(FUNC_T1_05),
    EP(FUNC_T1_06),
    EP(FUNC_T1_07),
    EP(FUNC_T1_08),
    EP(FUNC_T1_09),
    EP(FUNC_T1_0a),
    EP(FUNC_T1_0b),
    EP(FUNC_T1_0c),
    EP(FUNC_T1_0d),
    EP(FUNC_T1_0e),
    EP(FUNC_T1_0f),
    EP(FUNC_T1_10),
    EP(FUNC_T1_11),
    EP(FUNC_T1_12),
    EP(FUNC_T1_13),
    EP(FUNC_T1_14),
    EP(FUNC_T1_15),
    EP(FUNC_T1_16),
    EP(FUNC_T1_17),
    EP(FUNC_T1_18),
    EP(FUNC_T1_19),
    EP(FUNC_T1_1a),
    EP(FUNC_T1_1b),
    EP(FUNC_T1_1c),
    EP(FUNC_T1_1d),
    EP(FUNC_T1_1e),
    EP(FUNC_T1_1f),
    EP(FUNC_T1_20),
    EP(FUNC_T1_21),
    EP(FUNC_T1_22),
    EP(FUNC_T1_23),
    EP(FUNC_T1_24),
    EP(FUNC_T1_25),
    EP(FUNC_T1_26),
    EP(FUNC_T1_27),
    EP(FUNC_T1_28),
    EP(FUNC_T1_29),
    EP(FUNC_T1_2a),
    EP(FUNC_T1_2b),
    EP(FUNC_T1_2c),
    EP(FUNC_T1_2d),
    EP(FUNC_T1_2e),
    EP(FUNC_T1_2f),
    EP(FUNC_T1_30),
    EP(FUNC_T1_31),
    EP(FUNC_T1_32),
    EP(FUNC_T1_33),
    EP(FUNC_T1_34),
    EP(FUNC_T1_35),
    EP(FUNC_T1_36),
    EP(FUNC_T1_37),
    EP(FUNC_T1_38),
    EP(FUNC_T1_39),
    EP(FUNC_T1_3a),
    EP(FUNC_T1_3b),
    EP(FUNC_T1_3c),
    EP(FUNC_T1_3d),
    EP(FUNC_T1_3e),
    EP(FUNC_T1_3f)
};

const char *MNCS_FT2[] = {
    EP(FUNC_T2_00),
    EP(FUNC_T2_01),
    EP(FUNC_T2_02),
    EP(FUNC_T2_03),
    EP(FUNC_T2_04),
    EP(FUNC_T2_05),
    EP(FUNC_T2_06),
    EP(FUNC_T2_07),
    EP(FUNC_T2_08),
    EP(FUNC_T2_09),
    EP(FUNC_T2_0a),
    EP(FUNC_T2_0b),
    EP(FUNC_T2_0c),
    EP(FUNC_T2_0d),
    EP(FUNC_T2_0e),
    EP(FUNC_T2_0f),
    EP(FUNC_T2_10),
    EP(FUNC_T2_11),
    EP(FUNC_T2_12),
    EP(FUNC_T2_13),
    EP(FUNC_T2_14),
    EP(FUNC_T2_15),
    EP(FUNC_T2_16),
    EP(FUNC_T2_17),
    EP(FUNC_T2_18),
    EP(FUNC_T2_19),
    EP(FUNC_T2_1a),
    EP(FUNC_T2_1b),
    EP(FUNC_T2_1c),
    EP(FUNC_T2_1d),
    EP(FUNC_T2_1e),
    EP(FUNC_T2_1f),
    EP(FUNC_T2_20),
    EP(FUNC_T2_21),
    EP(FUNC_T2_22),
    EP(FUNC_T2_23),
    EP(FUNC_T2_24),
    EP(FUNC_T2_25),
    EP(FUNC_T2_26),
    EP(FUNC_T2_27),
    EP(FUNC_T2_28),
    EP(FUNC_T2_29),
    EP(FUNC_T2_2a),
    EP(FUNC_T2_2b),
    EP(FUNC_T2_2c),
    EP(FUNC_T2_2d),
    EP(FUNC_T2_2e),
    EP(FUNC_T2_2f),
    EP(FUNC_T2_30),
    EP(FUNC_T2_31),
    EP(FUNC_T2_32),
    EP(FUNC_T2_33),
    EP(FUNC_T2_34),
    EP(FUNC_T2_35),
    EP(FUNC_T2_36),
    EP(FUNC_T2_37),
    EP(FUNC_T2_38),
    EP(FUNC_T2_39),
    EP(FUNC_T2_3a),
    EP(FUNC_T2_3b),
    EP(FUNC_T2_3c),
    EP(FUNC_T2_3d),
    EP(FUNC_T2_3e),
    EP(FUNC_T2_3f)
};

const char *VMFLAGS[] = {
    EP(STK_F_T2N),
    EP(STK_F_T2R),
    EP(STK_F_N2T),
    EP(STK_F_R2P)
};

const char *DELTA[] = {
    "d+1",
    "d-1",
    "d-2",
    "r+1",
    "r-1",
    "r-2"
};

const uint8_t DELTA_CODE[] = {
    0x1,
    0x2,
    0x3,
    0x4,
    0x8,
    0xC
};

const uint8_t VMFLAGS_POS[] = {
    STK_F_T2N,
    STK_F_T2R,
    STK_F_N2T,
    STK_F_R2P
};

const uint8_t VMFLAGS_CODE[] = {
    0x80,
    0x40,
    0x20,
    0x10
};

#endif

