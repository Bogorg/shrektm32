/**
 ******************************************************************************
 * @file        : my_buttons.hpp
 * @brief       : My Buttons
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 25. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * My Buttons
 ******************************************************************************
 */

#ifndef SRC_MY_BUTTONS_HPP_
#define SRC_MY_BUTTONS_HPP_

#include "button.hpp"
#include "my_counter.hpp"
#include "my_rotary.hpp"
#include "rotary.hpp"
#include "seg7.hpp"

constexpr float kBrightnessMap[] = {
    0.005,
    0.007,
    0.01,
    0.025,
    0.05,
    0.1,
    0.5,
    1.0,
};

constexpr int kBrightnessLevels    = sizeof(kBrightnessMap) / sizeof(float);
constexpr int kBrightnessInitLevel = 4;

class CountButton : public Button {
   public:
    CountButton(int dir, Counter* c, Seg7* display, Rotary* rotary);
    void OnPress() override;
    void OnLongPress(int repetition) override;

   private:
    int dir_;
    Counter* counter_;
    Seg7* display_;
    Rotary* rotary_;
};

class ResetButton : public Button {
   public:
    ResetButton(Counter* c, Seg7* display, Rotary* rotary);
    void OnLongPress(int repetition) override;

   private:
    Counter* counter_;
    Seg7* display_;
    Rotary* rotary_;
};

class BrightnessButton : public Button {
   public:
    BrightnessButton(int dir, int* brightnessLevel, Seg7* display);
    void OnPress() override;
    void OnLongPress(int repetition) override;

   private:
    int dir_;
    int* brightnessLevel_;
    Seg7* display_;
};

#endif /* SRC_MY_BUTTONS_HPP_ */
