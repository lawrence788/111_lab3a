// NAME: Guanqun Ma, Larry Qu
// EMAIL: maguanqun0212@gmail.com, qularry1100@gmail.com
// ID: 305331164, 105206585

CC = gcc
CFLAGS = -g -Wall -Wextra

default: lab3a

lab3a: lab3a.c
	$(CC) $(CFLAGS) -o lab3a lab3a.c

dist:

clean:
