#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "constantes.h"
#include "colisiones.h"


int dentro_rectangulo(double x, double y, double w, double h, double px, double py)
{
    if (px >= x && px < x + w && py >= y && py < y + h)
    {
        return 1;
    }
    return 0;

}

int solape_recta_rect(double rx, double ry, double rw, double rh, double x1, double y1, double x2, double y2)
{
    if(dentro_rectangulo (rx, ry, rw, rh, x1, y1) || dentro_rectangulo (rx, ry, rw, rh, x2, y2))return 1;
    if(((x1 < rx) && (x2 > rx + rw)) || ((x2 < rx) && (x1 > rx + rw)))
    {
        if (y1 > ry && y1 < ry + rh && y2 > ry && y2 < ry + rh)return 1;
        double x3 = rx;
        double y3 = ry;
        double x4 = rx + rw;
        double y4 = ry + rh;
        double x;
        double y;
        double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
        y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;
        if (dentro_rectangulo(rx, ry, rw, rh, x, y))return 1;
        x3 = rx;
        y3 = y3 + rh;
        x4 = rx + rw;
        y3 = ry;
        denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
        y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;
        if (dentro_rectangulo(rx, ry, rw, rh, x, y))return 1;
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
