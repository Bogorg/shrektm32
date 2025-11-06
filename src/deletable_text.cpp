/**
 ******************************************************************************
 * @file        : deletable_text.cpp
 * @brief       : Deletable text
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @author      : Luca Haab <luca.haab@hefr.ch>
 * @date        : 10. December 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Deletable text used in conjunction with an Adafruit GFX display
 ******************************************************************************
 */

#include "deletable_text.hpp"

#include <stdio.h>
#include <string.h>

#include "AdafruitGFX.hpp"
#include "color.hpp"

DeletableText::DeletableText(AdafruitGFX* gfx, const char* text)
    : gfx_(gfx), x_{0}, y_{0}, w_{0}, h_{0} {
    snprintf(text_, sizeof(text_), text);
}

DeletableText::~DeletableText() {}

void DeletableText::Draw(int posX, int posY) {
    gfx_->setCursor(posX, posY);
    gfx_->getTextBounds(text_, posX, posY, &x_, &y_, &w_, &h_);
    gfx_->write(text_);
}

// cppcheck-suppress unusedFunction
void DeletableText::DrawCenter(int posY) {
    gfx_->getTextBounds(text_, 0, 0, &x_, &y_, &w_, &h_);
    Draw((gfx_->width() - w_) / 2, posY);
}

// cppcheck-suppress unusedFunction
void DeletableText::Delete(int bgColor) {
    gfx_->fillRect(x_, y_, w_, h_, bgColor);
}
