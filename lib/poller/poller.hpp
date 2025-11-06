/**
 ******************************************************************************
 * @file        : poller.hpp
 * @brief       : Poller
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 10. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Poller
 ******************************************************************************
 */

#ifndef LIB_POLLER_POLLER_HPP_
#define LIB_POLLER_POLLER_HPP_

#include <vector>

#include "stm32f4xx_hal.h"

class Poller {
   public:
    Poller() { Add(this); }
    virtual ~Poller() { Del(this); }

    HAL_StatusTypeDef static InitTimer(uint32_t prescaler, uint32_t frequency);
    virtual void Poll() = 0;

    static void PollAll();

   private:
    static void Add(Poller* p);
    static void Del(Poller* p);
    static std::vector<Poller*> pollers_;
};

#endif /* LIB_POLLER_POLLER_HPP_ */
