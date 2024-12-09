/**
 ******************************************************************************
 * @file        : my_rotary.cpp
 * @brief       : My Rotary
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
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

#include "my_rotary.hpp"

#include "arduino_shield.hpp"
#include "button.hpp"
#include "rotary.hpp"
#include "seg7.hpp"

MyRotary::MyRotary(ArduinoShield::ClickId id, Counter* c, Seg7* display)
    : Rotary(id), counter_{c}, display_{display}, patternMode_{0} {
    ShowPattern();
}

// cppcheck-suppress unusedFunction
void MyRotary::OnLongPress(int repetition) {
    counter_->Reset();
    display_->Print(counter_->GetCount());
    patternMode_ = savedPatternMode_;
    ShowPattern();
}

// cppcheck-suppress unusedFunction
void MyRotary::OnPress() {
    savedPatternMode_ = patternMode_;
    patternMode_      = (patternMode_ + 1) % 4;
    ShowPattern();
}

// cppcheck-suppress unusedFunction
void MyRotary::OnRotate(int dir) {
    if (dir == 1) {
        counter_->Increment();
    } else {
        counter_->Decrement();
    }
    display_->Print(counter_->GetCount());
    ShowPattern();
}

void MyRotary::ShowPattern() {
    switch (patternMode_) {
        case 0:
            LedPos(counter_->GetCount(), 1);
            break;
        case 1:
            LedPos(counter_->GetCount(), 2);
            break;
        case 2:
            LedPos(counter_->GetCount(), 3);
            break;
        case 3:
            LedFill(0, 1 + counter_->GetCount() * 15 / 99);
            break;
    }
}
