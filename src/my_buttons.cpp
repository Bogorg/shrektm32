/**
 ******************************************************************************
 * @file        : my_buttons.cpp
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

#include "my_buttons.hpp"

#include "button.hpp"
#include "seg7.hpp"

CountButton::CountButton(int dir, Counter* c, Seg7* display, Rotary* rotary)
    : Button(1000, 50),
      dir_{dir},
      counter_{c},
      display_{display},
      rotary_{rotary} {}

void CountButton::OnPress() {
    if (dir_ == 1) {
        counter_->Increment();
    } else {
        counter_->Decrement();
    }
    display_->Print(counter_->GetCount());
    rotary_->LedPattern(counter_->GetCount());
}

// cppcheck-suppress unusedFunction
void CountButton::OnLongPress(int repetition) { OnPress(); }

ResetButton::ResetButton(Counter* c, Seg7* display, Rotary* rotary)
    : Button(), counter_{c}, display_{display}, rotary_{rotary} {}
void ResetButton::OnLongPress(int repetition) {
    counter_->Reset();
    display_->Print(counter_->GetCount());
    rotary_->LedPattern(counter_->GetCount());
}

BrightnessButton::BrightnessButton(int dir, int* brightnessLevel, Seg7* display)
    : Button(),
      dir_{dir},
      brightnessLevel_{brightnessLevel},
      display_{display} {}
void BrightnessButton::OnPress() {
    if (dir_ == 1) {
        if (*brightnessLevel_ < kBrightnessLevels - 1) {
            (*brightnessLevel_)++;
        }
    } else {
        if (*brightnessLevel_ > 0) {
            (*brightnessLevel_)--;
        }
    }
    display_->SetBrightness(kBrightnessMap[*brightnessLevel_]);
}
void BrightnessButton::OnLongPress(int repetition) { OnPress(); }
