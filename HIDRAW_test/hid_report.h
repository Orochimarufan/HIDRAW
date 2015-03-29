// HIDRAW_test hidraw helpers

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
#include <stdbool.h>

// [[ hid_report.c ]]

/**
 * @brief Describes a node in the HID Report Descriptor
 * The descriptor has a tree-like structure.
 */
typedef struct hid_report_node_t {
	// This node
	uint8_t type;
	uint8_t tag;
	union {
		int32_t data;
		struct {
			uint8_t *long_data;
			uint8_t long_size;
		};
	};
	// Tree
	struct hid_report_node_t *parent;
	struct hid_report_node_t *first_child;
	struct hid_report_node_t *next;
} hid_report_node_t;

/**
 * @brief Describes a HID Report item
 */
typedef struct hid_report_item_t {
	// Type
	uint8_t type;
	uint16_t io_flags;
	// Usage
	union {
		uint32_t usage_id;
		struct {
			uint16_t usage_page;
			uint16_t usage;
		};
	};
	// Logical Limits
	int32_t logical_minimum;
	int32_t logical_maximum;
	// Physical Limits
	int32_t physical_minimum;
	int32_t physical_maximum;
	// Unit
	int32_t unit_exponent;
	int32_t unit;
	// Report
	uint32_t report_size;
	uint8_t report_id;
	// Designator
	uint32_t designator;
	// String
	uint32_t string;
	// Delimiter
	uint32_t delimiter;
	// References
	struct hid_report_node_t *node; //< Reference the report node this belongs to
	struct hid_report_item_t *next; //< Next item in linked list
} hid_report_item_t;

typedef struct hid_report_item_set_t {
	uint32_t size;
	uint32_t count;
	struct hid_report_item_t *front;
	struct hid_report_item_t *back;
} hid_report_item_set_t;

/**
 * @brief Holds a preprocessed description of the HID Report
 */
typedef struct hid_report_description_t {
	// Parsed tree structure
	struct hid_report_node_t *report_tree;
	// Physical report structure
	struct hid_report_item_set_t input;
	struct hid_report_item_set_t output;
	struct hid_report_item_set_t feature;
} hid_report_description_t;


typedef struct hid_report_parser_options_t {
	bool create_tree;
} hid_report_parser_options_t;

/**
 * @brief Parse a USB HID Report Descriptor into a hid_report_description_t
 * @arg data: The descriptor data
 * @arg size: The descriptor size
 * @return a pointer t a newly allocated hid_report_description_t
 * @sa free_description: Use it to free the hid_report_description_t
 */
hid_report_description_t *parse_description(uint8_t *data, uint32_t size, hid_report_parser_options_t *options);

/**
 * @brief Free a hid_report_description_t allocated by parse_description()
 * @arg description: The description to free
 */
void free_description(hid_report_description_t *description);

/**
 * @brief Advance \a node to the next one (Depth-First Pre-Order)
 * @arg node: Inout argument pointing to the node pointer
 * @arg level: Optional Inout argument pointing to the depth-level (max be NULL)
 */
void descriptor_tree_next(hid_report_node_t **node, int *level);

/**
 * @brief Get the first node of Post-Order iteration (Depth-First Post-Order)
 * @arg root: The root node
 * @arg level: Optional Inout argument pointing to the depth-level (max be NULL)
 */
hid_report_node_t *descriptor_tree_first_post(hid_report_node_t *root, int *level);

/**
 * @brief Advance \a node to the next one (Depth-First Post-Order)
 * @arg node: Inout argument pointing to the node pointer
 * @arg level: Optional Inout argument pointing to the depth-level (max be NULL)
 */
void descriptor_tree_next_post(hid_report_node_t **node, int *level);
