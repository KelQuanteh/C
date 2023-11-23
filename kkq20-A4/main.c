// main.c
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>

#include "game.h"

int main() {
    //inicializações
    al_init();
    al_install_keyboard();
    al_install_audio();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_primitives_addon();

    al_set_new_display_option(ALLEGRO_COLOR_SIZE, 32, ALLEGRO_REQUIRE);
    al_set_new_window_title("SPACE INVADERS");

    ALLEGRO_FONT* font = NULL;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    //carregar imagens 
    ALLEGRO_BITMAP* bitmap = NULL;
    ALLEGRO_BITMAP* pause = NULL;
    ALLEGRO_BITMAP* start = NULL;  
    ALLEGRO_BITMAP* sprite = NULL; //alien
    ALLEGRO_BITMAP* ship = NULL;   //player
    ALLEGRO_BITMAP* tiro = NULL;   //player bullet
    ALLEGRO_BITMAP* a_tiro = NULL; //alien bullet
    ALLEGRO_BITMAP* dead = NULL;   //alien morto
    ALLEGRO_BITMAP* disc = NULL;   //disco 
    ALLEGRO_BITMAP* barrier = NULL; 

    //criação dos objetos
    alien alien;
    nave player;
    pistol bullet;
    a_pistol a_bullet;
    disco disco;
    obj obstacle; 
    hit hit_count; 

    hit_count[0].count = 0;
    hit_count[1].count = 0;
    hit_count[2].count = 0;     

    disco.x = 150;
    disco.y = 100;
    disco.height = 50;
    disco.width = 50;

    player.x = SCREEN_X / 2;
    player.y = SCREEN_Y - (SCREEN_Y / 8);
    player.height = 50;
    player.width = 50;

    bullet.x = SCREEN_X / 2;
    bullet.y = SCREEN_Y - (SCREEN_Y / 8);
    bullet.height = 10;
    bullet.width = 10;

    a_bullet[0].x = SCREEN_X / 2;
    a_bullet[0].y = SCREEN_Y;
    a_bullet[0].height = 10;
    a_bullet[0].width = 10;

    a_bullet[1].x = SCREEN_X / 2;
    a_bullet[1].y = SCREEN_Y;
    a_bullet[1].height = 10;
    a_bullet[1].width = 10;

    int passo = 0;
    int tempo = 65;
    int t = 0;
    int score = 0;
    int vida = 3;
    int vidas = 3; 
    int play = 0; 
    int lft = 0;
    int dwn = 0;
    int dscx = 2000;
    int killed = 0;
    int num_aliens = 70;

    font = al_load_ttf_font("space_invaders.ttf", 35, 0); //load font
    if (!font) {
        fprintf(stderr, "Falha ao carregar a fonte!\n");
        return -1;
    }

    display = al_create_display(SCREEN_X, SCREEN_Y);
    queue = al_create_event_queue();
    
    timer = al_create_timer(1.0 / 60); //inicializa timer 60fps
    if (timer == NULL){
        printf("Falha ao alocar o timer!");
        return -1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    //carregar bitmaps
    bitmap = load_bitmap("background.png");
    pause = load_bitmap("bg_pause.png");
    start = load_bitmap("bg_inicio.png");
    sprite = load_bitmap("alien1.png");
    ship = load_bitmap("nave.png");
    tiro = load_bitmap("tiroA.png");
    a_tiro = load_bitmap("tiroB.png");
    dead = load_bitmap("explosion.png");
    disc = load_bitmap("alien2.png");
    barrier = load_bitmap("plasmabarrier.png");

    //carregar sons
    al_reserve_samples(4);

    ALLEGRO_SAMPLE* fire;
    ALLEGRO_SAMPLE* player_explosion;
    ALLEGRO_SAMPLE* alien_explosion;
    ALLEGRO_SAMPLE* saucer_explosion;
    ALLEGRO_KEYBOARD_STATE keyState;

    fire = load_sample("tiro.wav");
    player_explosion = load_sample("explosao_player.wav");
    alien_explosion = load_sample("explosao_alien.wav");
    saucer_explosion = load_sample("kill.wav");

    bool running = true;
    bool trigger = false;

    al_start_timer(timer);

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 10; j++) {
            alien[j][i].x = 250 + j * 100;
            alien[j][i].y = 200 + i * 50;
            alien[j][i].height = 50;
            alien[j][i].width = 50;
        }
    }

    for (int i = 0; i < 3; i++){
        obstacle[i].x = 250 + i * 350;
        obstacle[i].y = SCREEN_Y - (SCREEN_Y / 4);
        obstacle[i].width = 100;
        obstacle[i].height = 50; 
    }
    

    bool pausa = false;

    while (running) {

        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(start, 0, 0, 0);
        al_flip_display();
        al_get_keyboard_state(&keyState);
        
        if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
            running = false;
        } else if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)) {
            play = 1; 
            while (running || play) {
                if (vida == 0) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_X / 2, SCREEN_Y / 4, ALLEGRO_ALIGN_CENTRE, "G A M E  O V E R !!!" );
                    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_X / 2, SCREEN_Y / 3, ALLEGRO_ALIGN_CENTRE, "Score: %d", score);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), SCREEN_X / 2, SCREEN_Y / 2, ALLEGRO_ALIGN_CENTRE, "Replay ?  Y / N" );
                    al_flip_display();
                    al_get_keyboard_state(&keyState);
                    if (al_key_down(&keyState, ALLEGRO_KEY_N)) {
                            al_destroy_bitmap(disc);
                            al_destroy_bitmap(dead); 
                            al_destroy_bitmap(a_tiro);
                            al_destroy_bitmap(barrier);
                            al_destroy_bitmap(tiro);
                            al_destroy_bitmap(ship);  
                            al_destroy_bitmap(sprite);
                            al_destroy_bitmap(start);
                            al_destroy_bitmap(bitmap);
                            al_destroy_sample(saucer_explosion);
                            al_destroy_sample(alien_explosion);
                            al_destroy_sample(player_explosion);
                            al_destroy_sample(fire);
                            al_destroy_font(font);
                            al_destroy_timer(timer); 
                            al_destroy_event_queue(queue);
                            al_destroy_display(display);
                            play = 0; 
                            running = false;
                    } else if (al_key_down(&keyState, ALLEGRO_KEY_Y)){
                        vida = vidas;
                        score = 0; 
                        dscx = 2000;
                        play = 1;
                        for (int i = 0; i < 7; i++) {
                            for (int j = 0; j < 10; j++) {
                                alien[j][i].x = 250 + j * 100;
                                alien[j][i].y = 200 + i * 50;
                                alien[j][i].height = 50;
                                alien[j][i].width = 50;
                            }
                        }
                        al_rest(0.5);
                    }
                    
                } else if (vida > 0 && num_aliens != 0){
                    t++;
                    passo = 0;
                    if (t > tempo) {
                        passo = 1;
                        t = 0;
                    }

                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_bitmap(bitmap, 0, 0, 0);

                    //disco voador
                    dscx--;
                    disco.x = dscx;
                    if (disco.x < -disco.width) dscx = 2000;

                    al_draw_bitmap(disc, disco.x, disco.y, 0);

                    if (collide(bullet.x, bullet.y, disco.x, disco.y, bullet.width, bullet.height, disco.width, disco.height)) {
                        al_play_sample(saucer_explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        al_draw_bitmap(dead, disco.x, disco.y, 0); 
                        disco.y = SCREEN_Y;
                        score += 40; // +40 score
                        dscx = 2000;
                        trigger = false;
                    }

                    int sort = rand() % 10;

                    //alien bullets inicialização
                    if (a_bullet[0].y < SCREEN_Y)
                        a_bullet[0].y += 5;
                    if (a_bullet[1].y < SCREEN_Y)
                        a_bullet[1].y += 5;

                    for (int i = 0; i < 7; i++) {
                        //alien bullets (1)
                        if (a_bullet[1].y >= SCREEN_Y && alien[sort][6 - i].y < SCREEN_Y) {
                            a_bullet[1].x = alien[sort][4 - i].x + alien[sort][4 - i].width / 2;
                            a_bullet[1].y = alien[sort][4 - i].y + alien[sort][4 - i].height / 2;
                        }

                        for (int j = 0; j < 10; j++) {

                            if (alien[j][i].y < SCREEN_Y) {
                                if (alien[j][i].x < 10 && !lft) {
                                    dwn = 1;
                                    alien[j][i].x += passo * 10;
                                }
                                if (alien[j][i].x > SCREEN_X - 50 && lft) {
                                    dwn = 1;
                                    alien[j][i].x -= passo * 10;
                                }
                                lft ? (alien[j][i].x += passo * 30) : (alien[j][i].x -= passo * 30);
                            }

                            //alien bullets (0)
                            if (alien[9 - j][6 - i].x == player.x && a_bullet[0].y >= SCREEN_Y && alien[9 - j][6 - i].y < SCREEN_Y) {
                                a_bullet[0].x = alien[9 - j][6 - i].x + alien[9 - j][6 - i].width / 2;
                                a_bullet[0].y = alien[9 - j][6 - i].y + alien[9 - j][6 - i].height / 2;
                            }

                            al_draw_bitmap(sprite, alien[j][i].x, alien[j][i].y, 0); //draw aliens
                            
                            //draw alien bullets
                            al_draw_bitmap(a_tiro, a_bullet[0].x, a_bullet[0].y, 0);
                            al_draw_bitmap(a_tiro, a_bullet[1].x, a_bullet[1].y, 0);

                            // collision check
                            if (collide(bullet.x, bullet.y, alien[j][i].x, alien[j][i].y, bullet.width, bullet.height, alien[j][i].width, alien[j][i].height)) {
                                al_draw_bitmap(dead, alien[j][i].x, alien[j][i].y, 0); //draw explosion
                                alien[j][i].y = SCREEN_Y;
                                al_play_sample(alien_explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                                score += 10; // +10 score
                                num_aliens --;
                                trigger = false;
                            }
                        }
                    }


                    //barreiras
                    for (int i = 0; i < 3; i++){
                        al_draw_bitmap(barrier, obstacle[i].x, obstacle[i].y, 0);

                        for (int j = 0; j < 2; j++){
                            if (collide(a_bullet[j].x, a_bullet[j].y, obstacle[i].x, obstacle[i].y, a_bullet[j].width, a_bullet[j].height, obstacle[i].width, obstacle[i].height)){
                                a_bullet[j].y = SCREEN_Y;
                                
                                if (hit_count[i].count == 10){
                                    obstacle[i].y = SCREEN_Y;
                                } else
                                    hit_count[i].count++;
                            }
                        } 
                    }

                    if (trigger)
                        bullet.y -= 15;

                    if (bullet.y < (SCREEN_Y / 4) - 200)
                        trigger = false;

                    if (!trigger) {
                        bullet.x = player.x + 25;
                        bullet.y = player.y;
                    }

                    //kill check
                    if (collide(a_bullet[0].x, a_bullet[0].y, player.x, player.y, a_bullet[0].width, a_bullet[0].height, player.width, player.height) ||
                        collide(a_bullet[1].x, a_bullet[1].y, player.x, player.y, a_bullet[1].width, a_bullet[1].height, player.width, player.height)) {
                        al_play_sample(player_explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        killed = 1;
                    }

                    //aliens drop down
                    if (dwn) {
                        lft = !lft;
                        for (int i = 0; i < 7; i++) {
                            for (int j = 0; j < 10; j++) {
                                alien[j][i].y += 30;
                            }
                        }
                    }
                    dwn = 0;

                    if (killed) {
                        al_draw_bitmap(dead, player.x, player.y, 0);
                    } else {
                        al_draw_bitmap(ship, player.x, player.y, 0);
                        al_draw_bitmap(tiro, bullet.x, bullet.y, 0);
                    }

                    al_draw_textf(font, al_map_rgb(255, 0, 255), (SCREEN_X / 4) + SCREEN_X / 2, 50, 0, "SCORE: %d", score);
                    al_draw_textf(font, al_map_rgb(57, 255, 20), SCREEN_X / 4, 50, 0, "VIDAS: %d", vida);

                    al_get_keyboard_state(&keyState);

                    // controls
                    if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                        pausa = true;
                        al_rest(0.5); // Adicionar um pequeno atraso para evitar detecção acidental de pressionar tecla
                        while (pausa) {
                            al_clear_to_color(al_map_rgb(0, 0, 0));
                            al_draw_bitmap(pause, 0, 0, 0);
                            al_flip_display();
                            al_get_keyboard_state(&keyState);
                            if (al_key_down(&keyState, ALLEGRO_KEY_P)) {
                                al_rest(0.5);
                                pausa = false;
                            } else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
                                //liberar memória
                                al_destroy_bitmap(disc);
                                al_destroy_bitmap(dead); 
                                al_destroy_bitmap(a_tiro);
                                al_destroy_bitmap(tiro);
                                al_destroy_bitmap(barrier);
                                al_destroy_bitmap(ship);  
                                al_destroy_bitmap(sprite);
                                al_destroy_bitmap(start);
                                al_destroy_bitmap(bitmap);
                                al_destroy_sample(saucer_explosion);
                                al_destroy_sample(alien_explosion);
                                al_destroy_sample(player_explosion);
                                al_destroy_sample(fire);
                                al_destroy_font(font);
                                al_destroy_timer(timer); 
                                al_destroy_event_queue(queue);
                                al_destroy_display(display);
                                play = 0;
                                running = false;
                                pausa = false;
                            }
                        }
                    } else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && player.x > PLAYER_WIDTH) {
                        player.x -= 5;
                    } else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && player.x < SCREEN_X - PLAYER_WIDTH/2) {
                        player.x += 5;
                    } else if (al_key_down(&keyState, ALLEGRO_KEY_SPACE) && (!trigger)) {
                        al_play_sample(fire, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        trigger = true;
                    }
                    
                    al_flip_display();

                    if (killed){
                        vida--; 
                        play = 0; 
                        al_rest(2);
                        killed = 0;
                        player.x = SCREEN_X/2;
                        a_bullet[0].y = SCREEN_Y/2;
                        a_bullet[1].y = SCREEN_Y/2;  
                    } 
                    al_rest(0.016);
                } else {
                    al_flip_display();
                    vida ++; 
                    dscx = 2000;
                    num_aliens = 70;
                    play = 1;
                    for (int i = 0; i < 7; i++) {
                        for (int j = 0; j < 10; j++) {
                            alien[j][i].x = 250 + j * 100;
                            alien[j][i].y = 200 + i * 50;
                            alien[j][i].height = 50;
                            alien[j][i].width = 50;
                        }
                    }
                    al_rest(0.5); 
                }   
            }
        }    
    }

    al_uninstall_audio();
    al_uninstall_keyboard();

    return 0;
}

