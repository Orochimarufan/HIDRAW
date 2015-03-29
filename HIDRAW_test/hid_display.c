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

#include "hid.h"
#include "hid_display.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Get Usage page name
const char *get_usage_page_name(uint16_t usage_page)
{
#define UP(cnst, text) if (usage_page == HID_UP_ ## cnst) return # text
	UP(UNDEFINED, 			Undefined);
	UP(GENERIC_DESKTOP, 	Generic Desktop);
	UP(SIMULATION, 			Simulation Controls);
	UP(VR, 					VR Controls);
	UP(SPORT,				Sports Controls);
	UP(GAME,				Game Controls);
	UP(GENERIC_DEVICE,		Generic Device Controls);
	UP(KEYBOARD,			Keyboard/Keypad);
	UP(LED,					LEDs);
	UP(BUTTON,				Button);
	UP(ORDINAL,				Ordinal);
	UP(TELEPHONY,			Telephony);
	UP(CONSUMER,			Consumer);
	UP(DIGITIZER,			Digitizers);
	UP(PID,					Physical Input Devices (PID) page);
	UP(UNICODE,				Unicode);
	UP(ALPHANUM_DISPLAY,	Alphanumeric Display);
	UP(MED_INSTRUMENT,		Medical Instruments);
	UP(MONITOR_DEVICE,		Monitor Devices);
	UP(MONITOR_ENUM_VAL,	Monitor Enumerated Values);
	UP(VESA_VIRTUAL_CTL,	VESA Virtual Controls);
	UP(VESA_COMMAND,		VESA Command);
	UP(POWER_DEVICE,		Power Devices);
	UP(BATTERY_SYSTEM,		Battery Systems);
	UP(BARCODE_SCANNER,		Bar Code Scanner page);
	UP(SCALE,				Scale page);
	UP(MSR,					Magnetic Stripe Reading (MSR) Devices);
	UP(RESERVED_POS,		Reserved Point of Sale (POS) page);
	UP(CAMERA_CONTROL,		Camera Control page);
	UP(ARCADE,				Arcade page);
#undef UP
	return NULL;
}

