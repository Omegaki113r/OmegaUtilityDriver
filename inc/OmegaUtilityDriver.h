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
 * Last Modified: Wednesday, 11th September 2024 12:27:48 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 06-07-2024	0m3g4	adding OMEGA_STR2MAC implemented
 *
 * 05-07-2024	0m3g4	adding MAC_ADDRESS_BUFFER_LENGTH and MAC2STR
 */

#ifndef __OMEGA_UTILITY_DRIVER_H__
#define __OMEGA_UTILITY_DRIVER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#if ESP_PLATFORM
#include <esp_heap_caps.h>
#endif

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#define STRINGIFY(s) #s

#define START_ESCAPE_LOGGING_PARAMETER "\033["
#define END_ESCAPE_LOGGIN_PARAMETER "\033[0m"
#define DETAILED_BACKGROUND_FOREGROUND_COLOR "48;5;250;38;5;232;1"
#define INFO_BACKGROUND_FOREGROUND_COLOR "48;5;2;38;5;0"
#define INFO_TEXT_COLOR "38;5;2"
#define ERROR_BACKGROUND_FOREGROUND_COLOR "48;5;1;38;5;0"
#define ERROR_TEXT_COLOR "38;5;1"
#define WARN_BACKGROUND_FOREGROUND_COLOR "48;5;202;38;5;0"
#define WARN_TEXT_COLOR "38;5;202"
#define DEBUG_BACKGROUND_FOREGROUND_COLOR "48;5;3;38;5;0"
#define DEBUG_TEXT_COLOR "38;5;3"
#define VERBOSE_BACKGROUND_FOREGROUND_COLOR "48;5;15;38;5;0"
#define VERBOSE_TEXT_COLOR "38;5;15"
#define PROFILE_BACKGROUND_FOREGROUND_COLOR "48;5;207;38;5;0"
#define PROFILE_TEXT_COLOR "38;5;207"
#define END_PARAMETER "m"

#if CONFIG_OMEGA_LOGGING
    static inline void OmegLoggingSystemController_log_hex(const char *initial_text, const char *file_name, const char *function_name, const size_t line_number, const char *text_color, void *buffer, size_t length)
    {
        char ascii[17];
        size_t i, j;
        ascii[16] = '\0';
        for (i = 0; i < length; ++i)
        {
            if (i % 16 == 0)
            {
                printf(initial_text, file_name, function_name, line_number);
                printf(START_ESCAPE_LOGGING_PARAMETER "%s" END_PARAMETER, text_color);
            }
            printf("%02X ", ((unsigned char *)buffer)[i]);
            if (((unsigned char *)buffer)[i] >= ' ' && ((unsigned char *)buffer)[i] <= '~')
            {
                ascii[i % 16] = ((unsigned char *)buffer)[i];
            }
            else
            {
                ascii[i % 16] = '.';
            }
            if ((i + 1) % 8 == 0 || i + 1 == length)
            {
                printf(" ");
                if ((i + 1) % 16 == 0)
                {
                    printf("|%s|\n", ascii);
                }
                else if (i + 1 == length)
                {
                    ascii[(i + 1) % 16] = '\0';
                    if ((i + 1) % 16 <= 8)
                    {
                        printf(" ");
                    }
                    for (j = (i + 1) % 16; j < 16; ++j)
                    {
                        printf("   ");
                    }
                    printf("|%s|\n", ascii);
                }
            }
        }
        printf(END_ESCAPE_LOGGIN_PARAMETER);
    }
#define OMEGA_LOGV(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER VERBOSE_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [V] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER VERBOSE_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGD(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER DEBUG_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [D] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER DEBUG_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGI(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER INFO_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [I] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER INFO_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGW(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER WARN_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [W] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER WARN_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGE(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER ERROR_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [E] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER ERROR_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_HEX_LOGV(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER VERBOSE_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [V] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, VERBOSE_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGD(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER DEBUG_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [D] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, DEBUG_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGI(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER INFO_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [I] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, INFO_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGW(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER WARN_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [W] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, WARN_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGE(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER ERROR_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [E] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, ERROR_TEXT_COLOR, buffer, length)
#else
#define OMEGA_LOGV(format, ...)
#define OMEGA_LOGD(format, ...)
#define OMEGA_LOGI(format, ...)
#define OMEGA_LOGW(format, ...)
#define OMEGA_LOGE(format, ...)
#define OMEGA_HEX_LOGV(buffer, length)
#define OMEGA_HEX_LOGD(buffer, length)
#define OMEGA_HEX_LOGI(buffer, length)
#define OMEGA_HEX_LOGW(buffer, length)
#define OMEGA_HEX_LOGE(buffer, length)
#endif

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define internal static
#define UNUSED(arg) (void)arg

