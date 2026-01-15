#ifndef USB_DEVICE_MIDI_DRIVER_H_
#define USB_DEVICE_MIDI_DRIVER_H_

#include "GlobalConfiguration.h"
#include "usb/device_driver.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute((packed, aligned(1))) {
uint16_t keys[OCTAVE_COUNT];
} midi_report_t;

const usbd_driver_t *get_midi_device_driver();

#ifdef __cplusplus
}
#endif

#endif // USB_DEVICE_MIDI_DRIVER_H_