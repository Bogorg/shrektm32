/**
 ******************************************************************************
 * @file        : deletable_text.hpp
 * @brief       : Deletable text
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
 * Deletable text used in conjunction with an Adafruit GFX display
 ******************************************************************************
 */

#ifndef SRC_DELETABLE_TEXT_HPP_
#define SRC_DELETABLE_TEXT_HPP_

#include "AdafruitGFX.hpp"

class DeletableText {
   public:
    DeletableText(AdafruitGFX* gfx, const char* text);
    ~DeletableText();

    void Draw(int posX, int posY);
    void DrawCenter(int posY);
    void Delete(int bgColor = 0);

   private:
    AdafruitGFX* gfx_;
    char text_[256];
    int16_t x_, y_;
    uint16_t w_, h_;
};

#endif /* SRC_DELETABLE_TEXT_HPP_ */