const char *get_usage_name(uint16_t usage_page, uint16_t usage)
{
	if (usage_page == HID_UP_GENERIC_DESKTOP)
	{
#define GD(cnst, text) if (usage == HID_GD_ ## cnst) return # text
		GD(POINTER,				Pointer);
		GD(MOUSE,				Mouse);
		GD(JOYSTICK,			Joystick);
		GD(GAME_PAD,			Game Pad);
		GD(KEYBOARD,			Keyboard);
		GD(KEYPAD,				Keypad);
		GD(MULTIAXIS,			Multi-axis Game Controller);
		GD(TABLET_CTRL,			Tablet Device controls);
		GD(X,					X axis);
		GD(Y,					Y axis);
		GD(Z,					Z axis);
		GD(Rx,					Rx axis);
		GD(Ry,					Ry axis);
		GD(Rz,					Rz axis);
		GD(SLIDER,				Slider);
		GD(DIAL,				Dial);
		GD(WHEEL,				Wheel);
		GD(HAT_SWITCH,			Hat Switch);
		GD(COUNTED_BUFFER,		Counted Buffer);
		GD(BYTE_COUNT,			Byte Count);
		GD(MOTION_WAKEUP,		Motion Wakeup);
		GD(START,				Start);
		GD(SELECT,				Select);
		GD(Vx,					Vx Vector);
		GD(Vy,					Vy Vector);
		GD(Vz,					Vz Vector);
		GD(Vbrx,				Vbrx Vector);
		GD(Vbry,				Vbry Vector);
		GD(Vbrz,				Vbrz Vector);
		GD(Vno,					Vno Vector);
		GD(FEATURE_NOTIFICATION, Feature Notification);
		GD(RESOLUTION_MULTIPLY,	Resolution Multiplier);
		GD(SYSTEM_CONTROL,		System Control);
		GD(SYSTEM_POWER_DOWN,	System Power Down);
		GD(SYSTEM_SLEEP,		System Sleep);
		GD(SYSTEM_WAKE_UP,		System Wake Up);
		GD(SYSTEM_CONTEXT_MENU,	System Context Menu);
		GD(SYSTEM_MAIN_MENU,	System Main Menu);
		GD(SYSTEM_APP_MENU,		System Application Menu);
		GD(SYSTEM_MENU_HELP,	System Menu Help);
		GD(SYSTEM_MENU_EXIT,	System Menu Exit);
		GD(SYSTEM_MENU_SELECT,	System Menu Select);
		GD(SYSTEM_MENU_RIGHT,	System Menu Right);
		GD(SYSTEM_MENU_LEFT,	System Menu Right);
		GD(SYSTEM_MENU_UP,		System Menu Up);
		GD(SYSTEM_MENU_DOWN,	System Menu Down);
		GD(SYSTEM_COLD_RESTART,	System Cold Restart);
		GD(SYSTEM_WARM_RESTART,	System Warm Restart);
		GD(DPAD_UP,				D-Pad Up);
		GD(DPAD_DOWN,			D-Pad Down);
		GD(DPAD_RIGHT,			D-Pad Right);
		GD(DPAD_LEFT,			D-Pad Left);
		GD(SYSTEM_DOCK,			System Dock);
		GD(SYSTEM_UNDOCK,		System Undock);
		GD(SYSTEM_SETUP,		System Setup);
		GD(SYSTEM_BREAK,		System Break);
		GD(SYSTEM_DEBUG_BREAK,	System Debugging Break);
		GD(APP_BREAK,			Application Break);
		GD(APP_DEBUG_BREAK,		Application Debugging Break);
		GD(SYSTEM_SPEAKER_MUTE,	System Speaker Mute);
		GD(SYSTEM_HIBERNATE,	System Hibernate);
		GD(SYSTEM_DISPLAY_INVERT,		System Display Invert);
		GD(SYSTEM_DISPLAY_INTERNAL,		System Display Internal);
		GD(SYSTEM_DISPLAY_EXTERNAL,		System Display External);
		GD(SYSTEM_DISPLAY_BOTH,			System Display Both);
		GD(SYSTEM_DISPLAY_DUAL,			System Display Dual);
		GD(SYSTEM_DISPLAY_TOGGLE,		System Display Toggle);
		GD(SYSTEM_DISPLAY_SWAP,			System Display Swap);
		GD(SYSTEM_DISPLAY_LCD_AUTOSCALE, System Display LCD Autoscale);
#undef GD
	}
	
	return NULL;
}

