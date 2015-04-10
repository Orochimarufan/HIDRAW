# (c) 2015 Taeyeon Mori
# Makefile for uinput_ddrpad
# MIT License

DESTDIR=/
PREFIX=/usr/local

CC = gcc
LIBS = -lsuinput

CFLAGS = -Wall
override CFLAGS += -std=c11

all: uinput_ddrpad

uinput_ddrpad: main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	$(RM) *.o uinput_ddrpad

install: uinput_ddrpad
	install -D -m755 uinput_ddrpad $(DESTDIR)/$(PREFIX)/bin/uinput_ddrpad

