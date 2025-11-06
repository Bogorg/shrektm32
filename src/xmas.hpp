/**
 ******************************************************************************
 * @file        : xmas.hpp
 * @brief       : Xmas Tree
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
 * Xmas Tree used in conjunction with an Adafruit GFX display
 *
 * It displays a X-Mas tree - or part of it, depending on the height given.
 * In fact, if `height` of Draw(int height) is smaller than the `height` of
 * XmasTreeDef, then only a fraction of the tree height will be displayed
 ******************************************************************************
 */

#ifndef SRC_XMAS_HPP_
#define SRC_XMAS_HPP_

#include "AdafruitGFX.hpp"

typedef struct {
    int posX;
    int posY;
    int maxWidth;
    int minWidth;
    int diskHeight;
    int height;
    int discSpacing;
    int pegWidth;
    int baseWidth;
} XmasTreeDef;

class XmasTree {
   public:
    XmasTree(AdafruitGFX* gfx, const XmasTreeDef* def);
    ~XmasTree();

    void Draw(int height);

   private:
    AdafruitGFX* gfx_;
    int posX_;
    int posY_;
    int maxWidth_;
    int minWidth_;
    int diskHeight_;
    int height_;
    int discSpacing_;
    int pegWidth_;
    int baseWidth_;
    int prevHeight_;
    void DrawPeg();
    void DrawDisk(int width, int pos);
    void ClearDisk(int width, int pos);
};

#endif /* SRC_XMAS_HPP_ */
