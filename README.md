HIDRAW utils
============
A set of utility programs for working with Linux hidraw devices

CodeLite (http://codelite.org) is used as IDE and is required to build the projects.

uinput\_ddrpad also comes with a Makefile for building without CodeLite:

    cd uinput_ddrpad
    make
    make install

Note that depending on the permissions on your devices (/dev/\*), you may have to run these tools as root.

HIDRAW\_test
-----------
Analyze the HID report descriptor.

This will attempt to parse the HID report descriptor and display it in two different ways:
* As a descriptor tree similar to what the HID Descriptor Tool uses,
* It will try to construct a human-readable representation of the report structure.

Additionally, it will try to display the current state of the device and update until Ctrl-C is pressed.

The included descriptor parser is NOT optimized for speed, instead it tries to be as generic as possible.

Synopsis: HIDRAW\_test /dev/\<hidraw device\>

uinput\_ddrpad
--------------
Use the HIDRAW device to get vendor specific information from input reports of Konami's
DanceDanceRevolution Mat for PS3 and make it usable in Applications
through the uinput kernel module (via libsuinput)

This allows use of the PS3 DDR mat in StepMania without encountering the Axis problem
as well as without any conversion hardware.

Synopsis: uinput\_ddrpad [-v] [/dev/\<hidraw device\>]

LICENSE
=======
    The MIT license

    Copyright (c) 2014-2015 Taeyeon Mori

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

