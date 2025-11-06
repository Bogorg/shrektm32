/**
 ******************************************************************************
 * @file        : my_counter.cpp
 * @brief       : My Counter
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 25. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * My Counter
 ******************************************************************************
 */

#include "my_counter.hpp"

Counter::Counter() : count_(0) {}

// cppcheck-suppress unusedFunction
void Counter::Reset() { count_ = 0; }

// cppcheck-suppress unusedFunction
void Counter::Decrement() {
    if (count_ > 0) count_ = count_ - 1;
}

// cppcheck-suppress unusedFunction
void Counter::Increment() {
    if (count_ < 99) count_ = count_ + 1;
}

// cppcheck-suppress unusedFunction
int Counter::GetCount() { return count_; }
