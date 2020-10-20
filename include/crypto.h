#ifndef _crypto_h
#define _crypto_h

/**
 * @file	crypto.h
 * @author	en2
 * @date	08-06-2020
 * @brief	
 * @details	
**/

// aes - data wyrownane zawsze do 16 bajtow, klucz 128, 192, 256 bitow

namespace crypto::aes::ecb
{

void encrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size);
void decrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size);

}; /* namespace: crypto::aes::ecb */

namespace crypto::aes::cbc
{

void encrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size_key, unsigned char * iv);
void decrypt(unsigned char * input, unsigned char * output, int size_data, unsigned char * key, int size_key, unsigned char * iv);

}; /* namespace: crypto::aes::cbc */

namespace crypto::faes::ecb
{

void encrypt(unsigned char * input, unsigned char * output, int size, unsigned char * key);
void decrypt(unsigned char * input, unsigned char * output, int size, unsigned char * key);

}; /* namespace: crypto::faes::ecb */

namespace crypto::faes::cbc
{

void encrypt(unsigned char * input, unsigned char * output, int size, unsigned char * key, unsigned char * iv);
void decrypt(unsigned char * input, unsigned char * output, int size, unsigned char * key, unsigned char * iv);

}; /* namespace: crypto::faes::cbc */

namespace crypto
{

void sha_1(unsigned char * input, unsigned char * output, int size);
void sha_256(unsigned char * input, unsigned char * output, int size);
unsigned int xxhash(unsigned char * input, int size, unsigned int seed = 0);

}; /* namespace: crypto */

#endif /* define: crypto_h */