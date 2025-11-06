/**
 ******************************************************************************
 * @file        : my_rotary.hpp
 * @brief       : My Rotary
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 25. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * My Rotary
 ******************************************************************************
 */

#ifndef SRC_MY_ROTARY_HPP_
#define SRC_MY_ROTARY_HPP_

#include "arduino_shield.hpp"
#include "my_counter.hpp"
#include "rotary.hpp"
#include "seg7.hpp"

class MyRotary : public Rotary {
   public:
    MyRotary(ArduinoShield::ClickId id, Counter* c, Seg7* display);
    void OnLongPress(int repetition) override;
    void OnPress() override;
    void OnRotate(int dir) override;
    void ShowPattern();

   private:
    Counter* counter_;
    Seg7* display_;
    int patternMode_;
    int savedPatternMode_;
};

#endif /* SRC_MY_ROTARY_HPP_ */
