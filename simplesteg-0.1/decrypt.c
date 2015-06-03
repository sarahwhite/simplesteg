#include "decrypt.h"

unsigned char bits_to_byte(char* str)
{
        unsigned char byte = 0;
 
        for (int i = 0; i < 8; ++i)
        {
                char bit = str[i];
 
                if (bit || byte)
                {
                        byte <<= 1;
                        byte = byte ^ (unsigned char)bit;
                }
        }
 
        return byte;
}

char* get_data(SImage img, int dataLength)
{
    char* bytes = malloc(dataLength * 8);
    char* data = malloc(dataLength);
    char* len = malloc(8);
    
    // Get the length of the dataLength text
    snprintf(len, 8, "%d", dataLength);
    int index = (strlen(HEADER)*8) + strlen(len)*8;
    
    for (int c = 0; c < dataLength; ++c)
    {
        int b = 0;
    
        for (int i = c * 8; i < c * 8 + 8; ++i)
        {
            bytes[b] = get_lsb(img, i + index, CI_RED);
            ++b;
        }
        
        data[c] = bits_to_byte(bytes);
    }
    
    free(bytes);
    free(len);
    
    data[dataLength] = 0;
    
    return data;
}

int get_data_length(SImage img)
{
    char* bytes = malloc(8 * 8);
    char* data = malloc(8);
    
    int dataLength = 0;
    
    for (int c = 0; c < 8; ++c)
    {
        int b = 0;
    
        for (int i = c * 8; i < c * 8 + 8; ++i)
        {
            bytes[b] = get_lsb(img, i + strlen(HEADER)*8, CI_RED);
            ++b;
        }
        
        data[c] = bits_to_byte(bytes);
        
        // If we run into a null-byte, all data has been found
        if (data[c] == 0) break;
    }
    
    free(bytes);
    
    dataLength = atoi(data);
    
    return dataLength;
}

int find_header(SImage img)
{
    char* bytes = malloc(strlen(HEADER) * 8);
    char* data = malloc(strlen(HEADER));
    
    int ret = 0;

    for (int c = 0; c < strlen(HEADER); ++c)
    {
        int b = 0;
    
        for (int i = c * 8; i < c * 8 + 8; ++i)
        {
            bytes[b] = get_lsb(img, i, CI_RED);
            ++b;
        }
        
        data[c] = bits_to_byte(bytes);        
    }    
    
    data[strlen(HEADER)] = 0;
    
    if (!strcmp(data, HEADER))
    {
        ret = 1;
    }
    
    free(bytes);
    free(data);
    
    return ret;
}

void decrypt(char* filename)
{
    SImage img = load_image(filename);
    int dataLength = 0;
    
    if (img.rawData)
    {
        //printf("\nLoaded '%s'. Dimensions: (%dx%d)\n\n", filename, img.width, img.height);
        
        if (find_header(img))
        {
            //printf("Found the header!\n");
            
            dataLength = get_data_length(img);
            
            if (dataLength != 0)
            {
                //printf("The data is %d long.\n", dataLength);
                
                char* data = get_data(img, dataLength);
                
                printf("%s\n", data);
            }
            else
            {
                printf("Error: Failed to find length of data!\n");
            }
        }
        
        close_image(img);        
    }
}
