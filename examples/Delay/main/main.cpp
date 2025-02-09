#include <stdio.h>

#include "OmegaUtilityDriver/UtilityDriver.hpp"

Duration duration{0, 0, 5};
Duration duration_s{0, 0, 10};

extern "C" void app_main(void)
{
    for (;;)
    {
        OMEGA_LOGI("delay test ms");
        delay_ms(duration);
        OMEGA_LOGI("delay test s");
        delay_s(duration_s);
    }
}