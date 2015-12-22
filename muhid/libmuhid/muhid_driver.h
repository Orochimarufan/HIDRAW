//
//  muhid_driver.h
//  muHID internal header
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

#pragma once

#include "muhid.h"

// muHID Driver structure
typedef enum
{
    DRIVER_OK,              //< Device creation succeeded
    DRIVER_NOT_AVAILABLE,   //< Driver is not available on this machine
    DRIVER_GENERIC_ERROR,   //< Driver could not create device
    DRIVER_PERMISSION_ERROR, //< Driver could not create device because of missing permissions
} muhid_driver_create_error;

typedef muhid_driver_create_error (*muhid_driver_create)(muhid_handle);
typedef bool (*muhid_driver_post)(muhid_handle, void*, size_t);
typedef void (*muhid_driver_destroy)(muhid_handle);

typedef struct __muhid_drv
{
    struct __muhid_drv *__next;
    char *name;
    muhid_driver_create f_create;
    muhid_driver_post f_post;
    muhid_driver_destroy f_destroy;
} muhid_driver;

// muHID handle structure
struct __muhid_dev
{
    muhid_device_description *description;
    muhid_driver *driver;
    void *driver_data;
};

// Functions for drivers
/**
 * @brief Initialize a muHID driver
 * @arg name the driver name
 */
muhid_driver *muhid_create_driver(char *name);

/**
 * @brief Log a message at a specific verbosity level
 * @arg verbosity Verbosity, starting at 0=fatal
 * @arg message The message to log
 */
void muhid_log(int verbosity, const char *message);

/**
 * @brief Log a message, like printf
 * @arg verbosity Verbosity, starting at 0=fatal
 * @arg format Printf format
 */
void muhid_logf(int verbosity, const char *format, ...);
