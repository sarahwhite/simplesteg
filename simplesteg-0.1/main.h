#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include "encrypt.h"
#include "decrypt.h"

typedef enum { false, true } bool;

#include "main.h"

bool argument_exists(char* arg, int argc, char* argv[]);
char* get_argument_input(char* arg, int argc, char *argv[]);
void print_help();
void do_encrypt(int argc, char* argv[]);
void do_decrypt(int argc, char* argv[]);
int main(int argc, char* argv[]);

#endif
