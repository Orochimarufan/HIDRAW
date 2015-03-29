// HID Report Descriptor Constants

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

// 1. Types
// See HID 1.11 6.2.2.2 Short Items and HID 1.11 6.2.2.3 Long Items
#define HID_TYPE_MAIN		0
#define HID_TYPE_GLOBAL		1
#define HID_TYPE_LOCAL		2
#define HID_TYPE_RESERVED	3
#define HID_TYPE_LONG		7

// 2. Tags
// See https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/include/linux/hid.h?id=019e129f9b2d582e5901c0594427cb4026daa413
// 2.1 Main Tags
#define HID_INPUT				0x08
#define HID_OUTPUT				0x09
#define HID_FEATURE				0x0b
#define HID_COLLECTION			0x0a
#define HID_END_COLLECTION		0x0c

// 2.2 Global Tags
#define HID_USAGE_PAGE			0x00
#define HID_LOGICAL_MINIMUM		0x01
#define HID_LOGICAL_MAXIMUM		0x02
#define HID_PHYSICAL_MINIMUM	0x03
#define HID_PHYSICAL_MAXIMUM	0x04
#define HID_UNIT_EXPONENT		0x05
#define HID_UNIT				0x06
#define HID_REPORT_SIZE			0x07
#define HID_REPORT_ID			0x08
#define HID_REPORT_COUNT		0x09
#define HID_PUSH				0x0a
#define HID_POP					0x0b

// 2.3 Local Tags
#define HID_USAGE				0x00
#define HID_USAGE_MINIMUM		0x01
#define HID_USAGE_MAXIMUM		0x02
#define HID_DESIGNATOR_INDEX	0x03
#define HID_DESIGNATOR_MINIMUM	0x04
#define HID_DESIGNATOR_MAXIMUM	0x05
#define HID_STRING_INDEX		0x07
#define HID_STRING_MINIMUM		0x08
#define HID_STRING_MAXIMUM		0x09
#define HID_DELIMITER			0x0a

// 3. Collections
#define HID_COLLECTION_PHYSICAL		0x00
#define HID_COLLECTION_APPLICATION	0x01
#define HID_COLLECTION_LOGICAL		0x02

// 4. Input/Output Type
#define HID_IO_CONSTANT			0x001
#define HID_IO_VARIABLE			0x002
#define HID_IO_RELATIVE			0x004
#define HID_IO_WRAP				0x008
#define HID_IO_NONLINEAR		0x010
#define HID_IO_NO_PREFERRED		0x020
#define HID_IO_NULL_STATE		0x040
#define HID_IO_VOLATILE			0x080
#define HID_IO_BUFFERED_BYTE	0x100

// 5. Units
// See 6.2.2.7 Global Items -> Remarks (2)
// 5.1 System
#define HID_UNIT_SYSTEM				0x00
#define HID_UNIT_SI_LINEAR			0x01
#define HID_UNIT_SI_ROTATION		0x02
#define HID_UNIT_ENGLISH_LINEAR		0x03
#define HID_UNIT_ENGLISH_ROTATION	0x04
#define HID_UNIT_VENDOR_SYSTEM		0x0f

// 5.2 Length
#define HID_UNIT_LENGTH				0x10
#define HID_UNIT_CENTIMETER			0x11
#define HID_UNIT_RADIANS			0x12
#define HID_UNIT_INCH				0x13
#define HID_UNIT_DEGREES			0x14
#define HID_UNIT_VENDOR_LENGTH		0x1f

// 5.3 Mass
#define HID_UNIT_MASS				0x20
#define HID_UNIT_GRAM				0x21
// also HID_UNIT_GRAM				0x22
#define HID_UNIT_SLUG				0x23
// also HID_UNIT_SLUG				0x24
#define HID_UNIT_VENDOR_MASS		0x2f

// 5.4 Time
#define HID_UNIT_TIME				0x30
#define HID_UNIT_SECONDS			0x31
// also HID_UNIT_SECONDS			0x32
// also HID_UNIT_SECONDS			0x33
// also HID_UNIT_SECONDS			0x43
#define HID_UNIT_VENDOR_TIME		0x3f

