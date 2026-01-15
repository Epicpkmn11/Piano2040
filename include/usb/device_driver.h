#ifndef USB_DEVICE_DRIVER_H_
#define USB_DEVICE_DRIVER_H_

#include "device/usbd_pvt.h"

#include <stdint.h>

#define USBD_MANUFACTURER "Piano2040"
#define USBD_PRODUCT_BASE "Piano Keyboard"

#define USBD_MAX_POWER_MAX (500)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	USB_MODE_KEYBOARD,
	USB_MODE_MIDI,
	USB_MODE_DEBUG,
} usb_mode_t;

enum {
	USBD_STR_LANGUAGE,
	USBD_STR_MANUFACTURER,
	USBD_STR_PRODUCT,
	USBD_STR_SERIAL,
};

typedef struct {
	uint8_t *data;
	uint16_t size;
} usb_report_t;

typedef struct {
	const char *name;
	const usbd_class_driver_t *app_driver;
	// Descriptors
	const tusb_desc_device_t *desc_device;
	const uint8_t *desc_cfg;
	const uint8_t *desc_hid_report;
	const uint8_t *desc_bos;
	// Callbacks
	bool (*send_report)(usb_report_t report);
} usbd_driver_t;

extern char *const usbd_desc_str[];

void usbd_driver_init(usb_mode_t mode);
void usbd_driver_task();

usb_mode_t usbd_driver_get_mode();

void usbd_driver_send_report(usb_report_t report);

#ifdef __cplusplus
}
#endif

#endif // USB_DEVICE_DRIVER_H_
