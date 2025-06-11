#include <allegro5/allegro.h>
#include <usrtypes.h>
#include <stdio.h>
#include "cell.h"

void init_cells()
{
    // Allocate cells[][]
    cells = malloc(SIZE * sizeof(cell_t**));
    
    for (u16 y = 0; y < SIZE; y++)
    {
        // allocate cells[]
        cells[y] = malloc(SIZE * sizeof(cell_t*));

        for (u16 x = 0; x < SIZE; x++)
        {
            // allocate cell
            cells[y][x] = malloc(sizeof(cell_t));
            set_cell(x, y, VOID);
        }   
    }
}

cell_t* get_cell(u16 x, u16 y)
{
    return cells[y][x];
}

void swap_cells(u16 x1, u16 y1, u16 x2, u16 y2)
{
    cell_t* a = get_cell(x1, y1);
    cell_t* b = get_cell(x2, y2);

    u8 a_id = a->id;
    u32 a_col = a->col;
    b32 a_updated = a->updated;

    // Sawp a to b
    a->id = b->id;
    a->col = b->col;
    a->updated = a_updated;

    // Swap b to a
    b->id = a_id;
    b->col = a_col;
    b->updated = b->updated;
}

void set_cell(u16 x, u16 y, u8 id)
{
    if (x >= 0 && x <= SIZE - 1 && y >= 0 && y <= SIZE - 1)
    {
        // Set cell values
        cell_t* c = get_cell(x, y);
        c->id = id;
        c->col = get_colour_from_id(id);
    }
}

u32 get_colour_from_id(u8 id)
{
    switch (id)
    {
    case VOID:
        return unmap_al_colour(al_map_rgb(0, 0, 0));
        break;

    case SAND:
        return unmap_al_colour(al_map_rgb(0, 255, 255));
        break;
    
    default:
        return unmap_al_colour(al_map_rgb(0, 0, 0));
        break;
    }
}

u32 unmap_al_colour(ALLEGRO_COLOR c)
{
    u8 r, g, b;
    al_unmap_rgb(c, &r, &b, &g);
    u32 rgb = (b << 16) | (g << 8) | r;

    return rgb;
}

void update_cells()
{
    cell_t* c;

    for (u16 y = 0; y < SIZE; y++)
    {
        for (u16 x = 0; x < SIZE; x++)
        {
            c = get_cell(x, y);

            if (!c->updated)
            {
                switch (c->id)
                {
                    case VOID:
                        break;
                    
                    case SAND:
                        update_sand(x, y);
                        break;
                    
                    default:
                        break;
                }

                c->updated = true;
            }
        }
    }
}

void update_sand(u16 x, u16 y)
{
    if (y + 1 == SIZE) { return; }
    if (get_cell(x, y + 1)->id == VOID)
    {
        swap_cells(x, y, x, y + 1);
    } 
    else if (x > 0 && get_cell(x - 1, y + 1)->id == VOID)
    {
        swap_cells(x, y, x - 1, y + 1);
    }
    else if (x < SIZE - 1 && get_cell(x + 1, y + 1)->id == VOID)
    {
        swap_cells(x, y, x + 1, y + 1);
    }
}

void draw_cells(ALLEGRO_LOCKED_REGION* lock)
{
    u32* pixels = (u32*) lock->data;
    s32 pitch = lock->pitch / 4;

    for (u16 y = 0; y < SIZE; y++)
    {
        for (u16 x = 0; x < SIZE; x++)
        {
            pixels[(y * pitch) + x] = get_cell(x, y)->col;
            get_cell(x, y)->updated = false;
        }
    }
}

void destroy_cells()
{
    for (u16 y = 0; y < SIZE; y++)
    {
        for (u16 x = 0; x < SIZE; x++)
        {
            // Free cell
            free(cells[y][x]);
        }

        // Free cells[]
        free(cells[y]);
    }

    // Free cells[][]
    free(cells);
}
