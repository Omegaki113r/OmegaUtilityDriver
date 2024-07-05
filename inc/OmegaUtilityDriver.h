/**
 * @file OmegaUtilityDriver.h
 * @author Omegaki113r
 * @date Tuesday, 2nd July 2024 12:59:59 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaUtilityDriver
 * File Name: OmegaUtilityDriver.h
 * File Created: Tuesday, 2nd July 2024 12:59:59 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Friday, 5th July 2024 10:03:05 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef __OMEGA_UTILITY_DRIVER_H__
#define __OMEGA_UTILITY_DRIVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "OmegaBaseLoggingController.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define UNUSED(func) (void)func

#define MAC2STR(addr, str)                                                                                  \
    do                                                                                                      \
    {                                                                                                       \
        if (addr == NULL)                                                                                   \
        {                                                                                                   \
            OMEGA_LOGE("Bluetooth address was NULL");                                                       \
            return;                                                                                         \
        }                                                                                                   \
        if (str == NULL)                                                                                    \
        {                                                                                                   \
            OMEGA_LOGE("Provided buffer was NULL");                                                         \
            return;                                                                                         \
        }                                                                                                   \
        snprintf(str, 18, "%02x:%02x:%02x:%02x:%02x:%02x", bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]); \
    } while (0);

#if ESP_PLATFORM
#if CONFIG_SPIRAM
#define omega_malloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM)
#define omega_realloc(prev_ptr, new_size) heap_caps_realloc(prev_ptr, new_size, MALLOC_CAP_SPIRAM)
#define omega_free(ptr) heap_caps_free(ptr)
#else
#define omega_malloc(size) malloc(size)
#define omega_realloc(prev_ptr, new_size) realloc(prev_ptr, new_size)
#define omega_free(ptr) free(ptr)
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif
