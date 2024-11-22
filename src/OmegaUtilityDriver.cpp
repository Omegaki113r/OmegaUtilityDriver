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
 * Last Modified: Tuesday, 2nd July 2024 1:08:21 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include <vector>
#include "OmegaUtilityDriver.hpp"

internal std::vector<u64> _s_handles;

u64 OmegaUtilityDriver_generate_handle(){
    return ((u64)RAND() << 48) ^ ((u64)RAND() << 35) ^ ((u64)RAND() << 22) ^
             ((u64)RAND() << 9) ^ ((u64)RAND() >> 4);
}
