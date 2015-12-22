//
//  muhid_iokit.c
//  muHID OS X IOKit driver
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

#include "muhid_driver.h"

#include <CoreFoundation/CoreFoundation.h>
#include "IOHIDUserDevice.h"


typedef struct __muhid_osx_device
{
    IOHIDUserDeviceRef device;
} muhid_osx_device;

static inline muhid_osx_device *hdevice(muhid_handle handle)
{
    return (muhid_osx_device*)handle->driver_data;
}

static bool CFDictSetLong(CFMutableDictionaryRef dict, CFStringRef key, long value)
{
    CFNumberRef number = CFNumberCreate(kCFAllocatorDefault, kCFNumberLongType, &value);
    if (number)
    {
        CFDictionarySetValue(dict, key, number);
        CFRelease(number);
        return true;
    }
    else
    {
        const char *ckey = CFStringGetCStringPtr(key, CFStringGetSystemEncoding());
        muhid_logf(3, "[IOKit] Could not set property %s (long): %li", ckey, value);
        return false;
    }
}

static bool CFDictSetString(CFMutableDictionaryRef dict, CFStringRef key, const char *value)
{
    CFStringRef string = CFStringCreateWithCString(kCFAllocatorDefault, value, CFStringGetSystemEncoding());
    if (string)
    {
        CFDictionarySetValue(dict, key, string);
        CFRelease(string);
        return true;
    }
    else
    {
        const char *ckey = CFStringGetCStringPtr(key, CFStringGetSystemEncoding());
        muhid_logf(3, "[IOKit] Could not set device property %s (string): %s", ckey, value);
        return false;
    }
}


static muhid_driver_create_error create(muhid_handle handle)
{
    IOHIDUserDeviceRef device;
    CFMutableDictionaryRef props;

    if (getuid() != 0)
    {
        muhid_log(1, "[IOKit] Root permissions required!");
        return DRIVER_PERMISSION_ERROR;
    }

    props = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

    if (handle->description->name != NULL)
        CFDictSetString(props, CFSTR(kIOHIDProductKey), handle->description->name);

    if (handle->description->vid != 0)
        CFDictSetLong(props, CFSTR(kIOHIDVendorIDKey), handle->description->vid);

    if (handle->description->pid != 0)
        CFDictSetLong(props, CFSTR(kIOHIDProductIDKey), handle->description->pid);

    {
        CFDataRef descriptor = CFDataCreate(kCFAllocatorDefault, handle->description->desc_data, handle->description->desc_size);
        if (!descriptor)
        {
            muhid_log(1, "[IOKit] Could not create CFDataRef for Report Descriptor");
            CFRelease(props);
            return DRIVER_GENERIC_ERROR;
        }
        CFDictionarySetValue(props, CFSTR(kIOHIDReportDescriptorKey), descriptor);
        CFRelease(descriptor);
    }

    device = IOHIDUserDeviceCreate(kCFAllocatorDefault, props);
    CFRelease(props);

    if (!device)
    {
        muhid_log(1, "[IOKit] Failed to create IOHIDUserDevice");
        return DRIVER_GENERIC_ERROR;
    }

    handle->driver_data = malloc(sizeof(muhid_osx_device));
    hdevice(handle)->device = device;

    return DRIVER_OK;
}

static bool post(muhid_handle handle, void *report, size_t length)
{
    return IOHIDUserDeviceHandleReport(hdevice(handle)->device, report, length) == kIOReturnSuccess;
}

static void destroy(muhid_handle handle)
{
    CFRelease(hdevice(handle)->device);
    free(handle->driver_data);
}

void muhid_iokit_init(void)
{
    muhid_driver *drv = muhid_create_driver("OS X IOKit Driver");
    drv->f_create = create;
    drv->f_post = post;
    drv->f_destroy = destroy;
}
