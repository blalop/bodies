#include "bitmap.h"
#include "graphics.h"

void draw() {
    for(int i = 0; i < 50; i++)
        graphics_draw_rectangle(i, i, 20, 20);
}

int main(void) {
    graphics_init(800, 600, draw);
    unsigned int *bmp = bitmap_create(4);
    bitmap_set_bit(bmp, 2); 
    return 0;
}
