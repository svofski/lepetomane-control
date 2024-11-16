#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/usb/audio.h>
#include <libopencm3/usb/midi.h>

#include "usbcmp_descriptors.h"

enum USB_STRID {
    STRID_VENDOR = 1,
    STRID_PRODUCT,
    STRID_VERSION,
    STRID_INPUT_TERMINAL,
    STRID_OUTPUT_TERMINAL,
};

const char* usb_strings[] = {
    "svofski",
    "Petocontrole",
    "0.1",
    "Input Terminal",
    "Output Terminal",
};

const struct usb_device_descriptor usbcmp_device_descr = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0xef,       // Use interface association descriptor
    .bDeviceSubClass = 2,
    .bDeviceProtocol = 1,
    .bMaxPacketSize0 = 64,
    .idVendor = 0x6666,         // prototype vendor id
    .idProduct = 0x1237,        // 0x5740 = serial adapter
                                // Windows is boneheaded and disregards everything
                                // when it sees a known VID/PID combo. So to avoid
                                // this device being recognized as a simple serial
                                // port, a nonexistend PID is used.
    .bcdDevice = 0x0200,
    .iManufacturer = STRID_VENDOR,
    .iProduct = STRID_PRODUCT,
    .iSerialNumber = STRID_VERSION,
    .bNumConfigurations = 1,
};

#ifdef WITH_CDCACM
/*
 * This notification endpoint isn't implemented. According to CDC spec it's
 * optional, but its absence causes a NULL pointer dereference in the
 * Linux cdc_acm driver.
 */
static const struct usb_endpoint_descriptor comm_endp[] = {{
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = CDC_COMM_EP,
    .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
    .wMaxPacketSize = 16,
    .bInterval = 255,
} };

static const struct usb_endpoint_descriptor data_endp[] = {{
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = CDC_BULK_OUT_EP,
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = 64,
    .bInterval = 1,
}, {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = CDC_BULK_IN_EP,
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = 64,
    .bInterval = 1,
} };

static const struct {
    struct usb_cdc_header_descriptor header;
    struct usb_cdc_call_management_descriptor call_mgmt;
    struct usb_cdc_acm_descriptor acm;
    struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) cdcacm_functional_descriptors = {
    .header = {
        .bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_HEADER,
        .bcdCDC = 0x0110,
    },
    .call_mgmt = {
        .bFunctionLength =
            sizeof(struct usb_cdc_call_management_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
        .bmCapabilities = 0,
        .bDataInterface = 1,
    },
    .acm = {
        .bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_ACM,
        .bmCapabilities = 0,
    },
    .cdc_union = {
        .bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_UNION,
        .bControlInterface = 0,
        .bSubordinateInterface0 = 1,
     }
};

static const struct usb_interface_descriptor comm_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = CDCACM_COMM_INTERFACE, // 0
    .bAlternateSetting = 0,
    .bNumEndpoints = 1,
    .bInterfaceClass = USB_CLASS_CDC,
    .bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
    .bInterfaceProtocol = USB_CDC_PROTOCOL_NONE, //USB_CDC_PROTOCOL_AT,
    .iInterface = 0,

    .endpoint = comm_endp,

    .extra = &cdcacm_functional_descriptors,
    .extralen = sizeof(cdcacm_functional_descriptors)
} };

static const struct usb_interface_descriptor data_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = CDCACM_DATA_INTERFACE, // 1
    .bAlternateSetting = 0,
    .bNumEndpoints = 2,
    .bInterfaceClass = USB_CLASS_DATA,
    .bInterfaceSubClass = 0,
    .bInterfaceProtocol = 0,
    .iInterface = 0,

    .endpoint = data_endp,
} };

// An interface association allows the device to group a set of interfaces to
// represent one logical device to be managed by one host driver.
static const struct usb_iface_assoc_descriptor cdc_acm_interface_association = {
    // The size of an interface association descriptor: 8
    .bLength = USB_DT_INTERFACE_ASSOCIATION_SIZE,
    // A value of 11 indicates that this descriptor describes an interface
    // association.
    .bDescriptorType = USB_DT_INTERFACE_ASSOCIATION,
    // The first interface that is part of this group.
    .bFirstInterface = CDCACM_COMM_INTERFACE,
    // The number of included interfaces. This implies that the bundled
    // interfaces must be continugous.
    .bInterfaceCount = 2,
    // The class, subclass, and protocol of device represented by this
    // association. In this case a communication device.
    .bFunctionClass = USB_CLASS_CDC,
    // Using Abstract Control Model
    .bFunctionSubClass = USB_CDC_SUBCLASS_ACM,
    // With AT protocol (or Hayes compatible).
    .bFunctionProtocol = USB_CDC_PROTOCOL_AT,
    // A string representing this interface. Zero means not provided.
    .iFunction = 0,
};