const char *get_unit_name(uint32_t unit)
{
	uint8_t hi_nibble = unit & 0xf0;
	
	// TODO: support combinations
	unit &= 0xff;
	
#define TYPE(x) (hi_nibble == HID_UNIT_ ## x)
	if TYPE(SYSTEM) switch(unit)
	{
	case HID_UNIT_SYSTEM:
		return "System";
	case HID_UNIT_SI_LINEAR:
		return "SI Linear";
	case HID_UNIT_SI_ROTATION:
		return "SI Rotation";
	case HID_UNIT_ENGLISH_LINEAR:
		return "English Linear";
	case HID_UNIT_ENGLISH_ROTATION:
		return "English Rotation";
	case HID_UNIT_VENDOR_SYSTEM:
		return "System (Vendor-defined)";
	}
	else if TYPE(LENGTH) switch(unit)
	{
	case HID_UNIT_LENGTH:
		return "Length";
	case HID_UNIT_CENTIMETER:
		return "Centimeter";
	case HID_UNIT_RADIANS:
		return "Radians";
	case HID_UNIT_INCH:
		return "Inch";
	case HID_UNIT_DEGREES:
		return "Degrees";
	case HID_UNIT_VENDOR_LENGTH:
		return "Length (Vendor-defined)";
	}
	else if TYPE(MASS) switch(unit)
	{
	case HID_UNIT_MASS:
		return "Mass";
	case HID_UNIT_GRAM:
	case 0x22:
		return "Gram";
	case HID_UNIT_SLUG:
	case 0x24:
		return "Slug (Mass)";
	case HID_UNIT_VENDOR_MASS:
		return "Mass (Vendor-defined)";
	}
	else if TYPE(TIME) switch(unit)
	{
	case HID_UNIT_TIME:
		return "Time";
	case HID_UNIT_SECONDS:
	case 0x32:
	case 0x33:
	case 0x34:
		return "Seconds";
	case HID_UNIT_VENDOR_TIME:
		return "Time (Vendor-defined)";
	}
	else if TYPE(TEMPERATURE) switch(unit)
	{
	case HID_UNIT_TEMPERATURE:
		return "Temperature";
	case HID_UNIT_KELVIN:
	case 0x42:
		return "Kelvin";
	case HID_UNIT_FAHRENHEIT:
	case 0x44:
		return "Fahrenheit";
	case HID_UNIT_VENDOR_TEMPERATURE:
		return "Temperature (Vendor-defined)";
	}
	else if TYPE(CURRENT) switch(unit)
	{
	case HID_UNIT_CURRENT:
		return "Current";
	case HID_UNIT_AMPERE:
	case 0x52:
	case 0x53:
	case 0x54:
		return "Ampere";
	case HID_UNIT_VENDOR_CURRENT:
		return "Current (Vendor-defined)";
	}
	else if TYPE(LUMINOUS_INTENSITY) switch(unit)
	{
	case HID_UNIT_LUMINOUS_INTENSITY:
		return "Luminous Intensity";
	case HID_UNIT_CANDELA:
	case 0x62:
	case 0x63:
	case 0x64:
		return "Candela (Luminous Intensity)";
	case HID_UNIT_VENDOR_LUM_INTENS:
		return "Luminous Intensity (Vendor-defined)";
	}
#undef TYPE
	
	return NULL;
}

typedef struct strbuilder {
	char *begin;
	char *end;
	size_t length;
} strbuilder;

static inline void strbuilder_add(strbuilder *sb, const char *text)
{
	if (sb->end != sb->begin)
	{
		strncpy(sb->end, ", ", 3);
		sb->end += 2;
	}
	strncpy(sb->end, text, (sb->length - (sb->end - sb->begin)));
	sb->end += strlen(text);
}

const char *get_io_flags(uint16_t io_data)
{
	static char buffer[255];
	strbuilder sb;
	sb.begin = sb.end = buffer;
	sb.length = 255;

	if (io_data & HID_IO_CONSTANT)
		strbuilder_add(&sb, "Constant");
	if (io_data & HID_IO_VARIABLE)
		strbuilder_add(&sb, "Variable");
	if (io_data & HID_IO_RELATIVE)
		strbuilder_add(&sb, "Relative");
	if (io_data & HID_IO_WRAP)
		strbuilder_add(&sb, "Wrap");
	if (io_data & HID_IO_NONLINEAR)
		strbuilder_add(&sb, "Non-Linear");
	if (io_data & HID_IO_NO_PREFERRED)
		strbuilder_add(&sb, "No preferred");
	if (io_data & HID_IO_NULL_STATE)
		strbuilder_add(&sb, "Null state");
	if (io_data & HID_IO_VOLATILE)
		strbuilder_add(&sb, "VOLATILE");
	if (io_data & HID_IO_BUFFERED_BYTE)
		strbuilder_add(&sb, "Buffered byte");
	
	return buffer;
}

static inline hid_report_node_t *find_preceding_node(hid_report_node_t *node, uint8_t type, uint8_t tag)
{
	hid_report_node_t *found = NULL;

	for (; node && node->parent && !found; node = node->parent)
	{
		for (hid_report_node_t *this_node = node->parent->first_child; this_node && this_node != node; this_node = this_node->next)
		{
			if (this_node->type == type && this_node->tag == tag)
				found = this_node;
		}
	}
	
	return found;
}

