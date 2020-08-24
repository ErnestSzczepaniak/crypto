#include "test.h"
#include "faes.h"
#include "crypto.h"
#include <fstream>
#include "string.h"

bool open(std::fstream & stream, const char * path)
{
    stream.open(path, std::ios::out | std::ios::in);

    if (stream.is_open() == true) return true;

    stream.open(path, std::ios::out | std::ios::in | std::ios::trunc);

    if (stream.is_open() == false) return false;

    return true;
}

void read(std::fstream & stream, unsigned char * to, int size)
{
    stream.seekg(0, std::ios::beg);
    stream.read((char *) to, size);
    stream.flush();
}

void write(std::fstream & stream, unsigned char * from, int size)
{
    stream.seekp(0, std::ios::beg);
    stream.write((char *) from, size);
    stream.flush();
}

void close(std::fstream & stream)
{
    stream.close();
}

TEST_CASE("pop")
{
    static constexpr auto size_bitstream = 2159408;

    unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
    unsigned char iv[16] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    unsigned int expanded_encrypt[60];
    unsigned int expanded_decrypt[60];

    unsigned char plaintext[size_bitstream];
    unsigned char ciphertext[size_bitstream];
    unsigned char decrypted[size_bitstream];

    std::fstream stream_plaintext;
    std::fstream stream_ciphertext;

    open(stream_plaintext, "/home/en2/Documents/programs/crypto/bitstream.rbf");
    open(stream_ciphertext, "/home/en2/Documents/programs/crypto/bitstream_encrypted.rbf");

    read(stream_plaintext, plaintext, size_bitstream);

    faes_expand(key, expanded_encrypt, expanded_decrypt);

    faes_cbc_encrypt(plaintext, ciphertext, key, sizeof(plaintext), iv);
    faes_cbc_decrypt(ciphertext, decrypted, key, sizeof(plaintext), iv);

    auto res = memcmp(plaintext, decrypted, size_bitstream);

    REQUIRE(res == 0);

    write(stream_ciphertext, ciphertext, size_bitstream);

    // crypto::aes::cbc::decrypt(plaintext, ciphertext, sizeof(plaintext), key, 256, iv);
    //faes_cbc_decrypt(ciphertext, decrypted, expanded_decrypt);
}