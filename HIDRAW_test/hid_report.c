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

#include "hid.h"
#include "hid_report.h"
#include "hid_display.h"


#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#define new(T) memset(malloc(sizeof(T)), 0, sizeof(T))

// [[ Parser Stack ]]
typedef struct hid_parser_stack_item_t {
	struct hid_report_node_t *node;
	struct hid_parser_stack_item_t *next;
} hid_parser_stack_item_t;

static inline void parser_push(hid_parser_stack_item_t **stack, hid_report_node_t *node)
{
	hid_parser_stack_item_t *new_top = new(hid_parser_stack_item_t);
	new_top->node = node;
	new_top->next = *stack;
	*stack = new_top;
}

static inline hid_report_node_t *parser_pop(hid_parser_stack_item_t **stack)
{
	hid_parser_stack_item_t *top = *stack;
	hid_report_node_t *node = top->node;
	*stack = top->next;
	free(top);
	return node;
}

// [[ Queue ]]
#define DEFINE_LIST(type) \
	typedef struct type ## _list_item_t { \
		type value; \
		struct type ## _list_item_t *next; \
	} type ## _list_item_t;\
	typedef struct type ## _list_t { \
		struct type ## _list_item_t *first; \
		struct type ## _list_item_t *last; \
	} type ## _list_t;\
	void list_push_back_ ## type (type ## _list_t *list, type value) \
	{\
		type ## _list_item_t *item = new(type ## _list_item_t); \
		item->value = value; \
		if (!list->first) \
			list->first = list->last = item; \
		else \
		{\
			list->last->next = item; \
			list->last = item; \
		}\
	};\
	type list_pop_front_ ## type (type ## _list_t *list) \
	{\
		type ## _list_item_t *item; \
		type value; \
		item = list->first; \
		list->first = item->next; \
		value = item->value; \
		free(item); \
		return value; \
	};\
	void list_clear_ ## type (type ## _list_t *list) \
	{\
		type ## _list_item_t *item; \
		type ## _list_item_t *next = list->first; \
		while ((item = next)) \
		{\
			next = item->next; \
			free(item); \
		}\
	}

DEFINE_LIST(uint16_t);
DEFINE_LIST(uint32_t);

#undef DEFINE_LIST

// [[ Globals / Locals ]]
typedef struct hid_parser_globals_t {
	uint16_t INDEX;
	uint16_t usage_page;
	int32_t logical_minimum;
	int32_t logical_maximum;
	int32_t physical_minimum;
	int32_t physical_maximum;
	int32_t unit_exponent;
	int32_t unit;
	uint32_t report_size;
	uint32_t report_id;
	uint32_t report_count;
	// Globals Stack
	struct hid_parser_globals_t *next;
} hid_parser_globals_t;

typedef struct hid_parser_locals_t {
	uint16_t INDEX;
	uint16_t_list_t usage;
	uint16_t usage_minimum;
	uint32_t_list_t designator;
	uint32_t designator_minimum;
	uint32_t_list_t string;
	uint32_t string_minimum;
	uint32_t delimiter;
} hid_parser_locals_t;

typedef struct hid_parser_state_t {
	hid_parser_globals_t *globals;
	hid_parser_locals_t *locals;
} hid_parser_state_t;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"

#define MAKE_PROP_FN(scope, index, type, name) \
	static inline void scope ## s_mark_ ## name ## _set(hid_parser_ ## scope ## s_t *tbl) \
	{\
		tbl->INDEX |= 1 << index; \
	};\
	static inline void scope ## s_mark_ ## name ## _unset(hid_parser_ ## scope ## s_t *tbl) \
	{\
		tbl->INDEX &= ~(uint16_t)(1 << index); \
	};\
	static inline bool scope ## s_is_ ## name ## _set(hid_parser_ ## scope ## s_t *tbl) \
	{\
		return (tbl->INDEX & (1 << index)); \
	};\
	static inline void state_set_ ## name(hid_parser_state_t *state, type name) \
	{\
		state->scope ## s->name = name; \
		scope ## s_mark_ ## name ## _set(state-> scope ## s); \
	};\
	static inline bool state_is_ ## name ## _set(hid_parser_state_t *state) \
	{\
		return scope ## s_is_ ## name ## _set (state-> scope ##s); \
	};\
	static inline type state_get_ ## name(hid_parser_state_t *state) \
	{\
		return state-> scope ## s->name; \
	};\
	static inline void state_unset_ ## name(hid_parser_state_t *state) \
	{\
		scope ## s_mark_ ## name ## _unset(state->scope ## s); \
	}

