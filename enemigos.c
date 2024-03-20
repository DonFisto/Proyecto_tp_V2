#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "jugador.h"
#include "constantes.h"
#include "colisiones.h"
#include "rafaga.h"
#include "enemigos.h"

struct EnemigoRep
{
    double x;
    double y;
    double w;
    double h;
    double dx;
    double dy;
    double v;
    int reroute;
    int alert_dist;
    int type;
    int cdown;

};
struct EjercitoRep
{
    struct EnemigoRep * ej;
    int ealive;
    int n;
};

Ejercito create_army()
{
    Ejercito e = malloc(sizeof(struct EjercitoRep));
    e->ej = malloc(T_MAX_EJERCITO * sizeof(struct EnemigoRep));
    e->ealive = 0;
    e->n = T_MAX_EJERCITO;
    return e;
}
void free_army(Ejercito e)
{
    free(e->ej);
}
void insert_enemy(Ejercito e, double x, double y, int type)
{
    if(e->ealive<T_MAX_EJERCITO)
    {
        struct EnemigoRep enemigo;
        enemigo.x = x;
        enemigo.y = y;
        if (type == 0)
        {
            enemigo.w = 40;
            enemigo.h = 40;
            enemigo.v = 3;
            enemigo.alert_dist = 500;
            enemigo.type = 0;
        }
        else if(type == 1)
        {
            enemigo.w = 30;
            enemigo.h = 60;
            enemigo.v = 3.5;
            enemigo.alert_dist = 800;
            enemigo.type = 1;
        }
        else if(type == 2)
        {
            enemigo.w = 50;
            enemigo.h = 50;
            enemigo.v = 2;
            enemigo.alert_dist = 300;
            enemigo.type = 2;
        }
        e->ej[e->ealive] = enemigo;
        e->ealive = e->ealive + 1;
    }
}
void move_army(Ejercito e, double jx, double jy, int jinv, Rafaga r)
{
    for(int i = 0; i < e->ealive; i = i + 1)
    {
        double v = e->ej[i].v;
        double dp = distancia_punto_punto(e->ej[i].x, e->ej[i].y, jx, jy);
        if (e->ej[i].reroute == 0 && (dp>e->ej[i].alert_dist||jinv != 0))
        {
            e->ej[i].v = v;
            e->ej[i].dx = (rand()%100)/100.0;
            e->ej[i].dy = sqrt(1 - e->ej[i].dx * e->ej[i].dx);
            int dir = rand()%4;
            if(dir==1)
            {
                e->ej[i].dx = -e->ej[i].dx;
            }
            else if(dir==2)
            {
                e->ej[i].dy = -e->ej[i].dy;
            }
            else if(dir==3)
            {
                e->ej[i].dx = -e->ej[i].dx;
                e->ej[i].dy = -e->ej[i].dy;
            }
            e->ej[i].reroute = 40;
        }
        else if (e->ej[i].reroute == 0 && dp<=e->ej[i].alert_dist && jinv == 0)
        {
            if (e->ej[i].type == 0)
            {
                e->ej[i].v = v*37/12;
                e->ej[i].dx = (jx-e->ej[i].x)/dp;
                e->ej[i].dy = (jy-e->ej[i].y)/dp;
                e->ej[i].reroute = 0;
            }
            else if(e->ej[i].type == 1)
            {
                e->ej[i].v = 0;
                e->ej[i].dx = (jx-e->ej[i].x)/dp;
                e->ej[i].dy = (jy-e->ej[i].y)/dp;
                e->ej[i].reroute = 0;
                if(e->ej[i].cdown == 0)
                {
                    Bala b = create_bullet(e->ej[i].x+e->ej[i].w/2,e->ej[i].y + e->ej[i].h/2, e->ej[i].dx, e->ej[i].dy, 45);
                    insert_burst(r, b);
                    e->ej[i].cdown = 100;
                }
                else
                {
                    e->ej[i].cdown = e->ej[i].cdown - 1;
                }
            }
            if (e->ej[i].type == 2)
            {
                e->ej[i].v = v;
                e->ej[i].dx = (jx-e->ej[i].x)/dp;
                e->ej[i].dy = (jy-e->ej[i].y)/dp;
                e->ej[i].reroute = 0;
            }

        }
        else
        {
            e->ej[i].reroute--;
        }
        e->ej[i].x = e->ej[i].x + e->ej[i].v*e->ej[i].dx;
        e->ej[i].y = e->ej[i].y + e->ej[i].v*e->ej[i].dy;

        if(e->ej[i].x >= W )
        {
            e->ej[i].x = -e->ej[i].w+1;
            e->ej[i].reroute = 0;
        }
        if(e->ej[i].x <= -e->ej[i].w )
        {
            e->ej[i].x = W-1;
            e->ej[i].reroute = 0;
        }
        if(e->ej[i].y <= -e->ej[i].h )
        {
            e->ej[i].y = H-1;
            e->ej[i].reroute = 0;
        }
        if(e->ej[i].y >= H )
        {
            e->ej[i].y = -e->ej[i].h +1;
        }
        e->ej[i].v = v;
    }
}
void draw_army(Ejercito e)
{
    for (int i = 0; i < e->ealive; i = i + 1)
    {
        if (e->ej[i].type == 1)
        {
            color_relleno(132, 3, 252, 230);
        }
        else if (e->ej[i].type == 0)
        {
            color_relleno(255, 0, 0, 230);
        }
        else if (e->ej[i].type == 2)
        {
            color_relleno(255, 255, 0, 230);
        }
        dibuja_rectangulo(e->ej[i].x, e->ej[i].y, e->ej[i].w, e->ej[i].w);
        dibuja_linea((e->ej[i].x + e->ej[i].w/2),(e->ej[i].y + e->ej[i].h/2),(e->ej[i].x + e->ej[i].w/2 + 100*e->ej[i].dx),(e->ej[i].y + e->ej[i].h/2 + 100*e->ej[i].y));

    }
}
int object_army_collision(Ejercito e, double x, double y, double w, double h)
{
    for(int i = 0; i < e->ealive; i = i + 1)
    {
        if (solape_rectangulos(e->ej[i].x, e->ej[i].y, e->ej[i].w, e->ej[i].h, x, y, w, h)) return 1;
    }
    return 0;
}
int army_burst_shot_collision(Ejercito e, Rafaga r)
{
    int cont = 0;
    for(int i = 0; i < e->ealive; i = i + 1)
    {
        if (burst_shot_collision(r, e->ej[i].x, e->ej[i].y, e->ej[i].w, e->ej[i].h))
        {
            e->ealive = e->ealive - 1;
            e->ej[i] = e->ej[e->ealive - 1];
            cont = cont + 1;
        }
    }
    return cont;
}
