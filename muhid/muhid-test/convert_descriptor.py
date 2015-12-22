#!/usr/bin/python

from __future__ import print_function

descr = raw_input()

for i in range(0, len(descr), 2):
	print("0x%s" % descr[i:i+2], end=", ")

print()

