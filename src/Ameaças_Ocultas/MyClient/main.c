#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define largura 1024
#define Profundidade 768

#define FPS 60

int initAllegro();

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *grama = NULL, *cerca = NULL, *cerca_vert = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;

void DesenharGrama();

void DesenharParede();

int main(int argc, char *argv[]) {
    printf("O segredo do universo é %d\n", SegredoDoUniverso());

    int err = initAllegro();
    if(err) {
        return err;
    }

    bool running = true;
    bool redraw = true;

    // Display a Green screen
    al_clear_to_color(al_map_rgb(0, 110, 0));
    al_flip_display();

    // Game loop
    while (running) {
        ALLEGRO_EVENT event;

        // Check if we need to redraw
        if (redraw && al_is_event_queue_empty(event_queue)) {
            // Redraw
            al_clear_to_color(al_map_rgb(0, 110, 0));
            DesenharGrama();
            DesenharParede();
            al_flip_display();
            redraw = false;
        }
    }

    // Clean up
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

int initAllegro() {
    // Initialize allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro.\n");
        return 1;
    }

    al_init_image_addon();

    // Create the display
    display = al_create_display(largura, Profundidade);
    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return 1;
    }

    grama = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/GramaPQ.png");
    cerca = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/cerca_edit2.png");
    cerca_vert = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/cerca_edit_vert2.png");

    // Create the event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue.");
        return 1;
    }

    // Register event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));

    return 0;
}

void DesenharGrama(){
    
    int i, j;
    
    for(i = 0; i < 1024; i += 50){
        
        for(j = 0; j < 768; j += 50){
            al_draw_bitmap(grama, i, j, 0);
        }
    }
}

void DesenharParede(){
    int i;
    
    for(i = -20; i < 1004; i += 50){
        al_draw_bitmap(cerca, i, 0, 0);
        al_draw_bitmap(cerca, i, 755, 0);
    }
    
    for(i = -20; i < 748; i += 50){
        al_draw_bitmap(cerca_vert, 0, i, 0);
        al_draw_bitmap(cerca_vert, 1011, i, 0);
    }

    al_draw_bitmap(cerca_vert, 74, 13, 0);
    al_draw_bitmap(cerca_vert, 74, 26, 0);
    al_draw_bitmap(cerca_vert, 185, 13, 0);
    al_draw_bitmap(cerca_vert, 185, 26, 0);
    al_draw_bitmap(cerca_vert, 370, 13, 0);
    al_draw_bitmap(cerca_vert, 444, 13, 0);
    al_draw_bitmap(cerca_vert, 444, 26, 0);
    al_draw_bitmap(cerca_vert, 518, 13, 0);
    al_draw_bitmap(cerca_vert, 518, 26, 0);
    al_draw_bitmap(cerca_vert, 629, 13, 0);
    al_draw_bitmap(cerca_vert, 777, 13, 0);
    al_draw_bitmap(cerca_vert, 777, 26, 0);
    al_draw_bitmap(cerca_vert, 851, 13, 0);
    al_draw_bitmap(cerca_vert, 962, 13, 0);

    for(i = 148; i <= 296; i += 74){
        al_draw_bitmap(cerca_vert, i, 710, 0);
    }
    for(i = 407; i <= 777; i += 74){
        al_draw_bitmap(cerca_vert, i, 710, 0);
    }

    al_draw_bitmap(cerca, 37, 673, 0);
    al_draw_bitmap(cerca_vert, 37, 673, 0);
}