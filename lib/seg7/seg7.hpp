/**
 ******************************************************************************
 * @file        : seg7.hpp
 * @brief       : Seven Segment library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Seven Segment library
 ******************************************************************************
 */

#ifndef LIB_SEG7_SEG7_HPP_
#define LIB_SEG7_SEG7_HPP_

#include <stdint.h>

#include "arduino_shield.hpp"
#include "pwm.hpp"

class Seg7 {
   public:
    explicit Seg7(ArduinoShield::ClickId id = ArduinoShield::kClick1);
    ~Seg7();
    void Reset();

    void PrintPattern(uint16_t pattern);
    void Print(int i);
    void Print(float f);
    void PrintHex(int i);
    void SetBrightness(float level);

   private:
    ArduinoShield::ClickId id_;
    PwmChannel pwm_;
    uint32_t resetPin_;
    GPIO_TypeDef* resetPort_;
    uint32_t latchPin_;
    GPIO_TypeDef* latchPort_;

    void SendData(uint8_t* buffer, int len);
    void Latch();

    static SPI_HandleTypeDef hspi_;
    static void InitSpi();
};

#endif /* LIB_SEG7_SEG7_HPP_ */
