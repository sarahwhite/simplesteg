#ifndef ENCRYPT_H
#define ENCRYPT_H

#include "image_tools.h"

#define CI_RED 0
#define CI_GREEN 1
#define CI_BLUE 2
#define CI_ALPHA 3

#define HEADER "<3<3"

unsigned char get_lsb(SImage img, long pixel, int colorIndex);
void set_lsb(SImage img, long pixel, int colorIndex, char flag);
void write_lsb(SImage img, char* data, int index);
unsigned char* data_to_bits(char* data);
void encrypt(char* filename, char* data, char* outfile);

#endif
