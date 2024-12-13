/**
 ******************************************************************************
 * @file        : shift_reg.cpp
 * @brief       : Shift register library
 * @authors     : Bulliard Aurélien <aurelien.bulliard@edu.hefr.ch>
 *               & Casimiro Filipe <filipe.casimiro@edu.hefr.ch>    
 * @date        : 13.12.2024
 ******************************************************************************
 * @copyright   : Copyright (c) 2024 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Shift register library
 ******************************************************************************
 */

#include "shift_reg.hpp"

#include "arduino_shield.hpp"

SPI_HandleTypeDef ShiftReg::hspi_{}; //Instanciation of SPI
/**
 * Constructor
 */
ShiftReg::ShiftReg(ArduinoShield::ClickId id) : id_{id} {

    ArduinoShield* shield = ArduinoShield::GetInstance();
    resetPin_             = shield->GetGpioPin(id, ArduinoShield::kRST);
    resetPort_            = shield->GetGpioPort(id, ArduinoShield::kRST);
    latchPin_             = shield->GetGpioPin(id, ArduinoShield::kCS);
    latchPort_            = shield->GetGpioPort(id, ArduinoShield::kCS);

    GPIO_InitTypeDef gpio_init_structure;
    gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init_structure.Pull  = GPIO_PULLUP;
    gpio_init_structure.Speed = GPIO_SPEED_FREQ_HIGH;

    gpio_init_structure.Pin = resetPin_;
    HAL_GPIO_Init(resetPort_, &gpio_init_structure);
    gpio_init_structure.Pin = latchPin_;
    HAL_GPIO_Init(latchPort_, &gpio_init_structure);

    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_SET);
    InitSpi();
}

/**
 * Destructor
 */
ShiftReg::~ShiftReg() {
    HAL_GPIO_DeInit(resetPort_, resetPin_);
    HAL_GPIO_DeInit(latchPort_, latchPin_);
}

/**
 * Resets this register
 */
void ShiftReg::Reset() {
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(resetPort_, resetPin_, GPIO_PIN_SET);
}

/**
 * Latches this register
 */
void ShiftReg::Latch() {
    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_SET);
    HAL_GPIO_WritePin(latchPort_, latchPin_, GPIO_PIN_RESET);
}
/**
 * Sends data in buffer to SPI
 */
void ShiftReg::SendData(uint8_t* buffer, int len) {
    HAL_SPI_Transmit(&hspi_, &buffer[0], 2, 1000);
    Latch();
}
/**
 * Inits the SPI
 */
void ShiftReg::InitSpi() {
    static bool initialized = false;
    if (initialized) {
        return;
    }
    ArduinoShield* shield        = ArduinoShield::GetInstance();
    hspi_.Instance               = shield->GetSpi();
    hspi_.Init.Mode              = SPI_MODE_MASTER;
    hspi_.Init.Direction         = SPI_DIRECTION_2LINES;
    hspi_.Init.DataSize          = SPI_DATASIZE_8BIT;
    hspi_.Init.CLKPolarity       = SPI_POLARITY_LOW;
    hspi_.Init.CLKPhase          = SPI_PHASE_1EDGE;
    hspi_.Init.NSS               = SPI_NSS_SOFT;
    hspi_.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;  // 3.125 MHz
    hspi_.Init.FirstBit          = SPI_FIRSTBIT_MSB;
    shield->MspInitSpi();
    HAL_SPI_Init(&hspi_);
    initialized = true;
}
