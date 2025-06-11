#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <usr_macros.h>
#include <stdio.h>
#include <string.h>
#include "cell/cell.h"
#include "brush/brush.h"

#define SIZE 800

int main(void)
{
    al_init();
    ALLEGRO_DISPLAY* display = al_create_display(SIZE, SIZE);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    al_set_window_title(display, "Test Window");

    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_set_mouse_wheel_precision(120);

    // Font stuff
    ALLEGRO_FONT* font = al_load_ttf_font("./res/consolas/CONSOLA.TTF", 16, 
        ALLEGRO_TTF_MONOCHROME);

    ALLEGRO_BITMAP* fb = al_create_bitmap(CELLS_SIZE, CELLS_SIZE);
    s32 mouse_x, mouse_y;
    // s16 fb_mouse_x, fb_mouse_y;
    init_cells();
    init_brush();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    b32 running = true;
    b32 space = false;
    al_start_timer(timer);
    ALLEGRO_EVENT event;
    while (running)
    {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { running = false; }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { running = false; }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                space = true;
            }
        }

        if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            al_get_mouse_cursor_position(&mouse_x, &mouse_y);

            if (event.keyboard.keycode == ALLEGRO_KEY_0)
            {
                set_brush_id(VOID);
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_1)
            {
                set_brush_id(SAND);
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
                space = false;
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            // update
            update_cells();
            update_brush_str();

            if (space) {

                stamp_brush();

            }

            // render
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            // brush info text
            al_draw_text(font, al_map_rgb(255, 255, 255), 8, 8, 0, brush.data_str);
            
            al_set_target_bitmap(fb);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            draw_cells();
            
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_scaled_bitmap(fb, 0, 0, CELLS_SIZE, CELLS_SIZE, 0, 0, SIZE, SIZE, 0);

            al_flip_display();
        }
    }
    al_stop_timer(timer);

    al_unregister_event_source(event_queue, al_get_display_event_source(display));
    al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
    al_unregister_event_source(event_queue, al_get_keyboard_event_source());
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);

    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_shutdown_primitives_addon();

    destroy_cells();
}