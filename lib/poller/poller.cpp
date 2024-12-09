/**
 ******************************************************************************
 * @file        : poller.cpp
 * @brief       : Poller
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
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

#include "poller.hpp"

#include <stdio.h>

#include <vector>

#include "assert.h"

std::vector<Poller*> Poller::pollers_;
static TIM_HandleTypeDef htim3;

void callback(TIM_HandleTypeDef* htim) {
    (void)htim;
    Poller::PollAll();
}

/**
 * Initializes the timer used for polling.
 *
 * @param prescaler The prescaler value for the timer.
 * @param frequency The frequency of the timer.
 *
 * @returns HAL_OK if the timer was successfully initialized.
 */
HAL_StatusTypeDef Poller::InitTimer(uint32_t prescaler_freq,
                                    uint32_t frequency) {
    RCC_ClkInitTypeDef clkconfig;
    uint32_t latency;
    HAL_StatusTypeDef status;

    __HAL_RCC_TIM3_CLK_ENABLE();
    HAL_RCC_GetClockConfig(&clkconfig, &latency);

    uint32_t APB1Freq      = HAL_RCC_GetPCLK1Freq();
    uint32_t APB1Prescaler = clkconfig.APB1CLKDivider;

    uint32_t timclock;
    if (APB1Prescaler == RCC_HCLK_DIV1) {
        timclock = APB1Freq;
    } else {
        timclock = 2UL * APB1Freq;
    }

    uint32_t prescalerValue = (uint32_t)((timclock / prescaler_freq) - 1U);
    assert(prescalerValue <= 0xffff);
    htim3.Instance = TIM3;

    /* Initialize TIMx peripheral as follow:
    + Period = [(TIM3CLK/1000) - 1]. to have a 1 s time base.
    + Prescaler = (uwTimclock/1000 - 1) to have a 1kHz counter clock.
    + ClockDivision = 0
    + Counter direction = Up
    */

    uint32_t p = (prescaler_freq / frequency) - 1U;
    assert(p <= 0xffff);
    htim3.Init.Period            = p;
    htim3.Init.Prescaler         = prescalerValue;
    htim3.Init.ClockDivision     = 0;
    htim3.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    status = HAL_TIM_Base_Init(&htim3);
    if (status != HAL_OK) {
        return status;
    }
    status = HAL_TIM_RegisterCallback(
        &htim3, HAL_TIM_PERIOD_ELAPSED_CB_ID, callback);
    if (status != HAL_OK) {
        return status;
    }
    /* Start the TIM time Base generation in interrupt mode */
    status = HAL_TIM_Base_Start_IT(&htim3);
    if (status != HAL_OK) {
        return status;
    }
    /* Enable the TIM3 global Interrupt */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    return status;
}

/**
 * Adds a poller to the list of pollers.
 *
 * @param p The poller to add.
 *
 * @returns None
 */
void Poller::Add(Poller* p) { pollers_.push_back(p); }

/**
 * Removes a poller from the poller list.
 *
 * @param p The poller to remove.
 *
 * @returns None
 */
void Poller::Del(Poller* p) {
    int len = pollers_.size();
    for (std::vector<Poller*>::iterator it = pollers_.begin();
         it != pollers_.end();) {
        if (*it == p) {
            it = pollers_.erase(it);
        } else {
            ++it;
        }
    }
    assert((int)pollers_.size() == len - 1);
}

/**
 * Polls all registered Pollers.
 *
 * @returns None
 */
void Poller::PollAll() {
    for (Poller* p : pollers_) {
        p->Poll();
    }
}

extern "C" {

/**
 * Interrupt handler for TIM3.
 *
 * @returns None
 */
void TIM3_IRQHandler(void) { HAL_TIM_IRQHandler(&htim3); }
}