// 5.5 Temperature
#define HID_UNIT_TEMPERATURE		0x40
#define HID_UNIT_KELVIN				0x41
// also HID_UNIT_KELVIN				0x42
#define HID_UNIT_FAHRENHEIT			0x43
// also HID_UNIT_FAHRENHEIT			0x44
#define HID_UNIT_VENDOR_TEMPERATURE	0x4f

// 5.6 Current
#define HID_UNIT_CURRENT			0x50
#define HID_UNIT_AMPERE				0x51
// also HID_UNIT_AMPERE				0x52
// also HID_UNIT_AMPERE				0x53
// also HID_UNIT_AMPERE				0x54
#define HID_UNIT_VENDOR_CURRENT		0x5f

// 5.7 Luminous Intensity
#define HID_UNIT_LUMINOUS_INTENSITY	0x60
#define HID_UNIT_CANDELA			0x61
// also HID_UNIT_CANDELA			0x62
// also HID_UNIT_CANDELA			0x63
// also HID_UNIT_CANDELA			0x64
#define HID_UNIT_VENDOR_LUM_INTENS	0x6f

// A. Usage Pages
// See http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
#define HID_UP_UNDEFINED		0x00
#define HID_UP_GENERIC_DESKTOP	0x01
#define HID_UP_SIMULATION		0x02
#define HID_UP_VR				0x03
#define HID_UP_SPORT			0x04
#define HID_UP_GAME				0x05
#define HID_UP_GENERIC_DEVICE	0x06
#define HID_UP_KEYBOARD			0x07
#define HID_UP_LED				0x08
#define HID_UP_BUTTON			0x09
#define HID_UP_ORDINAL			0x0a
#define HID_UP_TELEPHONY		0x0b
#define HID_UP_CONSUMER			0x0c
#define HID_UP_DIGITIZER		0x0d
#define HID_UP_PID				0x0f
#define HID_UP_UNICODE			0x10
#define HID_UP_ALPHANUM_DISPLAY	0x14
#define HID_UP_MED_INSTRUMENT	0x40
// Monitor Control
#define HID_UP_MONITOR_DEVICE	0x80
#define HID_UP_MONITOR_ENUM_VAL	0x81
#define HID_UP_VESA_VIRTUAL_CTL	0x82
#define HID_UP_VESA_COMMAND		0x83
// Power Control
#define HID_UP_POWER_DEVICE		0x84
#define HID_UP_BATTERY_SYSTEM	0x85
// Point of Sale
#define HID_UP_BARCODE_SCANNER	0x8c
#define HID_UP_SCALE			0x8d
#define HID_UP_MSR				0x8e
#define HID_UP_RESERVED_POS		0x8f
// Other
#define HID_UP_CAMERA_CONTROL	0x90
#define HID_UP_ARCADE			0x91
#define HID_UP_VENDOR			0xff00
#define HID_UP_VENDOR_MAX		0xffff

