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


struct BalaRep
{
    double cx;
    double cy;
    double dx;
    double dy;
    double v;
    double rad;
};
int dentro_rectangulo(double x, double y, double w, double h, double px, double py)
{
    if (px >= x && px < x + w && py >= y && py < y + h)
    {
        return 1;
    }
    return 0;

}
double distancia_punto_punto( double x1, double y1, double x2, double y2 )
{
    double d = 0;
    d =  (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
    d = sqrt(d);
    return d;

}
int solape_rectangulos( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
    if (x2-x1 > w1 || x1-x2 > w2 || y2-y1 > h1 || y1-y2 > h2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int solape_circunferencias( double x1, double y1, double r1, double x2, double y2, double r2 )
{
    if (distancia_punto_punto( x1, y1, x2, y2 ) < r1 + r2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int solape_circ_rect(double cx, double cy, double r, double x, double y, double w, double h)
{

    double px = cx;
    if ( px < x ) px = x;
    if ( px > x + w ) px = x + w;
    double py = cy;
    if ( py < y ) py = y;
    if ( py > y + h ) py = y + h;
    double distancia = distancia_punto_punto(cx,cy,px,py);
    if ( distancia < r )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
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
