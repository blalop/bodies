#include "bitmap.h"

#include <stdlib.h>

static const int BITS_PER_WORD = sizeof(unsigned int) * 8;

unsigned int *bitmap_create(int dim) {
    unsigned int *bitmap = calloc(dim, sizeof(unsigned int));
    return bitmap;
}

void bitmap_set_bit(unsigned int *bitmap, int n) {
    bitmap[n/BITS_PER_WORD] |= (1 << n%BITS_PER_WORD);
}

void bitmap_clear_bit(unsigned int *bitmap, int n) {
    bitmap[n/BITS_PER_WORD] &= ~(1 << n%BITS_PER_WORD);
}

int bitmap_get_bit(unsigned int *bitmap, int n) {
    return (bitmap[n/BITS_PER_WORD] & (1 << n%BITS_PER_WORD)) != 0;
}

void bitmap_destroy(unsigned int *bitmap) {
    free(bitmap);
}