void get_node_name(hid_report_node_t *node, const char **tag_name, const char **data_repr)
{
	static char repr_buffer[255];
	*tag_name = *data_repr = NULL;

#define TYPE(x) (node->type == x)
#define TAG(x) (node->tag == x)
#define DATA(x) (node->data == x)
#define FORMAT(var, ...) { snprintf(repr_buffer, 255, __VA_ARGS__); var = repr_buffer; }

	if TYPE(HID_TYPE_MAIN)
	{
		if TAG(HID_INPUT)
		{
			*tag_name = "Input";
			*data_repr = get_io_flags(node->data);
		}
		else if TAG(HID_OUTPUT)
		{
			*tag_name = "Output";
			*data_repr = get_io_flags(node->data);
		}
		else if TAG(HID_FEATURE)
		{
			*tag_name = "Feature";
		}
		else if TAG(HID_COLLECTION)
		{
			*tag_name = "Collection";
			
			if DATA(HID_COLLECTION_PHYSICAL)
				*data_repr = "Physical";
			else if DATA(HID_COLLECTION_APPLICATION)
				*data_repr = "Application";
			else if DATA(HID_COLLECTION_LOGICAL)
				*data_repr = "Logical";
		}
		else if TAG(HID_END_COLLECTION)
			*tag_name = "End Collection";
	}
	else if TYPE(HID_TYPE_GLOBAL)
	{
		if TAG(HID_USAGE_PAGE)
		{
			*tag_name = "Usage Page";
			*data_repr = get_usage_page_name(node->data);
			if (!*data_repr)
			{
				if (node->data >= HID_UP_VENDOR && node->data <= HID_UP_VENDOR_MAX)
					FORMAT(*data_repr, "Vendor (%04x)", node->data)
				else
					FORMAT(*data_repr, "0x%04x", node->data)
			}
		}
		else if TAG(HID_LOGICAL_MINIMUM)
			*tag_name = "Logical Minimum";
		else if TAG(HID_LOGICAL_MAXIMUM)
			*tag_name = "Logical Maximum";
		else if TAG(HID_PHYSICAL_MINIMUM)
			*tag_name = "Physical Minimum";
		else if TAG(HID_PHYSICAL_MAXIMUM)
			*tag_name = "Physical Maximum";
		else if TAG(HID_UNIT_EXPONENT)
			*tag_name = "Unit Exponent";
		else if TAG(HID_UNIT)
		{
			*tag_name = "Unit";
			*data_repr = get_unit_name(node->data);
		}
		else if TAG(HID_REPORT_SIZE)
			*tag_name = "Report Size";
		else if TAG(HID_REPORT_ID)
			*tag_name = "Report ID";
		else if TAG(HID_REPORT_COUNT)
			*tag_name = "Report Count";
		else if TAG(HID_PUSH)
			*tag_name = "Push";
		else if TAG(HID_POP)
			*tag_name = "Pop";
	}
	else if TYPE(HID_TYPE_LOCAL)
	{
		if TAG(HID_USAGE)
		{
			*tag_name = "Usage";
			
			hid_report_node_t *usage_page = find_preceding_node(node, HID_TYPE_GLOBAL, HID_USAGE_PAGE);
			if (usage_page)
				*data_repr = get_usage_name(usage_page->data, node->data);
			
			if (!*data_repr)
				FORMAT(*data_repr, "0x%04x", node->data);
		}
		else if TAG(HID_USAGE_MINIMUM)
		{
			*tag_name = "Usage Minimum";
			FORMAT(*data_repr, "%u", node->data);
		}
		else if TAG(HID_USAGE_MAXIMUM)
		{
			*tag_name = "Usage Maximum";
			FORMAT(*data_repr, "%u", node->data);
		}
		else if TAG(HID_DESIGNATOR_INDEX)
			*tag_name = "Designator Index";
		else if TAG(HID_DESIGNATOR_MINIMUM)
			*tag_name = "Designator Minimum";
		else if TAG(HID_DESIGNATOR_MAXIMUM)
			*tag_name = "Designator Maximum";
		else if TAG(HID_STRING_INDEX)
			*tag_name = "String Index";
		else if TAG(HID_STRING_MINIMUM)
			*tag_name = "String Minimum";
		else if TAG(HID_STRING_MAXIMUM)
			*tag_name = "String Maximum";
		else if TAG(HID_DELIMITER)
			*tag_name = "Delimiter";
	}
	
	if (!*tag_name)
	{
		if (node->type == HID_TYPE_MAIN)
			snprintf(repr_buffer, 255, "MAIN:   %02hhx", node->tag);
		else if (node->type == HID_TYPE_GLOBAL)
			snprintf(repr_buffer, 255, "GLOBAL: %02hhx", node->tag);
		else if (node->type == HID_TYPE_LOCAL)
			snprintf(repr_buffer, 255, "LOCAL:  %02hhx", node->tag);
		else
			snprintf(repr_buffer, 255, "UNKNOWN(%02hhx): %02hhx", node->type, node->tag);
		*tag_name = repr_buffer;
	}

#undef TYPE
#undef TAG
#undef DATA
#undef FORMAT
}

