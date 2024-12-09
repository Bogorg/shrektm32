/**
 ******************************************************************************
 * @file        : progress.cpp
 * @brief       : Progress bar
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @author      : Luca Haab <luca.haab@hefr.ch>
 * @date        : 10. December 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Progress bar used in conjunction with an Adafruit GFX display
 *
 * It displays one progress bar, at the indicated position, between 0 and 100%
 * The maximum value is set with the parameter maxValue, with which 100% is
 * calculated (progress / maxValue)
 ******************************************************************************
 */

#include "progress.hpp"

#include "color.hpp"

ProgressMeter::ProgressMeter(
    AdafruitGFX* gfx, int posX, int posY, int width, int height, int maxValue)
    : gfx_(gfx),
      posX_(posX),
      posY_(posY),
      width_(width),
      height_(height),
      maxValue_(maxValue) {
    gfx->drawRect(posX, posY, width, height, ColorRGB(100, 100, 100));
}

ProgressMeter::~ProgressMeter() {}

// cppcheck-suppress unusedFunction
void ProgressMeter::Draw(int progress) {
    int barWidth = progress * (width_ - 2) / maxValue_;

    gfx_->fillRect(posX_ + 1,
                   posY_ + 1,
                   barWidth,
                   height_ - 2,
                   ColorHSL(progress * 360.0 / maxValue_, 1, 0.5));
    gfx_->fillRect(posX_ + 1 + barWidth,
                   posY_ + 1,
                   width_ - 2 - barWidth,
                   height_ - 2,
                   ColorRGB(50, 50, 50));
}
