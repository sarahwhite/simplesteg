#include "encrypt.h"

unsigned char get_lsb(SImage img, long pixel, int colorIndex)
{
    long index = (pixel * sizeof(SPixel)) + colorIndex;
    unsigned char lsb = img.rawData[index] & 0x01;
    
    return lsb;
}

void set_lsb(SImage img, long pixel, int colorIndex, char bit)
{
    long index = (pixel * sizeof(SPixel)) + colorIndex;
    img.rawData[index] &= 0xFE;
    img.rawData[index] ^= bit;
    
    // Update the SPixel struct as well
    switch (colorIndex)
    {
    case CI_RED:
        img.pixels[pixel].r = img.rawData[index];
        break;
    case CI_GREEN:
        img.pixels[pixel].g = img.rawData[index];
        break;
    case CI_BLUE:
        img.pixels[pixel].b = img.rawData[index];
        break;
    case CI_ALPHA:
        img.pixels[pixel].a = img.rawData[index];
        break;
    default:
        break;
    }
}

void write_lsb(SImage img, char* data, int index)
{
    unsigned char* hello = data_to_bits(data);
    
    int c = 0;
    
    for (int i = index; i < index + (strlen(data) * 8); ++i)
    {
        set_lsb(img, i, CI_RED, hello[c]);
        ++c;
    }
    
    free(hello);
}

unsigned char* data_to_bits(char* data)
{
    unsigned char* bits = malloc(strlen(data)*8);
    
    int c = 0;
    
    for (int i = 0; i < strlen(data); ++i)
    {
        char byte = data[i];
        
        bits[c+7] = byte & 0x01; byte >>= 1;
        bits[c+6] = byte & 0x01; byte >>= 1;
        bits[c+5] = byte & 0x01; byte >>= 1;
        bits[c+4] = byte & 0x01; byte >>= 1;
        bits[c+3] = byte & 0x01; byte >>= 1;
        bits[c+2] = byte & 0x01; byte >>= 1;
        bits[c+1] = byte & 0x01; byte >>= 1;
        bits[c+0] = byte & 0x01;
        
        c += 8;
    }
    
    return bits;
}

void encrypt(char* filename, char* data, char* outfile)
{
    SImage img = load_image(filename);
    
    if (img.rawData)
    {
        printf("\nLoaded '%s'. Dimensions: (%dx%d)\n\n", filename, img.width, img.height);
        
        char* dataLength = malloc(8);
        snprintf(dataLength, 8, "%d", (int)strlen(data));
        
        dataLength[strlen(dataLength)] = 0;
        
        int data_index = 0;
        write_lsb(img, HEADER, data_index);
        
        data_index = strlen(HEADER) * 8;
        write_lsb(img, dataLength, data_index);
        
        data_index += strlen(dataLength) * 8;
        write_lsb(img, data, data_index);
        
        save_image(outfile, img);
        
        close_image(img);
    }
}

