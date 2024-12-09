/**
 ******************************************************************************
 * @file        : rotary.cpp
 * @brief       : Rotary encoder library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Rotary encoder library
 ******************************************************************************
 */

#include "rotary.hpp"

static constexpr int kNumberOfLeds = 16;

Rotary::Rotary(ArduinoShield::ClickId id) : Button(), Poller(), ShiftReg(id) {
    ArduinoShield* shield = ArduinoShield::GetInstance();
    switchPort_           = shield->GetGpioPort(id, ArduinoShield::kINT);
    switchPin_            = shield->GetGpioPin(id, ArduinoShield::kINT);
    encAPort_             = shield->GetGpioPort(id, ArduinoShield::kPWM);
    encAPin_              = shield->GetGpioPin(id, ArduinoShield::kPWM);
    encBPort_             = shield->GetGpioPort(id, ArduinoShield::kAN);
    encBPin_              = shield->GetGpioPin(id, ArduinoShield::kAN);
    previousState_        = -1;

    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode  = GPIO_MODE_INPUT;
    gpio_init_structure.Pull  = GPIO_PULLDOWN;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio_init_structure.Pin = switchPin_;
    HAL_GPIO_Init(switchPort_, &gpio_init_structure);
    gpio_init_structure.Pin = encAPin_;
    HAL_GPIO_Init(encAPort_, &gpio_init_structure);
    gpio_init_structure.Pin = encBPin_;
    HAL_GPIO_Init(encBPort_, &gpio_init_structure);
}

Rotary::~Rotary() {
    HAL_GPIO_DeInit(switchPort_, switchPin_);
    HAL_GPIO_DeInit(encAPort_, encAPin_);
    HAL_GPIO_DeInit(encBPort_, encBPin_);
}

void Rotary::Poll() {
    // TODO(student): Implement the rotary poller (don't forget the push button)
}

// Shows the pattern to the LEDs
void Rotary::LedPattern(uint16_t pattern) {
    uint8_t buffer[2];
    buffer[0] = pattern & 0xFF;
    buffer[1] = pattern >> 8;
    SendData(buffer, 2);
}

// Shows a "filled" pattern to the LEDs
void Rotary::LedFill(int from, int len) {
    // TODO(student): Implement LedFill
    // The pattern is must contain "len" 1s starting at position "from"
    //
    //                                       from -----.
    //                                                 v
    // for example LedFill(3, 4) will show 0000000001111000
    // note that the LEDs are in a circle, so
    // LedFill(14, 5) is shown as "1100000000000111"
}

// Shows a "position" pattern to the LEDs
// mirror is typically 1, 2 or 4
void Rotary::LedPos(int pos, int mirror) {
    uint16_t pattern = 0;
    if (mirror > 4) {
        mirror = 4;
    }
    int nLeds = 1 << (mirror - 1);
    int step  = kNumberOfLeds / nLeds;
    for (int i = 0; i < nLeds; i++) {
        pattern |= (1 << (pos + i * step) % kNumberOfLeds);
    }
    pattern |= (1 << pos);
    LedPattern(pattern);
}
