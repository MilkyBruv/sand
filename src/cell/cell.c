#include <allegro5/allegro.h>
#include <usr_macros.h>
#include <stdio.h>
#include "cell.h"

void init_cells()
{
    // Allocate cells[][]
    cells = malloc(CELLS_SIZE * sizeof(cell_t**));
    
    for (u16 y = 0; y < CELLS_SIZE; y++)
    {
        // allocate cells[]
        cells[y] = malloc(CELLS_SIZE * sizeof(cell_t*));

        for (u16 x = 0; x < CELLS_SIZE; x++)
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

void swap_cells(cell_t* a, cell_t* b)
{
    cell_t p = *a; // Placeholder cell

    // Sawp a to b
    a->id = b->id;
    a->col = b->col;

    // Swap b to p (a)
    b->id = p.id;
    b->col = p.col;
    b->updated = p.updated;
}

void set_cell(u16 x, u16 y, u8 id)
{
    // Set cell values
    cell_t* c = get_cell(x, y);
    c->id = id;
    c->col = get_colour_from_id(id);
    c->updated = false;
}

ALLEGRO_COLOR get_colour_from_id(u8 id)
{
    switch (id)
    {
    case VOID:
        return al_map_rgb(0, 0, 0);
        break;

    case SAND:
        return al_map_rgb(0, 255, 255);
        break;
    
    default:
        return al_map_rgb(0, 0, 0);
        break;
    }
}

void update_cells()
{
    cell_t* c;

    for (u16 y = 0; y < CELLS_SIZE; y++)
    {
        for (u16 x = 0; x < CELLS_SIZE; x++)
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
    if (y + 1 == CELLS_SIZE) { return; }
    if (get_cell(x, y + 1)->id == VOID)
    {
        swap_cells(get_cell(x, y), get_cell(x, y + 1));
    } 
    else if (x > 0 && get_cell(x - 1, y + 1)->id == VOID)
    {
        swap_cells(get_cell(x, y), get_cell(x - 1, y + 1));
    }
    else if (x < CELLS_SIZE - 1 && get_cell(x + 1, y + 1)->id == VOID)
    {
        swap_cells(get_cell(x, y), get_cell(x + 1, y + 1));
    }
}

void draw_cells()
{
    cell_t* c;

    for (u16 y = 0; y < CELLS_SIZE; y++)
    {
        for (u16 x = 0; x < CELLS_SIZE; x++)
        {
            c = get_cell(x, y);

            if (c->id != VOID)
            {
                al_draw_pixel(x, y, c->col);
            }

            c->updated = false;
        }
    }
}

void destroy_cells()
{
    for (u16 y = 0; y < CELLS_SIZE; y++)
    {
        for (u16 x = 0; x < CELLS_SIZE; x++)
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
