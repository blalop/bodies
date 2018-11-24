#include "bitmap.h"

#include <assert.h>
#include <stdlib.h>

static const int BITS_PER_WORD = sizeof(unsigned int) * 8;

bitmap_t bitmap_create(int x, int y) {
    bitmap_t bitmap;
    bitmap.cols = x;
    bitmap.rows = y;
    int n = bitmap.rows * bitmap.cols;
    bitmap.data = calloc(n, sizeof(unsigned int));
    assert(bitmap.data != NULL);
    return bitmap;
}

void bitmap_set_bit(bitmap_t bitmap, int x, int y) {
    int n = bitmap.rows * y + x;
    bitmap.data[n/BITS_PER_WORD] |= (1 << n%BITS_PER_WORD);
}

void bitmap_clear_bit(bitmap_t bitmap, int x, int y) {
    int n = bitmap.rows * y + x;
    bitmap.data[n/BITS_PER_WORD] &= ~(1 << n%BITS_PER_WORD);
}

int bitmap_get_bit(bitmap_t bitmap, int x, int y) {
    int n = bitmap.rows * y + x;
    return (bitmap.data[n/BITS_PER_WORD] & (1 << n%BITS_PER_WORD)) != 0;
}

void bitmap_destroy(bitmap_t bitmap) {
    free(bitmap.data);
}
