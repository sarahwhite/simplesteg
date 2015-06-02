CC = gcc
CFLAGS = -Wall -g

simplesteg: lodepng.o image_tools.o main.o encrypt.o decrypt.o
	$(CC) $(CFLAGS) -o simplesteg lodepng.o image_tools.o main.o encrypt.o decrypt.o -I.

