#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef void (*action_func_t) (void);

void graphics_init(int cols, int rows, action_func_t facc);
void graphics_draw_dot(int col, int row);
void graphics_draw_rectangle(int col, int row, int width, int length);

#endif
