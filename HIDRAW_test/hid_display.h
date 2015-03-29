// HIDRAW_test hidraw formatting helpers

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

#pragma once

#include <stdint.h>

#include "hid_report.h"

// [[ hid_display.c ]]
/**
 * @brief Get the name of an Usage Page
 * @arg usage_page: the usage page
 * @return a Cstring constant containting the name or NULL
 */
const char *get_usage_page_name(uint16_t usage_page);

/**
 * @brief Get the name of an Usage ID
 * @arg usage_page: the Usage Page part of the Usage ID
 * @arg usage: the Usage part of the Usage ID
 * @return a Cstring constant containing the name or NULL
 */
const char *get_usage_name(uint16_t usage_page, uint16_t usage);

const char *get_unit_name(uint32_t unit);

/**
 * @brief Enumerate the flags given to IO descriptors HID_INPUT, HID_OUTPUT and HID_FEATURE
 * @arg io_flags: the data passed to HID_INPUT, HID_OUTPUT or HID_FEATURE
 * @return a semi-permanent Cstring containing a human-readable list of the flags
 * NOTE: semi-permanent: A static buffer is used, old values are overwritten when the function is called again.
 */
const char *get_io_flags(uint16_t io_flags);

/**
 * @brief Create a human readable representation of a node.
 * @arg node: the node
 * @arg tag: Output for the tag representation
 * @arg data_repr: Output for the data representation
 * NOTE: Out values may be constant OR semi-permanent. They need to be copied if kept around.
 */
void get_node_name(hid_report_node_t *node, const char **tag, const char **data_repr);

/**
 * @brief Print the descriptor tree to stdout.
 * @arg root: the virtual root node of the tree
 * @arg indent_level: the initial indendation level
 * NOTE: The printout starts with the first child of \a root!
 */
void print_descriptor_tree(hid_report_node_t *root, int indent_level);


void print_descriptor_items(hid_report_item_set_t *set, int indent_level);

const char **generate_item_headings(hid_report_item_set_t *descriptor);

void print_report(hid_report_item_set_t *descriptor, uint8_t *report, const char **headings);