#if ESP_PLATFORM
#define PERIPHERAL_CORE 0
#define APP_CORE 1
#endif

#if __has_include(<freertos/FreeRTOS.h>)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define delay_ms(x) vTaskDelay(pdMS_TO_TICKS(x))
#define delay_s(x) vTaskDelay(pdMS_TO_TICKS(x * 1000))
#endif

#define GPIO_LEVEL_LOW 0
#define GPIO_LEVEL_HIGH 1

#define MAC_ADDRESS_BUFFER_LENGTH 6
#define MAC_ADDRESS_STRING_BUFFER_LENGTH 17
#define MAC2STR_STRING "%02x:%02x:%02x:%02x:%02x:%02x"
#define STR2MAC_STRING "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx"
#define BUFFER_EXPAND(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define OMEGA_MAC2STR(addr, str)                                \
    do                                                          \
    {                                                           \
        if (addr == NULL)                                       \
        {                                                       \
            OMEGA_LOGE("Bluetooth address was NULL");           \
            return;                                             \
        }                                                       \
        if (str == NULL)                                        \
        {                                                       \
            OMEGA_LOGE("Provided buffer was NULL");             \
            return;                                             \
        }                                                       \
        snprintf(str, 18, MAC2STR_STRING, BUFFER_EXPAND(addr)); \
    } while (0)
#define OMEGA_STR2MAC(str, addr)                                                                 \
    do                                                                                           \
    {                                                                                            \
        if (str == NULL)                                                                         \
        {                                                                                        \
            OMEGA_LOGE("String buffer was NULL");                                                \
            return;                                                                              \
        }                                                                                        \
        if (addr == NULL)                                                                        \
        {                                                                                        \
            OMEGA_LOGE("Destination buffer was NULL");                                           \
            return;                                                                              \
        }                                                                                        \
        sscanf(str, STR2MAC_STRING, &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]); \
    } while (0)

#if ESP_PLATFORM
#if CONFIG_SPIRAM
#define omega_malloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM)
#define omega_realloc(prev_ptr, new_size) heap_caps_realloc(prev_ptr, new_size, MALLOC_CAP_SPIRAM)
#define omega_free(ptr)      \
    do                       \
    {                        \
        heap_caps_free(ptr); \
        ptr = NULL;          \
    } while (0)
#else
#define omega_malloc(size) malloc(size)
#define omega_realloc(prev_ptr, new_size) realloc(prev_ptr, new_size)
#define omega_free(ptr) \
    do                  \
    {                   \
        free(ptr);      \
        ptr = NULL;     \
    } while (0)
#endif
#endif

    typedef uint8_t u8;
    typedef int8_t i8;
    typedef uint16_t u16;
    typedef int16_t i16;
    typedef uint64_t u64;
    typedef int64_t i64;

#define CREATE_BUFFER_U8(name, ...) u8 name[] = {__VA_ARGS__};
#define CREATE_BUFFER_U16(name, ...) u16 name[] = {__VA_ARGS__};
#define CREATE_BUFFER_FLOAT(name, ...) float name[] = {__VA_ARGS__};

#define STATIC_CREATE_BUFFER_U8(name, ...) static u8 name[] = {__VA_ARGS__};
#define STATIC_CREATE_BUFFER_U16(name, ...) static u16 name[] = {__VA_ARGS__};
#define STATIC_CREATE_BUFFER_FLOAT(name, ...) static float name[] = {__VA_ARGS__};

#define CREATE_EMPTY_BUFFER_U8(name, size) u8 name[size] = {0};
#define CREATE_EMPTY_BUFFER_U16(name, size) u16 name[size] = {0};
#define CREATE_EMPTY_BUFFER_FLOAT(name, size) float name[size] = {0};
#define STATIC_EMPTY_CREATE_BUFFER_U8(name, size) static u8 name[size] = {0};
#define STATIC_EMPTY_CREATE_BUFFER_U16(name, size) static u16 name[size] = {0};
#define STATIC_EMPTY_CREATE_BUFFER_FLOAT(name, size) static float name[size] = {0};

#define BIT(x) 1<<x
#define LSHIFT(x,count) x>>count
#define RSHIFT(x,count) x<<count

typedef enum
{
    eSUCCESS,
    eFAILED,
    eTIMEOUT,
    eNOT_INITED,
    eALREADY_INITED,
    eNOT_STARTED,
    eALREADY_STARTED,
}OmegaStatus;

#define OMEGA_GPIO_PORT_NC NULL
#define OMEGA_GPIO_PIN_NC -1
#define OMEGA_GPIO_NC ((OmegaGPIO_t){.port = NULL,.pin = -1})
typedef struct
{
    void* port;
    int32_t pin;
}OmegaGPIO_t;

#ifdef __cplusplus
}
#endif

#endif
