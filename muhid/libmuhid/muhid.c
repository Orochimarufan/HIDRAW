//
//  muhid.c
//  muHID core implemenation
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

#include "muhid.h"
#include "muhid_driver.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

// Globals
static struct
{
    muhid_driver *drivers;
    void (*logging_callback)(int, const char*);
} muhid;

// Initialization
void muhid_init_drivers(void);

static void muhid_init(void)
{
    static bool has_init = false;
    if (has_init)
        return;

    muhid.logging_callback = NULL;
    muhid.drivers = NULL;
    muhid_init_drivers();

    has_init = true;
}

// Logging
void muhid_log(int verbosity, const char *message)
{
    if (muhid.logging_callback)
        muhid.logging_callback(verbosity, message);
}

void muhid_logf(int verbosity, const char *format, ...)
{
    va_list args;
    size_t msg_length;
    char *buffer;

    if (!muhid.logging_callback)
        return;

    va_start(args, format);
    msg_length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    buffer = malloc(msg_length + 1);

    va_start(args, format);
    vsnprintf(buffer, msg_length + 1, format, args);
    va_end(args);

    muhid.logging_callback(verbosity, buffer);
    free(buffer);
}

void muhid_set_logging(void(*cb)(int, const char*))
{
    muhid_init();
    muhid.logging_callback = cb;
}

// Drivers
muhid_driver *muhid_create_driver(char *name)
{
    muhid_driver *drv = calloc(1, sizeof(muhid_driver));
    drv->__next = muhid.drivers;
    muhid.drivers = drv;
    drv->name = name;
    return drv;
}

// Actual Work
muhid_handle muhid_create(muhid_device_description* dev)
{
    muhid_init();

    muhid_handle handle = malloc(sizeof(struct __muhid_dev));
    handle->description = dev;

    muhid_driver *drv = muhid.drivers;
    while (drv)
    {
        handle->driver = drv;
        if (drv->f_create(handle) == DRIVER_OK)
        {
            return handle;
        }
        drv = drv->__next;
    }

    muhid_log(0, "Could not find a suitable driver!");
    free(handle);

    return NULL;
}

bool muhid_post(muhid_handle handle, void *report, size_t length)
{
    // Pass it to the driver
    return handle->driver->f_post(handle, report, length);
}

void muhid_destroy(muhid_handle handle)
{
    if (!handle)
        return;

    // Destroy driver instance
    handle->driver->f_destroy(handle);

    // Free handle
    free(handle);
}
