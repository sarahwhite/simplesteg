#ifndef DECRYPT_H
#define DECRYPT_H

#include <stdio.h>
#include "encrypt.h"

unsigned char bits_to_byte(char* str);

char* get_data(SImage img, int dataLength);
int get_data_length(SImage img);
int find_header(SImage img);
void decrypt(char* filename);

#endif
