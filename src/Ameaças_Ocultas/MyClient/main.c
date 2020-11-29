#include "lib.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

extern bool chegou;
extern bool running;
extern bool redraw;
extern int tecla;
extern int zona;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_BITMAP *grama, *cerca, *cerca_vert, *kit, *vacina, *cearense_doctor, *Blue_Virus, *Green_Virus, *Pink_Virus, *Red_Virus, *Yellow_Virus;
extern int recebe[20];
extern int Vetor_Posicao[num_elementos_vet];
extern int matriz[20][27];

int initAllegro();

int main(int argc, char *argv[]) {
    printf("O segredo do universo é %d\n", SegredoDoUniverso());

    int err = initAllegro();
    if(err) {
        return err;
    }

    // Display a Green screen
    al_clear_to_color(al_map_rgb(0, 110, 0));
    al_flip_display();

    zona = posicaoPersonagem(Vetor_Posicao);
    posicaoVirus(Vetor_Posicao, zona, recebe);
    
    // Game loop
    while (running) {
        
        // Check if we need to redraw
        if (redraw && al_is_event_queue_empty(event_queue)) {
            // Redraw
            al_clear_to_color(al_map_rgb(0, 110, 0));
            DesenharGrama();
            DesenharParede();
            al_draw_bitmap(kit, 500, 430, 0);
            al_draw_bitmap(vacina, 20, 730, 0);
            desenhaPersonagem(zona);
            desenhaVirus(recebe);
        }
        if(chegou)
        andar();
        al_flip_display();
        redraw = false;
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
    kit = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/kit.png");
    vacina = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Explosives_and_Medic_Icons_From_Youtube_series_PixelTime.png");
    cearense_doctor = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/PARADO.png");
    Blue_Virus = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Blue_Virus.png");
    Green_Virus = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Green_Virus.png");
    Pink_Virus = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Pink_Virus.png");
    Red_Virus = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Red_Virus.png");
    Yellow_Virus = al_load_bitmap("src/Ameaças_Ocultas/Resources/Tile_Sets/Imagens_editadas/Yellow_Virus.png");

    // Create the event queue
    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "Failed to create event queue.");
        return 1;
    }

    matriz_Posicao(matriz);

    // Register event sources
    al_register_event_source(event_queue, al_get_display_event_source(display));

    return 0;
}