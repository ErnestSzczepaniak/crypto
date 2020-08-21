#ifdef build_platform_host

#define CATCH_CONFIG_MAIN
#include "build.h"
#include "test.h"

#else

#include "build.h"
#include "faes.h"
#include "string.h"
#include "timer_private.h"
#include "crypto.h"


static constexpr auto blocks = 1024 * 100;
unsigned char ciphertext[16 * blocks];

void fast()
{
    faes_encrypt(nullptr, ciphertext, nullptr, sizeof(ciphertext));
}

void slow()
{
    crypto::aes::ecb::encrypt(nullptr, ciphertext, sizeof(ciphertext), nullptr, 256);
}

template<typename T>
double measure(T function)
{
    timer_private.disable();
    timer_private.load(0xffffffff);
    timer_private.enable();

    auto start = timer_private.counter();

    function();

    auto stop = timer_private.counter();
    auto diff = start - stop;
    auto period = (double)diff / 231e6;
    auto speed = sizeof(ciphertext) / period;

    return (speed / (1024 * 1024));
}

int main()
{
    volatile auto f = measure(fast);

    volatile auto w = measure(slow);


    while(1);
}

#endif
