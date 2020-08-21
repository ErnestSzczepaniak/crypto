#ifndef _faes_h
#define _faes_h

/**
 * @file	faes.h
 * @author	en2
 * @date	21-08-2020
 * @brief	
 * @details	
**/

void faes_expand(unsigned char * input, unsigned int * encrypt, unsigned int * decrypt);
void faes_block_encrypt(unsigned char * input, unsigned char * output, unsigned int * key);
void faes_block_decrypt(unsigned char * input, unsigned char * output, unsigned int * key);
void faes_encrypt(unsigned char * input, unsigned char * output, unsigned char * key, int size);

#endif /* define: faes_h */