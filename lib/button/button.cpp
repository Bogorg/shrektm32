/**
 ******************************************************************************
 * @file        : button.cpp
 * @brief       : Button Handler
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 10. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Button Handler
 ******************************************************************************
 */

#include "button.hpp"

#include "f412disco_ado.h"
#include "poller.hpp"

Button::Button(uint32_t long_press, uint32_t repeated_press)
    : state_{ButtonState::kUndefined},
      long_press_{long_press},
      repeated_press_{repeated_press} {}

/**
 * Updates the button state and calls the appropriate callback.
 *
 * @param tick The current tick value.
 * @param value The current value of the button.
 *
 * @returns None
 */
void Button::Update(uint32_t tick, uint32_t value) {
    if (value == GPIO_PIN_SET && last_value_ == GPIO_PIN_RESET) {
        state_ = ButtonState::kPressed;
        OnPress();
        last_event_ = tick;
    } else if (value == GPIO_PIN_RESET && last_value_ == GPIO_PIN_SET) {
        state_ = ButtonState::kReleased;
        OnRelease();
    } else if (state_ == ButtonState::kPressed) {
        uint32_t press_time = tick - last_event_;
        if (press_time >= long_press_) {
            state_      = ButtonState::kLongPressed;
            repetition_ = 0;
            last_event_ = tick;
            OnLongPress(repetition_);
        }

    } else if (state_ == ButtonState::kLongPressed) {
        uint32_t press_time = tick - last_event_;
        if (press_time >= repeated_press_) {
            repetition_++;
            last_event_ = tick;
            OnLongPress(repetition_);
        }
    }
    last_value_ = value;
}

WakeUpButton::WakeUpButton() : Poller(), Button() {
    BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
    Poll();
}

void WakeUpButton::Poll() {
    Update(HAL_GetTick(), BSP_PB_GetState(BUTTON_WAKEUP));
}
