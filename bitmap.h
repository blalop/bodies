#ifndef BITMAP_H
#define BITMAP_H

typedef struct {
    unsigned int *data;
    int rows, cols;
} bitmap_t;

bitmap_t bitmap_create(int x, int y);
void bitmap_set_bit(bitmap_t bitmap, int x, int y);
void bitmap_clear_bit(bitmap_t bitmap, int x, int y);
int bitmap_get_bit(bitmap_t bitmap, int x, int y);
void bitmap_destroy(bitmap_t bitmap);

#endif
