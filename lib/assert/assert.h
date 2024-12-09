/**
 ******************************************************************************
 * @file        : assert.h
 * @brief       : Assertions
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
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

#ifndef LIB_ASSERT_ASSERT_H_
#define LIB_ASSERT_ASSERT_H_

#include <stdint.h>

#include "app_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CHECK_ASSERT
#define assert(expr) \
    ((expr) ? (void)0U : assert_failed((uint8_t*)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert(expr) ((void)0U)
#endif /* CHECK_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* LIB_ASSERT_ASSERT_H_ */
