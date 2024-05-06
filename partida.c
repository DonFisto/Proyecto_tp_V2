#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "jugador.h"
#include "constantes.h"
#include "colisiones.h"
#include "rafaga.h"
#include "enemigos.h"
#include "consumibles.h"
#include "partida.h"
#include "mapa.h"
#include "camara.h"

typedef char * Nombre;
struct Leaderboard
{
    Nombre * l;
    int * pts;
};

struct PartidaRep
{
    int active;
    int menu;
    int pause;
    int round;
    int troundleft;
    int pts;
    struct Leaderboard lb;
    Imagen backg;
};
int get_game_active(Partida p)
{
    return p->active;
}
int get_game_pause(Partida p)
{
    return p->pause;
}
int get_game_round(Partida p)
{
    return p->round;
}
int get_game_time(Partida p)
{
    return p->troundleft;
}
int get_game_pts(Partida p)
{
    return p->pts;
}
void add_game_pts(Partida p, int n)
{
    p->pts = p->pts + n;
}
void unpause(Partida p)
{
    p->pause = 0;
}
void end_game(Partida p)
{
    p->active = 0;
}
struct Leaderboard read_records()
{
    struct Leaderboard lb;
    lb.l = malloc(LB_SIZE * sizeof(Nombre));
    for(int i = 0; i<LB_SIZE; i++)
    {
        lb.l[i] = malloc(9 * sizeof(char));
    }
    lb.pts = malloc(LB_SIZE * sizeof (int));
    FILE * fp = NULL;
    fp = fopen("record.txt", "r");
    if (fp != NULL)
    {
        for(int i = 0; i < LB_SIZE; i = i + 1)
        {
            fscanf(fp,"%d %s", &lb.pts[i], lb.l[i]);
        }
    }
    return lb;
    fclose(fp);
}
void update_records(Partida p)
{
    char * msg;
    int n = 0;
    struct Leaderboard lb = p->lb;
    while (n < LB_SIZE && p->pts <= lb.pts[n])
    {
        n++;
    }
    if(n!=LB_SIZE)
    {
        for(int i = LB_SIZE-1; i > n; i = i - 1)
        {
            lb.l[i] = lb.l[i-1];
            lb.pts[i] = lb.pts[i-1];
        }
        printf("OK\n");

        lb.pts[n] = p->pts;
        msg = lee_texto(750, 375, 8, "Introduce tu nombre:  ");
        lb.l[n] = msg;
    }
    FILE * fp = NULL;
    fp = fopen("record.txt", "w");
    if (fp != NULL)
    {
        for(int i = 0; i < LB_SIZE; i = i + 1)
        {
            fprintf(fp,"%d %s ", lb.pts[i], lb.l[i]);
        }
    }
    fclose(fp);
}

