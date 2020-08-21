#ifndef _faes_h
#define _faes_h

/**
 * @file	faes.h
 * @author	en2
 * @date	21-08-2020
 * @brief	
 * @details	
**/

#include "faes_table.h"

static inline void faes_expand(unsigned char * input, unsigned int * encrypt, unsigned int * decrypt)
{
	for (int i = 0; i < 8; i++)
	{
		encrypt[i] = ((input[i * 4 + 0] << 24) | (input[i * 4 + 1] << 16) | (input[i * 4 + 2] << 8) | (input[i * 4 + 3]));
	}

	auto temp = encrypt[7];

	for (int i = 1; i < 7; i++)
	{
		temp = ((temp << 8) | (temp >> 24));
		temp = (faes_sbox[temp >> 24] << 24) | (faes_sbox[temp >> 16 & 0xff] << 16) | (faes_sbox[temp >> 8 & 0xff] << 8) | (faes_sbox[temp & 0xff]);
		temp ^= faes_rcon[i - 1];
		temp ^= encrypt[i * 8 - 8];
		encrypt[i * 8] = temp;

		temp ^= encrypt[i * 8 - 7];
		encrypt[i * 8 + 1] = temp;

		temp ^= encrypt[i * 8 - 6];
		encrypt[i * 8 + 2] = temp;

		temp ^= encrypt[i * 8 - 5];
		encrypt[i * 8 + 3] = temp;

		temp = (faes_sbox[temp >> 24] << 24) | (faes_sbox[temp >> 16 & 0xff] << 16) | (faes_sbox[temp >> 8 & 0xff] << 8) | (faes_sbox[temp & 0xff]);
		temp ^= encrypt[i * 8 - 4];
		encrypt[i * 8 + 4] = temp;

		temp ^= encrypt[i * 8 - 3];
		encrypt[i * 8 + 5] = temp;

		temp ^= encrypt[i * 8 - 2];
		encrypt[i * 8 + 6] = temp;

		temp ^= encrypt[i * 8 - 1];
		encrypt[i * 8 + 7] = temp;
	}

	temp = ((temp << 8) | (temp >> 24));
	temp = (faes_sbox[temp >> 24] << 24) | (faes_sbox[temp >> 16 & 0xff] << 16) | (faes_sbox[temp >> 8 & 0xff] << 8) | (faes_sbox[temp & 0xff]);
	temp ^= faes_rcon[7 - 1];
	temp ^= encrypt[7 * 8 - 8];
	encrypt[7 * 8] = temp;

	temp ^= encrypt[7 * 8 - 7];
	encrypt[7 * 8 + 1] = temp;

	temp ^= encrypt[7 * 8 - 6];
	encrypt[7 * 8 + 2] = temp;

	temp ^= encrypt[7 * 8 - 5];
	encrypt[7 * 8 + 3] = temp;

    for (int i = 0; i < 4; i++)
    {
        decrypt[i] = encrypt[i];
        decrypt[56 + i] = encrypt[56 + i];
    }

    for (int i = 4; i < 56; i++)
    {
        decrypt[i] = faes_td0[faes_sbox[encrypt[i] >> 24]] ^ faes_td1[faes_sbox[encrypt[i] >> 16 & 0xff]] ^ faes_td2[faes_sbox[encrypt[i] >> 8 & 0xff]] ^ faes_td3[faes_sbox[encrypt[i] & 0xff]];
    }
}

static inline void faes_block_encrypt(unsigned char * input, unsigned char * output, unsigned int * key)
{
    unsigned int s[4];

	for (int i = 0; i < 4; i++)
	{
		s[i] = ((input[i * 4 + 0] << 24) | (input[i * 4 + 1] << 16) | (input[i * 4 + 2] << 8) | (input[i * 4 + 3]));
	}

    s[0] ^= key[0];
    s[1] ^= key[1];
    s[2] ^= key[2];
    s[3] ^= key[3];

    for (int i = 1; i < 14; i++)
    {
        auto tmp0 = faes_te0[s[0] >> 24] ^ faes_te1[s[1] >> 16 & 0xff] ^ faes_te2[s[2] >> 8 & 0xff] ^ faes_te3[s[3] & 0xff];
        auto tmp1 = faes_te0[s[1] >> 24] ^ faes_te1[s[2] >> 16 & 0xff] ^ faes_te2[s[3] >> 8 & 0xff] ^ faes_te3[s[0] & 0xff];
        auto tmp2 = faes_te0[s[2] >> 24] ^ faes_te1[s[3] >> 16 & 0xff] ^ faes_te2[s[0] >> 8 & 0xff] ^ faes_te3[s[1] & 0xff];
        auto tmp3 = faes_te0[s[3] >> 24] ^ faes_te1[s[0] >> 16 & 0xff] ^ faes_te2[s[1] >> 8 & 0xff] ^ faes_te3[s[2] & 0xff];

        s[0] = tmp0 ^ key[4 * i];
        s[1] = tmp1 ^ key[4 * i + 1];
        s[2] = tmp2 ^ key[4 * i + 2];
        s[3] = tmp3 ^ key[4 * i + 3];
    }
    
	auto tmp0 = ((faes_sbox[s[0] >> 24] << 24) | (faes_sbox[s[1] >> 16 & 0xff] << 16) | (faes_sbox[s[2] >> 8 & 0xff] << 8) | (faes_sbox[s[3] & 0xff]));
	auto tmp1 = ((faes_sbox[s[1] >> 24] << 24) | (faes_sbox[s[2] >> 16 & 0xff] << 16) | (faes_sbox[s[3] >> 8 & 0xff] << 8) | (faes_sbox[s[0] & 0xff]));
	auto tmp2 = ((faes_sbox[s[2] >> 24] << 24) | (faes_sbox[s[3] >> 16 & 0xff] << 16) | (faes_sbox[s[0] >> 8 & 0xff] << 8) | (faes_sbox[s[1] & 0xff]));
	auto tmp3 = ((faes_sbox[s[3] >> 24] << 24) | (faes_sbox[s[0] >> 16 & 0xff] << 16) | (faes_sbox[s[1] >> 8 & 0xff] << 8) | (faes_sbox[s[2] & 0xff]));

    s[0] = tmp0 ^ key[4 * 14];
    s[1] = tmp1 ^ key[4 * 14 + 1];
    s[2] = tmp2 ^ key[4 * 14 + 2];
    s[3] = tmp3 ^ key[4 * 14 + 3];

    for (int i = 0; i < 4; i++)
    {
        output[i * 4 + 0] = (s[i] >> 24 & 0xff);
        output[i * 4 + 1] = (s[i] >> 16 & 0xff);
        output[i * 4 + 2] = (s[i] >> 8 & 0xff);
        output[i * 4 + 3] = (s[i] & 0xff);
    }
}

