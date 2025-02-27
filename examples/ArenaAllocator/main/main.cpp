#include <stdio.h>

#include <OmegaUtilityDriver/UtilityDriver.hpp>

StaticArenaAllocator<1000> arena;

extern "C" void app_main(void)
{
    for (;;)
    {
        int *allocated = arena.allocate<int>(10);
        OMEGA_LOGE("Remaining size: %d", arena.remaining());
    }

    Arena arena{};
}
