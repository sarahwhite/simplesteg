#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SPixel;

typedef struct
{
    SPixel* pixels;
    
    unsigned width;
    unsigned height;
    unsigned char* rawData;
} SImage;

void save_image(char* filename, SImage image);
void close_image(SImage image);
SImage load_image(char* filename);

#endif