static inline void print_indents(int level)
{
	for (int i = level; i; --i)
		putchar('\t');
}

void print_descriptor_tree(hid_report_node_t *root, int indent_level)
{
	hid_report_node_t *node = root->first_child;
	
	while (node)
	{
		const char *tag, *value;

		// Indent
		//if (!node->next && node->parent && !node->first_child)
		//	--indent_level;
		for (int i = 0; i < indent_level; ++i)
			putchar('\t');

		// Print item
		get_node_name(node, &tag, &value);
		if (tag)
			printf("%s ", tag);
		else
			printf("0x%02hhx ", node->tag);
		if (value)
			printf("(%s)", value);
		else
			printf("(%i)", node->data);
		
		putchar('\n');
		
		// Continue
		descriptor_tree_next(&node, &indent_level);
	}
}

void print_descriptor_items(hid_report_item_set_t *set, int indent_level)
{
	char page_buf[32], usage_buf[32];
	const char *page, *usage, *type;

	for (hid_report_item_t *item = set->front; item; item = item->next)
	{
		print_indents(indent_level);
		
		if (item->usage == 0 && item->io_flags == HID_IO_CONSTANT)
		{
			printf("(%i) %i bit Padding\n", item->report_id, item->report_size);
			continue;
		}
		
		page = get_usage_page_name(item->usage_page);
		usage = get_usage_name(item->usage_page, item->usage);
		
		if (!page)
		{
			snprintf(page_buf, 32, "0x%04hx", item->usage_page);
			page = page_buf;
		}
		
		if (!usage)
		{
			if (item->usage_page == HID_UP_BUTTON)
				snprintf(usage_buf, 32, "%hi", item->usage);
			else
				snprintf(usage_buf, 32, "0x%04hx", item->usage);
			usage = usage_buf;
		}
		
		if (item->type == HID_INPUT)
			type = "Input";
		else if (item->type == HID_OUTPUT)
			type = "Output";
		else if (item->type == HID_FEATURE)
			type = "Feature";
		else
			type = "[Unknown Type]";
		
		printf("(%i) %i bit %s %s %s (%s)\t[%i < lv < %i, %i < pv < %i (%s ^%i)]\n",
				item->report_id, item->report_size,
				page, usage, type, get_io_flags(item->io_flags),
				item->logical_minimum, item->logical_maximum,
				item->physical_minimum, item->physical_maximum,
				get_unit_name(item->unit), item->unit_exponent);
	}
}

typedef struct bit_position_t {
	size_t byte;
	uint8_t bit;
} bit_position_t;

void bit_position_advance(bit_position_t *pos, unsigned bits)
{	
	pos->byte += bits / 8;
	pos->bit += bits % 8;
	
	if (pos->bit & 0b1000)
	{
		pos->bit &= 0b0111;
		++pos->byte;
	}
}

