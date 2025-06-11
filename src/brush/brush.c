#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "brush.h"
#include "../cell/cell.h"

void init_brush()
{
    brush = malloc(sizeof(brush_t));
    brush->x = 8;
    brush->y = 8;
    brush->id = SAND;
    brush->size = 2;

    update_brush_str();
}

void stamp_brush()
{
    for (s16 y = brush->y - brush->size; y < brush->y + brush->size; y++)
    {
        for (s16 x = brush->x - brush->size; x < brush->x + brush->size; x++)
        {
            set_cell(x, y, brush->id);
        }   
    }
}

void set_brush_pos(s32 x, s32 y)
{
    if (x >= 0 && x <= SIZE - 1 && y >= 0 && y <= SIZE - 1)
    {
        brush->x = x;
        brush->y = y;
    }
}

void set_brush_id(u8 id)
{
    brush->id = id;
}

void set_brush_size(s32 mouse_z)
{
    if (mouse_z <= 2)
    {
        brush->size = 2;
        al_set_mouse_z(2);
    }
    else
    {
        brush->size = mouse_z;
    }
}

void update_brush_str()
{
    snprintf(brush->data_str, sizeof(brush->data_str), "x: %u, y: %u, id: %u, size: %d", 
        brush->x, brush->y, brush->id, brush->size);
}

void draw_brush(ALLEGRO_FONT * font)
{   
    al_draw_filled_rectangle(8, 8, SIZE - 8, 24, al_map_rgb(0, 0, 255));
    al_draw_text(font, al_map_rgb(255, 255, 255), 8, 8, 0, brush->data_str);

    if (brush->x >= 0 && brush->x <= SIZE - 1 && brush->y >= 0 && brush->y <= SIZE - 1)
    {
        al_draw_rectangle(
            brush->x - brush->size, brush->y - brush->size, brush->x + brush->size, brush->y + brush->size, 
            al_map_rgb(255, 255, 255), 1
        );
    }
}

void destroy_brush()
{
    free(brush);
}
