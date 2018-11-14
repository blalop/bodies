
#include "map.h"

void draw() {
    map_draw_rectangle(40, 40, 20, 20);
}

int main(void) {
    map_init(800, 600, draw);
    return 0;
}
