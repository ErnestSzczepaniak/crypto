#include "crypto.h"

#include "aes.h"
#include "arcfour.h"
#include "base64.h"
#include "blowfish.h"
#include "des.h"
#include "md2.h"
#include "md5.h"
#include "rot-13.h"
#include "sha1.h"
#include "sha256.h"

#define XXH_INLINE_ALL
#include "xxhash.h"

namespace crypto::aes::ecb
{

void encrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size_key)
{
    if (size_key != 128 || size_key != 192 || size_key != 256) return;
    if ((size_data % AES_BLOCK_SIZE) != 0) return;

    WORD key_schedule[60]; // odpowiednio 11, 13 i 15 wordow
    aes_key_setup((const BYTE *)key, key_schedule, size_key);

    auto blocks = size_data / AES_BLOCK_SIZE;

    for (int i = 0; i < blocks; i++)
    {
        aes_encrypt((const BYTE *) input, (BYTE *) output, key_schedule, size_key);

        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
    }
}

void decrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size_key)
{
    if (size_key != 128 || size_key != 192 || size_key != 256) return;
    if ((size_data % AES_BLOCK_SIZE) != 0) return;

    WORD key_schedule[60]; // odpowiednio 11, 13 i 15 wordow
    aes_key_setup((const BYTE *)key, key_schedule, size_key);

    auto blocks = size_data / AES_BLOCK_SIZE;

    for (int i = 0; i < blocks; i++)
    {
        aes_decrypt((const BYTE *) input, (BYTE *) output, key_schedule, size_key);

        input += AES_BLOCK_SIZE;
        output += AES_BLOCK_SIZE;
    }
}

}; /* namespace: crypto::aes::ecb */



//---------------------------------------------| info |---------------------------------------------//

// void c_hash_sha_1(unsigned char * input, unsigned char * output, int size)
// {
//     if ((size % SHA1_BLOCK_SIZE) == 0)
//     {
//         SHA1_CTX ctx;

//         sha1_init(&ctx);
//         sha1_update(&ctx, (const BYTE *) input, size);
//         sha1_final(&ctx, (BYTE *) output);
//     }
// }

// void c_hash_sha_256(unsigned char * input, unsigned char * output, int size)
// {
//     if ((size % SHA256_BLOCK_SIZE) == 0)
//     {
//         SHA256_CTX ctx;

//         sha256_init(&ctx);
//         sha256_update(&ctx, (const BYTE *) input, size);
//         sha256_final(&ctx, (BYTE *) output);
//     }
// }

// unsigned int c_hash_xxhash_32(void * input, int size, unsigned int seed)
// {
//     XXH32_state_t state;

//     XXH32_reset(&state, seed);
//     XXH32_update(&state, input, size);
//     return XXH32_digest(&state);
// }