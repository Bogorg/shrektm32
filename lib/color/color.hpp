/**
 ******************************************************************************
 * @file        : color.hpp
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

#ifndef LIB_COLOR_COLOR_HPP_
#define LIB_COLOR_COLOR_HPP_

#include <math.h>
#include <stdint.h>

uint16_t ColorRGB(uint8_t r, uint8_t g, uint8_t b);
uint16_t ColorHSL(double h, double s, double l);

const uint16_t kColorBlack   = ColorRGB(0, 0, 0);
const uint16_t kColorRed     = ColorRGB(255, 0, 0);
const uint16_t kColorGreen   = ColorRGB(0, 255, 0);
const uint16_t kColorBlue    = ColorRGB(0, 0, 255);
const uint16_t kColorWhite   = ColorRGB(255, 255, 255);
const uint16_t kColorYellow  = ColorRGB(255, 255, 0);
const uint16_t kColorCyan    = ColorRGB(0, 255, 255);
const uint16_t kColorMagenta = ColorRGB(255, 0, 255);

#endif /* LIB_COLOR_COLOR_HPP_ */
