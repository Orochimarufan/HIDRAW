// muhid_ddrpad: bridge vendor-specific HID report to proper HID events in userspace
// 				 to avoid the axis problem with various console DDR mats.
// This version specifically targets Konami's Dance Dance Revolution Mat for PS3

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

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>

// hidapi
#include <hidapi/hidapi.h>

// muhid
#include <muhid.h>

#include "../../common.h"
#include "../../Devices/konami_ps3.h"


#define new(T) (memset(malloc(sizeof(T)), 0, sizeof(T)))

#include "descriptor.h"

typedef union {
    uint16_t buttons;
    struct {
        uint8_t button1 :1;
        uint8_t button2 :1;
        uint8_t button3 :1;
        uint8_t button4 :1;
        uint8_t button5 :1;
        uint8_t button6 :1;
        uint8_t button7 :1;
        uint8_t button8 :1;
        uint8_t button9 :1;
        uint8_t button10 :1;
        uint8_t button11 :1;
        uint8_t button12 :1;
        uint8_t button13 :1;
        uint8_t button14 :1;
        uint8_t button15 :1;
        uint8_t button16 :1;
    };
} output_report_t;

static const uint8_t report_request[] = {0x00, 0x81};

static muhid_device_description virtual_device = {
    .name="virtual ddrpad",
    .vid=0,
    .pid=0,
    .sn=0,
    .desc_size=REPORT_DESCRIPTOR_SIZE,
    .desc_data=(void*)&REPORT_DESCRIPTOR,
};

void update_report(output_report_t *report, ps3_ddrpad_state_t *state)
{
    report->button1 = state->right;
    report->button2 = state->left;
    report->button3 = state->up;
    report->button4 = state->down;
    report->button5 = state->cross;
    report->button6 = state->circle;
    report->button7 = state->triangle;
    report->button8 = state->square;
    report->button9 = state->start;
    report->button10 = state->select;
    report->button11 = state->pshome;
}

void synopsis(const char *prog)
{
	printf("Synopsis: %s [-v]\n", prog);
}

static bool run = true;

void sigint(int sig)
{
    run = false;
}

int main(int argc, char **argv)
{
    // Locals
    int res;
    hid_device *ha_handle;
    muhid_handle mu_handle;
    
    ps3_ddrpad_state_t state1, state2;
    ps3_ddrpad_state_t *state = &state1, *oldstate = &state2, *tmp;
	ps3_ddrpad_report_t in_report;
    output_report_t out_report;

	bool opt_print_events = 0;
	
    // Initialize stuff
    memset(&state1, 0, sizeof(state1));
    memset(&state2, 0, sizeof(state2));
    memset(&out_report, 0, sizeof(out_report));
	
    // Run
	printf("muhid_ddrpad 1.0\n");
	printf("(c) 2014-2016 Taeyeon Mori\n\n");
	
	if (argc > 1)
		for (int i = 1; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-v"))
				opt_print_events = 1;
			else
			{
				synopsis(argv[0]);
				return 255;
			}
		}
    
    // Open HIDAPI
    res = hid_init();
    ha_handle = hid_open(VENDOR, PRODUCT, NULL);
    
    if (!ha_handle)
    {
        printf("Could not open raw input device.\n");
        return 1;
    }
	
	// muhid
    mu_handle = muhid_create(&virtual_device);
    signal(SIGINT, &sigint);
    
    if (!mu_handle)
    {
        printf("Could not open virtual HID device. Are you root?\n");
        return 1;
    }
    
    out_report.button12 = 1;
	
	while (run)
	{
        res = hid_write(ha_handle, report_request, 2);
        res = hid_read(ha_handle, (void*)&in_report, sizeof(in_report));
		if (res > 0)
		{
			read_report(&in_report, state);

            // Compare
            if (opt_print_events)
            {
                for (int i = 0; i < 11; ++i)
                {
                    if (state->buttons[i] != oldstate->buttons[i])
                    {
                        if (state->buttons[i])
                            printf("Press   %s\n", button_names[i]);
                        else
                            printf("Release %s\n", button_names[i]);
                    }
                }
                tmp = oldstate;
                oldstate = state;
                state = tmp;
            }

            update_report(&out_report, state);
            muhid_post(mu_handle, &out_report, sizeof(out_report));
		}
	}
    
    // Cleanup
    muhid_destroy(mu_handle);
    hid_exit();
}
