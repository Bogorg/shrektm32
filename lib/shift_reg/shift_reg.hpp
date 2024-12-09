/**
 ******************************************************************************
 * @file        : shift_reg.hpp
 * @brief       : Shift register library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Shift register library
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
    // TODO(student): Add required additional private attributes

    static SPI_HandleTypeDef hspi_;
    static void InitSpi();
};

#endif  // LIB_SHIFT_REG_SHIFT_REG_HPP_
