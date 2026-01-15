#include "usb/device/hid/common.h"

#include "usb/device/hid/keyboard_driver.h"
#include "usb/device_driver.h"

#include "class/hid/hid_device.h"
#include "tusb.h"

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
	switch (usbd_driver_get_mode()) {
		case USB_MODE_KEYBOARD:
			return hid_keyboard_get_report_cb(instance, report_id, report_type, buffer, reqlen);
		default:
			break;
	}

	return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
	switch (usbd_driver_get_mode()) {
		case USB_MODE_KEYBOARD:
			hid_keyboard_set_report_cb(instance, report_id, report_type, buffer, bufsize);
			break;
		default:
			break;
	}
}

uint8_t const *tud_hid_descriptor_report_cb(uint8_t instance) {
	(void)instance;

	switch (usbd_driver_get_mode()) {
		case USB_MODE_KEYBOARD:
			return keyboard_desc_hid_report;
		default:
			break;
	}

	return NULL;
}

const usbd_class_driver_t hid_app_driver = {
#if CFG_TUSB_DEBUG >= 2
	.name = "HID",
#endif
	.init = hidd_init,
	.reset = hidd_reset,
	.open = hidd_open,
	.control_xfer_cb = hidd_control_xfer_cb,
	.xfer_cb = hidd_xfer_cb,
	.sof = NULL
};
