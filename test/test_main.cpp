/**
 ******************************************************************************
 * @file        : test_main.cpp
 * @brief       : Tests runner
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 11. August 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Tests runner
 ******************************************************************************
 */

#include "f412disco_ado.h"
#include "stm32412g_discovery.h"
#include "stm32f4xx_hal.h"
#include "system_clock.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    HAL_Delay(2000);  // Mandatory waiting for 2 seconds...
    UNITY_BEGIN();    // Mandatory call to initialize test framework
    UNITY_END();      // Mandatory call to finalize test framework

    while (1) {
        asm("nop");
    }
}
