/**
 ******************************************************************************
 * @file        : assert.c
 * @brief       : Assertions
 * @author      : Aurélien Bulliard <aurelien.bulliard@hefr.ch>
 * @date        : 27. July 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Assertions
 ******************************************************************************
 */

#include "assert.h"

#include <stdio.h>

#include "f412disco_ado.h"

void assert_failed(uint8_t* file, uint32_t line) {
    printf("Assertion failed at %s, line %d\n", __FILE__, __LINE__);
    BSP_LED_Init(LED_ORANGE);
    while (1) {
        BSP_LED_Toggle(LED_ORANGE);
        HAL_Delay(50);
    }
}
