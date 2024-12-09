/**
 ******************************************************************************
 * @file        : unity_config.h
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

#ifndef TEST_UNITY_CONFIG_H_
#define TEST_UNITY_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

void UnityOutputStart();
void UnityOutputChar(char);
void UnityOutputFlush();
void UnityOutputComplete();

#define UNITY_OUTPUT_START() UnityOutputStart()
#define UNITY_OUTPUT_CHAR(c) UnityOutputChar(c)
#define UNITY_OUTPUT_FLUSH() UnityOutputFlush()
#define UNITY_OUTPUT_COMPLETE() UnityOutputComplete()

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* TEST_UNITY_CONFIG_H_ */
