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
}