// B. Usages
// B.1 General Desktop (0x01)
#define HID_GD_POINTER				0x01
#define HID_GD_MOUSE				0x02
#define HID_GD_JOYSTICK				0x04
#define HID_GD_GAME_PAD				0x05
#define HID_GD_KEYBOARD				0x06
#define HID_GD_KEYPAD				0x07
#define HID_GD_MULTIAXIS			0x08
#define HID_GD_TABLET_CTRL			0x09
#define HID_GD_X					0x30
#define HID_GD_Y					0x31
#define HID_GD_Z					0x32
#define HID_GD_Rx					0x33
#define HID_GD_Ry					0x34
#define HID_GD_Rz					0x35
#define HID_GD_SLIDER				0x36
#define HID_GD_DIAL					0x37
#define HID_GD_WHEEL				0x38
#define HID_GD_HAT_SWITCH			0x39
#define HID_GD_COUNTED_BUFFER		0x3a
#define HID_GD_BYTE_COUNT			0x3b
#define HID_GD_MOTION_WAKEUP		0x3c
#define HID_GD_START				0x3d
#define HID_GD_SELECT				0x3e
#define HID_GD_Vx					0x40
#define HID_GD_Vy					0x41
#define HID_GD_Vz					0x42
#define HID_GD_Vbrx					0x43
#define HID_GD_Vbry					0x44
#define HID_GD_Vbrz					0x45
#define HID_GD_Vno					0x46
#define HID_GD_FEATURE_NOTIFICATION	0x47
#define HID_GD_RESOLUTION_MULTIPLY	0x48
#define HID_GD_SYSTEM_CONTROL		0x80
#define HID_GD_SYSTEM_POWER_DOWN	0x81
#define HID_GD_SYSTEM_SLEEP			0x82
#define HID_GD_SYSTEM_WAKE_UP		0x83
#define HID_GD_SYSTEM_CONTEXT_MENU	0x84
#define HID_GD_SYSTEM_MAIN_MENU		0x85
#define HID_GD_SYSTEM_APP_MENU		0x86
#define HID_GD_SYSTEM_MENU_HELP		0x87
#define HID_GD_SYSTEM_MENU_EXIT		0x88
#define HID_GD_SYSTEM_MENU_SELECT	0x89
#define HID_GD_SYSTEM_MENU_RIGHT	0x8a
#define HID_GD_SYSTEM_MENU_LEFT		0x8b
#define HID_GD_SYSTEM_MENU_UP		0x8c
#define HID_GD_SYSTEM_MENU_DOWN		0x8d
#define HID_GD_SYSTEM_COLD_RESTART	0x8e
#define HID_GD_SYSTEM_WARM_RESTART	0x8f
#define HID_GD_DPAD_UP				0x90
#define HID_GD_DPAD_DOWN			0x91
#define HID_GD_DPAD_RIGHT			0x92
#define HID_GD_DPAD_LEFT			0x93
#define HID_GD_SYSTEM_DOCK			0xa0
#define HID_GD_SYSTEM_UNDOCK		0xa1
#define HID_GD_SYSTEM_SETUP			0xa2
#define HID_GD_SYSTEM_BREAK			0xa3
#define HID_GD_SYSTEM_DEBUG_BREAK	0xa4
#define HID_GD_APP_BREAK			0xa5
#define HID_GD_APP_DEBUG_BREAK		0xa6
#define HID_GD_SYSTEM_SPEAKER_MUTE	0xa7
#define HID_GD_SYSTEM_HIBERNATE		0xa8
// System Display *
#define HID_GD_SYSTEM_DISPLAY_INVERT		0xb0
#define HID_GD_SYSTEM_DISPLAY_INTERNAL		0xb1
#define HID_GD_SYSTEM_DISPLAY_EXTERNAL		0xb2
#define HID_GD_SYSTEM_DISPLAY_BOTH			0xb3
#define HID_GD_SYSTEM_DISPLAY_DUAL			0xb4
#define HID_GD_SYSTEM_DISPLAY_TOGGLE		0xb5
#define HID_GD_SYSTEM_DISPLAY_SWAP			0xb6
#define HID_GD_SYSTEM_DISPLAY_LCD_AUTOSCALE	0xb7

