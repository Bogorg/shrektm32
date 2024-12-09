/**
 ******************************************************************************
 * @file        : color.cpp
 * @brief       : Color generation and definitions
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 25. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Color generation and definitions
 ******************************************************************************
 */

#include "color.hpp"

#include <math.h>
#include <stdint.h>

uint16_t ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
    return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);
}

uint16_t ColorHSL(double h, double s, double l) {
    double c = 1 - fabs(2 * l - 1) * s;  // chroma
    double x = c * (1 - fabs(fmod(h / 60.0, 2.0) - 1));
    double m = l - c / 2;
    double r, g, b;
    if (h < 60) {
        r = c;
        g = x;
        b = 0;
    } else if (h < 120) {
        r = x;
        g = c;
        b = 0;
    } else if (h < 180) {
        r = 0;
        g = c;
        b = x;
    } else if (h < 240) {
        r = 0;
        g = x;
        b = c;
    } else if (h < 300) {
        r = x;
        g = 0;
        b = c;
    } else {
        r = c;
        g = 0;
        b = x;
    }

    int ri = (r + m) * 0x1f;
    int gi = (g + m) * 0x3f;
    int bi = (b + m) * 0x1f;

    return ((ri & 0x1f) << 11) | ((gi & 0x3f)) << 5 | (bi & 0x1f);
}
