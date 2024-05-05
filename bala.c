#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "colisiones.h"
#include "bala.h"


struct BalaRep
{
    double cx;
    double cy;
    double dx;
    double dy;
    double v;
    double rad;
};

Bala create_bullet(double x, double y, double dx, double dy, double v)
{
    Bala bullet = malloc(sizeof(struct BalaRep));
    bullet->cx = x;
    bullet->cy = y;
    bullet->dx = dx;
    bullet->dy = dy;
    bullet->v = v;
    bullet->rad = 10;
    return bullet;
}
void free_bullet(Bala b)
{
    free(b);
}
void move_bullet(Bala b)
{
    if(b != NULL)
    {
        b->cx = b->cx + b->dx * b->v;
        b->cy = b->cy + b->dy * b->v;

    }
}
void draw_bullet(Bala b)
{
    color_relleno(255, 0, 0, 255);
    if(b != NULL)
    {
        dibuja_circulo(b->cx, b->cy, b->rad);
    }
}
double get_bullet_x(Bala b)
{
    return b->cx;
}
double get_bullet_y(Bala b)
{
    return b->cy;
}
double get_bullet_rad(Bala b)
{
    return b->rad;
}
int bullet_collision(Bala b, double x, double y, double w, double h)
{
    return solape_circ_rect(b->cx, b->cy, b->rad, x, y, w, h);
}

