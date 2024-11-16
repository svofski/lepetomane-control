#pragma once

#include <inttypes.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

int cdc_control_request(usbd_device *usbd_dev,
    struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
    void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req));
void cdc_set_config(usbd_device *usbd_dev, uint16_t wValue);
