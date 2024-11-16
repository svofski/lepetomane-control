#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/audio.h>
#include <libopencm3/usb/midi.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "usbcmp.h"
#include "xprintf.h"

#include "util.h"

#include "usbcmp_descriptors.h"
#include "usbcmp_cdc.h"
#include "usbmidi.h"

usbd_device *device = NULL;

bool usb_configured_flag = false;

static volatile uint32_t npackets_fb;
static volatile uint32_t flag;
static volatile uint32_t pid;
static volatile uint32_t flush_count;

static volatile uint32_t npackets_rx;
static volatile uint16_t fb_timer_last;

static volatile uint32_t feedback_value = 48 << 14;
static volatile uint32_t sink_buffer_fullness;

// -- descriptors here

/* Buffer to be used for control requests. Needs to be large to fit all those descriptors. */
static uint8_t usbd_control_buffer[512]; // vcp + audio (no mic) + midi = 362


static int common_control_request(usbd_device *usbd_dev,
    struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
    void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
    (void)complete;
    (void)buf;
    (void)usbd_dev;

    //xprintf("control_request: %x Value=%x Index=%x \n", req->bRequest, req->wValue, req->wIndex);

    switch (req->bRequest) {
        case USB_CDC_REQ_SET_CONTROL_LINE_STATE:
        case USB_CDC_REQ_SET_LINE_CODING:
            return cdc_control_request(usbd_dev, req, buf, len, complete);
    }
    return 0;
}


static void set_config_cb(usbd_device *usbd_dev, uint16_t wValue)
{
    (void)wValue;

    //xprintf("set_config wValue=%d\n", wValue);

    cdc_set_config(usbd_dev, wValue);

    usbd_register_control_callback(usbd_dev,
                USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE, //type
                USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,  //mask
                common_control_request);

    usbmidi_set_config(usbd_dev, wValue);

    usb_configured_flag = true;
}

void usbcmp_poll(void) {
    usbd_poll(device);
}

void usbcmp_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_OTGFS);

    /*
     * This is a somewhat common cheap hack to trigger device re-enumeration
     * on startup.  Assuming a fixed external pullup on D+, (For USB-FS)
     * setting the pin to output, and driving it explicitly low effectively
     * "removes" the pullup.  The subsequent USB init will "take over" the
     * pin, and it will appear as a proper pullup to the host.
     * The magic delay is somewhat arbitrary, no guarantees on USBIF
     * compliance here, but "it works" in most places.
     */
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ,
            GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
    gpio_clear(GPIOA, GPIO12);
    for (unsigned i = 0; i < 800000; i++) {
            __asm__("nop");
    }

    device = usbd_init(&st_usbfs_v1_usb_driver,
            &usbcmp_device_descr, &usbcmp_device_config,
            usb_strings, usbcmp_nstrings(),
            usbd_control_buffer, sizeof(usbd_control_buffer));

    usbd_register_set_config_callback(device, set_config_cb);
}

