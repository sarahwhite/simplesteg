#include "main.h"

bool argument_exists(char* arg, int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], arg))
        {
            return true;
        }
    }
    
    return false;
}

char* get_argument_input(char* arg, int argc, char *argv[])
{
    char* input = (char*)malloc(255);
    
    strncpy(input, "$NOINPUT$", 254);

    for (int i = 0; i < argc; ++i)
    {
        if (i < argc - 1 &&
            !strcmp(argv[i], arg) &&
            strlen(argv[i+1]) &&
            argv[i+1][0] != '-')
        {
            strncpy(input, argv[i+1], 254);
        }
    }
    
    return input;
}

void print_help()
{
    printf( "\nSimpleSteg v0.01 Usage:\n----------------------------------\n"
            "-h\t\tDisplay this help text.\n"
            "-e <file>\tEncrypt an image with a text. Carrier file.\n"
            "-d <file>\tDecrypt an image to reveal the hidden text.\n"
            "-s <text>\tString to encrypt into image.\n"
            "-f <file>\tFilename to save embedded PNG to.\n"
            "Examples:\n"
            "./simplesteg -e cat.png -s \"Sarah rules! <3\" -f coolcat.png\n"
            "./simplesteg -d coolcat.png"
            "\n\n");
            
}

void do_encrypt(int argc, char* argv[])
{
    char* input;
    char* data;
    char* output;

    input = get_argument_input("-e", argc, argv);
    data = get_argument_input("-s", argc, argv);
    output = get_argument_input("-f", argc, argv);

    if (strcmp(input, "$NOINPUT$") && strcmp(data, "$NOINPUT$") && strcmp(output, "$NOINPUT$"))
    {
        encrypt(input, data, output);
    }
    else
    {
        printf("\nError: Missing argument(s), please use -h to view a list of commands.\n\n");
    }

    free(input);
    free(data);
    free(output);
}

void do_decrypt(int argc, char* argv[])
{
    char* input;
            
    input = get_argument_input("-d", argc, argv);

    if (strcmp(input, "$NOINPUT$"))
    {
        decrypt(input);
    }
    else
    {
        printf("\nError: Missing argument, please use -h to view a list of commands.\n\n");
    }

    free(input);
}

int main(int argc, char* argv[])
{
    if (argument_exists("-h", argc, argv) ||
       (!argument_exists("-e", argc, argv) &&
        !argument_exists("-d", argc, argv)))
    {
        print_help();
        return 0;
    }
    
    if (argument_exists("-e", argc, argv) &&
        argument_exists("-s", argc, argv) &&
        argument_exists("-f", argc, argv))
    {
        do_encrypt(argc, argv);
    }
    else if (argument_exists("-d", argc, argv))
    {
        do_decrypt(argc, argv);
    }

    return 0;
}