#endif // WITH_CDCACM

//
//
//
//
// --------------------- MIDI --------------------------
//
//
//

/*
 * Midi specific endpoint descriptors.
 */
static const struct usb_midi_endpoint_descriptor midi_bulk_endp[] = {{
    /* Table B-12: MIDI Adapter Class-specific Bulk OUT Endpoint
     * Descriptor
     */
    .head = {
        .bLength = sizeof(struct usb_midi_endpoint_descriptor),
        .bDescriptorType = USB_AUDIO_DT_CS_ENDPOINT,
        .bDescriptorSubType = USB_MIDI_SUBTYPE_MS_GENERAL,
        .bNumEmbMIDIJack = 1,
    },
    .jack[0] = {
        .baAssocJackID = 0x01,
    },
    }, {
    /* Table B-14: MIDI Adapter Class-specific Bulk IN Endpoint
     * Descriptor
     */
    .head = {
        .bLength = sizeof(struct usb_midi_endpoint_descriptor),
        .bDescriptorType = USB_AUDIO_DT_CS_ENDPOINT,
        .bDescriptorSubType = USB_MIDI_SUBTYPE_MS_GENERAL,
        .bNumEmbMIDIJack = 1,
    },
    .jack[0] = {
        .baAssocJackID = 0x03,
    },
} };

/*
 * Standard endpoint descriptors
 */
static const struct usb_endpoint_descriptor midi_standard_bulk_endp[] = {{
    /* Table B-11: MIDI Adapter Standard Bulk OUT Endpoint Descriptor */
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = MIDI_OUT_EP,            // 0x03
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = 0x40,
    .bInterval = 0x00,

    .extra = &midi_bulk_endp[0],
    .extralen = sizeof(midi_bulk_endp[0])
}, {
    .bLength = USB_DT_ENDPOINT_SIZE,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = MIDI_IN_EP,             // 0x84
    .bmAttributes = USB_ENDPOINT_ATTR_BULK,
    .wMaxPacketSize = 0x40,
    .bInterval = 0x00,

    .extra = &midi_bulk_endp[1],
    .extralen = sizeof(midi_bulk_endp[1])
} };

/*
 * Table B-4: MIDI Adapter Class-specific AC Interface Descriptor
 */
static const struct {
    struct usb_audio_header_descriptor_head header_head;
    struct usb_audio_header_descriptor_body header_body;
} __attribute__((packed)) midi_control_functional_descriptors = {
    .header_head = {
        .bLength = sizeof(struct usb_audio_header_descriptor_head) +
            1 * sizeof(struct usb_audio_header_descriptor_body),
        .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .bDescriptorSubtype = USB_AUDIO_TYPE_HEADER,
        .bcdADC = 0x0100,
        .wTotalLength =
            sizeof(struct usb_audio_header_descriptor_head) +
            1 * sizeof(struct usb_audio_header_descriptor_body),
        .binCollection = 1,
    },
    .header_body = {
        .baInterfaceNr = MIDI_STREAMING_IFACE,
    },
};

// MIDI audio control standard interface descriptor
static const struct usb_interface_descriptor midi_control_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = MIDI_CONTROL_IFACE, // 4
    .bAlternateSetting = 0,
    .bNumEndpoints = 0,
    .bInterfaceClass = USB_CLASS_AUDIO,
    .bInterfaceSubClass = USB_AUDIO_SUBCLASS_CONTROL,
    .bInterfaceProtocol = 0,
    .iInterface = 0,

    .extra = &midi_control_functional_descriptors,
    .extralen = sizeof(midi_control_functional_descriptors)
} };




/*
 * Class-specific MIDI streaming interface descriptor
 */
