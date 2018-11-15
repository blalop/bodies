#ifndef BITMAP_H
#define BITMAP_H

unsigned int *bitmap_create(int dim);
void bitmap_set_bit(unsigned int *bitmap, int n);
void bitmap_clear_bit(unsigned int *bitmap, int n);
int bitmap_get_bit(unsigned int *bitmap, int n);
void bitmap_destroy(unsigned int *bitmap);

#endif
