/**
 ******************************************************************************
 * @file        : button.hpp
 * @brief       : Button Handler
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
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

#ifndef LIB_BUTTON_BUTTON_HPP_
#define LIB_BUTTON_BUTTON_HPP_

#include <stdint.h>

#include "poller.hpp"

class Button {
   private:
    enum class ButtonState { kUndefined, kPressed, kReleased, kLongPressed };
    ButtonState state_;
    uint32_t long_press_;
    uint32_t repeated_press_;
    uint32_t last_event_;
    uint32_t last_value_;
    int repetition_;

   public:
    explicit Button(uint32_t long_press = 1000, uint32_t repeated_press = 200);
    void Update(uint32_t tick, uint32_t value);
    virtual void OnPress() {}
    virtual void OnLongPress(int repetition) { (void)repetition; }
    virtual void OnRelease() {}
};

class WakeUpButton : public Poller, Button {
   public:
    WakeUpButton();
    void Poll() override;
};

#endif /* LIB_BUTTON_BUTTON_HPP_ */
