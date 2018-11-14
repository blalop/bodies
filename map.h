#ifndef MAP_H
#define MAP_H

typedef void (*action_func_t) (void);

void map_init(unsigned short cols, unsigned short rows, action_func_t facc);
void map_draw_dot(unsigned short col, unsigned short row);
void map_draw_rectangle(unsigned short col, unsigned short row, unsigned short width, unsigned short length);

#endif
