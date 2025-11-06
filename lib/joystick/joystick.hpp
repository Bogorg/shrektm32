/**
 ******************************************************************************
 * @file        : joystick.hpp
 * @brief       : Joystick Handler
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
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

#ifndef LIB_JOYSTICK_JOYSTICK_HPP_
#define LIB_JOYSTICK_JOYSTICK_HPP_

#include "button.hpp"
#include "poller.hpp"

constexpr int kNumButtons = 5;

class Joystick : public Poller {
   public:
    enum ButtonId {
        kButtonUp     = 0,
        kButtonDown   = 1,
        kButtonLeft   = 2,
        kButtonRight  = 3,
        kButtonSelect = 4,
    };
    static Joystick* GetInstance();

    void AddButton(enum ButtonId buttonId, Button* button);
    void DelButton(enum ButtonId buttonId);
    void Poll() override;

   private:
    Button* buttons_[kNumButtons];
    Joystick();
    Joystick(Joystick const&);
    void operator=(Joystick const&);
};

#endif /* LIB_JOYSTICK_JOYSTICK_HPP_ */
