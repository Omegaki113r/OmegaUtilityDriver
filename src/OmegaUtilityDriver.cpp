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

#include "OmegaUtilityDriver.hpp"
#include <algorithm>
#include <vector>

namespace Omega
{
    namespace UtilityDriver
    {
        constexpr internal u8 MAX_ITERATION_AMOUNT = 100;
        internal std::vector<OmegaHandle> _s_handles{};

        OmegaHandle generate_handle()
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
            OMEGA_LOGV("Generated Handle: %llu, Vector Size: %d", generated_handle, _s_handles.size());
            return generated_handle;
        }

        bool delete_handle(OmegaHandle in_handle)
        {
            bool ret = false;
            if (auto iterator = std::ranges::find(_s_handles, in_handle); iterator != _s_handles.end())
            {
                _s_handles.erase(iterator);
                ret = true;
                goto response;
            }
        response:
            OMEGA_LOGV("Deleting Handle: %llu, Vector Size: %d", in_handle, _s_handles.size());
            return ret;
        }
    } // namespace UtilityDriver
} // namespace Omega
