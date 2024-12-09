/**
 ******************************************************************************
 * @file        : led.hpp
 * @brief       : Class for LEDs
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 27. July 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Class for LEDs
 ******************************************************************************
 */

#ifndef LIB_LED_LED_HPP_
#define LIB_LED_LED_HPP_

#include "f412disco_ado.h"

class Led {
   public:
    explicit Led(Led_TypeDef led);
    ~Led();
    int Read();
    void Write(int value);
    void Toggle();
    void On();
    void Off();
    Led& operator=(int value);
    Led& operator=(const Led& rhs);
    operator int();

   private:
    Led_TypeDef led_;
};

#endif /* LIB_LED_LED_HPP_ */