Partida start_game()
{
    Partida p = malloc(sizeof(struct PartidaRep));
    p->active = 1;
    p->menu = 0;
    p->pause = 0;
    p->round = 0;
    p->troundleft = 500;
    p->pts = 0;
    p->lb = read_records();
    p->backg = lee_imagen("map4.bmp", 0);
    return p;
}
void free_game(Partida p)
{
    free(p->backg);
    free(p);
}
int check_end_game(Partida p, Jugador j)
{
    if(get_player_lives(j) == 0)
    {
     p->lb = read_records();
     update_records(p);
     p->menu = 0;

     return 1;
    }
    return 0;
}
void army_generation(Partida p, Ejercito e, Jugador j, Mapa m)
{
    int e0;
    int e1;
    int e2;
    int hoard_size = p->round + 10;
    if (hoard_size > T_MAX_EJERCITO)
    {
        hoard_size = T_MAX_EJERCITO;
    }
    switch(hoard_size)
    {
    case 10:
        e0 = 0;
        e1 = 0;
        e2 = 10;
        break;
    case 11:
        e0 = 0;
        e1 = 3;
        e2 = 8;
        break;
    case 12:
        e0 = 0;
        e1 = 4;
        e2 = 8;
        break;
    case 13:
        e0 = 0;
        e1 = 5;
        e2 = 8;
        break;
    case 14:
        e0 = 3;
        e1 = 3;
        e2 = 8;
        break;
    case 15:
        e0 = 3;
        e1 = 4;
        e2 = 8;
        break;
    case 16:
        e0 = 5;
        e1 = 6;
        e2 = 5;
        break;
    case 17:
        e0 = 7;
        e1 = 6;
        e2 = 4;
        break;
    case 18:
        e0 = 7;
        e1 = 8;
        e2 = 3;
        break;
    case 19:
        e0 = 8;
        e1 = 8;
        e2 = 3;
        break;
    case 20:
        e0 = 7;
        e1 = 10;
        e2 = 3;
        break;
    case 21:
        e0 = 10;
        e1 = 9;
        e2 = 2;
        break;
    case 22:
        e0 = 11;
        e1 = 10;
        e2 = 1;
        break;
    case 23:
        e0 = 8;
        e1 = 14;
        e2 = 1;
        break;
    case 24:
        e0 = 14;
        e1 = 9;
        e2 = 1;
        break;
    case 25:
        e0 = 12;
        e1 = 13;
        e2 = 0;
        break;
    case 26:
        e0 = 14;
        e1 = 12;
        e2 = 0;
        break;
    case 27:
        e0 = 3;
        e1 = 24;
        e2 = 0;
        break;
    case 28:
        e0 = 20;
        e1 = 7;
        e2 = 1;
        break;
    case 29:
        e0 = 5;
        e1 = 24;
        e2 = 0;
        break;
    default:
        e0 = 7;
        e1 = 7;
        e2 = 1;
    }
    if(get_army_ealive(e)>hoard_size)
    {
        set_ealive(e, hoard_size);
    }
    for (int i = 0; i<(hoard_size - get_army_ealive(e)); i++)
    {
        int x = rand()%(W-40);
        int y = rand()%(H-40);
        while(distancia_punto_punto((get_player_pos_x(j) + get_player_width(j)/2),(get_player_pos_y(j) + get_player_height(j)/2), x, y) < 500 || map_collision(m, x, y, 80, 80))
        {
            x = rand()%(W-40);
            y = rand()%(H-40);
        }
        if(e0 > 0)
        {
            insert_enemy(e, x, y, 0);
            e0 = e0 - 1;
        }
        else if (e1 > 0)
        {
            insert_enemy(e, x, y, 1);
            e1 = e1 - 1;
        }
        else if (e2 > 0)
        {
            insert_enemy(e, x, y, 2);
            e2 = e2 - 1;
        }
    }



}
void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re, Mapa m)
{
    move_army(e, get_player_pos_x(j), get_player_pos_y(j), get_player_inv(j), re, m);
    if ((object_army_collision(e, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j))||(burst_shot_collision(re, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j))))&&(!get_player_inv(j)))
    {
        dmg(j);
    }
    add_game_pts(p,army_burst_shot_collision(e, rj));
    if(p->troundleft == 0)
    {
        p->round = p->round + 1;
        army_generation(p, e, j, m);
        printf("-----ROUND %d-----\n",p->round);
        p->troundleft = TROUND;
    }
    else if(get_army_ealive(e) == 0)
    {
        p->troundleft = 0;
    }
    else
    {
        p->troundleft = p->troundleft - 1;
    }



}
void box_behavior(Partida p, Caja c, Jugador j, Mapa m)
{
    if(box_collision(c, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j)))
    {
        add_game_pts(p, 2);
        switch(get_box_type(c))
        {
        case 0:
            set_energy(j, 120);
            break;
        case 1:
            set_energy(j, 120);
            break;
        case 2:
            set_energy(j, 120);
            break;
        case 3:
            set_inv(j, 100);
            break;
        case 4:
            set_lives(j, get_player_lives(j) + 1);
            break;
        case 5:
            set_triple_shot(j);
            break;

        }
        move_box(c, m);
    }
}
void draw_HUD(Partida p, Jugador j, Ejercito e, Caja c, Mapa m, Camara cam)
{
    int ratiow = W/CAMERA_W;
    char msg[15];
    dibuja_rectangulo(5, 5, 200, 20);
    sprintf(msg, "vidas: %d\n", get_player_lives(j));
    dibuja_texto(msg, 10, 10);
    sprintf(msg,"pts: %d\n", get_game_pts(p) );
    dibuja_texto(msg, 100, 10);
    draw_minimap(m, CAMERA_W - W/ratiow/5, 0, 5);
    color_relleno(0, 0, 255, 100);
    dibuja_rectangulo(get_player_pos_x(j)/W*CAMERA_W/5 + CAMERA_W - W/ratiow/5, get_player_pos_y(j)/H*CAMERA_H/5, 4, 4);
    color_relleno(255, 0, 0, 255);
    for(int i = 0; i < get_army_ealive(e); i = i + 1)
    {
        dibuja_rectangulo(get_enemy_x(e, i)/W*CAMERA_W/5 + CAMERA_W - W/20, get_enemy_y(e, i)/H*CAMERA_H/5, 4, 4);
    }
    color_relleno(0, 255, 0, 255);
    dibuja_rectangulo(get_box_x(c)/W*CAMERA_W/5 + CAMERA_W - W/20, get_box_y(c)/H*CAMERA_H/5, 4, 4);

}
void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m, Camara cam)
{
    double offset_x = get_cam_x(cam);
    double offset_y = get_cam_y(cam);
    dibuja_imagen(p->backg, -200 -offset_x/15, -300 - offset_y/15, 2400, 1350);
    draw_map(m, cam);
    draw_player(j, cam);
    draw_army(e, cam);
    draw_burst_shot(rj, cam);
    draw_burst_shot(re, cam);
    draw_box(c, cam);
    draw_HUD(p, j, e, c, m, cam);


}
void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m, Camara cam)
{
    move_player(j, rj, m);
    army_behavior(p, e, j, rj, re, m);
    move_burst_shot(rj, m);
    move_burst_shot(re, m);
    camera_follow(cam, get_player_pos_x(j), get_player_pos_y(j));
    box_behavior(p, c, j, m);
    if(tecla_pulsada(SDL_SCANCODE_ESCAPE))
    {
        p->pause = 1;
        while (pantalla_activa() && tecla_pulsada(SDL_SCANCODE_ESCAPE))
        {
            espera(1);
        }
    }
    if(check_end_game(p, j))
    {
        end_game(p);
    }

}




