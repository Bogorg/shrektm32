/**
 ******************************************************************************
 * @file        : tracing.c
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

#include "tracing.h"

#include <stdarg.h>

#include "error_handler.h"
#include "f412disco_ado.h"

static char* level_name[] = {
    [TRACE_LEVEL_DEBUG]   = "DEBUG",
    [TRACE_LEVEL_INFO]    = "INFO",
    [TRACE_LEVEL_WARNING] = "WARN",
    [TRACE_LEVEL_ERROR]   = "ERROR",
    [TRACE_LEVEL_FATAL]   = "FATAL",
};

static void __trace(int level, const char* fmt, va_list args) {
    printf("%-6s: ", level_name[level]);
    vprintf(fmt, args);
    printf("\n");
    if (level >= TRACE_LEVEL_FATAL) {
        ErrorHandler();
    }
}

void trace(int level, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    __trace(level, fmt, ap);
    va_end(ap);
}
