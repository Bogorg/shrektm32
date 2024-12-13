/**
 ******************************************************************************
 * @file        : seg7.hpp
 * @brief       : Seven segments display's library's headerfile
 * @authors     : Bulliard Aurélien <aurelien.bulliard@edu.hefr.ch>
 *               & Casimiro Filipe <filipe.casimiro@edu.hefr.ch>    
 * @date        : 13.12.2024
 ******************************************************************************
 * @copyright   : Copyright (c) 2024 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Seven segments display's library's headerfile
 ******************************************************************************
 */

#ifndef LIB_SEG7_SEG7_HPP_
#define LIB_SEG7_SEG7_HPP_

#include <stdint.h>
#include "shift_reg.hpp"

#include "arduino_shield.hpp"
#include "pwm.hpp"

class Seg7 : ShiftReg{
   public:
    explicit Seg7(ArduinoShield::ClickId id = ArduinoShield::kClick1);
    ~Seg7();

    void PrintPattern(uint16_t pattern);
    void Print(int i);
    void Print(float f);
    void PrintHex(int i);
    void SetBrightness(float level);

   private:
    ArduinoShield::ClickId id_;
    PwmChannel pwm_;
    ShiftReg shiftReg_;
};

#endif /* LIB_SEG7_SEG7_HPP_ */
