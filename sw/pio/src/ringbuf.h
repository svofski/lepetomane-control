#pragma once

#define RINGBUF_SIZE 256
#define RINGBUF_SIZE_MASK 0xFF

typedef struct {
    char data[RINGBUF_SIZE];
    int head;
    int tail;
    int avail;  // how many bytes of data
} ringbuf_t;

void ringbuf_init(ringbuf_t * buf);

int ringbuf_can_put(ringbuf_t * buf);
void ringbuf_put(ringbuf_t * buf, int ch);
int ringbuf_get(ringbuf_t * buf);
