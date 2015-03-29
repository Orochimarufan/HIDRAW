// HIDRAW_test: A hid debug tool

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

// Derived from:
/*
 * Hidraw Userspace Example
 *
 * Copyright (c) 2010 Alan Ott <alan@signal11.us>
 * Copyright (c) 2010 Signal 11 Software
 *
 * The code may be used by anyone for any purpose,
 * and can serve as a starting point for developing
 * applications using hidraw.
 */
 
#include "HIDRAW_test.h"

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

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024


const char *bus_str(int bus);

int main(int argc, char **argv)
{
	int fd;
	int32_t res, desc_size = 0;
	uint8_t buf[BUFFER_SIZE];
	struct hidraw_report_descriptor rpt_desc;
	struct hidraw_devinfo info;
	struct hid_report_description_t *descriptor;
	
	puts("HIDRAW_test 0.1\n");
	
	if (argc < 2)
	{
		printf("Synopsis: %s <hidraw device>\n", argv[0]);
		return 255;
	}

	/* Open the Device with non-blocking reads. In real life,
	   don't use a hard coded path; use libudev instead. */
	// XX Nonblocking Reads (O_NOBLOCK) cause the read to fail with EAGAIN
	fd = open(argv[1], O_RDONLY);

	if (fd < 0) {
		perror("Unable to open device");
		return 1;
	}

	memset(&rpt_desc, 0x0, sizeof(rpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));

	// Raw info
	{
		/* Get Raw Name */
		res = ioctl(fd, HIDIOCGRAWNAME(256), buf);
		if (res < 0)
			perror("HIDIOCGRAWNAME");
		else
			printf("Raw Name: %s\n", buf);

		/* Get Physical Location */
		res = ioctl(fd, HIDIOCGRAWPHYS(256), buf);
		if (res < 0)
			perror("HIDIOCGRAWPHYS");
		else
			printf("Raw Phys: %s\n", buf);

		/* Get Raw Info */
		res = ioctl(fd, HIDIOCGRAWINFO, &info);
		if (res < 0) {
			perror("HIDIOCGRAWINFO");
		} else {
			printf("Raw Info:\n");
			printf("\tbustype: %d (%s)\n",
				info.bustype, bus_str(info.bustype));
			printf("\tvendor: 0x%04hx\n", info.vendor);
			printf("\tproduct: 0x%04hx\n", info.product);
		}
		
		putchar('\n');
	}
	
	/* Get Report Descriptor Size */
	res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
	if (res < 0)
		perror("HIDIOCGRDESCSIZE");
	else
		printf("Report Descriptor Size: %d\n", desc_size);

	/* Get Report Descriptor */
	rpt_desc.size = desc_size;
	res = ioctl(fd, HIDIOCGRDESC, &rpt_desc);
	if (res < 0) {
		perror("HIDIOCGRDESC");
		return 2;
	} else {
		printf("Report Descriptor Data:\n");
		print_hex_lines(rpt_desc.value, rpt_desc.size);
		
		printf("Report Descriptor:\n");
		descriptor = parse_description(rpt_desc.value, rpt_desc.size, NULL);
		print_descriptor_tree(descriptor->report_tree, 1);
		
		printf("Incoming Report (%i Items; Total %i bits = %iB):\n",
				descriptor->input.count,
				descriptor->input.size,
				descriptor->input.size / 8);
		print_descriptor_items(&descriptor->input, 1);
		
		if (descriptor->output.front)
		{
			printf("Outgoing Report (%i Items; Total %i bits = %iB):\n",
					descriptor->output.count,
					descriptor->output.size,
					descriptor->output.size / 8);
			print_descriptor_items(&descriptor->output, 1);
		}
		
		if (descriptor->feature.front)
		{
			printf("Feature Report (%i Items; Total %i bits = %iB):\n",
					descriptor->feature.count,
					descriptor->feature.size,
					descriptor->feature.size / 8);
			print_descriptor_items(&descriptor->feature, 1);
		}
		
		putchar('\n');
	}

	// Features
	if (0)
	{
		/* Set Feature */
		buf[0] = 0x9; /* Report Number */
		buf[1] = 0xff;
		buf[2] = 0xff;
		buf[3] = 0xff;
		res = ioctl(fd, HIDIOCSFEATURE(4), buf);
		if (res < 0)
			perror("HIDIOCSFEATURE");
		else
			printf("ioctl HIDIOCGFEATURE returned: %d\n", res);

		/* Get Feature */
		buf[0] = 0x9; /* Report Number */
		res = ioctl(fd, HIDIOCGFEATURE(256), buf);
		if (res < 0) {
			perror("HIDIOCGFEATURE");
		} else {
			printf("ioctl HIDIOCGFEATURE returned: %d\n", res);
			printf("Report data (not containing the report number):\n\t");
			print_hex_data(buf, res);
			puts("\n");
		}

		/* Send a Report to the Device */
		buf[0] = 0x1; /* Report Number */
		buf[1] = 0x77;
		res = write(fd, buf, 2);
		if (res < 0) {
			printf("Error: %d\n", errno);
			perror("write");
		} else {
			printf("write() wrote %d bytes\n", res);
		}

		putchar('\n');
	}
	
	/* Get reports from the device */
	const char ** headings = generate_item_headings(&descriptor->input);
	while (1) {
		res = read(fd, buf, BUFFER_SIZE);
		if (res < 0) {
			printf("\r\033[2K"); // Return Carriage & clear line
			perror("read");
		} else {
			//printf("\rReport(%iB): ", res);
			//print_hex_data(buf, res);
			putchar('\r');
			print_report(&descriptor->input, buf, headings);
			for (int i = 0; i < 5; ++i)
				putchar(' ');
		}
	}
	
	putchar('\n');
	
	close(fd);
	return 0;
}

const char *bus_str(int bus)
{
	switch (bus) {
	case BUS_USB:
		return "USB";
		break;
	case BUS_HIL:
		return "HIL";
		break;
	case BUS_BLUETOOTH:
		return "Bluetooth";
		break;
	case BUS_VIRTUAL:
		return "Virtual";
		break;
	default:
		return "Other";
		break;
	}
}