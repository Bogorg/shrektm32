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
    : pwm_{id == ArduinoShield::kClick1 ? PwmChannel::kPF3
                                        : PwmChannel::kPF10} {
    ArduinoShield* shield = ArduinoShield::GetInstance();
    resetPin_             = shield->GetGpioPin(id, ArduinoShield::kRST);
    resetPort_            = shield->GetGpioPort(id, ArduinoShield::kRST);
    latchPin_             = shield->GetGpioPin(id, ArduinoShield::kCS);
    latchPort_            = shield->GetGpioPort(id, ArduinoShield::kCS);

    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull  = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio_init_structure.Pin = resetPin_;
    HAL_GPIO_Init(resetPort_, &gpio_init_structure);
    gpio_init_structure.Pin = latchPin_;
    HAL_GPIO_Init(latchPort_, &gpio_init_structure);

    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_SET);
    InitSpi();
    pwm_.Start();
}

Seg7::~Seg7() {
    pwm_.SetDutyCycle(0);
    pwm_.Stop();
    HAL_GPIO_DeInit(resetPort_, resetPin_);
    HAL_GPIO_DeInit(latchPort_, latchPin_);
}

void Seg7::Reset() {
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_SET);
}

void Seg7::Latch() {
    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_SET);
    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_RESET);
}

void Seg7::SendData(uint8_t* buffer, int len) {
    HAL_SPI_Transmit(&hspi_, &buffer[0], 2, 1000);
    Latch();
}

void Seg7::InitSpi() {
    static bool initialized = false;
    if (initialized) {
        return;
    }
    ArduinoShield* shield        = ArduinoShield::GetInstance();
    hspi_.Instance               = shield->GetSpi();
    hspi_.Init.Mode              = SPI_MODE_MASTER;
    hspi_.Init.Direction         = SPI_DIRECTION_2LINES;
    hspi_.Init.DataSize          = SPI_DATASIZE_8BIT;
    hspi_.Init.CLKPolarity       = SPI_POLARITY_LOW;
    hspi_.Init.CLKPhase          = SPI_PHASE_1EDGE;
    hspi_.Init.NSS               = SPI_NSS_SOFT;
    hspi_.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;  // 3.125 MHz
    hspi_.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    shield->MspInitSpi();
    HAL_SPI_Init(&hspi_);
    initialized = true;
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
