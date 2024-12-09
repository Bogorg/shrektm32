/**
 ******************************************************************************
 * @file        : pwm.hpp
 * @brief       : PWM library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * PWM library
 ******************************************************************************
 */

#ifndef LIB_PWM_PWM_HPP_
#define LIB_PWM_PWM_HPP_

#include "stm32f4xx_hal.h"

class PwmChannel {
   public:
    enum Pin { kPF3, kPF5, kPF10 };
    explicit PwmChannel(Pin pin);
    ~PwmChannel();
    void SetDutyCycle(float duty_cycle);
    HAL_StatusTypeDef Start();
    HAL_StatusTypeDef Stop();

   private:
    static TIM_HandleTypeDef htim5;
    static HAL_StatusTypeDef InitPwm();
    Pin pin_;
};

#endif /* LIB_PWM_PWM_HPP_ */
