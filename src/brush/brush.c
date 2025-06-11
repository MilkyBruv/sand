#include <stdio.h>
#include "brush.h"

void init_brush()
{
    brush.x = 8;
    brush.y = 8;
    brush.id = SAND;
    brush.shape = RECT;
    brush.size = 2;

    update_brush_str();
}

void stamp_brush()
{
    switch (brush.shape)
    {
    case RECT:
        
        // Set cells in rectangle shape in bounds of display
        for (s16 y = brush.y - brush.size; 
            y < brush.size * 2 && y >= 0 && y < CELLS_SIZE; y++)
        {
            for (s16 x = brush.x - brush.size; 
                x < brush.size * 2 && x >= 0 && x < CELLS_SIZE; x++)
            {
                set_cell(brush.x, brush.y, brush.id);
            }   
        }
        break;
    
    default:
        break;
    }
}

void set_brush_pos(u16 x, u16 y)
{
    // 
}

void set_brush_shape(u8 shape)
{
    // 
}

void set_brush_id(u8 id)
{
    // 
}

void set_brush_size(u16 size)
{
    // 
}

void update_brush_str()
{
    sprintf(brush.data_str, "x: %d\ny: %d\nid: %d\nshape: %d\nsize: %d", 
        brush.x, brush.y, brush.id, brush.shape, brush.size);
}

void render_brush()
{
    // 
}