static const struct {
    struct usb_midi_header_descriptor header;
    struct usb_midi_in_jack_descriptor in_embedded;
    struct usb_midi_in_jack_descriptor in_external;
    struct usb_midi_out_jack_descriptor out_embedded;
    struct usb_midi_out_jack_descriptor out_external;
} __attribute__((packed)) midi_streaming_functional_descriptors = {
    /* Table B-6: Midi Adapter Class-specific MS Interface Descriptor */
    .header = {
        .bLength = sizeof(struct usb_midi_header_descriptor),
        .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .bDescriptorSubtype = USB_MIDI_SUBTYPE_MS_HEADER,
        .bcdMSC = 0x0100,
        .wTotalLength = sizeof(midi_streaming_functional_descriptors),
    },
    /* Table B-7: MIDI Adapter MIDI IN Jack Descriptor (Embedded) */
    .in_embedded = {
        .bLength = sizeof(struct usb_midi_in_jack_descriptor),
        .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .bDescriptorSubtype = USB_MIDI_SUBTYPE_MIDI_IN_JACK,
        .bJackType = USB_MIDI_JACK_TYPE_EMBEDDED,
        .bJackID = 0x01,
        .iJack = 0x00,
    },
    /* Table B-8: MIDI Adapter MIDI IN Jack Descriptor (External) */
    .in_external = {
        .bLength = sizeof(struct usb_midi_in_jack_descriptor),
        .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
        .bDescriptorSubtype = USB_MIDI_SUBTYPE_MIDI_IN_JACK,
        .bJackType = USB_MIDI_JACK_TYPE_EXTERNAL,
        .bJackID = 0x02,
        .iJack = 0x00,
    },
    /* Table B-9: MIDI Adapter MIDI OUT Jack Descriptor (Embedded) */
    .out_embedded = {
        .head = {
            .bLength = sizeof(struct usb_midi_out_jack_descriptor),
            .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
            .bDescriptorSubtype = USB_MIDI_SUBTYPE_MIDI_OUT_JACK,
            .bJackType = USB_MIDI_JACK_TYPE_EMBEDDED,
            .bJackID = 0x03,
            .bNrInputPins = 1,
        },
        .source[0] = {
            .baSourceID = 0x02,
            .baSourcePin = 0x01,
        },
        .tail = {
            .iJack = 0x00,
        }
    },
    /* Table B-10: MIDI Adapter MIDI OUT Jack Descriptor (External) */
    .out_external = {
        .head = {
            .bLength = sizeof(struct usb_midi_out_jack_descriptor),
            .bDescriptorType = USB_AUDIO_DT_CS_INTERFACE,
            .bDescriptorSubtype = USB_MIDI_SUBTYPE_MIDI_OUT_JACK,
            .bJackType = USB_MIDI_JACK_TYPE_EXTERNAL,
            .bJackID = 0x04,
            .bNrInputPins = 1,
        },
        .source[0] = {
            .baSourceID = 0x01,
            .baSourcePin = 0x01,
        },
        .tail = {
            .iJack = 0x00,
        },
    },
};

/*
 * Table B-5: MIDI Adapter Standard MS Interface Descriptor
 */
static const struct usb_interface_descriptor midi_streaming_iface[] = {{
    .bLength = USB_DT_INTERFACE_SIZE,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = MIDI_STREAMING_IFACE,
    .bAlternateSetting = 0,
    .bNumEndpoints = 2,
    .bInterfaceClass = USB_CLASS_AUDIO,
    .bInterfaceSubClass = USB_AUDIO_SUBCLASS_MIDISTREAMING,
    .bInterfaceProtocol = 0,
    .iInterface = 0,

    .endpoint = midi_standard_bulk_endp,

    // vv this murders the enumerator
    .extra = &midi_streaming_functional_descriptors,
    .extralen = sizeof(midi_streaming_functional_descriptors)
} };


static const struct usb_iface_assoc_descriptor midi_interface_association = {
    .bLength = USB_DT_INTERFACE_ASSOCIATION_SIZE,
    .bDescriptorType = USB_DT_INTERFACE_ASSOCIATION,
    .bFirstInterface = MIDI_CONTROL_IFACE,
    .bInterfaceCount = 2, // control + midistreaming
    .bFunctionClass = USB_CLASS_AUDIO,
    .bFunctionSubClass = USB_AUDIO_SUBCLASS_CONTROL,
    .bFunctionProtocol = 0,
    .iFunction = 0,
};

static const struct usb_interface ifaces[] = {
#ifdef WITH_CDCACM
    {
        .num_altsetting = 1,
        .iface_assoc = &cdc_acm_interface_association,
        .altsetting = comm_iface,
    },
    {
        .num_altsetting = 1,
        .altsetting = data_iface,
    },
#endif
    // MIDI
    {
        .num_altsetting = 1,
        .iface_assoc = &midi_interface_association,
        .altsetting = midi_control_iface,
    },
    {
        .num_altsetting = 1,
        .altsetting = midi_streaming_iface,
    }
};

const struct usb_config_descriptor usbcmp_device_config = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0,   // Length of the total configuration block, 
                         // including this descriptor, in bytes.
    .bNumInterfaces = sizeof(ifaces)/sizeof(ifaces[0]), 
    .bConfigurationValue = 1,   
    .iConfiguration = 0,
    .bmAttributes = USB_CONFIG_ATTR_DEFAULT,
    .bMaxPower = 0xfa, // 500mA

    .interface = ifaces,
};

uint32_t usbcmp_nstrings(void) {
    return sizeof(usb_strings)/sizeof(usb_strings[0]);
}
