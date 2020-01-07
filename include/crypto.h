#ifndef _crypto_h
#define _crypto_h

void c_encrypt_aes_ecb_256(unsigned char * input, unsigned char * output, unsigned char * key, int size);
void c_decrypt_aes_ecb_256(unsigned char * input, unsigned char * output, unsigned char * key, int size);

void c_hash_sha_1(unsigned char * input, unsigned char * output, int size);
void c_hash_sha_256(unsigned char * input, unsigned char * output, int size);

unsigned int c_hash_xxhash_32(void * input, int size, unsigned int seed = 0);

#endif