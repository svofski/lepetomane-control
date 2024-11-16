#pragma once

#define WITH_CDCACM

#define XSTR(x) STR(x)
#define STR(x) #x

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#define IFSTART                             (-1)

#define EPSTART                             0

#ifdef WITH_CDCACM
    #define CDCACM_COMM_INTERFACE           ((IFSTART) + 1)
    #define CDCACM_DATA_INTERFACE           ((IFSTART) + 2)
    #define IFCDC                           (CDCACM_DATA_INTERFACE)
#else
    #define IFCDC                           IFSTART
#endif

#define IFMIDI                              ((IFCDC) + 1)

#define MIDI_CONTROL_IFACE                  ((IFMIDI) + 0)
#define MIDI_STREAMING_IFACE                ((IFMIDI) + 1)

// An attempt at sane endpoint definition, just listing them out 
#define CDC_BULK_OUT_EP 0x01
#define CDC_BULK_IN_EP  0x82
#define CDC_COMM_EP     0x83
#define MIDI_OUT_EP     0x02
#define MIDI_IN_EP      0x84

extern const char* usb_strings[];
extern const struct usb_device_descriptor usbcmp_device_descr;
extern const struct usb_config_descriptor usbcmp_device_config;

uint32_t usbcmp_nstrings(void);
