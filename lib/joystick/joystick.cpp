/**
 ******************************************************************************
 * @file        : joystick.cpp
 * @brief       : Joystick Handler
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Joystick Handler
 ******************************************************************************
 */

#include "joystick.hpp"

#include "stm32412g_discovery.h"

static constexpr JOYState_TypeDef kJoyButtons[] = {
    [Joystick::kButtonUp]     = JOY_DOWN,
    [Joystick::kButtonDown]   = JOY_UP,
    [Joystick::kButtonLeft]   = JOY_RIGHT,
    [Joystick::kButtonRight]  = JOY_LEFT,
    [Joystick::kButtonSelect] = JOY_SEL,
};

Joystick* Joystick::GetInstance() {
    static Joystick* instance = new Joystick;
    return instance;
}
Joystick::Joystick() {
    BSP_JOY_Init(JOY_MODE_GPIO);
    for (int i = 0; i < kNumButtons; i++) {
        buttons_[i] = nullptr;
    }
}

void Joystick::AddButton(enum ButtonId buttonId, Button* button) {
    buttons_[buttonId] = button;
}

void Joystick::DelButton(enum ButtonId buttonId) {
    buttons_[buttonId] = nullptr;
}

void Joystick::Poll() {
    uint32_t now           = HAL_GetTick();
    JOYState_TypeDef value = BSP_JOY_GetState();
    for (int i = 0; i < kNumButtons; i++) {
        if (buttons_[i] != nullptr) {
            buttons_[i]->Update(
                now, value == kJoyButtons[i] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        }
    }
}
