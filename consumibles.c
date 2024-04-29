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

struct CajaRep
{
    double x;
    double y;
    double w;
    double h;
    int type;
};

int get_box_type(Caja c)
{
    return c->type;
}

Caja create_box()
{
    Caja c = malloc(sizeof(struct CajaRep));
    c->x = rand()%(W-40);
    c->y = rand()%(H-40);
    c->w = 40;
    c->h = 40;
    c->type = rand()%3;
    return c;
}
void free_box(Caja c)
{
    free(c);
}
int box_collision(Caja c, double x, double y, double w, double h)
{
    return solape_rectangulos(c->x, c->y, c->w, c->h, x, y, w, h);
}
void move_box(Caja c)
{
    c->x = rand()%(W-40);
    c->y = rand()%(H-40);
    c->type = rand()%4;
}
void draw_box(Caja c)
{
    color_relleno(0,255,0,255);
    dibuja_rectangulo(c->x, c->y, c->w, c->h);
    if(c->type == 0)
    {
        color_relleno(162, 103, 18, 255);
        dibuja_circulo(c->x + c->w/3*2,c->y + c->h/2 - 0.0005, 6.1);
        color_relleno(50, 50, 50, 255);
        dibuja_rectangulo(c->x + c->w/4, c->y + c->h/3, c->w/3 + c->w/12, c->h/3);
    }
    else if(c->type == 1)
    {
        color_relleno(20, 209, 218, 255);
        dibuja_circulo(c->x + c->w/2, c->y + c->h/2, c->w/4);
    }
    else if(c->type == 2)
    {
        color_relleno(255, 0, 0, 255);
        dibuja_rectangulo(c->x + c->w/3, c->y + c->h/3, c->w/3, c->h/3);
    }
    else if(c->type == 3)
    {
        color_relleno(115, 0, 255, 255);
        dibuja_rectangulo(c->x + c->w/3, c->y + c->h/3, c->w/3, c->h/3);
    }


}
