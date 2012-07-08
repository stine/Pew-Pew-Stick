/*
Pew Pew Stick Microcontroller Code
Copyright (c) 2012, Matt Stine
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "usb_profiles.h"


/**************************************************************************
 * PC Profile Descriptors
 **************************************************************************/

#define STR_MANUFACTURER	L"Matt Stine"
#define STR_PRODUCT		L"Pew Pew Stick"
#define VENDOR_ID		0xDEAD
#define PRODUCT_ID		0xBEEF

#define ENDPOINT0_SIZE		32

#define GAMEPAD_INTERFACE	0
#define GAMEPAD_ENDPOINT	3
#define GAMEPAD_SIZE		4
#define GAMEPAD_BUFFER		EP_DOUBLE_BUFFER

static const uint8_t PROGMEM endpoint_config_table[] = {
	1, EP_TYPE_INTERRUPT_IN,  EP_SIZE(GAMEPAD_SIZE) | GAMEPAD_BUFFER,
	0,
};

const static uint8_t PROGMEM device_descriptor[] = {
	18,					// bLength
	1,					// bDescriptorType
	LSB(0x0200), MSB(0x0200),       	// bcdUSB
	0,					// bDeviceClass
	0,					// bDeviceSubClass
	0,					// bDeviceProtocol
	ENDPOINT0_SIZE,				// bMaxPacketSize0
	LSB(VENDOR_ID), MSB(VENDOR_ID),		// idVendor
	LSB(PRODUCT_ID), MSB(PRODUCT_ID),	// idProduct
	LSB(0x0100), MSB(0x0100),		// bcdDevice
	1,					// iManufacturer
	2,					// iProduct
	0,					// iSerialNumber
	1					// bNumConfigurations
};

const static uint8_t PROGMEM gamepad_hid_report_desc[] = { 
	0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
	0x09, 0x05,        // USAGE (Gamepad)
	0xa1, 0x01,        // COLLECTION (Application)
	0x09, 0x01,        //   USAGE (Pointer)
	0xa1, 0x00,        //   COLLECTION (Physical)
	0x09, 0x30,        //     USAGE (X)
	0x09, 0x31,        //     USAGE (Y)
	0x15, 0x00,        //     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,  //     LOGICAL_MAXIMUM (255)
	0x75, 0x08,        //     REPORT_SIZE (8)
	0x95, 0x02,        //     REPORT_COUNT (2)
	0x81, 0x02,        //     INPUT (Data,Var,Abs)
	0xc0,              //   END_COLLECTION
	0x05, 0x09,        //   USAGE_PAGE (Button)
	0x19, 0x01,        //   USAGE_MINIMUM (Button 1)
	0x29, 0x0C,        //   USAGE_MAXIMUM (Button 12)
	0x15, 0x00,        //   LOGICAL_MINIMUM (0)
	0x25, 0x01,        //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,        //   REPORT_SIZE (1)
	0x95, 0x0C,        //   REPORT_COUNT (12)
	0x81, 0x02,        //   INPUT (Data,Var,Abs)
	0x95, 0x04,        //   REPORT_COUNT (4)
        0x81, 0x03,        //   INPUT (Constant,Var,Abs)
	0xc0               // END_COLLECTION
};

#define CONFIG1_DESC_SIZE        (9+9+9+7)
#define GAMEPAD_HID_DESC_OFFSET  (9+9)
const static uint8_t PROGMEM config1_descriptor[CONFIG1_DESC_SIZE] = {
	// configuration descriptor, USB spec 9.6.3, page 264-266, Table 9-10
	9, 					// bLength;
	0x02,					// bDescriptorType;
	LSB(CONFIG1_DESC_SIZE), MSB(CONFIG1_DESC_SIZE), // wTotalLength
	1,					// bNumInterfaces
	1,					// bConfigurationValue
	0,					// iConfiguration
	0x80,					// bmAttributes
	100,					// bMaxPower
	// interface descriptor, USB spec 9.6.5, page 267-269, Table 9-12
	9,					// bLength
	0x04,					// bDescriptorType
	GAMEPAD_INTERFACE,			// bInterfaceNumber
	0,					// bAlternateSetting
	1,					// bNumEndpoints
	0x03,					// bInterfaceClass (0x03 = HID)
	0x00,					// bInterfaceSubClass (0x00 = No Boot)
	0x00,					// bInterfaceProtocol (0x00 = No Protocol)
	0,					// iInterface
	// HID interface descriptor, HID 1.11 spec, section 6.2.1
	9,					// bLength
	0x21,					// bDescriptorType
	LSB(0x0111), MSB(0x0111),		// bcdHID
	0,					// bCountryCode
	1,					// bNumDescriptors
	0x22,					// bDescriptorType
	sizeof(gamepad_hid_report_desc),	// wDescriptorLength
	0,
	// endpoint descriptor, USB spec 9.6.6, page 269-271, Table 9-13
	7,					// bLength
	5,					// bDescriptorType
	GAMEPAD_ENDPOINT | 0x80,		// bEndpointAddress
	0x03,					// bmAttributes (0x03=intr)
	LSB(GAMEPAD_SIZE), MSB(GAMEPAD_SIZE),   // wMaxPacketSize
	1					// bInterval
};

// If you're desperate for a little extra code memory, these strings
// can be completely removed if iManufacturer, iProduct, iSerialNumber
// in the device desciptor are changed to zeros.
struct usb_string_descriptor_struct {
	uint8_t bLength;
	uint8_t bDescriptorType;
	int16_t wString[];
};
const static struct usb_string_descriptor_struct PROGMEM string0 = {
	4,
	3,
	{0x0409}
};
const static struct usb_string_descriptor_struct PROGMEM string1 = {
	sizeof(STR_MANUFACTURER),
	3,
	STR_MANUFACTURER
};
const static struct usb_string_descriptor_struct PROGMEM string2 = {
	sizeof(STR_PRODUCT),
	3,
	STR_PRODUCT
};

// This table defines which descriptor data is sent for each specific
// request from the host (in wValue and wIndex).
const static struct descriptor_list_struct {
	uint16_t	wValue;
	uint16_t	wIndex;
	const uint8_t	*addr;
	uint8_t		length;
} PROGMEM descriptor_list[] = {
	{0x0100, 0x0000, device_descriptor, sizeof(device_descriptor)},
	{0x0200, 0x0000, config1_descriptor, sizeof(config1_descriptor)},
	{0x2100, GAMEPAD_INTERFACE, config1_descriptor+GAMEPAD_HID_DESC_OFFSET, 9},
	{0x2200, GAMEPAD_INTERFACE, gamepad_hid_report_desc, sizeof(gamepad_hid_report_desc)},
	{0x0300, 0x0000, (const uint8_t *)&string0, 4},
	{0x0301, 0x0409, (const uint8_t *)&string1, sizeof(STR_MANUFACTURER)},
	{0x0302, 0x0409, (const uint8_t *)&string2, sizeof(STR_PRODUCT)}
};
#define NUM_DESC_LIST (sizeof(descriptor_list)/sizeof(struct descriptor_list_struct))



int get_endpoint_table(
  Profile profile,
  const uint8_t tableOut[])
{

  return 0;
}

int get_descriptor(
  Profile profile,
  uint16_t wValue,
  uint16_t wIndex,
  const uint8_t **descAddrOut,
  const uint8_t *descLenOut)
{

  return 0;
}

uint8_t get_report_size(
  Profile profile)
{

  return 0;
}

int format_report(
  Profile profile,
  uint8_t rawControl[],
  uint8_t rawControlLen,
  uint8_t reportOut[])
{

  return 0;
}
