#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "constantes.h"
#include "colisiones.h"
#include "consumibles.h"
#include "mapa.h"
#include "camara.h"

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
double get_box_x(Caja c)
{
    return c->x;
}
double get_box_y(Caja c)
{
    return c->y;
}

Caja create_box(Mapa m)
{
    Caja c = malloc(sizeof(struct CajaRep));
    double x = rand()%(W-40);
    double y = rand()%(H-40);
    while(map_collision(m, c->x, c->y, c->w, c->h))
    {
        x = rand()%(W-40);
        y = rand()%(H-40);
    }
    c->x = x;
    c->y = y;
    c->w = 40;
    c->h = 40;
    c->type = rand()%6;
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
void move_box(Caja c, Mapa m)
{
    double x = rand()%(W-40);
    double y = rand()%(H-40);
    while(map_collision(m, c->x, c->y, c->w, c->h))
    {
        x = rand()%(W-40);
        y = rand()%(H-40);
    }
    c->x = x;
    c->y = y;
    c->type = rand()%4;
}
void draw_box(Caja c, Camara cam)
{
    double offset_x = get_cam_x(cam);
    double offset_y = get_cam_y(cam);
    color_relleno(0,255,0,255);
    dibuja_rectangulo(c->x - offset_x, c->y - offset_y, c->w, c->h);
    if(c->type >= 0 && c->type <=2)
    {
        color_relleno(162, 103, 18, 255);
        dibuja_circulo(c->x + c->w/3*2 - offset_x,c->y + c->h/2 - 0.0005 - offset_y, 6.1);
        color_relleno(50, 50, 50, 255);
        dibuja_rectangulo(c->x + c->w/4 - offset_x, c->y + c->h/3 - offset_y, c->w/3 + c->w/12, c->h/3);
    }
    else if(c->type == 3)
    {
        color_relleno(20, 209, 218, 255);
        dibuja_circulo(c->x + c->w/2 - offset_x, c->y + c->h/2 - offset_y, c->w/4);
    }
    else if(c->type == 4)
    {
        color_relleno(255, 0, 0, 255);
        color_trazo(0, 0, 0, 0);
        dibuja_rectangulo(c->x + c->w/3 - offset_x, c->y + c->h/4 - offset_y, c->w/3, c->h/2);
        dibuja_rectangulo(c->x + c->w/4 - offset_x, c->y + c->h/3 - offset_y, c->w/2, c->h/3);
        color_trazo(0, 0, 0, 255);
    }
    else if(c->type == 5)
    {
        color_relleno(115, 0, 255, 255);
        dibuja_circulo(c->x + c->w/4 - offset_x, c->y + c->h*2/3 - offset_y, c->y/6);
        dibuja_circulo(c->x + c->w*3/4 - offset_x, c->y + c->h*2/3 - offset_y, c->y/6);
        dibuja_circulo(c->x + c->w/2 - offset_x, c->y + c->h/3 - offset_y, c->y/6);
    }


}
