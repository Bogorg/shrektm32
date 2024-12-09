/**
 ******************************************************************************
 * @file        : tracing.h
 * @brief       : Tracing
 * @author      : Jacques Supcik <jacques.supcik@hefr.ch>
 * @date        : 27. July 2022
 ******************************************************************************
 * @copyright   : Copyright (c) 2022 HEIA-FR / ISC
 *                Haute école d'ingénierie et d'architecture de Fribourg
 *                Informatique et Systèmes de Communication
 * @attention   : SPDX-License-Identifier: MIT OR Apache-2.0
 ******************************************************************************
 * @details
 * Tracing
 ******************************************************************************
 */

#ifndef LIB_TRACING_TRACING_H_
#define LIB_TRACING_TRACING_H_

#include <stdio.h>

#include "app_conf.h"
#include "f412disco_ado.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TRACE_LEVEL_DEBUG 0
#define TRACE_LEVEL_INFO 1
#define TRACE_LEVEL_WARNING 2
#define TRACE_LEVEL_ERROR 3
#define TRACE_LEVEL_FATAL 4

void trace(int level, const char* fmt, ...);

#if TRACE_LEVEL <= TRACE_LEVEL_DEBUG
#define tr_debug(fmt, ...) trace(TRACE_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#else
#define tr_debug(fmt, ...) ((void)0U)
#endif

#if TRACE_LEVEL <= TRACE_LEVEL_INFO
#define tr_info(fmt, ...) trace(TRACE_LEVEL_INFO, fmt, ##__VA_ARGS__)
#else
#define tr_info(fmt, ...) ((void)0U)
#endif

#if TRACE_LEVEL <= TRACE_LEVEL_WARNING
#define tr_warn(fmt, ...) trace(TRACE_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#else
#define tr_warn(fmt, ...) ((void)0U)
#endif

#if TRACE_LEVEL <= TRACE_LEVEL_ERROR
#define tr_error(fmt, ...) trace(TRACE_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#else
#define tr_error(fmt, ...) ((void)0U)
#endif

#define tr_fatal(fmt, ...) trace(TRACE_LEVEL_FATAL, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* LIB_TRACING_TRACING_H_ */