static inline void faes_block_decrypt(unsigned char * input, unsigned char * output, unsigned int * key)
{
    unsigned int s[4];

	for (int i = 0; i < 4; i++)
	{
		s[i] = ((input[i * 4 + 0] << 24) | (input[i * 4 + 1] << 16) | (input[i * 4 + 2] << 8) | (input[i * 4 + 3]));
	}  

    s[0] ^= key[56];
    s[1] ^= key[57];
    s[2] ^= key[58];
    s[3] ^= key[59];

    for (int i = 13; i > 0; i--)
    {
        auto tmp0 = faes_td0[s[0] >> 24] ^ faes_td1[s[3] >> 16 & 0xff] ^ faes_td2[s[2] >> 8 & 0xff] ^ faes_td3[s[1] & 0xff];
        auto tmp1 = faes_td0[s[1] >> 24] ^ faes_td1[s[0] >> 16 & 0xff] ^ faes_td2[s[3] >> 8 & 0xff] ^ faes_td3[s[2] & 0xff];
        auto tmp2 = faes_td0[s[2] >> 24] ^ faes_td1[s[1] >> 16 & 0xff] ^ faes_td2[s[0] >> 8 & 0xff] ^ faes_td3[s[3] & 0xff];
        auto tmp3 = faes_td0[s[3] >> 24] ^ faes_td1[s[2] >> 16 & 0xff] ^ faes_td2[s[1] >> 8 & 0xff] ^ faes_td3[s[0] & 0xff];

        s[0] = tmp0 ^ key[4 * i];
        s[1] = tmp1 ^ key[4 * i + 1];
        s[2] = tmp2 ^ key[4 * i + 2];
        s[3] = tmp3 ^ key[4 * i + 3];
    }
    
    auto tmp0 = ((faes_isbox[s[0] >> 24] << 24) | (faes_isbox[s[3] >> 16 & 0xff] << 16) | (faes_isbox[s[2] >> 8 & 0xff] << 8) | (faes_isbox[s[1] & 0xff]));
    auto tmp1 = ((faes_isbox[s[1] >> 24] << 24) | (faes_isbox[s[0] >> 16 & 0xff] << 16) | (faes_isbox[s[3] >> 8 & 0xff] << 8) | (faes_isbox[s[2] & 0xff]));
    auto tmp2 = ((faes_isbox[s[2] >> 24] << 24) | (faes_isbox[s[1] >> 16 & 0xff] << 16) | (faes_isbox[s[0] >> 8 & 0xff] << 8) | (faes_isbox[s[3] & 0xff]));
    auto tmp3 = ((faes_isbox[s[3] >> 24] << 24) | (faes_isbox[s[2] >> 16 & 0xff] << 16) | (faes_isbox[s[1] >> 8 & 0xff] << 8) | (faes_isbox[s[0] & 0xff]));

    s[0] = tmp0 ^ key[0];
    s[1] = tmp1 ^ key[1];
    s[2] = tmp2 ^ key[2];
    s[3] = tmp3 ^ key[3];

    for (int i = 0; i < 4; i++)
    {
        output[i * 4 + 0] = (s[i] >> 24 & 0xff);
        output[i * 4 + 1] = (s[i] >> 16 & 0xff);
        output[i * 4 + 2] = (s[i] >> 8 & 0xff);
        output[i * 4 + 3] = (s[i] & 0xff);
    }
}

static inline void faes_encrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size)
{
    if (size % 16 != 0) return;

    auto blocks = size / 16;
    unsigned int expanded_encrypt[60];
    unsigned int expanded_decrypt[60];

    faes_expand(key, expanded_encrypt, expanded_decrypt);

    for (int i = 0; i < blocks; i++)
    {
        faes_block_encrypt(&input[i * 16], &output[i * 16], expanded_encrypt);
    }
}

#endif /* define: faes_h */