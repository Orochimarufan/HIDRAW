// Copyright (c) 2014-2016 Taeyeon Mori
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

#pragma once

#include "common.h"


#define VENDOR 0x1ccf // Konami Digital Entertainment
#define PRODUCT 0x1010 // DDR Mat for PS3


// HID Input Report structure
typedef struct ps3_ddrpad_report_t {
    // These are also detected by the linux usbhid driver
    uint16_t buttons;
    uint8_t hat;
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t rz;
    // These however are vendor-specific
    uint8_t u20_right;
    uint8_t u21_left;
    uint8_t u22_up;
    uint8_t u23_down;
    uint8_t u24;
    uint8_t u25;
    uint8_t u26;
    uint8_t u27;
    uint8_t u28;
    uint8_t u29;
    uint8_t u2a;
    uint8_t u2b;
    uint16_t u2c;
    uint16_t u2d;
    uint16_t u2e;
    uint16_t u2f;
} ps3_ddrpad_report_t;

#define BUTTON(report, n) (report->buttons & (1 << (16 - n)))
#define HAT(report) ((report->hat & 0xf0) >> 4)

static inline void read_report(ps3_ddrpad_report_t *report, ps3_ddrpad_state_t *state)
{
    state->square = BUTTON(report, 0);
    state->cross = BUTTON(report, 1);
    state->circle = BUTTON(report, 2);
    state->triangle = BUTTON(report, 3);
    
    state->select = BUTTON(report, 8);
    state->start = BUTTON(report, 9);
    state->pshome = BUTTON(report, 12);
    
    state->right = report->u20_right;
    state->left = report->u21_left;
    state->up = report->u22_up;
    state->down = report->u23_down;
}

#undef BUTTON
#undef HAT