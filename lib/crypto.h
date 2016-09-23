//
// Created by paultpt on 21/06/16.
//

#ifndef GR_ADSB_SEND_SIGNATURE_H
#define GR_ADSB_SEND_SIGNATURE_H

#include <stdio.h>
#include <string.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/hmac.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>


//The legnth in bits of the hash appended to the ADS-B packet. This should be a multiple of 8 ( we work with bytes)
#define HASH_LEGNTH 16
#define SIGN_FREQ 3
#define  KEY_FREQ 30
//Size of the signature in bytes
#define SIGLENGTH 40
#define NUMKEYS 5760

const unsigned int POLY=0xFFF409;
uint32_t modesChecksum(unsigned char *msg, int bytes, unsigned char r_crc[3]);

class Crypto
{

public:
    Crypto();
    ~Crypto();

    //This should be generated by the CA. For test purposes
    static  void gen_signature(const unsigned char addr[3], const unsigned  char sync, const unsigned char key[32], unsigned char sig[39+SIGLENGTH]);

    //Each time a new key is generated, we bublish the last one.
    static void publish_key(const unsigned char addr[3], const unsigned char key[32], unsigned char pub_key[39]);

    //Generates the keys from the root key
    static void gen_keys(const unsigned char root_key[32], unsigned char keyskeys[NUMKEYS][32], int nb_keys, unsigned char last_key[32]);


};



/*
const uint32_t modes_checksum_table[112] = {
0x3935ea, 0x1c9af5, 0xf1b77e, 0x78dbbf, 0xc397db, 0x9e31e9, 0xb0e2f0, 0x587178,
0x2c38bc, 0x161c5e, 0x0b0e2f, 0xfa7d13, 0x82c48d, 0xbe9842, 0x5f4c21, 0xd05c14,
0x682e0a, 0x341705, 0xe5f186, 0x72f8c3, 0xc68665, 0x9cb936, 0x4e5c9b, 0xd8d449,
0x939020, 0x49c810, 0x24e408, 0x127204, 0x093902, 0x049c81, 0xfdb444, 0x7eda22,
0x3f6d11, 0xe04c8c, 0x702646, 0x381323, 0xe3f395, 0x8e03ce, 0x4701e7, 0xdc7af7,
0x91c77f, 0xb719bb, 0xa476d9, 0xadc168, 0x56e0b4, 0x2b705a, 0x15b82d, 0xf52612,
0x7a9309, 0xc2b380, 0x6159c0, 0x30ace0, 0x185670, 0x0c2b38, 0x06159c, 0x030ace,
0x018567, 0xff38b7, 0x80665f, 0xbfc92b, 0xa01e91, 0xaff54c, 0x57faa6, 0x2bfd53,
0xea04ad, 0x8af852, 0x457c29, 0xdd4410, 0x6ea208, 0x375104, 0x1ba882, 0x0dd441,
0xf91024, 0x7c8812, 0x3e4409, 0xe0d800, 0x706c00, 0x383600, 0x1c1b00, 0x0e0d80,
0x0706c0, 0x038360, 0x01c1b0, 0x00e0d8, 0x00706c, 0x003836, 0x001c1b, 0xfff409,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};
*/

#endif //GR_ADSB_SEND_SIGNATURE_H