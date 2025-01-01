/**
 * @file OmegaUtilityDriver.cpp
 * @author Omegaki113r
 * @date Tuesday, 2nd July 2024 1:01:18 pm
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaUtilityDriver
 * File Name: OmegaUtilityDriver.cpp
 * File Created: Tuesday, 2nd July 2024 1:01:18 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Tuesday, 17th December 2024 1:59:27 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include <algorithm>
#include <vector>
#include <cstdio>

#include "OmegaUtilityDriver.hpp"

void __attribute__((constructor)) OmegaLoggingInitialized();

void OmegaLoggingInitialized()
{
    printf("%s\r\n", "Logging Initialized");
}

        constexpr internal u8 MAX_ITERATION_AMOUNT = 100;
        internal std::vector<OmegaHandle> _s_handles{};

        OmegaHandle OmegaUtilityDriver_generate_handle()
        {
            u64 iteration_count = 0;
            u64 generated_handle = 0;
            do
            {
                regenerate_handle:
                    generated_handle = ((u64)RAND() << 48) ^ ((u64)RAND() << 35) ^ ((u64)RAND() << 22) ^
                                       ((u64)RAND() << 9) ^ ((u64)RAND() >> 4);
                if (std::find(_s_handles.begin(), _s_handles.end(), generated_handle) != _s_handles.end())
                {
                    goto regenerate_handle;
                }
            } while (generated_handle <= 0 && iteration_count++ < MAX_ITERATION_AMOUNT);
            if (iteration_count >= MAX_ITERATION_AMOUNT)
            {
                OMEGA_LOGE("Unable to create valid handle");
                generated_handle = 0;
                goto response;
            }
            _s_handles.push_back(generated_handle);
        response:
            // OMEGA_LOGD("Generated Handle: %llu, Vector Size: %d", generated_handle, _s_handles.size());
            return generated_handle;
        }

        bool OmegaUtilityDriver_delete_handle(OmegaHandle in_handle)
        {
            bool ret = false;
            if(0 == in_handle){
                OMEGA_LOGE("Provided Handle is invalid: %lld", in_handle);
                goto response;
            }
            if (auto iterator = std::ranges::find(_s_handles, in_handle); iterator != _s_handles.end())
            {
                _s_handles.erase(iterator);
                ret = true;
                goto response;
            }
        response:
            // OMEGA_LOGD("Deleting Handle: %llu, Vector Size: %d", in_handle, _s_handles.size());
            return ret;
        }


// Initialize the arena with a given size
int arena_init(Arena *arena, size_t size) {
    arena->arena_start = (char *)malloc(size);
    if (arena->arena_start == NULL) {
        return -1;  // Memory allocation failed
    }
    arena->arena_end = arena->arena_start + size;
    arena->current_pos = arena->arena_start;
    return 0;  // Success
}

// Allocate memory from the arena
void *arena_alloc(Arena *arena, size_t size) {
    if (arena->current_pos + size > arena->arena_end) {
        return NULL;  // Not enough space in the arena
    }

    void *block = arena->current_pos;
    arena->current_pos += size;
    return block;
}

// Free the entire arena
void arena_free(Arena *arena) {
    free(arena->arena_start);
    arena->arena_start = NULL;
    arena->arena_end = NULL;
    arena->current_pos = NULL;
}



// Initialize the memory pool
void pool_init(MemoryPool *mp) {
    mp->free_index = 0;  // Initialize free_index to 0 (beginning of the pool)
    mp->free_list = NULL;  // No free chunks initially
}

// Allocate memory from the pool
void *pool_allocate(MemoryPool *mp, size_t size) {
    // Check if the requested size exceeds the chunk size
    if (size > CHUNK_SIZE) {
        printf("Error: Requested size exceeds chunk size.\n");
        return NULL;
    }

    // If there's a free list, take from it
    if (mp->free_list != NULL) {
        void* ptr = mp->free_list;
        mp->free_list = *((void**)ptr);  // Update the free list to the next free chunk
        return ptr;
    }

    // Check if there is enough space left in the pool
    if (mp->free_index + size > POOL_SIZE) {
        printf("Error: Not enough memory in the pool.\n");
        return NULL;
    }

    // Return a pointer to the current free memory and advance the free index
    void *ptr = mp->pool + mp->free_index;
    mp->free_index += size;  // Move the free index forward
    return ptr;
}

// Free a chunk in the pool and add it to the free list
void pool_free(MemoryPool *mp, void *ptr) {
    // Add the freed chunk to the free list
    *((void**)ptr) = mp->free_list;  // Point the freed chunk to the previous free list
    mp->free_list = ptr;  // Update the free list to point to the newly freed chunk
}

