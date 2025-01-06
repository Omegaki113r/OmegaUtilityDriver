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

#pragma once

#include <stdint.h>

#if ESP_PLATFORM
#include <esp_heap_caps.h>
#endif

#ifndef __FILE_NAME__
#define __FILE_NAME__ __FILE__
#endif

#define US_TO_MS(x) (x/1000)
#define US_TO_S(x) (x/(1000*1000))
#define S_TO_MS(x) (x*1000)

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

#define OMEGA_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define OMEGA_MIN(x, y) (((x) < (y)) ? (x) : (y))

#define internal static
#ifndef UNUSED
#define UNUSED(arg) (void)arg
#endif

#if ESP_PLATFORM
#define PERIPHERAL_CORE 0
#define APP_CORE 1
#endif

#if __has_include(<freertos/FreeRTOS.h>)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#define delay_ms(x) vTaskDelay(pdMS_TO_TICKS(x))
#define delay_s(x) vTaskDelay(pdMS_TO_TICKS(x * 1000))

#ifdef __cplusplus

constexpr int operator"" _ms(unsigned long long in_milliseconds)
{
    return in_milliseconds;
}

constexpr int operator"" _s(unsigned long long in_seconds)
{
    return S_TO_MS(in_seconds);
}

inline void delay(unsigned long long in_delay)
{
    delay_ms(in_delay);
}

#endif
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

#if ESP_PLATFORM && CONFIG_SPIRAM
#define omega_psmalloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM)
#else
#define omega_psmalloc(size) NULL
#endif

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
    typedef uint32_t u32;
    typedef int32_t i32;

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

#define OMEGA_BIT(x) (1<<x)
#define OMEGA_LSHIFT(x,count) (x>>count)
#define OMEGA_RSHIFT(x,count) (x<<count)
#define OMEGA_BIT_SET(x, bit) (x|OMEGA_BIT(bit))
#define OMEGA_BIT_CLEAR(x,bit) (x & ~(OMEGA_BIT(bit)))
#define OMEGA_BIT_CHECK(x,bit) (x & (1<<bit))

#ifdef __cplusplus
enum class
#else
typedef enum
#endif
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
}OmegaStatus;

#define OMEGA_GPIO_PORT_NC NULL
#define OMEGA_GPIO_PIN_NC -1
#define OMEGA_GPIO_NC ((OmegaGPIO_t){.port = NULL,.pin = -1})
typedef struct
{
    void* port;
    int32_t pin;
}OmegaGPIO_t;

#if ESP_PLATFORM
#include <esp_random.h>
#define RAND() (esp_random() & 0x7fff)
#else
#include <stdlib.h>
#define RAND() (rand() & 0x7fff)
#endif

typedef u64 OmegaHandle;

struct CHeapDeleter {
    void operator()(void* ptr) const {
        omega_free(ptr);
    }
};

#if __has_include(<cJSON.h>) || __has_include(<cJSON/cJSON.h>)
#if __has_include(<cJSON.h>)
    #include <cJSON.h>
#endif
#if __has_include(<cJSON/cJSON.h>)
    #include <cJSON/cJSON.h>
#endif
struct cJSONDeleter {
    void operator()(cJSON* ptr) const {
        cJSON_Delete(ptr);
    }
};
#endif

OmegaHandle OmegaUtilityDriver_generate_handle();
bool OmegaUtilityDriver_delete_handle(OmegaHandle);

#define ARENA_SIZE 1024 * 1024  // 1MB arena size
typedef struct {
    char *arena_start;   // Pointer to the beginning of the arena
    char *arena_end;     // Pointer to the end of the arena
    char *current_pos;   // Pointer to the current position for the next allocation
} Arena;

template <std::size_t pSZ, std::size_t cSZ>
class MemoryPool {
public:
    // The actual memory pool (raw storage)
    uint8_t pool[pSZ];

    // Free list pointer, initially pointing to the first chunk
    void* free_list;

    // Constructor: initializes the pool and the free list
    MemoryPool() {
        static_assert(pSZ % cSZ == 0, "poll size must be a multiple of chunk size");

        free_list = static_cast<void*>(pool);
        uint8_t* ptr = pool;

        // Initialize free list: each chunk points to the next one
        std::size_t num_chunks = pSZ / cSZ;
        for (std::size_t i = 0; i < num_chunks - 1; ++i) {
            *(reinterpret_cast<void**>(ptr)) = ptr + cSZ;
            ptr += cSZ;
        }
        *(reinterpret_cast<void**>(ptr)) = nullptr;  // Last chunk points to nullptr (end of list)
    }

    // Allocate memory for multiple objects (batch allocation)
    void* allocate(std::size_t count=1) {
        if (free_list == nullptr) {
            OMEGA_LOGE("Error: No memory left in the pool.");
            return nullptr;
        }

        // Calculate the total size required for the requested number of objects
        std::size_t total_size = count * cSZ;

        if (total_size > pSZ) {
            OMEGA_LOGE("Error: Not enough memory for the requested allocation.");
            return nullptr;
        }

        // Allocate contiguous blocks of memory
        void* ptr = free_list;
        void* next_free = ptr;
        for (std::size_t i = 1; i < count; ++i) {
            next_free = *(reinterpret_cast<void**>(next_free));
        }

        // Update the free list
        free_list = *(reinterpret_cast<void**>(next_free));

        return ptr;
    }

    // Free a contiguous block of memory
    void free(void* ptr, std::size_t count=1) {
        // Return the chunk to the free list
        void* next_free = ptr;
        for (std::size_t i = 0; i < count; ++i) {
            void* current = next_free;
            next_free = *(reinterpret_cast<void**>(current));
            *(reinterpret_cast<void**>(current)) = free_list;
            free_list = current;
        }
    }
};
