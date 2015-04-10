# (c) 2015 Taeyeon Mori
# Makefile for uinput_ddrpad
# MIT License

DESTDIR=/usr/local
CC=gcc
CFLAGS=-Wall -std=c11
LIBS=-lsuinput

all: uinput_ddrpad

uinput_ddrpad: main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	$(RM) *.o uinput_ddrpad

install: uinput_ddrpad
	install -m755 uinput_ddrpad $(DESTDIR)/bin/uinput_ddrpad

