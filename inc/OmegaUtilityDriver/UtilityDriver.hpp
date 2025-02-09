/**
 * @file OmegaUtilityDriver.hpp
 * @author Omegaki113r
 * @date Tuesday, 2nd July 2024 12:59:59 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaUtilityDriver
 * File Name: OmegaUtilityDriver.hpp
 * File Created: Tuesday, 2nd July 2024 12:59:59 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Sunday, 9th February 2025 6:05:02 pm
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

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdio>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint64_t u64;
typedef int64_t i64;
typedef uint32_t u32;
typedef int32_t i32;

typedef u64 OmegaHandle;

#define internal static
#define global static
#ifndef UNUSED
#define UNUSED(arg) (void)arg
#endif

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#define PERIPHERAL_CORE 0
#define APP_CORE 1

#define GPIO_LEVEL_LOW 0
#define GPIO_LEVEL_HIGH 1

#define OMEGA_BIT(x) (1 << x)
#define OMEGA_LSHIFT(x, count) (x >> count)
#define OMEGA_RSHIFT(x, count) (x << count)
#define OMEGA_BIT_SET(x, bit) (x | OMEGA_BIT(bit))
#define OMEGA_BIT_CLEAR(x, bit) (x & ~(OMEGA_BIT(bit)))
#define OMEGA_BIT_CHECK(x, bit) (x & (1 << bit))

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
#define DEBUG_BACKGROUND_FOREGROUND_COLOR "48;5;15;38;5;0"
#define DEBUG_TEXT_COLOR "38;5;15"
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
#define OMEGA_LOGD(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER DEBUG_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [D] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER DEBUG_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGI(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER INFO_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [I] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER INFO_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGW(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER WARN_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [W] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER WARN_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_LOGE(format, ...) printf(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER ERROR_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [E] " END_ESCAPE_LOGGIN_PARAMETER " " START_ESCAPE_LOGGING_PARAMETER ERROR_TEXT_COLOR END_PARAMETER format END_ESCAPE_LOGGIN_PARAMETER "\r\n", __func__, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define OMEGA_HEX_LOGD(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER DEBUG_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [D] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, DEBUG_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGI(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER INFO_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [I] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, INFO_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGW(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER WARN_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [W] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, WARN_TEXT_COLOR, buffer, length)
#define OMEGA_HEX_LOGE(buffer, length) OmegLoggingSystemController_log_hex(START_ESCAPE_LOGGING_PARAMETER DETAILED_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " %s >> %s:%d " END_ESCAPE_LOGGIN_PARAMETER "" START_ESCAPE_LOGGING_PARAMETER ERROR_BACKGROUND_FOREGROUND_COLOR END_PARAMETER " [E] " END_ESCAPE_LOGGIN_PARAMETER " ", __func__, __FILE_NAME__, __LINE__, ERROR_TEXT_COLOR, buffer, length)
#else
#define OMEGA_LOGD(format, ...)
#define OMEGA_LOGI(format, ...)
#define OMEGA_LOGW(format, ...)
#define OMEGA_LOGE(format, ...)
#define OMEGA_HEX_LOGD(buffer, length)
#define OMEGA_HEX_LOGI(buffer, length)
#define OMEGA_HEX_LOGW(buffer, length)
#define OMEGA_HEX_LOGE(buffer, length)
#endif

// #if ESP_PLATFORM
// #include <esp_heap_caps.h>
// #endif

#ifdef __cplusplus
template <typename T>
inline constexpr T US_TO_MS(T in_us) noexcept { return in_us / 1000; }
template <typename T>
inline constexpr T MS_TO_S(T in_ms) noexcept { return in_ms / 1000; }
template <typename T>
inline constexpr T US_TO_S(T in_us) noexcept { return in_us / (1000 * 1000); }
template <typename T>
inline constexpr T S_TO_MS(T in_s) noexcept { return in_s * 1000; }
template <typename T>
inline constexpr T MS_TO_US(T in_ms) noexcept { return in_ms * 1000; }
template <typename T>
inline constexpr T S_TO_US(T in_s) noexcept { return in_s * 1000 * 1000; }
#else
#define US_TO_MS(x) (x / 1000)
#define MS_TO_S(x) (x / 1000)
#define US_TO_S(x) (x / (1000 * 1000))
#define S_TO_MS(x) (x * 1000)
#define MS_TO_US(x) (x * 1000)
#define S_TO_US(x) (x * 1000 * 1000)
#endif

#define CHAR2INT(x) (('0' <= x && x <= '9') ? (x - '0') : (('a' <= x && x <= 'f') ? (10 + (x - 'a')) : (('A' <= x && x <= 'F') ? (10 + (x - 'A')) : (0))))

#ifdef __cplusplus
template <typename T>
inline constexpr T OMEGA_MAX(T in1, T in2) noexcept { return (((in1) > (in2)) ? (in1) : (in2)); }
template <typename T>
inline constexpr T OMEGA_MIN(T in1, T in2) noexcept { return (((in1) < (in2)) ? (in1) : (in2)); }
#else
#define OMEGA_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define OMEGA_MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifdef __cplusplus
struct Duration
{
    u16 h;
    u8 m;
    u8 s;
    u16 ms;
    u64 us;

    constexpr u16 us_to_ms(const auto in_us) { return in_us / 1000; }
    constexpr u8 ms_to_s(const auto in_ms) { return in_ms / 1000; }
    constexpr u8 s_to_mins(const auto in_s) { return in_s / 60; }
    constexpr u16 mins_to_hrs(const auto in_mins) { return in_mins / 60; }
    constexpr u64 to_us() const
    {
        const auto hour_us = h * 60 * 60 * 1000 * 1000;
        const auto minutes_us = m * 60 * 1000 * 1000;
        const auto seconds_us = s * 1000 * 1000;
        const auto milliseconds_us = ms * 1000;
        return hour_us + minutes_us + seconds_us + milliseconds_us + us;
    }

    constexpr Duration() : h(0), m(0), s(0), ms(0), us(0) {}
    constexpr Duration(u16 in_h) : h(in_h), m(0), s(0), ms(0), us(0) {}
    constexpr Duration(u16 in_h, u16 in_m) : h(in_h), m(in_m), s(0), ms(0), us(0) {}
    constexpr Duration(u16 in_h, u16 in_m, u32 in_s) : h(in_h), m(in_m), s(in_s), ms(0), us(0) {}
    constexpr Duration(u16 in_h, u16 in_m, u32 in_s, u32 in_ms) : h(in_h), m(in_m), s(in_s), ms(in_ms), us(0) {}
    constexpr Duration(u16 in_h, u16 in_m, u32 in_s, u32 in_ms, u64 in_us) : h(in_h), m(in_m), s(in_s), ms(in_ms), us(in_us) {}

    constexpr static u64 to_usecs(const Duration &duration) noexcept
    {
        return duration.us + duration.ms * 1000 + duration.s * 1000000 + duration.m * 60000000 + duration.h * 3600000000;
    }

    constexpr static u64 to_msecs(const Duration &duration) noexcept
    {
        return duration.us / 1000 + duration.ms + duration.s * 1000 + duration.m * 60 * 1000 + duration.h * 60 * 60 * 1000;
    }

    constexpr static u64 to_secs(const Duration &duration) noexcept
    {
        return duration.us / (1000 * 1000) + duration.ms / 1000 + duration.s + duration.m * 60 + duration.h * 60 * 60;
    }

    constexpr bool operator==(const Duration &other) const { return h == other.h && m == other.m && s == other.s && ms == other.ms && us == other.us; }

    constexpr bool operator!=(const Duration &other) const { return h != other.h || m != other.m || s != other.s || ms != other.ms || us != other.us; }

    constexpr bool operator>(const Duration &other) const
    {
        const auto calculate_total_us = [](const Duration &duration)
        {
            const auto hour_us = duration.h * 60 * 60 * 1000 * 1000;
            const auto minutes_us = duration.m * 60 * 1000 * 1000;
            const auto seconds_us = duration.s * 1000 * 1000;
            const auto milliseconds_us = duration.ms * 1000;
            return hour_us + minutes_us + seconds_us + milliseconds_us + duration.us;
        };
        return calculate_total_us(*this) > calculate_total_us(other);
    }

    constexpr bool operator<(const Duration &other) const
    {
        const auto calculate_total_us = [](const Duration &duration)
        {
            const auto hour_us = duration.h * 60 * 60 * 1000 * 1000;
            const auto minutes_us = duration.m * 60 * 1000 * 1000;
            const auto seconds_us = duration.s * 1000 * 1000;
            const auto milliseconds_us = duration.ms * 1000;
            return hour_us + minutes_us + seconds_us + milliseconds_us + duration.us;
        };
        return calculate_total_us(*this) < calculate_total_us(other);
    }

    constexpr bool operator<=(const Duration &other) const
    {
        const auto calculate_total_us = [](const Duration &duration)
        {
            const auto hour_us = duration.h * 60 * 60 * 1000 * 1000;
            const auto minutes_us = duration.m * 60 * 1000 * 1000;
            const auto seconds_us = duration.s * 1000 * 1000;
            const auto milliseconds_us = duration.ms * 1000;
            return hour_us + minutes_us + seconds_us + milliseconds_us + duration.us;
        };
        return calculate_total_us(*this) <= calculate_total_us(other);
    }

    constexpr bool operator>=(const Duration &other) const
    {
        const auto calculate_total_us = [](const Duration &duration)
        {
            const auto hour_us = duration.h * 60 * 60 * 1000 * 1000;
            const auto minutes_us = duration.m * 60 * 1000 * 1000;
            const auto seconds_us = duration.s * 1000 * 1000;
            const auto milliseconds_us = duration.ms * 1000;
            return hour_us + minutes_us + seconds_us + milliseconds_us + duration.us;
        };
        return calculate_total_us(*this) >= calculate_total_us(other);
    }

    constexpr Duration operator+(const Duration &other) const noexcept
    {
        u64 total_us = us + ms * 1000 + s * 1000000 + m * 60000000 + h * 3600000000;
        u64 other_total_us = other.us + other.ms * 1000 + other.s * 1000000 + other.m * 60000000 + other.h * 3600000000;

        u64 result_us = total_us + other_total_us;
        u64 result_h = static_cast<u64>(result_us / 3600000000);
        result_us %= 3600000000;

        u64 result_m = static_cast<u64>(result_us / 60000000);
        result_us %= 60000000;

        u64 result_s = static_cast<u64>(result_us / 1000000);
        result_us %= 1000000;

        u64 result_ms = static_cast<u64>(result_us / 1000);
        result_us %= 1000;

        u64 result_us_remaining = result_us;
        return Duration(result_h, result_m, result_s, result_ms, result_us_remaining);
    };

    constexpr Duration operator-(const Duration &other) const noexcept
    {
        u64 total_us = us + ms * 1000 + s * 1000000 + m * 60000000 + h * 3600000000;
        u64 other_total_us = other.us + other.ms * 1000 + other.s * 1000000 + other.m * 60000000 + other.h * 3600000000;

        if (other_total_us > total_us)
        {
            return Duration(0, 0, 0, 0, 0);
        }

        u64 result_us = total_us - other_total_us;
        u64 result_h = static_cast<u64>(result_us / 3600000000);
        result_us %= 3600000000;
        u64 result_m = static_cast<u64>(result_us / 60000000);
        result_us %= 60000000;
        u64 result_s = static_cast<u64>(result_us / 1000000);
        result_us %= 1000000;
        u64 result_ms = static_cast<u64>(result_us / 1000);
        result_us %= 1000;
        u64 result_us_remaining = result_us;
        return Duration(result_h, result_m, result_s, result_ms, result_us_remaining);
    }

    constexpr Duration operator=(u64 in_time_us) noexcept
    {
        return {0, 0, 0, 0, in_time_us};
    }

    constexpr u64 get_in_msecs() const noexcept
    {
        return (h * 60 * 60 * 1000) + (m * 60 * 1000) + (s * 1000) + ms + (us / 1000);
    }

    constexpr Duration hours(const Duration in_duration)
    {
        h = in_duration.h;
        return *this;
    }
    constexpr Duration hours(const u64 in_duration)
    {
        h = in_duration;
        return *this;
    }

    constexpr Duration minutes(const Duration in_duration)
    {
        m = in_duration.m;
        return *this;
    }
    constexpr Duration minutes(const u64 in_duration)
    {
        m = in_duration;
        return *this;
    }

    constexpr Duration seconds(const Duration in_duration)
    {
        s = in_duration.s;
        return *this;
    }
    constexpr Duration seconds(const u64 in_duration)
    {
        s = in_duration;
        return *this;
    }

    constexpr Duration milliseconds(const Duration in_duration)
    {
        ms = in_duration.ms;
        return *this;
    }
    constexpr Duration milliseconds(const u64 in_duration)
    {
        ms = in_duration;
        return *this;
    }

    constexpr Duration microseconds(const Duration in_duration)
    {
        us = in_duration.us;
        return *this;
    }
    constexpr Duration microseconds(const u64 in_duration)
    {
        us = in_duration;
        return *this;
    }
};
#else
typedef struct
{
    u16 h;
    u8 m;
    u8 s;
    u16 ms;
    u64 us;
} Duration;

#define DURATION() (Duration){0, 0, 0, 0, 0}
#define DURATION_HRS(hrs) (Duration){hrs, 0, 0, 0, 0}
#define DURATION_MINS(hrs, mins) (Duration){hrs, mins, 0, 0, 0}
#define DURATION_SECS(hrs, mins, secs) (Duration){hrs, mins, secs, 0, 0}
#define DURATION_MSECS(hrs, mins, secs, msecs) (Duration){hrs, mins, secs, msecs, 0}
#define DURATION_USECS(hrs, mins, secs, msecs, usecs) \
    (Duration) { hrs, mins, secs, msecs, usecs }
#define DURATION_EQ(x, y) (x.h == y.h) && (x.m == y.m) && (x.s == y.s) && (x.ms == y.ms) && (x.us == y.us)
#define DURATION_NEQ(x, y) (x.h != y.h) || (x.m != y.m) || (x.s != y.s) || (x.ms != y.ms) || (x.us != y.us)
u64 calculate_usec(Duration duration)
{
    const auto hour_us = duration.h * 60 * 60 * 1000 * 1000;
    const auto minutes_us = duration.m * 60 * 1000 * 1000;
    const auto seconds_us = duration.s * 1000 * 1000;
    const auto milliseconds_us = duration.ms * 1000;
    return hour_us + minutes_us + seconds_us + milliseconds_us + duration.us;
}
#define DURATION_GREATER_THAN_EQ(x, y) calculate_usec(x) >= calculate_usec(y)
#define DURATION_GREATER_THAN(x, y) calculate_usec(x) > calculate_usec(y)
#define DURATION_LESS_THAN_EQ(x, y) calculate_usec(x) <= calculate_usec(y)
#define DURATION_LESS_THAN(x, y) calculate_usec(x) < calculate_usec(y)
#define DURATION_ADD(x, y)                                                                                               \
    {                                                                                                                    \
        u64 total_us = us + ms * 1000 + s * 1000000 + m * 60000000 + h * 3600000000;                                     \
        u64 other_total_us = other.us + other.ms * 1000 + other.s * 1000000 + other.m * 60000000 + other.h * 3600000000; \
                                                                                                                         \
        u64 result_us = total_us + other_total_us;                                                                       \
        u64 result_h = result_us / 3600000000;                                                                           \
        result_us %= 3600000000;                                                                                         \
                                                                                                                         \
        u64 result_m = result_us / 60000000;                                                                             \
        result_us %= 60000000;                                                                                           \
                                                                                                                         \
        u64 result_s = result_us / 1000000;                                                                              \
        result_us %= 1000000;                                                                                            \
                                                                                                                         \
        u64 result_ms = result_us / 1000;                                                                                \
        result_us %= 1000;                                                                                               \
                                                                                                                         \
        u64 result_us_remaining = result_us;                                                                             \
        return {result_h, result_m, result_s, result_ms, result_us_remaining};                                           \
    }
#define DURATION_SUB(x, y)                                                                                               \
    {                                                                                                                    \
        u64 total_us = us + ms * 1000 + s * 1000000 + m * 60000000 + h * 3600000000;                                     \
        u64 other_total_us = other.us + other.ms * 1000 + other.s * 1000000 + other.m * 60000000 + other.h * 3600000000; \
                                                                                                                         \
        if (other_total_us > total_us)                                                                                   \
        {                                                                                                                \
            return {0, 0, 0, 0, 0};                                                                                      \
        }                                                                                                                \
                                                                                                                         \
        u64 result_us = total_us - other_total_us;                                                                       \
        u64 result_h = result_us / 3600000000;                                                                           \
        result_us %= 3600000000;                                                                                         \
        u64 result_m = result_us / 60000000;                                                                             \
        result_us %= 60000000;                                                                                           \
        u64 result_s = result_us / 1000000;                                                                              \
        result_us %= 1000000;                                                                                            \
        u64 result_ms = result_us / 1000;                                                                                \
        result_us %= 1000;                                                                                               \
        u64 result_us_remaining = result_us;                                                                             \
        return Duration(result_h, result_m, result_s, result_ms, result_us_remaining);                                   \
    }
#endif

#if __has_include(<freertos/FreeRTOS.h>)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#ifdef __cplusplus
constexpr void delay_ms(Duration duration) { vTaskDelay(pdMS_TO_TICKS(Duration::to_msecs(duration))); }
constexpr void delay_s(Duration duration) { vTaskDelay(pdMS_TO_TICKS(Duration::to_msecs(duration))); }
#else
#endif
#endif

#define MAC_ADDRESS_BUFFER_LENGTH 6
#define IP_ADDRESS_STRING_BUFFER_LENGTH 17
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

#if ESP_PLATFORM && CONFIG_SPIRAM
#define omega_psmalloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM)
#define omega_psfree(ptr)    \
    do                       \
    {                        \
        heap_caps_free(ptr); \
        ptr = NULL           \
    } while (0)
#else
#define omega_psmalloc(size) NULL
#define omega_psfree(ptr)
#endif

#define omega_malloc(size) malloc(size)
#define omega_realloc(prev_ptr, new_size) realloc(prev_ptr, new_size)
#define omega_free(ptr) \
    do                  \
    {                   \
        free(ptr);      \
        ptr = NULL;     \
    } while (0)

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

typedef enum
{
    eSUCCESS,
    eFAILED,
    eUNKNOWN,
    eTIMEOUT,
    eNOT_INITED,
    eALREADY_INITED,
    eNOT_STARTED,
    eALREADY_STARTED,
    /// @brief Indicates API misuse of using invalid `FileSystemOpenMode` in `OmegaFileSystemController_open_file()`
    eFSC_INVALID_OPENMODE,
    /// @brief Indicates failure fir to invalid parameters
    eFSC_INVALID_PARAMETERS,
    /// @brief Indicates a failure "File Not existing on the file system" when calling `OmegaFileSystemController_open_file()` with READING only
    eFSC_FILE_NOT_EXIST,
    /// @brief Indicates a API misuse of invalid parameter of type FileHandle being received to functions
    eFSC_FILE_HANDLE_NOT_EXIST,
    /// @brief Indicates failure due to not having enough heap memory needed to allocate for the operation
    eFSC_NO_MEM,
    /// @brief Indicates a failure during file writing operation. All the content were no written to the file
    eFSC_INCOMPLETE_FILE_WRITE,
    /// @brief Indicates the end of file reading a file
    eFSC_END_OF_FILE,
    /// @brief //!TODO: Implement the usage of this inside `OmegaFileSystemController_open_file()`
    eFSC_FILE_ALREADY_OPENED,
} OmegaStatus;

#define OMEGA_GPIO_PORT_NC NULL
#define OMEGA_GPIO_PIN_NC -1
#ifdef ESP_PLATFORM
#define OMEGA_GPIO_NC ((OmegaGPIO_t){.pin = OMEGA_GPIO_PIN_NC})
#else
#define OMEGA_GPIO_NC ((OmegaGPIO_t){.port = OMEGA_GPIO_PORT_NC, .pin = OMEGA_GPIO_PIN_NC})
#endif
struct OmegaGPIO
{
#ifndef ESP_PLATFORM
    void *port;
#endif
    u32 pin;
    bool operator==(OmegaGPIO other) const
    {
        if (other.pin == pin)
            return true;
        return false;
    }
};

#if ESP_PLATFORM
#include <esp_random.h>
#define RAND() (esp_random() & 0x7fff)
#else
#include <stdlib.h>
#define RAND() (rand() & 0x7fff)
#endif

OmegaHandle OmegaUtilityDriver_generate_handle();
bool OmegaUtilityDriver_delete_handle(OmegaHandle);

#define UUID2ARRAY(uuid)                                  \
    (uint8_t[])                                           \
    {                                                     \
        16 * CHAR2INT(uuid[34]) + CHAR2INT(uuid[35]),     \
            16 * CHAR2INT(uuid[32]) + CHAR2INT(uuid[33]), \
            16 * CHAR2INT(uuid[30]) + CHAR2INT(uuid[31]), \
            16 * CHAR2INT(uuid[28]) + CHAR2INT(uuid[29]), \
            16 * CHAR2INT(uuid[26]) + CHAR2INT(uuid[27]), \
            16 * CHAR2INT(uuid[24]) + CHAR2INT(uuid[25]), \
            16 * CHAR2INT(uuid[21]) + CHAR2INT(uuid[22]), \
            16 * CHAR2INT(uuid[19]) + CHAR2INT(uuid[20]), \
            16 * CHAR2INT(uuid[16]) + CHAR2INT(uuid[17]), \
            16 * CHAR2INT(uuid[14]) + CHAR2INT(uuid[15]), \
            16 * CHAR2INT(uuid[11]) + CHAR2INT(uuid[12]), \
            16 * CHAR2INT(uuid[9]) + CHAR2INT(uuid[10]),  \
            16 * CHAR2INT(uuid[6]) + CHAR2INT(uuid[7]),   \
            16 * CHAR2INT(uuid[4]) + CHAR2INT(uuid[5]),   \
            16 * CHAR2INT(uuid[2]) + CHAR2INT(uuid[3]),   \
            16 * CHAR2INT(uuid[0]) + CHAR2INT(uuid[1]),   \
    }

#define UUID2LIST(uuid)                               \
    16 * CHAR2INT(uuid[34]) + CHAR2INT(uuid[35]),     \
        16 * CHAR2INT(uuid[32]) + CHAR2INT(uuid[33]), \
        16 * CHAR2INT(uuid[30]) + CHAR2INT(uuid[31]), \
        16 * CHAR2INT(uuid[28]) + CHAR2INT(uuid[29]), \
        16 * CHAR2INT(uuid[26]) + CHAR2INT(uuid[27]), \
        16 * CHAR2INT(uuid[24]) + CHAR2INT(uuid[25]), \
        16 * CHAR2INT(uuid[21]) + CHAR2INT(uuid[22]), \
        16 * CHAR2INT(uuid[19]) + CHAR2INT(uuid[20]), \
        16 * CHAR2INT(uuid[16]) + CHAR2INT(uuid[17]), \
        16 * CHAR2INT(uuid[14]) + CHAR2INT(uuid[15]), \
        16 * CHAR2INT(uuid[11]) + CHAR2INT(uuid[12]), \
        16 * CHAR2INT(uuid[9]) + CHAR2INT(uuid[10]),  \
        16 * CHAR2INT(uuid[6]) + CHAR2INT(uuid[7]),   \
        16 * CHAR2INT(uuid[4]) + CHAR2INT(uuid[5]),   \
        16 * CHAR2INT(uuid[2]) + CHAR2INT(uuid[3]),   \
        16 * CHAR2INT(uuid[0]) + CHAR2INT(uuid[1])

#define UUID128(name, ...) \
    uint8_t name[16] = {__VA_ARGS__};

#ifdef __cplusplus
struct CHeapDeleter
{
    void operator()(void *ptr) const
    {
        omega_free(ptr);
    }
};
#endif

#ifdef __cplusplus
template <typename T>
inline T map(T x, T in_min, T in_max, T out_min, T out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
#endif

#ifdef __cplusplus
#if __has_include(<cJSON.h>) || __has_include(<cJSON/cJSON.h>)
#if __has_include(<cJSON.h>)
#include <cJSON.h>
#endif
#if __has_include(<cJSON/cJSON.h>)
#include <cJSON/cJSON.h>
#endif
struct cJSONDeleter
{
    void operator()(cJSON *ptr) const
    {
        cJSON_Delete(ptr);
    }
};
#endif
#endif

#ifdef __cplusplus
template <size_t arena_size>
class StaticArenaAllocator
{
public:
    template <typename T>
    T *allocate(size_t count = 1) noexcept
    {
        const size_t required_memory = count * sizeof(T);
        if (used_memory + required_memory > arena_size)
        {
            OMEGA_LOGE("Not enough space in arena");
            return nullptr;
        }
        T *ptr = reinterpret_cast<T *>(arena + used_memory);
        used_memory += required_memory;
        return ptr;
    }

    void reset() noexcept { used_memory = 0; }
    size_t remaining() const noexcept { return arena_size - used_memory; }

private:
    size_t used_memory = 0;
    alignas(1) u8 arena[arena_size];
};

#else
typedef struct
{
    uint8_t *arena;
    size_t size;
    size_t used;
} StaticArenaAllocator;

#define INIT_ARENA(allocator, buffer)      \
    do                                     \
    {                                      \
        (allocator).arena = (buffer);      \
        (allocator).size = sizeof(buffer); \
        (allocator).used = 0;              \
    } while (0)
#define ARENA_ALLOC(allocator, type, count) \
    ((type *)arenaAllocate(&(allocator), sizeof(type) * (count)))

void *arenaAllocate(StaticArenaAllocator *allocator, size_t size)
{
    if (allocator->used + size > allocator->size)
    {
        OMEGA_LOGE("Arena overflow: not enough memory!");
        return NULL;
    }
    void *ptr = allocator->arena + allocator->used;
    allocator->used += size;
    return ptr;
}
void resetArenaAllocator(StaticArenaAllocator *allocator) { allocator->used = 0; }
size_t remainingMemory(StaticArenaAllocator *allocator) { return allocator->size - allocator->used; }
#endif
