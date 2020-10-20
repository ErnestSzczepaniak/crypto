#include "test.h"
#include "crypto.h"

TEST_CASE("sha256")
{
    unsigned char tx[] = {0x00, 0x01, 0x02, 0x03};
    unsigned char rx[32];

    crypto::sha_256(tx, rx, 4);

}
