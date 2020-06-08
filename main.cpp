#ifdef build_platform_host

#define CATCH_CONFIG_MAIN
#include "build.h"
#include "test.h"

#else

#include "build.h"

int main()
{
    int k = 2;

    while(1);
}

#endif