MAKE_PROP_FN(global, 0, uint16_t, usage_page);
MAKE_PROP_FN(global, 1, int32_t, logical_minimum);
MAKE_PROP_FN(global, 2, int32_t, logical_maximum);
MAKE_PROP_FN(global, 3, int32_t, physical_minimum);
MAKE_PROP_FN(global, 4, int32_t, physical_maximum);
MAKE_PROP_FN(global, 5, int32_t, unit_exponent);
MAKE_PROP_FN(global, 6, int32_t, unit);
MAKE_PROP_FN(global, 7, uint32_t, report_size);
MAKE_PROP_FN(global, 8, uint32_t, report_id);
MAKE_PROP_FN(global, 9, uint32_t, report_count);

MAKE_PROP_FN(local, 0, uint16_t_list_t, usage);
MAKE_PROP_FN(local, 1, uint16_t, usage_minimum);
MAKE_PROP_FN(local, 3, uint32_t_list_t, designator);
MAKE_PROP_FN(local, 4, uint32_t, designator_minimum);
MAKE_PROP_FN(local, 6, uint32_t_list_t, string);
MAKE_PROP_FN(local, 7, uint32_t, string_minimum);
MAKE_PROP_FN(local, 9, uint32_t, delimiter);

#undef MAKE_PROP_FN
#pragma clang diagnostic pop

