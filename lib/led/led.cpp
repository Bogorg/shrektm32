/**
 ******************************************************************************
 * @file        : led.cpp
 * @brief       : Class for LEDs
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 27. July 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Class for LEDs
 ******************************************************************************
 */

#include "led.hpp"

#include "f412disco_ado.h"

static const uint32_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN};

Led::Led(Led_TypeDef led) : led_{led} { BSP_LED_Init(led); }

Led::~Led() { BSP_LED_DeInit(led_); }

int Led::Read() {
    return HAL_GPIO_ReadPin(LEDx_GPIO_PORT, GPIO_PIN[led_]) == GPIO_PIN_RESET;
}

void Led::Write(int value) {
    if (value)
        this->On();
    else
        this->Off();
}

void Led::Toggle() { BSP_LED_Toggle(led_); }

void Led::On() { BSP_LED_On(led_); }

void Led::Off() { BSP_LED_Off(led_); }

Led& Led::operator=(int value) {
    this->Write(value);
    return *this;
}

Led& Led::operator=(const Led& rhs) {
    this->Write(((Led&)rhs).Read());
    return *this;
}

Led::operator int() { return this->Read(); }
