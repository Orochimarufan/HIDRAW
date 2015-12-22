//
//  muhid_drivers.c
//  muHID driver index
//
//  Created by Taeyeon on 22/12/15.
//  Copyright © 2015 Taeyeon Mori. All rights reserved.
//

void muhid_iokit_init();
void muhid_uhid_init();

void muhid_init_drivers()
{
#if defined(__APPLE__)
    muhid_iokit_init();
#elif defined(__linux__)
    muhid_uhid_init();
#endif
}
