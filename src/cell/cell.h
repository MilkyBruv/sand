#ifndef CELL_H
#define CELL_H

#include <allegro5/allegro.h>
#include <usr_macros.h>

#define CELLS_SIZE 64
#define TOTAL_CELLS (CELLS_SIZE * CELLS_SIZE);

#define VOID ((u8) 0)
#define SAND ((u8) 1)

typedef struct cell
{
    u8 id;
    ALLEGRO_COLOR col;
    b32 updated;
} cell_t;

static cell_t*** cells;

void init_cells();

cell_t* get_cell(u16 x, u16 y);
void swap_cells(cell_t* a, cell_t* b);
void set_cell(u16 x, u16 y, u8 id);
ALLEGRO_COLOR get_colour_from_id(u8 id);

void update_cells();
void update_sand(u16 x, u16 y);

void draw_cells();

void destroy_cells();


#endif
