#include <inttypes.h>
#include <stdlib.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

#include "usbcmp_descriptors.h"
#include "usbcmp_cdc.h"
#include "ringbuf.h"

#ifdef WITH_CDCACM
static char cdc_buf[64];
static ringbuf_t putchar_buf;
static int flush = 0;
static int connected = 0;
#endif

static void cdcacm_sof_callback(void);

extern usbd_device *device;

int cdc_putchar(int ch);

int cdc_control_request(usbd_device *usbd_dev,
    struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
    void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req)) 
{
    (void)usbd_dev;
    (void)buf;
    (void)complete;

    switch (req->bRequest) {
    case USB_CDC_REQ_SET_CONTROL_LINE_STATE: {
        /*
         * This Linux cdc_acm driver requires this to be implemented
         * even though it's optional in the CDC spec, and we don't
         * advertise it in the ACM functional descriptor.
         */
        uint16_t rtsdtr = req->wValue;	// DTR is bit 0, RTS is bit 1
        connected = rtsdtr & 1;
        return USBD_REQ_HANDLED;
        }
    case USB_CDC_REQ_SET_LINE_CODING:
        if (*len < sizeof(struct usb_cdc_line_coding)) {
            return USBD_REQ_NOTSUPP; // 0
        }
        return USBD_REQ_HANDLED; // 1
    }
    return USBD_REQ_NOTSUPP;
}

#ifdef WITH_CDCACM
static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
    (void)ep;

    size_t len = usbd_ep_read_packet(usbd_dev, CDC_BULK_OUT_EP, cdc_buf, sizeof(cdc_buf) - 1);

    // this always works, good for debugging
    //if (flush && connected) {
    //    usbd_ep_write_packet(usbd_dev, CDC_BULK_IN_EP, cdc_txbuf, cdc_txcount);
    //    cdc_txcount = 0;
    //    flush = 0;
    //}

}

void cdcacm_sof_callback()
{
    if (!connected) return;

    int i;
    for (i = 0; i < 64 && putchar_buf.avail; ++i) {
        int ch = ringbuf_get(&putchar_buf);
        cdc_buf[i] = (char) ch; 
    }
    usbd_ep_write_packet(device, CDC_BULK_IN_EP, cdc_buf, i);
}
#endif

void cdc_set_config(usbd_device *usbd_dev, uint16_t wValue)
{
    (void)usbd_dev;
    (void)wValue;

#ifdef WITH_CDCACM
    usbd_ep_setup(usbd_dev, CDC_BULK_OUT_EP, USB_ENDPOINT_ATTR_BULK, 64, cdcacm_data_rx_cb);
    usbd_ep_setup(usbd_dev, CDC_BULK_IN_EP, USB_ENDPOINT_ATTR_BULK, 64, NULL);
    usbd_ep_setup(usbd_dev, CDC_COMM_EP, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);
    ringbuf_init(&putchar_buf);
    flush = 0;
    connected = 0;
    usbd_register_sof_callback(usbd_dev, cdcacm_sof_callback);
#endif
}

int cdc_putchar(int ch) 
{
    if (!ringbuf_can_put(&putchar_buf)) {
        (void)ringbuf_get(&putchar_buf);
    }
    ringbuf_put(&putchar_buf, ch);
    return 0;
}
