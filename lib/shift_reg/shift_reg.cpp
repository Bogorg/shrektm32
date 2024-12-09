/**
 ******************************************************************************
 * @file        : shift_reg.cpp
 * @brief       : Shift register library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Shift register library
 ******************************************************************************
 */

#include "shift_reg.hpp"

#include "arduino_shield.hpp"

// TODO(student): define ShiftReg::hspi_;

ShiftReg::ShiftReg(ArduinoShield::ClickId id) : id_{id} {
    // TODO(student): Implement Constructor (see Seg7::Seg7() in
    // lib/seg7/seg7.cpp)
}

ShiftReg::~ShiftReg() {
    // TODO(student): Implement Destructor (see Seg7::~Seg7() in
    // lib/seg7/seg7.cpp)
}

void ShiftReg::Reset() {
    // TODO(student): Implement Reset
}

void ShiftReg::Latch() {
    // TODO(student): Implement Latch
}

void ShiftReg::SendData(uint8_t* buffer, int len) {
    // TODO(student): Implement SendData
}

void ShiftReg::InitSpi() {
    // TODO(student): Implement InitSpi (see Seg7::InitSpi() in
    // lib/seg7/seg7.cpp)
}
