/**
 ******************************************************************************
 * @file        : arduino_shield.hpp
 * @brief       : Arduino shield library
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @author      : Luca Haab <luca.haab@hefr.ch>
 * @date        : 11. December 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Arduino shield library
 ******************************************************************************
 */

#ifndef LIB_ARDUINO_SHIELD_ARDUINO_SHIELD_HPP_
#define LIB_ARDUINO_SHIELD_ARDUINO_SHIELD_HPP_

#include <stdint.h>

#include "stm32f4xx_hal.h"

class ArduinoShield {
   public:
    enum ClickId {
        kClick1 = 0,
        kClick2 = 1,
    };

    enum PinName {
        kAN   = 0,
        kRST  = 1,
        kCS   = 2,
        kSCK  = 3,
        kMISO = 4,
        kMOSI = 5,
        kPWM  = 6,
        kINT  = 7,
        kRX   = 8,
        kTX   = 9,
        kSCL  = 10,
        kSDA  = 11,
    };

    // Returns the instance of ArduinoShield
    static ArduinoShield* GetInstance();
    // Returns the GPIO_TypeDef of a given pin on a defined Click Board
    GPIO_TypeDef* GetGpioPort(ClickId c, PinName pin);
    // Returns the pin id of a given pin on a defined Click Board
    uint32_t GetGpioPin(ClickId c, PinName pin);
    // Returns the SPI controller used by the board (e.g. SPI1)
    SPI_TypeDef* GetSpi();
    // Returns the I2C controller used by the board (e.g. I2C2)
    I2C_TypeDef* GetI2C();
    // Returns the USART controller used by the board (e.g. USART6)
    USART_TypeDef* GetUsart();

    // Initializes the SPI controller
    void MspInitSpi();
    // Initializes the I2C controller
    void MspInitI2c();
    // Initializes the USART controller
    void MspInitUsart();

   private:
    ArduinoShield();
    ArduinoShield(ArduinoShield const&);
    void operator=(ArduinoShield const&);
};

#endif  // LIB_ARDUINO_SHIELD_ARDUINO_SHIELD_HPP_
