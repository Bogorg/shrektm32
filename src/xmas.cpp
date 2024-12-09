/**
 ******************************************************************************
 * @file        : xmas.cpp
 * @brief       : Xmas Tree
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
 * * Xmas Tree used in conjunction with an Adafruit GFX display
 *
 * It displays a X-Mas tree - or part of it, depending on the height given.
 * In fact, if `height` of Draw(int height) is smaller than the `height` of
 * XmasTreeDef, then only a fraction of the tree height will be displayed
 ******************************************************************************
 */

#include "xmas.hpp"

#include "AdafruitGFX.hpp"
#include "color.hpp"

const uint16_t kPegColor  = ColorRGB(174, 116, 73);
const uint16_t kDiskColor = ColorRGB(0, 150, 0);

XmasTree::XmasTree(AdafruitGFX* gfx, const XmasTreeDef* def) : gfx_(gfx) {
    posX_        = def->posX;
    posY_        = def->posY;
    maxWidth_    = def->maxWidth;
    minWidth_    = def->minWidth;
    diskHeight_  = def->diskHeight;
    height_      = def->height;
    discSpacing_ = def->discSpacing;
    pegWidth_    = def->pegWidth;
    baseWidth_   = def->baseWidth;
    prevHeight_  = 0;
    DrawPeg();
}

XmasTree::~XmasTree() {}

// cppcheck-suppress unusedFunction
void XmasTree::Draw(int height) {
    if (height == prevHeight_) {
        return;
    }
    for (int i = 0; i < height; i++) {
        int width = maxWidth_ - (maxWidth_ - minWidth_) * i / (height_ - 1);
        DrawDisk(width, i);
    }
    for (int i = height; i < prevHeight_; i++) {
        int width = maxWidth_ - (maxWidth_ - minWidth_) * i / (height_ - 1);
        ClearDisk(width, i);
    }
    prevHeight_ = height;
}

void XmasTree::DrawPeg() {
    gfx_->fillRect(posX_ - baseWidth_ / 2,
                   posY_ - pegWidth_ / 2,
                   baseWidth_,
                   pegWidth_,
                   kPegColor);
    int pegHeight = (diskHeight_ + discSpacing_) * height_ + discSpacing_;

    gfx_->fillRect(posX_ - pegWidth_ / 2,
                   posY_ - pegWidth_ / 2 - pegHeight,
                   pegWidth_,
                   pegHeight,
                   kPegColor);
}

void XmasTree::DrawDisk(int width, int pos) {
    gfx_->fillRect(
        posX_ - width / 2,
        posY_ - pegWidth_ / 2 - (pos + 1) * (diskHeight_ + discSpacing_),
        width,
        diskHeight_,
        kDiskColor);
}

void XmasTree::ClearDisk(int width, int pos) {
    gfx_->fillRect(
        posX_ - width / 2,
        posY_ - pegWidth_ / 2 - (pos + 1) * (diskHeight_ + discSpacing_),
        width,
        diskHeight_,
        kColorBlack);

    gfx_->fillRect(
        posX_ - pegWidth_ / 2,
        posY_ - pegWidth_ / 2 - (pos + 1) * (diskHeight_ + discSpacing_),
        pegWidth_,
        diskHeight_,
        kPegColor);
}
