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

Partida start_game()
{
    Partida p = malloc(sizeof(struct PartidaRep));
    p->active = 1;
    p->round = 0;
    p->troundleft = 500;
    p->pts = 0;
    p->lb = read_records();
    p->backg = lee_imagen("map4.bmp", 0);
    return p;
}
int check_end_game(Jugador j)
{
    return (get_player_lives(j) == 0);
}
void army_generation(Partida p, Ejercito e, Jugador j)
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
        e1 = 0;
        e2 = 3;
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

        if(e0 > 0)
        {
            insert_enemy(e, rand()%(W-40), rand()%(H-40), 0, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j));
            e0 = e0 - 1;
        }
        else if (e1 > 0)
        {
            insert_enemy(e, rand()%(W-40), rand()%(H-40), 1, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j));
            e1 = e1 - 1;
        }
        else if (e2 > 0)
        {
            insert_enemy(e, rand()%(W-40), rand()%(H-40), 2, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j));
            e2 = e2 - 1;
        }
    }



}
void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re)
{
    move_army(e, get_player_pos_x(j), get_player_pos_y(j), get_player_inv(j), re);
    if ((object_army_collision(e, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j))||(burst_shot_collision(re, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j))))&&(!get_player_inv(j)))
    {
        dmg(j);
    }
    army_burst_shot_collision(e, rj);
    if(p->troundleft == 0)
    {
        p->round = p->round + 1;
        army_generation(p, e, j);
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
void box_behavior(Caja c, Jugador j)
{
    if(box_collision(c, get_player_pos_x(j), get_player_pos_y(j), get_player_width(j), get_player_height(j)))
    {
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
            break;
        }
        move_box(c);
    }
}
void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c)
{
    dibuja_imagen(p->backg, -50.0, -75, 1600, 900);
    char msg[15];
    dibuja_rectangulo(5, 5, 200, 20);
    sprintf(msg, "vidas: %d\n", get_player_lives(j));
    dibuja_texto(msg, 10, 10);
    sprintf(msg,"pts: %d\n", get_player_pts(j) );
    dibuja_texto(msg, 100, 10);
    draw_player(j);
    draw_army(e);
    draw_burst_shot(rj);
    draw_burst_shot(re);
    draw_box(c);

}
void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c)
{
    move_player(j, rj);
    army_behavior(p, e, j, rj, re);
    move_burst_shot(rj);
    move_burst_shot(re);
    box_behavior(c, j);
    if(check_end_game(j))
    {
        p->active = 0;
    }

}