// B.2 Simulation (0x02)
#define HID_SIM_FLIGHT_SIM_DEVICE			0x01
#define HID_SIM_AUTOMOBILE_SIM_DEVICE		0x02
#define HID_SIM_TANK_SIM_DEVICE				0x03
#define HID_SIM_SPACESHIP_SIM_DEVICE		0x04
#define HID_SIM_SUBMARINE_SIM_DEVICE		0x05
#define HID_SIM_SAILING_SIM_DEVICE			0x06
#define HID_SIM_MOTORCYCLE_SIM_DEVICE		0x07
#define HID_SIM_SPORTS_SIM_DEVICE			0x08
#define HID_SIM_AIRPLANE_SIM_DEVICE			0x09
#define HID_SIM_HELICOPTER_SIM_DEVICE		0x0a
#define HID_SIM_MAGIC_CARPET_SIM_DEVICE		0x0b
#define HID_SIM_BICYCLE_SIM_DEVICE			0x0c
#define HID_SIM_FLIGHT_CONTROL_STICK		0x20
#define HID_SIM_FLIGHT_STICK				0x21
#define HID_SIM_CYCLIC_CONTROL				0x22
#define HID_SIM_CYCLIC_TRIM					0x23
#define HID_SIM_FLIGHT_YOKE					0x24
#define HID_SIM_TRACK_CONTROL				0x25
#define HID_SIM_AILERON						0xb0
#define HID_SIM_AILERON_TRIM				0xb1
#define HID_SIM_ANTI_TORQUE_CONTROL			0xb2
#define HID_SIM_AUTOPILOT_ENABLE			0xb3
#define HID_SIM_CHAFF_RELEASE				0xb4
#define HID_SIM_COLLECTIVE_CONTROL			0xb5
#define HID_SIM_DIVE_BRAKE					0xb6
#define HID_SIM_ELECTRONIC_COUNTERMEASURES	0xb7
#define HID_SIM_ELEVATOR					0xb8
#define HID_SIM_ELEVATOR_TRIM				0xb9
#define HID_SIM_RUDDER						0xba
#define HID_SIM_THROTTLE					0xbb
#define HID_SIM_FLIGHT_COMMUNICATIONS		0xbc
#define HID_SIM_FLARE_RELEASE				0xbd
#define HID_SIM_LANDING_GEAR				0xbe
#define HID_SIM_TOE_BRAKE					0xbf
#define HID_SIM_TRIGGER						0xc0
#define HID_SIM_WEAPONS_ARM					0xc1
#define HID_SIM_WEAPONS_SELECT				0xc2
#define HID_SIM_WING_FLAPS					0xc3
#define HID_SIM_ACCELERATOR					0xc4
#define HID_SIM_BRAKE						0xc5
#define HID_SIM_CLUTCH						0xc6
#define HID_SIM_SHIFTER						0xc7
#define HID_SIM_STEERING					0xc8
#define HID_SIM_TURRET_DIRECTION			0xc9
#define HID_SIM_BARREL_ELEVATION			0xca
#define HID_SIM_DIVE_PLANE					0xcb
#define HID_SIM_BALLAST						0xcc
#define HID_SIM_BICYCLE_CRANK				0xcd
#define HID_SIM_HANDLE_BARS					0xce
#define HID_SIM_FRONT_BRAKE					0xcf
#define HID_SIM_REAR_BRAKE					0xd0

// B.3 VR Controls (0x03)
#define HID_VR_BELT					0x01
#define HID_VR_BODY_SUIT			0x02
#define HID_VR_FLEXOR				0x03
#define HID_VR_GLOVE				0x04
#define HID_VR_HEAD_TRACKER			0x05
#define HID_VR_HEAD_MOUNTED_DISPLAY	0x06
#define HID_VR_HAND_TRACKER			0x07
#define HID_VR_OCULOMETER			0x08
#define HID_VR_VEST					0x09
#define HID_VR_ANIMATRONIC_DEVICE	0x0a
#define HID_VR_STEREO_ENABLE		0x20
#define HID_VR_DISPLAY_ENABLE		0x21

// B.4 TODO: Sports Controls (0x04)

// B.5 Game Controls (0x05)
#define HID_GAME_3D_GAME_CONTROLLER	0x01
#define HID_GAME_PINBALL_DEVICE		0x02
#define HID_GAME_GUN_DEVICE			0x03
#define HID_GAME_POINT_OF_VIEW		0x20
#define HID_GAME_TURN_RIGHTLEFT		0x21
#define HID_GAME_PITCH_FORBACK		0x22
#define HID_GAME_ROLL_RIGHTLEFT		0x23
#define HID_GAME_MOVE_RIGHTLEFT		0x24
#define HID_GAME_MOVE_FORBACK		0x25
#define HID_GAME_MOVE_UPDOWN		0x26
#define HID_GAME_LEAN_RIGHTLEFT		0x27
#define HID_GAME_LEAN_FORBACK		0x28
#define HID_GAME_HEIGHT_OF_POV		0x29
#define HID_GAME_FLIPPER			0x2a
#define HID_GAME_SECONDARY_FLIPPER	0x2b
#define HID_GAME_BUMP				0x2c
#define HID_GAME_NEW_GAME			0x2d
#define HID_GAME_SHOOT_BALL			0x2e
#define HID_GAME_PLAYER				0x2f
#define HID_GAME_GUN_BOLT			0x30
#define HID_GAME_GUN_CLIP			0x31
#define HID_GAME_GUN_SELECTOR		0x32
#define HID_GAME_GUN_SINGLE_SHOT	0x33
#define HID_GAME_GUN_BURST			0x34
#define HID_GAME_GUN_AUTOMATIC		0x35
#define HID_GAME_GUN_SAFETY			0x36
#define HID_GAME_GAMEPAD_FIRE_JUMP	0x37
#define HID_GAME_GAMEPAD_TRIGGER	0x38

