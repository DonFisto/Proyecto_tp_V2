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
    int hoard_size = p->round/2 + 1;
    if (hoard_size > T_MAX_EJERCITO)
    {
        hoard_size = T_MAX_EJERCITO;
    }
    switch(hoard_size)
    {
    case 1:
        e0 = 0;
        e1 = 0;
        e2 = 1;
        break;
    case 2:
        e0 = 0;
        e1 = 0;
        e2 = 2;
        break;
    case 3:
        e0 = 0;
        e1 = 1;
        e2 = 2;
        break;
    case 4:
        e0 = 1;
        e1 = 0;
        e2 = 3;
        break;
    case 5:
        e0 = 3;
        e1 = 0;
        e2 = 2;
        break;
    case 6:
        e0 = 4;
        e1 = 1;
        e2 = 1;
        break;
    case 7:
        e0 = 3;
        e1 = 2;
        e2 = 2;
        break;
    case 8:
        e0 = 4;
        e1 = 3;
        e2 = 1;
        break;
    case 9:
        e0 = 2;
        e1 = 6;
        e2 = 1;
        break;
    case 10:
        e0 = 5;
        e1 = 3;
        e2 = 2;
        break;
    case 11:
        e0 = 3;
        e1 = 6;
        e2 = 2;
        break;
    case 12:
        e0 = 6;
        e1 = 4;
        e2 = 2;
        break;
    case 13:
        e0 = 11;
        e1 = 1;
        e2 = 1;
        break;
    case 14:
        e0 = 2;
        e1 = 8;
        e2 = 4;
        break;
    case 15:
        e0 = 7;
        e1 = 7;
        e2 = 1;
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
void box_behavior(Partida p, Caja c, Jugador j)
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
            set_inv(j, 100);
            break;
        case 2:
            set_lives(j, get_player_lives(j) + 1);
            break;
        case 3:
            set_triple_shot(j);
            break;
        }
        move_box(c);
    }
}
void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m)
{
    dibuja_imagen(p->backg, -50.0, -75, 1600, 900);
    draw_map(m);
    char msg[15];
    dibuja_rectangulo(5, 5, 200, 20);
    sprintf(msg, "vidas: %d\n", get_player_lives(j));
    dibuja_texto(msg, 10, 10);
    sprintf(msg,"pts: %d\n", get_game_pts(p) );
    dibuja_texto(msg, 100, 10);
    draw_player(j);
    draw_army(e);
    draw_burst_shot(rj);
    draw_burst_shot(re);
    draw_box(c);

}
void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m)
{
    move_player(j, rj, m);
    army_behavior(p, e, j, rj, re, m);
    move_burst_shot(rj, m);
    move_burst_shot(re, m);
    box_behavior(p, c, j);
    if(tecla_pulsada(SDL_SCANCODE_ESCAPE))
    {
        p->pause = 1;
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
    //botón de partida
    color_relleno(100, 100, 100, 255);
    dibuja_rectangulo(500, 100, 500, 150);
    if(button_click(500, 100, 500, 150))return 1;
    //botón salir
    color_relleno(255, 0, 0, 255);
    dibuja_rectangulo(500, 500, 500, 150);
    if(button_click(500, 500, 500, 150))return 3;
    //botón mapa nuevo
    color_relleno(0, 255, 0, 255);
    dibuja_rectangulo(1300, 200, 50, 50);
    if(button_click(1300, 200, 50, 50))return 4;


    return 0;

}
int pause_menu(Partida p)
{
    color_relleno(255, 255, 255, 75);
    dibuja_rectangulo(0, 0, 1500, 750);
    //botón de partida
    color_relleno(100, 100, 100, 255);
    dibuja_rectangulo(500, 100, 500, 150);
    if(button_click(500, 100, 500, 150)||tecla_pulsada(SDL_SCANCODE_BACKSPACE))return 1;
    //botón salir
    color_relleno(255, 0, 0, 255);
    dibuja_rectangulo(500, 500, 500, 150);
    if(button_click(500, 500, 500, 150))return 2;


    return 0;

}

