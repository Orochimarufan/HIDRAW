//
//  muhid.h
//  muHID cross-platform userspace virtual HID device library
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

#pragma once

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Opaque handle for muHID devices
 */
typedef struct __muhid_dev *muhid_handle;

/**
 * @brief Describes a muHID device
 */
typedef struct __muhid_desc
{
    // Device Info
    char *name;     //< Device Name
    int64_t vid;    //< Vendor ID
    int64_t pid;    //< Product ID
    int64_t sn;     //< Serial Number
    // HID Descriptor
    size_t desc_size; //< Descriptor size
    void *desc_data;  //< Descriptor data
} muhid_device_description;

/**
 * @brief create a muHID device
 * @arg device The device description
 * @return a muHID handle or NULL
 */
muhid_handle muhid_create(muhid_device_description *device);

/**
 * @brief Post a (one) HID report
 * @arg handle The muHID handle
 * @arg report The report data
 * @arg length The report buffer length
 * @return success
 */
bool muhid_post(muhid_handle handle, void *report, size_t length);

/**
 * @brief Destroy a muHID device
 * @arg handle The muHID handle
 * @warning The handle must not be used afterwards
 */
void muhid_destroy(muhid_handle handle);


/**
 * @brief Set a logging function for muHID to use
 * @arg logging_callback A callback function taking 2 arguments: verbosity and message.
 *      Pass NULL to disable logging.
 * @warning The callback MUST NOT rely on the message staying in memory!
 */
void muhid_set_logging(void (*logging_callback)(int verbosity, const char *message));
