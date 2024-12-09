/**
 ******************************************************************************
 * @file        : unity_config.c
 * @brief       : Unity Configuration
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 26. July 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Configure the Unity test framework to use USART2 for I/O
 ******************************************************************************
 */

#include "unity_config.h"

#include "stm32412g_discovery.h"
#include "stm32f4xx_hal.h"

static UART_HandleTypeDef uart_handle;

void UnityOutputStart() {
    uart_handle.Instance          = USART2;
    uart_handle.Init.BaudRate     = 115200;
    uart_handle.Init.WordLength   = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits     = UART_STOPBITS_1;
    uart_handle.Init.Parity       = UART_PARITY_NONE;
    uart_handle.Init.Mode         = UART_MODE_TX_RX;
    uart_handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;

    // I know it looks weird, but you really have to use COM1 for USART2!
    BSP_COM_Init(COM1, &uart_handle);
}

void UnityOutputChar(char c) {
    HAL_UART_Transmit(&uart_handle, (uint8_t*)(&c), 1, 1000);
}

void UnityOutputFlush() {}

void UnityOutputComplete() { BSP_COM_DeInit(COM1, &uart_handle); }
