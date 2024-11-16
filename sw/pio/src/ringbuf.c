#include "ringbuf.h"
#include <string.h>

void ringbuf_init(ringbuf_t * buf)
{
    memset(buf, 0, sizeof * buf);
}

void ringbuf_put(ringbuf_t * buf, int ch)
{
    if (buf->avail < RINGBUF_SIZE) {
        buf->data[buf->head] = (char)ch;
        buf->head = (buf->head + 1) & RINGBUF_SIZE_MASK;
        ++buf->avail;
    }
}

int ringbuf_get(ringbuf_t * buf)
{
    if (buf->avail == 0) {
        return -1;
    }
    int res = buf->data[buf->tail];
    buf->tail = (buf->tail + 1) & RINGBUF_SIZE_MASK;
    --buf->avail;

    return res;
}

int ringbuf_can_put(ringbuf_t * buf)
{
    return buf->avail < RINGBUF_SIZE;
}