#define MAKE_PROP_STACK(type, name) \
	static inline void state_push_ ## name(hid_parser_state_t *state, type name) \
	{\
		if (!state_is_ ## name ## _set(state)) \
			locals_mark_ ## name ## _set(state->locals); \
		list_push_back_ ## type(&state->locals->name, name); \
	};\
	static inline type state_pop_ ## name(hid_parser_state_t *state) \
	{\
		if (!state_is_ ## name ## _set(state)) \
			return 0; /*TODO: what to do? according to spec, this is malformed*/\
		if (state->locals->name.first == state->locals->name.last) \
			locals_mark_ ## name ## _unset(state->locals); \
		return list_pop_front_ ## type(&state->locals->name); \
	};\
	static inline void state_clear_ ## name(hid_parser_state_t *state) \
	{\
		if (state_is_ ## name ## _set(state)) \
			list_clear_ ## type(&state->locals->name); \
	}

MAKE_PROP_STACK(uint16_t, usage);
MAKE_PROP_STACK(uint32_t, designator);
MAKE_PROP_STACK(uint32_t, string);

static inline void state_clear_locals(hid_parser_state_t *state)
{
	state_clear_usage(state);
	state_clear_designator(state);
	state_clear_string(state);
	memset(state->locals, 0, sizeof(hid_parser_locals_t));
}

#undef MAKE_PROP_STACK

static inline void globals_push(hid_parser_state_t *state)
{
	hid_parser_globals_t *new_top = new(hid_parser_globals_t);
	memcpy(new_top, state->globals, sizeof(hid_parser_globals_t));
	new_top->next = state->globals;
	state->globals = new_top;
}

static inline void globals_pop(hid_parser_state_t *state)
{
	hid_parser_globals_t *top = state->globals;
	state->globals = top->next;
	free(top);
}

// [[ Items ]]
static inline hid_report_item_t *new_item(hid_parser_state_t *state, uint8_t type, uint16_t io_flags, uint32_t offset)
{
	hid_report_item_t *item = new(hid_report_item_t);
	
	// Item
	item->type = type;
	item->io_flags = io_flags;
	
	// Usage
	item->usage_page = state_get_usage_page(state);
		item->usage = state_pop_usage(state);
	
	// Other Locals
	item->designator = state_pop_designator(state);
	item->string = state_pop_string(state);
	item->delimiter = state_get_delimiter(state);
	
	// Logical Limits
	item->logical_minimum = state_get_logical_minimum(state);
	item->logical_maximum = state_get_logical_maximum(state);
	
	// Physical Limits
	// See 6.2.2.7 Global Items > Remarks
	if 	(!state_is_physical_minimum_set(state)
	  || !state_is_physical_maximum_set(state)
	  || (!state_get_physical_minimum(state) && !state_get_physical_maximum(state)))
	{
		item->physical_minimum = state_get_logical_minimum(state);
		item->physical_maximum = state_get_logical_maximum(state);
	}
	else
	{
		item->physical_minimum = state_get_physical_minimum(state);
		item->physical_maximum = state_get_physical_maximum(state);
	}
	
	// Unit
	item->unit = state_get_unit(state);
	item->unit_exponent = state_get_unit_exponent(state); // Defaults to 0 anyway
	
	// Report
	item->report_size = state_get_report_size(state);
	item->report_id = state_get_report_id(state);
	
	return item;
}

static inline void item_push(hid_report_description_t *description, hid_report_item_t *item)
{
	hid_report_item_set_t *set;
	
	if (item->type == HID_INPUT)
		set = &description->input;
	else if (item->type == HID_OUTPUT)
		set = &description->output;
	else if (item->type == HID_FEATURE)
		set = &description->feature;
	else
		return; // What to do?

	if (!set->front)
		set->front = set->back = item;
	else
	{
		set->back->next = item;
		set->back = item;
	}
	
	++set->count;
	set->size += item->report_size;
}

// [[ Parse descriptor ]]
hid_report_description_t *parse_description(uint8_t *data, uint32_t size, hid_report_parser_options_t *options)
{
	bool opt_create_tree = !options || options->create_tree;
	hid_report_description_t *description = new(hid_report_description_t);
	
	// Parse it
	{
		hid_parser_state_t *state = NULL;
		hid_report_node_t *root = NULL;
		hid_parser_stack_item_t *stack = NULL;
		hid_report_node_t *last = NULL;
		
		state = new(hid_parser_state_t);
		state->globals = new(hid_parser_globals_t);
		state->locals = new(hid_parser_locals_t);
		
		if (opt_create_tree)
		{
			root = new(hid_report_node_t);
			parser_push(&stack, root);
		}

		for (int i = 0; i < size;)
		{
			hid_report_node_t *node = new(hid_report_node_t);
			
			// See HID 1.11 6.2.2.2 Short Items
			// and HID 1.11 6.2.2.3 Long Items
			uint8_t prefix = data[i++];
			uint8_t bytes;
			
			if (prefix == 0b11111110)
			{
				// Read Long Item header
				bytes = data[i++];
				node->type = HID_TYPE_LONG;
				node->tag = data[i++];
				
				// Copy data
				node->long_data = new(uint8_t[bytes]);
				node->long_size = bytes;
				memcpy(node->long_data, data + i, bytes);
				i += bytes;
			}
			else
			{
				// Read Short Item header
				bytes = prefix & 0b11;
				bytes = bytes == 0b11 ? 4 : bytes;
				node->type = (prefix >> 2) & 0b11;
				node->tag = prefix >> 4;
				
				// Read data
				if (bytes == 1)
					node->data = *((int8_t*)data + i);
				else if (bytes == 2)
					node->data = *((int16_t*)data + i);
				else if (bytes == 4)
					node->data = *((int32_t*)data + i);
				i += bytes;
			}

			// Insert into tree
			if (opt_create_tree)
			{
				node->parent = stack->node;

				if (!last)
					stack->node->first_child = node;
				else
					last->next = node;
				
				last = node;
			}

			// Act on it
			if (node->type == HID_TYPE_MAIN)
			{
				if (node->tag == HID_COLLECTION)
				{
					if (opt_create_tree)
					{
						parser_push(&stack, node);
						last = NULL;
					}
				}
				else if (node->tag == HID_END_COLLECTION)
				{
					if (opt_create_tree)
						last = parser_pop(&stack);
				}
				else if (node->tag == HID_INPUT || node->tag == HID_OUTPUT || node->tag == HID_FEATURE)
				{
					uint32_t count = state_get_report_count(state);
					
					for (int k = 0; k < count; ++k)
						item_push(description, new_item(state, node->tag, node->data, k));
				}
				
				// Main items pop the locals
				state_clear_locals(state);
			}
			
			else if (node->type == HID_TYPE_GLOBAL)
			{
				if (node->tag == HID_PUSH)
					globals_push(state);
				else if (node->tag == HID_POP)
					globals_pop(state);
				else if (node->tag == HID_USAGE_PAGE)
					state_set_usage_page(state, node->data);
				else if (node->tag == HID_LOGICAL_MINIMUM)
					state_set_logical_minimum(state, node->data);
				else if (node->tag == HID_LOGICAL_MAXIMUM)
					state_set_logical_maximum(state, node->data);
				else if (node->tag == HID_PHYSICAL_MINIMUM)
					state_set_physical_minimum(state, node->data);
				else if (node->tag == HID_PHYSICAL_MAXIMUM)
					state_set_physical_maximum(state, node->data);
				else if (node->tag == HID_UNIT_EXPONENT)
					state_set_unit_exponent(state, node->data);
				else if (node->tag == HID_UNIT)
					state_set_unit(state, node->data);
				else if (node->tag == HID_REPORT_SIZE)
					state_set_report_size(state, node->data);
				else if (node->tag == HID_REPORT_ID)
					state_set_report_id(state, node->data);
				else if (node->tag == HID_REPORT_COUNT)
					state_set_report_count(state, node->data);
			}
			
			else if (node->type == HID_TYPE_LOCAL)
			{
				if (node->tag == HID_USAGE)
					state_push_usage(state, node->data);
				else if (node->tag == HID_USAGE_MINIMUM)
					state_set_usage_minimum(state, node->data);
				else if (node->tag == HID_USAGE_MAXIMUM)
				{
					if (!state_is_usage_minimum_set(state))
						puts("WARNING: Ignored USAGE_MAXIMUM without previous USAGE_MINIMUM");
					else
					{
						for (int k = state_get_usage_minimum(state); k <= node->data; ++k)
							state_push_usage(state, k);
						state_unset_usage_minimum(state);
					}
				}
				else if (node->tag == HID_DESIGNATOR_INDEX)
					state_push_designator(state, node->data);
				else if (node->tag == HID_DESIGNATOR_MINIMUM)
					state_set_designator_minimum(state, node->data);
				else if (node->tag == HID_DESIGNATOR_MAXIMUM)
				{
					if (!state_is_designator_minimum_set(state))
						puts("WARNING: Ignored DESIGNATOR_MAXIMUM without previous DESIGNATOR_MINIMUM");
					else
					{
						for (int k = state_get_designator_minimum(state); k <= node->data; ++k)
							state_push_designator(state, k);
						state_unset_designator_minimum(state);
					}
				}
				else if (node->tag == HID_STRING_INDEX)
					state_push_string(state, node->data);
				else if (node->tag == HID_STRING_MINIMUM)
					state_set_string_minimum(state, node->data);
				else if (node->tag == HID_STRING_MAXIMUM)
				{
					if (!state_is_string_minimum_set(state))
						puts("WARNING: Ignored STRING_MAXIMUM without previous STRING_MINIMUM");
					else
					{
						for (int k = state_get_string_minimum(state); k <= node->data; ++k)
							state_push_string(state, k);
						state_unset_string_minimum(state);
					}
				}
				else if (node->tag == HID_DELIMITER)
					state_set_delimiter(state, node->data);
			}
			
			if (!opt_create_tree)
				free(node);
		}

		description->report_tree = root;
	}
	
	return description;
}

// [[ Traverse ]]
void descriptor_tree_next(hid_report_node_t **node, int *level)
{
	if ((*node)->first_child)
	{
		*node = (*node)->first_child;
		if (level)
			++*level;
	}
	else if ((*node)->next)
		*node = (*node)->next;
	else
	{
		while (*node && !(*node)->next)
		{
			*node = (*node)->parent;
			if (level)
				--*level;
		}
		if (*node)
			*node = (*node)->next;
	}
}

hid_report_node_t *descriptor_tree_first_post(hid_report_node_t *root, int *level)
{
	hid_report_node_t *node = root;
	while (node->first_child)
	{
		node = node->first_child;
		if (level)
			++*level;
	}
	return node;
}

void descriptor_tree_next_post(hid_report_node_t **node, int *level)
{
	if ((*node)->next)
	{
		*node = (*node)->next;
		while ((*node)->first_child)
		{
			*node = (*node)->first_child;
			if (level)
				++*level;
		}
	}
	else
		*node = (*node)->parent;
}

// [[ Free ]]
static inline void free_tree(hid_report_node_t *root)
{
	hid_report_node_t *node = descriptor_tree_first_post(root, NULL);
	hid_report_node_t *toDelete;
	
	while ((toDelete = node))
	{
		descriptor_tree_next_post(&node, NULL);
		free(toDelete);
	}
}

static inline void free_items(hid_report_item_t *first_item)
{
	hid_report_item_t *item = first_item;
	hid_report_item_t *toDelete;
	
	while ((toDelete = item))
	{
		item = item->next;
		free(toDelete);
	}
}

void free_description(hid_report_description_t *description)
{
	free_tree(description->report_tree);
	free_items(description->input.front);
	free_items(description->output.front);
	free_items(description->feature.front);
	free(description);
}
