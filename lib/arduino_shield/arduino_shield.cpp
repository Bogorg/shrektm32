/**
 ******************************************************************************
 * @file        : arduino_shield.cpp
 * @brief       : Arduino shield library
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 24. August 2022
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

#include "arduino_shield.hpp"

#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_usart.h"

// clang-format off
constexpr static struct {
    GPIO_TypeDef* port;
    uint32_t pin;
} pinsConfig[][2] = {
    [ArduinoShield::kAN]   = {{GPIOA,  GPIO_PIN_1}, {GPIOC,  GPIO_PIN_1}},
    [ArduinoShield::kRST]  = {{GPIOC,  GPIO_PIN_4}, {GPIOC,  GPIO_PIN_3}},
    [ArduinoShield::kCS]   = {{GPIOA, GPIO_PIN_15}, {GPIOB,  GPIO_PIN_8}},
    [ArduinoShield::kSCK]  = {{GPIOA,  GPIO_PIN_5}, {GPIOA,  GPIO_PIN_5}},  // SPI1
    [ArduinoShield::kMISO] = {{GPIOA,  GPIO_PIN_6}, {GPIOA,  GPIO_PIN_6}},  // SPI1
    [ArduinoShield::kMOSI] = {{GPIOA,  GPIO_PIN_7}, {GPIOA,  GPIO_PIN_7}},  // SPI1
    [ArduinoShield::kPWM]  = {{GPIOF,  GPIO_PIN_3}, {GPIOF, GPIO_PIN_10}},
    [ArduinoShield::kINT]  = {{GPIOG, GPIO_PIN_13}, {GPIOF,  GPIO_PIN_4}},
    [ArduinoShield::kRX]   = {{GPIOG,  GPIO_PIN_9}, {GPIOG,  GPIO_PIN_9}},  // USART6
    [ArduinoShield::kTX]   = {{GPIOG, GPIO_PIN_14}, {GPIOG, GPIO_PIN_14}},  // USART6
    [ArduinoShield::kSCL]  = {{GPIOB, GPIO_PIN_10}, {GPIOB, GPIO_PIN_10}},  // I2C2
    [ArduinoShield::kSDA]  = {{GPIOB,  GPIO_PIN_9}, {GPIOB,  GPIO_PIN_9}},  // I2C2
};
// clang-format on

ArduinoShield::ArduinoShield() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_USART6_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();

    // Configure kRST and kCS as output
    GPIO_InitTypeDef gpio_init_structure;
    for (int i = 0; i < 2; i++) {
        gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
        gpio_init_structure.Pull  = GPIO_PULLUP;
        gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

        gpio_init_structure.Pin = pinsConfig[ArduinoShield::kRST][i].pin;
        HAL_GPIO_Init(pinsConfig[ArduinoShield::kRST][i].port,
                      &gpio_init_structure);
        gpio_init_structure.Pin = pinsConfig[ArduinoShield::kCS][i].pin;
        HAL_GPIO_Init(pinsConfig[ArduinoShield::kCS][i].port,
                      &gpio_init_structure);
    }

    /* Configure USART Tx/Tx as alternate function */
    gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
    gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Alternate = GPIO_AF8_USART6;
    gpio_init_structure.Pin       = pinsConfig[ArduinoShield::kTX][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kTX][0].port, &gpio_init_structure);
    gpio_init_structure.Pin = pinsConfig[ArduinoShield::kRX][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kTX][0].port, &gpio_init_structure);
}

ArduinoShield* ArduinoShield::GetInstance() {
    static ArduinoShield* instance = new ArduinoShield;
    return instance;
}

GPIO_TypeDef* ArduinoShield::GetGpioPort(ClickId c, PinName pin) {
    return pinsConfig[pin][c].port;
}

uint32_t ArduinoShield::GetGpioPin(ClickId c, PinName pin) {
    return pinsConfig[pin][c].pin;
}

SPI_TypeDef* ArduinoShield::GetSpi() { return SPI1; }

I2C_TypeDef* ArduinoShield::GetI2C() { return I2C2; }

USART_TypeDef* ArduinoShield::GetUsart() { return USART6; }

void ArduinoShield::MspInitSpi() {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();
    /* Configure SPI as alternate function */
    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
    gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Alternate = GPIO_AF5_SPI1;
    gpio_init_structure.Pin       = pinsConfig[ArduinoShield::kSCK][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kSCK][0].port,
                  &gpio_init_structure);
    gpio_init_structure.Pin = pinsConfig[ArduinoShield::kMISO][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kMISO][0].port,
                  &gpio_init_structure);
    gpio_init_structure.Pin = pinsConfig[ArduinoShield::kMOSI][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kMOSI][0].port,
                  &gpio_init_structure);
}

void ArduinoShield::MspInitI2c() {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C2_CLK_ENABLE();
    /* Configure I2C as alternate function */
    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
    gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Alternate = GPIO_AF4_I2C2;
    gpio_init_structure.Pin       = pinsConfig[ArduinoShield::kSCL][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kSCL][0].port,
                  &gpio_init_structure);
    gpio_init_structure.Alternate = GPIO_AF9_I2C2;
    gpio_init_structure.Pin       = pinsConfig[ArduinoShield::kSDA][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kSDA][0].port,
                  &gpio_init_structure);
}

void ArduinoShield::MspInitUsart() {
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_USART6_CLK_ENABLE();
    /* Configure USART Tx/Tx as alternate function */
    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
    gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.Pull      = GPIO_PULLUP;
    gpio_init_structure.Alternate = GPIO_AF8_USART6;
    gpio_init_structure.Pin       = pinsConfig[ArduinoShield::kTX][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kTX][0].port, &gpio_init_structure);
    gpio_init_structure.Pin = pinsConfig[ArduinoShield::kRX][0].pin;
    HAL_GPIO_Init(pinsConfig[ArduinoShield::kTX][0].port, &gpio_init_structure);
}