int button_click(double x, double y, double w, double h)
{
    return (dentro_rectangulo(x, y, w, h, x_raton(), y_raton()) && boton_raton_pulsado(SDL_BUTTON_LEFT));
}
int menu(Partida p)
{
    int result = 0;
    //botón de partida
    color_relleno(100, 100, 100, 255);
    dibuja_rectangulo(500, 100, 500, 150);
    dibuja_texto("JUGAR", 730, 175);
    if(button_click(500, 100, 500, 150))result = 1;
    //botón ayuda
    dibuja_rectangulo(500, 300, 500, 150);
    dibuja_texto("AYUDA", 730, 375);
    if(button_click(500, 300, 500, 150))result = 2;
    //botón salir
    color_relleno(255, 0, 0, 255);
    dibuja_rectangulo(500, 500, 500, 150);
    dibuja_texto("SALIR", 730, 575);
    if(button_click(500, 500, 500, 150))result = 3;
    //botón mapa nuevo
    color_relleno(0, 255, 0, 255);
    dibuja_rectangulo(1300, 200, 50, 50);
    dibuja_texto("GENERAR MAPA ALEATORIO", 1230, 175);
    if(button_click(1300, 200, 50, 50))result = 4;
    while (pantalla_activa() && (button_click(500, 100, 500, 150) || button_click(500, 500, 500, 150) || button_click(1300, 200, 50, 50)))
    {
        espera(1);
    }

    return result;

}
int pause_menu(Partida p)
{
    int result = 0;
    color_relleno(255, 255, 255, 75);
    dibuja_rectangulo(0, 0, 1500, 750);

    //botón de partida
    color_relleno(100, 100, 100, 255);
    dibuja_rectangulo(500, 100, 500, 150);
    dibuja_texto("CONTINUAR", 700, 175);
    if(button_click(500, 100, 500, 150)||tecla_pulsada(SDL_SCANCODE_ESCAPE))result = 1;
    while (pantalla_activa() && tecla_pulsada(SDL_SCANCODE_ESCAPE))
    {
        espera(1);
    }
    //botón salir
    color_relleno(255, 0, 0, 255);
    dibuja_rectangulo(500, 500, 500, 150);
    dibuja_texto("SALIR A MENU", 690, 575);
    if(button_click(500, 500, 500, 150))result = 2;

    while (pantalla_activa() && (button_click(500, 100, 500, 150) || button_click(500, 500, 500, 150) || tecla_pulsada(SDL_SCANCODE_ESCAPE)))
    {
        espera(1);
    }

    return result;

}
void ayuda(Partida p, Jugador j, Ejercito e, Rafaga r, Camara cam)
{
    int activo = 1;
    while (pantalla_activa()&&activo)
    {
        dibuja_imagen(p->backg, -50, -75, 1600, 900);
        color_relleno(255, 255, 255, 255);
        dibuja_rectangulo(700, 50, 100, 50);
        dibuja_texto("TUTORIAL", 715, 70);
        Mapa m =create_map();
        reset_map(m);
        actualiza_pantalla();
        espera(10);
        while(pantalla_activa()&&!solape_circ_rect(CAMERA_W/2, CAMERA_H/2, 100, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j)))
        {
            double offset_x = get_cam_x(cam);
            double offset_y = get_cam_y(cam);
            dibuja_imagen(p->backg, -50, -75, 1600, 900);
            color_relleno(255, 255, 255, 70);
            dibuja_circulo(CAMERA_W/2 - offset_x, CAMERA_H/2 - offset_y, 100);
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo(700, 50, 100, 50);
            dibuja_texto("TUTORIAL", 715, 70);
            dibuja_rectangulo( CAMERA_W/2 - offset_x - 200, CAMERA_H/2 - offset_y - 150 , 400, 25);
            dibuja_texto("MUEVE EL JUGADOR HASTA EL CIRCULO (WASD)", CAMERA_W/2 - offset_x - 180 ,  CAMERA_H/2 - offset_y - 145 );
            draw_player(j, cam);
            camera_follow(cam, get_player_pos_x(j), get_player_pos_y(j));
            move_player(j, r, m);
            actualiza_pantalla();
            espera(15);
        }
        insert_enemy(e, CAMERA_W/2 + 300, CAMERA_H/2, 2);
        while(pantalla_activa()&&!burst_shot_collision(r, get_enemy_x(e, 0), get_enemy_y(e, 0), 50, 50))
        {
            double offset_x = get_cam_x(cam);
            double offset_y = get_cam_y(cam);
            dibuja_imagen(p->backg, -50, -75, 1600, 900);
            color_relleno(255, 255, 255, 70);
            draw_army(e, cam);
            draw_burst_shot(r, cam);
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo(700, 50, 100, 50);
            dibuja_texto("TUTORIAL", 715, 70);
            dibuja_rectangulo( get_enemy_x(e, 0)- 175 - offset_x, get_enemy_y(e, 0) - 75 - offset_y, 400, 50);
            dibuja_texto("DISPARA AL ENEMIGO PARA CONSEGUIR PUNTOS", get_enemy_x(e, 0)- 150 - offset_x ,  get_enemy_y(e, 0) - 70 - offset_y );
            dibuja_texto("<- Y -> PARA APUNTAR, ESPACIO PARA DISPARAR", get_enemy_x(e, 0)- 170 - offset_x ,  get_enemy_y(e, 0) - 40 - offset_y );
            draw_player(j, cam);
            camera_follow(cam, get_player_pos_x(j), get_player_pos_y(j));
            move_player(j, r, m);
            move_burst_shot(r, m);
            set_energy(j, 120);
            actualiza_pantalla();
            espera(15);
        }
        double rx = CAMERA_W/2 - 300;
        double ry = CAMERA_H/2 + 300;
        while(pantalla_activa()&&!solape_rectangulos(rx + 10, ry + 10, 10, 10, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j)))
        {
            double offset_x = get_cam_x(cam);
            double offset_y = get_cam_y(cam);
            dibuja_imagen(p->backg, -50, -75, 1600, 900);
            color_relleno(255, 255, 255, 70);
            color_relleno(0, 255, 0, 255);
            dibuja_rectangulo(rx - offset_x, ry - offset_y, 40, 40);
            draw_burst_shot(r, cam);
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo(700, 50, 100, 50);
            dibuja_texto("TUTORIAL", 715, 70);
            dibuja_rectangulo( rx - offset_x - 180, ry - offset_y - 75 , 400, 25);
            dibuja_texto("CONSIGUE EL TESORO PARA OBTENER MEJORAS", rx - offset_x - 155 ,  ry - offset_y - 70 );
            draw_player(j, cam);
            camera_follow(cam, get_player_pos_x(j), get_player_pos_y(j));
            move_player(j, r, m);
            move_burst_shot(r, m);
            actualiza_pantalla();
            espera(15);
        }
        int cutscene = 1;
        color_relleno(20, 20, 20, 180);
        dibuja_rectangulo(0, 0, CAMERA_W, CAMERA_H);
        while(pantalla_activa() && cutscene)
        {
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo( 550, 145 , 400, 25);
            dibuja_texto("HAY CUATRO TIPOS DE TESORO DISTINTOS: ", 575 ,  150 );
            actualiza_pantalla();
            espera(15);
            int i = 0;
            while (pantalla_activa() && i < 100)
            {
                espera(20);
                i = i + 1;
            }
            dibuja_rectangulo( 200, 300 , 200, 25);
            dibuja_texto("RECARGA DE MUNICION ", 215 ,  305 );
            color_relleno(0,255,0,255);
            dibuja_rectangulo(280, 355, 40, 40);
            color_relleno(162, 103, 18, 255);
            dibuja_circulo(280 + 40/3*2,355 + 40/2 - 0.0005, 6.1);
            color_relleno(50, 50, 50, 255);
            dibuja_rectangulo(280 + 40/4, 355 + 40/3, 40/3 + 40/12, 40/3);
            actualiza_pantalla();
            espera(15);
            i = 0;
            while (pantalla_activa() && i < 80)
            {
                espera(20);
                i = i + 1;
            }
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo( 550, 300 , 100, 25);
            dibuja_texto("ESCUDO", 575 ,  305 );
            color_relleno(0,255,0,255);
            dibuja_rectangulo(580, 355, 40, 40);
            color_relleno(20, 209, 218, 255);
            dibuja_circulo(580 + 40/2, 355 + 40/2 , 40/4);
            actualiza_pantalla();
            espera(15);
            i = 0;
            while (pantalla_activa() && i < 80)
            {
                espera(20);
                i = i + 1;
            }
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo( 800, 300 , 200, 25);
            dibuja_texto("VIDA EXTRA ", 845 ,  305 );
            color_relleno(0,255,0,255);
            dibuja_rectangulo(880, 355, 40, 40);
            color_relleno(255, 0, 0, 255);
            color_trazo(0, 0, 0, 0);
            dibuja_rectangulo(880 + 15, 355 + 40/4, 40/4, 40/2);
            dibuja_rectangulo(880 + 40/4, 355 + 15, 40/2, 40/4);
            color_trazo(0, 0, 0, 255);
            actualiza_pantalla();
            espera(15);
            i = 0;
            while (pantalla_activa() && i < 80)
            {
                espera(20);
                i = i + 1;
            }
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo( 1100, 300 , 200, 25);
            dibuja_texto("TRIPLE DISPARO ", 1145 ,  305 );
            color_relleno(0,255,0,255);
            dibuja_rectangulo(1180, 355, 40, 40);
            color_relleno(115, 0, 255, 255);
            dibuja_circulo(1180 + 40/4, 355 + 40*2/3, 40/6);
            dibuja_circulo(1180 + 40*3/4, 355 + 40*2/3, 40/6);
            dibuja_circulo(1180 + 40/2, 355 + 40/3, 40/6);
            actualiza_pantalla();
            espera(15);
            i = 0;
            while (pantalla_activa() && i < 200)
            {
                espera(20);
                i = i + 1;
            }
            color_relleno(255, 255, 255, 255);
            dibuja_rectangulo( 500, 645 , 500, 25);
            dibuja_texto("ESTE ES  EL FINAL DEL TUTORIAL, PULSE ESC PARA SALIR ", 525 ,  650 );
            actualiza_pantalla();
            espera(15);
            while (pantalla_activa() && !tecla_pulsada(SDL_SCANCODE_ESCAPE))
            {
                espera(10);
            }
            cutscene = 0;
            activo = 0;

        }
    }
}

