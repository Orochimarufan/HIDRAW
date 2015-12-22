//
//  main.c
//  muhid-test muHID example & test application
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

#include "muhid.h"
#include "muhid_driver.h"

#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct report {
    bool b1 : 1;
    bool b2 : 1;
    bool b3 : 1;
    bool b4 : 1;
    bool b5 : 1;
    bool b6 : 1;
    unsigned _ : 2;
};

uint8_t report_descr[] = { // 6 button game controller
    0x05, 0x01, 0x09, 0x05, 0xA1, 0x01, 0xA0, 0x05, 0x09, 0x19, 0x01, 0x29, 0x06, 0x14, 0x25, 0x01, 0x95, 0x06, 0x75, 0x01, 0x81, 0x02, 0xC0, 0xC0,
};

muhid_device_description descr = {
    "Test Device",
    0,
    0,
    0,
    sizeof(report_descr),
    report_descr
};

static bool breakapp = false;

void handle_int(int _ __unused)
{
    breakapp = true;
}

void hlog(int level, const char *msg)
{
    printf("muHID(%i): %s\n", level, msg);
}

int main(int argc, const char * argv[]) {
    signal(SIGINT, handle_int);

    muhid_set_logging(hlog);

    muhid_handle device = muhid_create(&descr);
    if (!device)
        return -1;

    printf("Selected driver: %s\n", device->driver->name);
    printf("Hit Ctrl+C to Quit\n");

    while (!breakapp) {
        long rnd = random();
        muhid_post(device, (struct report*)&rnd, sizeof(struct report));
        sleep(1);
    }

    muhid_destroy(device);
}
