#ifndef BRUSH_H
#define BRUSH_H

#include <usr_macros.h>
#include "../cell/cell.h"

#define RECT ((u8) 100)
#define SPHR ((u8) 101)

typedef struct brush
{
    u16 x, y;
    u8 id, shape;
    u16 size;
    char data_str[64];
} brush_t;

static brush_t brush = {
    .x = 0, .y = 0, .id = SAND, .shape = RECT, .size = 8
};

void init_brush();
void stamp_brush();
void set_brush_pos(u16 x, u16 y);
void set_brush_shape(u8 shape);
void set_brush_id(u8 id);
void set_brush_size(u16 size);
void update_brush_str();
void render_brush();

#endif