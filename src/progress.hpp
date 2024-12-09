/**
 ******************************************************************************
 * @file        : progress.hpp
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

#ifndef SRC_PROGRESS_HPP_
#define SRC_PROGRESS_HPP_

#include "AdafruitGFX.hpp"

class ProgressMeter {
   public:
    ProgressMeter(AdafruitGFX* gfx,
                  int posX,
                  int posY,
                  int width,
                  int height,
                  int maxValue);
    ~ProgressMeter();
    void Draw(int progress);

   private:
    AdafruitGFX* gfx_;
    int posX_;
    int posY_;
    int width_;
    int height_;
    int maxValue_;
};

#endif /* SRC_PROGRESS_HPP_ */
