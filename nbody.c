#include "bitmap.h"
#include "graphics.h"

#include <time.h>
#include <stdlib.h>

#define COLS 800
#define ROWS 600

bitmap_t bmp;

void draw() {
    bmp = bitmap_create(COLS, ROWS);
    srand(time(NULL));
    for(int i = 0; i < COLS*ROWS/2; i++) {
        bitmap_set_bit(bmp, rand() % COLS, rand() % ROWS);
    }

    for(int i = 0; i < COLS; i++) {
        for(int j = 0; j < ROWS; j++) {
            if (bitmap_get_bit(bmp, i, j)) {
                graphics_draw_rectangle(i, j, 1, 1);
            }
        }
    }
}

int main(void) {
    graphics_init(COLS, ROWS, draw);
    return 0;
}
