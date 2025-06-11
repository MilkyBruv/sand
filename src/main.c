#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <usrtypes.h>
#include <stdio.h>
#include <string.h>
#include "cell/cell.h"
#include "brush/brush.h"

#define ALLEGRO_UNSTABLE

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
    al_set_mouse_wheel_precision(2);
    al_set_mouse_z(0);

    // Font stuff
    ALLEGRO_FONT* font = al_load_ttf_font("./res/consolas/CONSOLA.TTF", 16, 
        ALLEGRO_TTF_MONOCHROME);

    // Framebuffer
    ALLEGRO_BITMAP* fb = al_create_bitmap(SIZE, SIZE);
    ALLEGRO_LOCKED_REGION* fb_lock;

    init_cells();
    init_brush();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    
    b32 running = true;
    b32 redraw = false;
    b32 mouse_down = false;
    al_start_timer(timer);
    ALLEGRO_MOUSE_STATE mouse_state;
    while (running)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            running = false;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { running = false; }
            break;

        case ALLEGRO_EVENT_KEY_UP:
            if (event.keyboard.keycode == ALLEGRO_KEY_0)
            {
                set_brush_id(VOID);
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_1)
            {
                set_brush_id(SAND);
            }
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            set_brush_size(event.mouse.z);
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            mouse_down = true;
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            mouse_down = false;
            break;

        case ALLEGRO_EVENT_TIMER:
        
            // update
            update_cells();
            update_brush_str();
            al_get_mouse_state(&mouse_state);
            set_brush_pos(mouse_state.x, mouse_state.y);

            if (mouse_down) {

                stamp_brush();

            }

            redraw = true;
            break;
        
        default:
            break;
        }

        if (redraw && al_is_event_queue_empty(event_queue))
        {
            // render
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_set_target_bitmap(fb);
            fb_lock = al_lock_bitmap(fb, ALLEGRO_PIXEL_FORMAT_BGR_888, ALLEGRO_LOCK_WRITEONLY);
            draw_cells(fb_lock);
            al_unlock_bitmap(fb);

            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(fb, 0, 0, 0);
            draw_brush(font);

            al_flip_display();
        }
    }
    al_stop_timer(timer);

    destroy_cells();
    destroy_brush();

    al_unlock_bitmap(fb);

    al_unregister_event_source(event_queue, al_get_display_event_source(display));
    al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
    al_unregister_event_source(event_queue, al_get_keyboard_event_source());
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_bitmap(fb);

    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_shutdown_image_addon();
    al_shutdown_font_addon();
    al_shutdown_ttf_addon();
    al_shutdown_primitives_addon();

    return 0;
}