uint64_t bit_position_read_at(uint8_t *data, bit_position_t *pos, uint8_t bits)
{
	assert(bits <= 64 && "bit_position_read_at() only supports up to 64 bits!");
	//assert(bits <= 8 || bits == 16 || bits == 32 || bits == 64 && "bit_position_read_at(): Only 2-,4- and 8-byte reads supported");
	
	uint8_t *first_byte = data + pos->byte;
	
	// multibyte
	if (!pos->bit && !(bits % 8))
	{
		uint8_t bytes = bits / 8;
		pos->byte += bytes;
		if (bytes == 1)
			return *(uint8_t*)first_byte;
		else if (bytes == 2)
			return *(uint16_t*)first_byte;
		else if (bytes == 4)
			return *(uint32_t*)first_byte;
		else if (bytes == 8)
			return *(uint64_t*)first_byte;
		assert(false);
	}
	// other
	else
	{
		uint64_t result;
		uint64_t bitmask = 0;
		
		for (int i = 0; i < bits; ++i)
			bitmask |= 1 << i;
		
		bitmask <<= pos->bit;
		
		result = ((*(uint64_t*)first_byte) & bitmask) >> pos->bit;
		
		bit_position_advance(pos, bits);
		
		return result;
	}
}

int64_t bit_position_signed_read_at(uint8_t *data, bit_position_t *pos, uint8_t bits)
{
	uint64_t value = bit_position_read_at(data, pos, bits);
	
	// Apply Two's complement
	uint8_t sign_bit = (uint8_t)(value >> bits);
	
	if (!sign_bit)
		return (int64_t)value;
	else
		return -(1 << bits) + (value & ~ (1 << bits));
}

const char **generate_item_headings(hid_report_item_set_t *descriptor)
{
	const char **headings = memset(malloc(sizeof(const char *) * descriptor->count), 0, sizeof(const char *) * descriptor->count);
	int i = 0;
	
	for (hid_report_item_t *item = descriptor->front; item; item = item->next)
	{
		if (item->usage_page == HID_UP_GENERIC_DESKTOP)
		{
			if (item->usage == HID_GD_X)
				headings[i] = "X";
			else if (item->usage == HID_GD_Y)
				headings[i] = "Y";
			else if (item->usage == HID_GD_Z)
				headings[i] = "Z";
			else if (item->usage == HID_GD_Rx)
				headings[i] = "Rx";
			else if (item->usage == HID_GD_Ry)
				headings[i] = "Ry";
			else if (item->usage == HID_GD_Rz)
				headings[i] = "Rz";
			else if (item->usage == HID_GD_HAT_SWITCH)
				headings[i] = "HAT";
			else
				headings[i] = get_usage_name(HID_UP_GENERIC_DESKTOP, item->usage);
		}
		else if (item->usage_page == HID_UP_BUTTON)
		{
			static const char* buttons[32] = {"B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "B10",
												"B11", "B12", "B13", "B14", "B15", "B16", "B17", "B18", "B19", "B20",
												"B21", "B22", "B23", "B24", "B25", "B26", "B27", "B28", "B29", "B30",
												"B31", "B32"};
			headings[i] = item->usage <= 32 ? buttons[item->usage - 1] : NULL;
		}
		++i;
	}
	
	return headings;
}

void print_report(hid_report_item_set_t *descriptor, uint8_t *report, const char **headings)
{
	int i = 0, report_id = 0;
	bit_position_t pos;
	memset(&pos, 0, sizeof(pos));
	
	if (descriptor->front->report_id != 0)
	{
		report_id = bit_position_read_at(report, &pos, 8);
		printf("(%i) ", report_id);
	}
	
	for (hid_report_item_t *item = descriptor->front; item; ++i && (item = item->next))
	{
		if (report_id != item->report_id)
			continue;

		if (item->usage == 0 && item->io_flags == HID_IO_CONSTANT)
		{
			// Skip padding
			bit_position_advance(&pos, item->report_size);
			continue;
		}
		
		if (headings && headings[i])
			printf("%s=", headings[i]);

		// unsigned
		if (item->logical_minimum >= 0 && item->logical_maximum >= 0)
			printf("%lu ", bit_position_read_at(report, &pos, item->report_size));
		else
			printf("%li ", bit_position_signed_read_at(report, &pos, item->report_size));
	}
}
