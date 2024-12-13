/**
 ******************************************************************************
 * @file        : seg7.hpp
 * @brief       : Seven Segment library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Seven Segment library
 ******************************************************************************
 */

#include "seg7.hpp"

#include <cmath>

#include "pwm.hpp"

const uint8_t kDecimalPoint = 0b00000001;
const uint8_t kMinusSign    = 0b10000000;
const uint8_t kDigits[]     = {
        0b01111110,  // 0
        0b00001010,  // 1
        0b10110110,  // 2
        0b10011110,  // 3
        0b11001010,  // 4
        0b11011100,  // 5
        0b11111100,  // 6
        0b00001110,  // 7
        0b11111110,  // 8
        0b11011110,  // 9
        0b11101110,  // A
        0b11111000,  // b
        0b01110100,  // C
        0b10111010,  // d
        0b11110100,  // E
        0b11100100,  // F
};

SPI_HandleTypeDef Seg7::hspi_{};

Seg7::Seg7(ArduinoShield::ClickId id)
    : ShiftReg(id), pwm_{id == ArduinoShield::kClick1 ? PwmChannel::kPF3
                                        : PwmChannel::kPF10} {
    pwm_.Start();
}

Seg7::~Seg7() {
    pwm_.SetDutyCycle(0);
    pwm_.Stop();
}

void Seg7::PrintPattern(uint16_t pattern) {
    uint8_t buffer[2];
    buffer[0] = pattern & 0xFF;
    buffer[1] = pattern >> 8;
    SendData(buffer, 2);
}

void Seg7::Print(int i) {
    uint16_t msd = 0;
    uint16_t lsd = 0;
    if (i < -9 || i > 99) {
        msd = kMinusSign;
        lsd = kMinusSign;
    } else if (i < 0) {
        msd = kMinusSign;
        lsd |= kDigits[-i % 10];
    } else {
        msd |= kDigits[i / 10 % 10];
        lsd |= kDigits[i % 10];
    }
    PrintPattern(msd << 8 | lsd);
}

void Seg7::Print(float f) {
    uint16_t msd = 0;
    uint16_t lsd = 0;
    int i0       = (int)roundf(f);
    int i1       = (int)roundf(f * 10);
    if (i0 < -9 || i0 > 99) {
        msd = kMinusSign;
        lsd = kMinusSign;
    } else if (i1 < -9) {
        msd = kMinusSign;
        lsd = kDigits[-i0 % 10] | kDecimalPoint;
    } else if (i1 < 0) {
        msd = kMinusSign | kDecimalPoint;
        lsd = kDigits[-i1 % 10];
    } else if (i1 < 100) {
        msd = kDigits[i1 / 10 % 10] | kDecimalPoint;
        lsd = kDigits[i1 % 10];
    } else {
        msd = kDigits[i0 / 10 % 10];
        lsd = kDigits[i0 % 10] | kDecimalPoint;
    }
    PrintPattern(msd << 8 | lsd);
}

void Seg7::PrintHex(int i) {
    uint16_t msd = 0;
    uint16_t lsd = 0;
    if (i < -0xF || i > 0xFF) {
        msd = kMinusSign;
        lsd = kMinusSign;
    } else if (i < 0) {
        msd = kMinusSign;
        lsd |= kDigits[-i % 16];
    } else {
        msd |= kDigits[i / 16 % 16];
        lsd |= kDigits[i % 16];
    }
    PrintPattern(msd << 8 | lsd);
}

void Seg7::SetBrightness(float level) { pwm_.SetDutyCycle(level); }
