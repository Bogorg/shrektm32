/**
 ******************************************************************************
 * @file        : rotary.hpp
 * @brief       : Rotary encoder library
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
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

#ifndef LIB_ROTARY_ROTARY_HPP_
#define LIB_ROTARY_ROTARY_HPP_

#include <stdint.h>

#include "arduino_shield.hpp"
#include "button.hpp"
#include "poller.hpp"
#include "pwm.hpp"
#include "shift_reg.hpp"

class Rotary : public Button, Poller, ShiftReg {
   public:
    explicit Rotary(ArduinoShield::ClickId id = ArduinoShield::kClick2);
    ~Rotary();
    virtual void OnRotate(int direction) {}
    void Poll() override;

    void LedPattern(uint16_t pattern);
    void LedFill(int from, int len);
    void LedPos(int pos, int mirror = 1);

   private:
    GPIO_TypeDef* switchPort_;
    uint32_t switchPin_;
    GPIO_TypeDef* encAPort_;
    uint32_t encAPin_;
    GPIO_TypeDef* encBPort_;
    uint32_t encBPin_;
    int previousState_;
};

#endif /* LIB_ROTARY_ROTARY_HPP_ */