// B.6 Generic Device Controls (0x06)
#define HID_DEV_BATTERY_STRENGTH				0x20
#define HID_DEV_WIRELESS_CHANNEL				0x21
#define HID_DEV_WIRELESS_ID						0x22
#define HID_DEV_DISCOVER_WIRELESS				0x23
#define HID_DEV_SECURITY_CODE_CHARACTER_ENTERED	0x24
#define HID_DEV_SECURITY_CODE_CHARACTER_ERASED	0x25
#define HID_DEV_SECURITY_CODE_CLEARED			0x26

// B.7 Keyboard/Keypad (0x07)
#define HID_KEY_ERROR_ROLL_OVER		0x01
#define HID_KEY_POST_FAIL			0x02
#define HID_KEY_ERROR_UNDEFINED		0x03
#define HID_KEY_A					0x04
#define HID_KEY_B					0x05
#define HID_KEY_C					0x06
#define HID_KEY_D					0x07
#define HID_KEY_E					0x08
#define HID_KEY_F					0x09
#define HID_KEY_G					0x0a
#define HID_KEY_H					0x0b
#define HID_KEY_I					0x0c
#define HID_KEY_J					0x0d
#define HID_KEY_K					0x0e
#define HID_KEY_L					0x0f
#define HID_KEY_M					0x10
#define HID_KEY_N					0x11
#define HID_KEY_O					0x12
#define HID_KEY_P					0x13
#define HID_KEY_Q					0x14
#define HID_KEY_R					0x15
#define HID_KEY_S					0x16
#define HID_KEY_T					0x17
#define HID_KEY_U					0x18
#define HID_KEY_V					0x19
#define HID_KEY_W					0x1a
#define HID_KEY_X					0x1b
#define HID_KEY_Y					0x1c
#define HID_KEY_Z					0x1d
#define HID_KEY_1					0x1e
#define HID_KEY_2					0x1f
#define HID_KEY_3					0x20
#define HID_KEY_4					0x21
#define HID_KEY_5					0x22
#define HID_KEY_6					0x23
#define HID_KEY_7					0x24
#define HID_KEY_8					0x25
#define HID_KEY_9					0x26
#define HID_KEY_0					0x27
#define HID_KEY_ENTER				0x28
#define HID_KEY_ESCAPE				0x29
#define HID_KEY_DELETE				0x2a
#define HID_KEY_TAB					0x2b
#define HID_KEY_SPACE				0x2c
#define HID_KEY_MINUS				0x2d
#define HID_KEY_EQUALS				0x2e
#define HID_KEY_OPEN_BRACKET		0x2f
#define HID_KEY_CLOSE_BRACKET		0x30
#define HID_KEY_BACKSLASH			0x31
#define HID_KEY_NONUS_SHARP			0x32
#define HID_KEY_SEMICOLON			0x33
#define HID_KEY_APOSTROPHE			0x34
#define HID_KEY_GRAVE_ACCENT		0x35
#define HID_KEY_COMMA				0x36
#define HID_KEY_DOT					0x37
#define HID_KEY_SLASH				0x38
#define HID_KEY_CAPS_LOCK			0x39
#define HID_KEY_F1					0x3a
#define HID_KEY_F2					0x3b
#define HID_KEY_F3					0x3c
#define HID_KEY_F4					0x3d
#define HID_KEY_F5					0x3e
#define HID_KEY_F6					0x3f
#define HID_KEY_F7					0x40
#define HID_KEY_F8					0x41
#define HID_KEY_F9					0x42
#define HID_KEY_F10					0x43
#define HID_KEY_F11					0x44
#define HID_KEY_F12					0x45
#define HID_KEY_PRINT_SCREEN		0x46
#define HID_KEY_SCROLL_LOCK			0x47
#define HID_KEY_PAUSE				0x48
#define HID_KEY_INSERT				0x49
#define HID_KEY_HOME				0x4a
#define HID_KEY_PAGE_UP				0x4b
#define HID_KEY_DELETE_FORWARD		0x4c
#define HID_KEY_END					0x4d
#define HID_KEY_PAGE_DOWN			0x4e
#define HID_KEY_RIGHT_ARROW			0x4f
#define HID_KEY_LEFT_ARROW			0x50
#define HID_KEY_DOWN_ARROW			0x51
#define HID_KEY_UP_ARROW			0x52
#define HID_KEY_KEYPAD_NUM_LOCK		0x53
#define HID_KEY_KEYPAD_DIVIDE		0x54
#define HID_KEY_KEYPAD_MULTIPLY		0x55
#define HID_KEY_KEYPAD_MINUS		0x56
#define HID_KEY_KEYPAD_PLUS			0x57
#define HID_KEY_KEYPAD_ENTER		0x58
#define HID_KEY_KEYPAD_1			0x59
#define HID_KEY_KEYPAD_2			0x5a
#define HID_KEY_KEYPAD_3			0x5b
#define HID_KEY_KEYPAD_4			0x5c
#define HID_KEY_KEYPAD_5			0x5d
#define HID_KEY_KEYPAD_6			0x5e
#define HID_KEY_KEYPAD_7			0x5f
#define HID_KEY_KEYPAD_8			0x60
#define HID_KEY_KEYPAD_9			0x61
#define HID_KEY_KEYPAD_0			0x62
#define HID_KEY_KEYPAD_POINT		0x63
#define HID_KEY_NONUS_BACKSLASH		0x64
#define HID_KEY_APPLICATION			0x65
#define HID_KEY_POWER				0x66
#define HID_KEY_KEYPAD_EQUALS		0x67
#define HID_KEY_F13					0x68
#define HID_KEY_F14					0x69
#define HID_KEY_F15					0x6a
#define HID_KEY_F16					0x6b
#define HID_KEY_F17					0x6c
#define HID_KEY_F18					0x6d
#define HID_KEY_F19					0x6e
#define HID_KEY_F20					0x6f
#define HID_KEY_F21					0x70
#define HID_KEY_F22					0x71
#define HID_KEY_F23					0x72
#define HID_KEY_F24					0x73
#define HID_KEY_EXECUTE				0x74
#define HID_KEY_HELP				0x75
#define HID_KEY_MENU				0x76
#define HID_KEY_SELECT				0x77
#define HID_KEY_STOP				0x78
#define HID_KEY_AGAIN				0x79
#define HID_KEY_UNDO				0x7a
#define HID_KEY_CUT					0x7b
#define HID_KEY_COPY				0x7c
#define HID_KEY_PASTE				0x7d
#define HID_KEY_FIND				0x7e
#define HID_KEY_MUTE				0x7f
#define HID_KEY_VOLUME_UP			0x80
#define HID_KEY_VOLUME_DOWN			0x81
#define HID_KEY_LOCKING_CAPS		0x82
#define HID_KEY_LOCKING_NUM			0x83
#define HID_KEY_LOCKING_SCROLL		0x84
#define HID_KEY_KEYPAD_COMMA		0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN	0x86
#define HID_KEY_INTERNATIONAL_1		0x87
#define HID_KEY_INTERNATIONAL_2		0x88
#define HID_KEY_INTERNATIONAL_3		0x89
#define HID_KEY_INTERNATIONAL_4		0x8a
#define HID_KEY_INTERNATIONAL_5		0x8b
#define HID_KEY_INTERNATIONAL_6		0x8c
#define HID_KEY_INTERNATIONAL_7		0x8d
#define HID_KEY_INTERNATIONAL_8		0x8e
#define HID_KEY_INTERNATIONAL_9		0x8f
#define HID_KEY_LANG_1				0x90
#define HID_KEY_LANG_2				0x91
#define HID_KEY_LANG_3				0x92
#define HID_KEY_LANG_4				0x93
#define HID_KEY_LANG_5				0x94
#define HID_KEY_LANG_6				0x95
#define HID_KEY_LANG_7				0x96
#define HID_KEY_LANG_8				0x97
#define HID_KEY_LANG_9				0x98
#define HID_KEY_ALTERNATE_ERASE		0x99
#define HID_KEY_SYSREQATTENTION		0x9a
#define HID_KEY_CANCEL				0x9b
#define HID_KEY_CLEAR				0x9c
#define HID_KEY_PRIOR				0x9d
#define HID_KEY_RETURN				0x9e
#define HID_KEY_SEPARATOR			0x9f
#define HID_KEY_OUT					0xa0
#define HID_KEY_OPER				0xa1
#define HID_KEY_CLEAR_AGAIN			0xa2
#define HID_KEY_CRSEL_PROPS			0xa3
#define HID_KEY_EXSEL				0xa4
#define HID_KEY_KEYPAD_00			0xb0
#define HID_KEY_KEYPAD_000			0xb1
#define HID_KEY_THOUSANDS_SEP		0xb2
#define HID_KEY_DECIMAL_SEP			0xb3
#define HID_KEY_CURRENCY_UNIT		0xb4
#define HID_KEY_CURRENCY_SUBUNIT	0xb5
#define HID_KEY_KEYPAD_OPEN_PAREN	0xb6
#define HID_KEY_KEYPAD_CLOSE_PAREN	0xb7
#define HID_KEY_KEYPAD_OPEN_BRACE	0xb8
#define HID_KEY_KEYPAD_CLOSE_BRACE	0xb9
#define HID_KEY_KEYPAD_TAB			0xba
#define HID_KEY_KEYPAD_BACKSPACE	0xbb
#define HID_KEY_KEYPAD_A			0xbc
#define HID_KEY_KEYPAD_B			0xbd
#define HID_KEY_KEYPAD_C			0xbe
#define HID_KEY_KEYPAD_D			0xbf
#define HID_KEY_KEYPAD_E			0xc0
#define HID_KEY_KEYPAD_F			0xc1
#define HID_KEY_KEYPAD_XOR			0xc2
#define HID_KEY_KEYPAD_POWER		0xc3
#define HID_KEY_KEYPAD_MODULO		0xc4
#define HID_KEY_KEYPAD_LESSTHAN		0xc5
#define HID_KEY_KEYPAD_GREATERTHAN	0xc6
#define HID_KEY_KEYPAD_AND			0xc7
#define HID_KEY_KEYPAD_LOGICAL_AND	0xc8
#define HID_KEY_KEYPAD_OR			0xc9
#define HID_KEY_KEYPAD_LOGICAL_OR	0xca
#define HID_KEY_KEYPAD_COLON		0xcb
#define HID_KEY_KEYPAD_SHARP		0xcc
#define HID_KEY_KEYPAD_SPACE		0xcd
#define HID_KEY_KEYPAD_COMM_AT		0xce
#define HID_KEY_KEYPAD_FACTORIAL	0xcf
#define HID_KEY_KEYPAD_MEM_STORE	0xd0
#define HID_KEY_KEYPAD_MEM_RECALL	0xd1
#define HID_KEY_KEYPAD_MEM_CLEAR	0xd2
#define HID_KEY_KEYPAD_MEM_ADD		0xd3
#define HID_KEY_KEYPAD_MEM_SUBTRACT	0xd4
#define HID_KEY_KEYPAD_MEM_MULTIPLY	0xd5
#define HID_KEY_KEYPAD_MEM_DIVIDE	0xd6
#define HID_KEY_KEYPAD_SIGN			0xd7
#define HID_KEY_KEYPAD_CLEAR		0xd8
#define HID_KEY_KEYPAD_CLEAR_ENTRY	0xd9
#define HID_KEY_KEYPAD_BINARY		0xda
#define HID_KEY_KEYPAD_OCTAL		0xdb
#define HID_KEY_KEYPAD_DECIMAL		0xdc
#define HID_KEY_KEYPAD_HEXADECIMAL	0xdd
#define HID_KEY_LEFT_CONTROL		0xe0
#define HID_KEY_LEFT_SHIFT			0xe1
#define HID_KEY_LEFT_ALT			0xe2
#define HID_KEY_LEFT_GUI			0xe3
#define HID_KEY_RIGHT_CONTROL		0xe4
#define HID_KEY_RIGHT_SHIFT			0xe5
#define HID_KEY_RIGHT_ALT			0xe6
#define HID_KEY_RIGHT_GUI			0xe7

// B.8 TODO: LEDs (0x08)

// B.9 Buttons (0x09)
// The Buttons page defines 65535 distinct Button usages: Button 1 - Button 6553B.

// B.10 Ordinal (0x0a)
// Allows multiple instances of other Usage Pages

// B.11 TODO: Telephony (0x0b)

// B.12 TODO: Consumer Page (0x0c)

// B.13 TODO: Digitizer (0x0d)

// B.14 Unicode (0x10)
// Used to display things using "Alphanumeric Display Page"

// B.15 TODO: Alphanumeric Display Page (0x14)

// B.16 TODO: Medical Instrument Page (0x40)
