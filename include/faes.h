#ifndef _faes_h
#define _faes_h

/**
 * @file	faes.h
 * @author	en2
 * @date	21-08-2020
 * @brief	
 * @details	
**/

void faes_block_copy(unsigned char * output, unsigned char * input);
void faes_block_xor(unsigned char * input1, unsigned char * input2, unsigned char * output);

void faes_expand(unsigned char * input, unsigned int * encrypt, unsigned int * decrypt);
void faes_block_encrypt(unsigned char * input, unsigned char * output, unsigned int * key);
void faes_block_decrypt(unsigned char * input, unsigned char * output, unsigned int * key);

void faes_ecb_encrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size);
void faes_ecb_decrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size);

void faes_cbc_encrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size, unsigned char * iv);
void faes_cbc_decrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size, unsigned char * iv);

#endif /* define: faes_h */