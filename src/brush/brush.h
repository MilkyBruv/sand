#ifndef BRUSH_H
#define BRUSH_H

#include <usrtypes.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "./../cell/cell.h"

#define RECT ((u8) 100)
#define SPHR ((u8) 101)

typedef struct brush
{
    u16 x, y;
    u8 id;
    u16 size;
    char data_str[128];
} brush_t;

static brush_t* brush;

void init_brush();
void stamp_brush();
void set_brush_pos(s32 x, s32 y);
void set_brush_id(u8 id);
void set_brush_size(s32 mouse_z);
void update_brush_str();
void draw_brush(ALLEGRO_FONT* font);
void destroy_brush();

#endif