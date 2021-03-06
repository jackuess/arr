#include <stdalign.h>
#include <stddef.h>
#include <stdlib.h>

#include "arr.h"

#define INITAL_CAP 4

struct Header {
    size_t cap;
    size_t len;
    size_t item_size;
    unsigned int padding : (sizeof(size_t) * 3) % alignof(max_align_t);
};

static inline struct Header *arrhead(const void *data) {
    return (struct Header *)data - 1;
}

static void *arrsetcap(void *data, size_t item_size, size_t cap) {
    const size_t data_offset = sizeof(struct Header);
    unsigned char *buf = NULL;

    if (data == NULL) {
        buf = malloc(data_offset + cap * item_size);
    } else {
        buf = realloc(arrhead(data), data_offset + cap * item_size);
    }
    if (buf == NULL) {
        return NULL;
    }

    return buf + data_offset;
}

void *arrnew(size_t len, size_t item_size) {
    size_t cap = (len > INITAL_CAP) ? len : INITAL_CAP;
    void *data = arrsetcap(NULL, item_size, cap);
    if (data == NULL) {
        return NULL;
    }

    struct Header *head = arrhead(data);
    head->cap = cap;
    head->len = len;
    head->item_size = item_size;

    return data;
}

void *arrextend(void **data, size_t n) {
    struct Header *head = arrhead(*data);
    if (head->len + n > head->cap) {
        size_t new_cap = 2 * (head->len + n);  // TODO(Jacques): Backoff from
                                               // doubling at a certain capacity
        *data = arrsetcap(*data, head->item_size, new_cap);
        if (*data == NULL) {
            return NULL;
        }
        head = arrhead(*data);
        head->cap = new_cap;
    }

    unsigned char *data_bytes = *data;
    void *extension = &data_bytes[head->len * head->item_size];

    head->len += n;

    return extension;
}

void *arrappend(void **data) { return arrextend(data, 1); }

size_t arrlen(const void *data) {
    struct Header *head = arrhead(data);
    return head->len;
}

void arrfree(const void *data) { free(arrhead(data)); }
