#include "image_tools.h"

void save_image(char* filename, SImage image)
{
    unsigned error = lodepng_encode32_file(filename, image.rawData, image.width, image.height);
    
    if (error)
        printf("Error: %u: %s\n", error, lodepng_error_text(error));
}

void close_image(SImage image)
{
    free(image.pixels);
    free(image.rawData);
}

SImage load_image(char* filename)
{
    unsigned error;
    unsigned char* image;
    unsigned width, height;
    unsigned char* png;
    size_t pngsize;
    
    SPixel pixel;
    SImage img;

    lodepng_load_file(&png, &pngsize, filename);
    error = lodepng_decode32(&image, &width, &height, png, pngsize);
    
    if (error)
    {
        printf("Error: %u: %s\n", error, lodepng_error_text(error));
    }
    else
    {
        free(png);        
        int c = 0;
        
        img.pixels = (SPixel*)malloc(sizeof(SPixel)*width*height);
        img.width = width;
        img.height = height;
        img.rawData = image;
        
        // Fill the SImage pixels from the raw data
        for (int i = 0; i < width * sizeof(SPixel); i += sizeof(SPixel))
        {
            pixel.r = image[i+0];
            pixel.g = image[i+1];
            pixel.b = image[i+2];
            pixel.a = image[i+3];
            
            img.pixels[c] = pixel;
            ++c;
        }
    }
    
    return img;
}


