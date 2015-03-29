// uinput_ddrpad: bridge vendor-specific HID report to linux events in userspace
// 				  to avoid the axis problem with various console DDR mats.
// This version specifically targets Konami's Dance Dance Revolution Mat for PS3

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

/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

// libsuinput
#include <suinput.h>

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

// Physical controller state
typedef union ps3_ddrpad_state_t {
	struct  {
		// Arrows
		bool right;
		bool left;
		bool up;
		bool down;
		// Buttons
		bool square;
		bool cross;
		bool circle;
		bool triangle;
		// Special
		bool select;
		bool start;
		bool pshome;
	};
	bool buttons[11];
} ps3_ddrpad_state_t;

// Maps ps3_ddrpad_state_t fields to linux/input button codes
uint16_t button_codes[11] = {
	BTN_0,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_WEST,
	BTN_SOUTH,
	BTN_EAST,
	BTN_NORTH,
	BTN_SELECT,
	BTN_START,
	BTN_MODE,
};

const char *button_names[11] = {
	"Right",
	"Left",
	"Up",
	"Down",
	"Square",
	"Cross",
	"Circle",
	"Triangle",
	"Select",
	"Start",
	"PS Home"
};

// What buttons to relay.
// Should be 4 or 11, 4 means only arrows, 11 means all buttons
#define PUBLISH_BUTTONS 4

#define BUTTON(report, n) (report->buttons & (1 << (16 - n)))
#define HAT(report) ((report->hat & 0xf0) >> 4)

#define new(T) (memset(malloc(sizeof(T)), 0, sizeof(T)))


void read_report(ps3_ddrpad_report_t *report, ps3_ddrpad_state_t *state)
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

void print_state(ps3_ddrpad_state_t *state)
{
	printf("%i%i%i%i %i%i%i %i%i%i%i\n", state->square, state->cross, state->circle, state->triangle,
	state->select, state->start, state->pshome,
	state->right, state->left, state->up, state->down);
}

void synopsis(const char *prog)
{
	printf("Synopsis: %s <hidraw device> [-v]\n", prog);
}


int main(int argc, char **argv)
{
    int fd_hid, fd_sui, res;
	ps3_ddrpad_state_t *state, *newstate, *tmp;
	ps3_ddrpad_report_t *report;
	struct uinput_user_dev user_dev;
	struct hidraw_devinfo info;
	char buf[255];
	char *hidraw = 0;
	bool opt_print_events = 0;
	
	state = new(ps3_ddrpad_state_t);
	newstate = new(ps3_ddrpad_state_t);
	report = new(ps3_ddrpad_report_t);
	
	printf("uinput_ddrpad 1.0\n");
	printf("(c) 2014 Taeyeon Mori\n\n");
	
	if (argc > 1)
		for (int i = 1; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-v"))
				opt_print_events = 1;
			else if (!hidraw)
				hidraw = argv[i];
			else
			{
				synopsis(argv[0]);
				return 255;
			}
		}
	
	if (!hidraw)
	{
		// Search for the device
		DIR *folder = opendir("/dev");
		struct dirent *entry;
		while ((entry = readdir(folder)))
		{
			if (!strncmp("hidraw", entry->d_name, 6))
			{
				snprintf(buf, 255, "/dev/%s", entry->d_name);
				//printf("Looking at %s\n", buf);
				fd_hid = open(buf, O_RDONLY);
				if (fd_hid < 0)
				{
					printf("Checking hidraw device %s\n", buf);
					perror("Could not open hidraw device");
					continue;
				}
				
				res = ioctl(fd_hid, HIDIOCGRAWINFO, &info);
				if (res < 0)
				{
					close(fd_hid);
					continue;
				}
				
				if (info.vendor == VENDOR && info.product == PRODUCT)
				{
					hidraw = buf;
					break;
				}
				else
					close(fd_hid);
			}
		}
		closedir(folder);
		
		if (!hidraw)
		{
			printf("Could not determine PAD hidraw device. Make sure it is connected and hidraw.ko is loaded\n");
			return 10;
		}
		else
		{
			printf("Found PAD device at %s\n", hidraw);
		}
	}
	else
	{
		// HIDRAW
		fd_hid = open(hidraw, O_RDONLY);
		if (fd_hid < 0)
		{
			perror("Unable to open device");
			return 1;
		}
	
		res = ioctl(fd_hid, HIDIOCGRAWINFO, &info);
		if (res < 0)
		{
			perror("Could not Query Device Info");
			return 3;
		}
		else if (info.vendor != VENDOR || info.product != PRODUCT)
		{
			res = ioctl(fd_hid, HIDIOCGRAWNAME(256), buf);
			if (res < 0)
				strcpy(buf, "<Unknown>");
			printf("Device '%s' (%04hx:%04hx) isn't the Konami DDR Mat for PS3 (%04x:%04x).\n"
					"The HID descriptor is hardcoded and therefore this program is product-specific.\n"
					"Feel free to modify the source to work with different devices!\n",
					buf, info.vendor, info.product, VENDOR, PRODUCT);
			return 4;
		}
	}
	
	// UInput
	fd_sui = suinput_open();
	if (fd_sui < 0)
	{
		perror("Could not open uinput");
		return 2;
	}
	
	for (int i = 0; i < PUBLISH_BUTTONS; ++i)
		suinput_enable_event(fd_sui, EV_KEY, button_codes[i]);
	
	// Otherwise StepMania will ignore us
	suinput_enable_event(fd_sui, EV_ABS, ABS_X);
	
	memset(&user_dev, 0, sizeof(user_dev));
	strcpy(user_dev.name, "ps3_ddrpad");
	suinput_create(fd_sui, &user_dev);
	
	while (1)
	{
		res = read(fd_hid, report, sizeof(ps3_ddrpad_report_t));
		if (res > 0)
		{
			read_report(report, newstate);
			
			// Compare & Emit events
			for (int i = 0; i < PUBLISH_BUTTONS; ++i)
			{
				if (newstate->buttons[i] != state->buttons[i])
				{
					if (newstate->buttons[i])
					{
						suinput_emit(fd_sui, EV_KEY, button_codes[i], 1);
						if (opt_print_events)
							printf("Press   %s\n", button_names[i]);
					}
					else
					{
						suinput_emit(fd_sui, EV_KEY, button_codes[i], 0);
						if (opt_print_events)
							printf("Release %s\n", button_names[i]);
					}
				}
			}
			
			suinput_syn(fd_sui);
			
			// Swap out state buffers
			tmp = state;
			state = newstate;
			newstate = tmp;
		}
	}
}
