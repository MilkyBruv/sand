#ifndef CELL_H
#define CELL_H

#include <allegro5/allegro.h>
#include <usrtypes.h>

#define SIZE 800
#define TOTAL_CELLS (SIZE * SIZE);

#define VOID ((u8) 0)
#define SAND ((u8) 1)

typedef struct cell
{
    u8 id;
    u32 col;
    b32 updated;
} cell_t;

static cell_t*** cells;

void init_cells();

cell_t* get_cell(u16 x, u16 y);
void swap_cells(u16 x1, u16 y1, u16 x2, u16 y2);
void set_cell(u16 x, u16 y, u8 id);
u32 get_colour_from_id(u8 id);
u32 unmap_al_colour(ALLEGRO_COLOR c);

void update_cells();
void update_sand(u16 x, u16 y);

void draw_cells(ALLEGRO_LOCKED_REGION* lock);

void destroy_cells();


#endif
