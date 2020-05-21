# NAME: Guanqun Ma
# EMAIL: maguanqun0212@gmail.com
# ID: 305331164

CC = gcc
CFLAGS = -g -Wall -Wextra

default: lab3a

lab3a: lab3a.c
	$(CC) $(CFLAGS) -o lab3a lab3a.c

dist:

clean: