// HIDRAW_test Terminal display helpers

// Copyright (c) 2014 Taeyeon Mori
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "HIDRAW_test.h"

#include <sys/ioctl.h>
#include <stdio.h>


// Get the terminal window size
inline void gettermsize(int *w, int *h)
{
	struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
	
	if (w != NULL)
		*w = ws.ws_col;
	if (h != NULL)
		*h = ws.ws_row;
}


#define HEX_FORMAT_CODE "%02hhx"

// Print hex data according to HEX_FORMAT_CODE
void print_hex_data(uint8_t *data, uint32_t size)
{
	for (int i = 0; i < size; i++)
		printf(HEX_FORMAT_CODE " ", data[i]);
}

// Print hex data that might be multiple lines on its own (indented) lines with sane wraparound.
void print_hex_lines(uint8_t *data, uint32_t size)
{
	int term_width, per_line;
	gettermsize(&term_width, NULL);
	per_line = term_width / 3 - 3;
	
	for (int i = 0; i < size; ++i)
	{
		if (!(i % per_line))
		{
			if (i)
				putchar('\n');
			putchar('\t');
		}
		printf(HEX_FORMAT_CODE " ", data[i]);
	}
	putchar('\n');
}
