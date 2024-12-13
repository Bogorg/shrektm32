/**
 ******************************************************************************
 * @file        : shift_reg.hpp
 * @brief       : Shift register's headerfile
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
 * Shift register's headerfile
 ******************************************************************************
 */

#ifndef LIB_SHIFT_REG_SHIFT_REG_HPP_
#define LIB_SHIFT_REG_SHIFT_REG_HPP_

#include <stdint.h>

#include "arduino_shield.hpp"
#include "pwm.hpp"
#include "stm32f4xx_hal_spi.h"

class ShiftReg {
   public:
    explicit ShiftReg(ArduinoShield::ClickId id = ArduinoShield::kClick1);
    ~ShiftReg();
    void Reset();
    void SendData(uint8_t* buffer, int len);
    void Latch();

   private:
    ArduinoShield::ClickId id_;
    uint32_t resetPin_;
    GPIO_TypeDef* resetPort_;
    uint32_t latchPin_;
    GPIO_TypeDef* latchPort_;

    static SPI_HandleTypeDef hspi_;
    static void InitSpi();
};

#endif  // LIB_SHIFT_REG_SHIFT_REG_HPP_
