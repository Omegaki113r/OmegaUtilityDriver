/**
 * @file OmegaUtilityDriver.c
 * @author Omegaki113r
 * @date Tuesday, 2nd July 2024 1:01:18 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaUtilityDriver
 * File Name: OmegaUtilityDriver.c
 * File Created: Tuesday, 2nd July 2024 1:01:18 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Tuesday, 2nd July 2024 1:08:21 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include "OmegaUtilityDriver.h"


#define MAX_ITERATION_AMOUNT 100

#if ESP_PLATFORM && OMEGA_ESP_HARDWARE_GEN
#include <esp_random.h>
#define RAND() (esp_random() & 0x7fff)
#elseif OMEGA_STC_RANDOM_GEN
#define RAND() (crand() & 0x7fff)
#else
#define RAND() (rand() & 0x7fff)
#endif

#define i_TYPE Vector, u64
#include <vec.h>

internal Vector handles;

uint64_t OmegaHandleGenerator_create_handle()
{
    u64 iteration_count = 0;
    u64 generated_handle = 0;
    do
    {
    regenerate_handle:
        generated_handle = ((u64)RAND() << 48) ^ ((u64)RAND() << 35) ^ ((u64)RAND() << 22) ^
                           ((u64)RAND() << 9) ^ ((u64)RAND() >> 4);
        c_foreach(handle_iterator, Vector, handles)
        {
            if (generated_handle == *handle_iterator.ref)
                goto regenerate_handle;
        }
    } while (generated_handle <= 0 && iteration_count++ < MAX_ITERATION_AMOUNT);
    if (iteration_count >= MAX_ITERATION_AMOUNT)
    {
        OMEGA_LOGE("Unable to create valid handle");
        generated_handle = 0;
        goto response;
    }
    Vector_value *inserted_handle = Vector_push_back(&handles, generated_handle);
    if (inserted_handle == NULL)
    {
        OMEGA_HANDLE_GENERATOR_LOGE("Inserting handle to vector failed");
        generated_handle = 0;
    }
response:
    OMEGA_LOGV("Generated Handle: %llu, Vector Size: %d", generated_handle, Vector_size(&handles));
    return generated_handle;
}

bool OmegaHandleGenerator_delete_handle(uint64_t in_handle)
{
    bool ret = false;
    c_foreach(handle_iterator, Vector, handles)
    {
        if (*handle_iterator.ref == in_handle)
        {
            Vector_erase_at(&handles, handle_iterator);
            ret = true;
            goto response;
        }
    }
response:
    OMEGA_LOGV("Deleting Handle: %llu, Vector Size: %d", in_handle, Vector_size(&handles));
    return ret;
}
