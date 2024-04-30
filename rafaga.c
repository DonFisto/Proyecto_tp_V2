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

struct NodoBala
{
    Bala b;
    struct NodoBala * sig;
};

Rafaga create_burst_shot()
{
    Rafaga r = malloc(sizeof(struct NodoBala));
    r->b = NULL;
    r->sig = NULL;
    return r;
}
void free_burst_shot(Rafaga r)
{
    while(r->sig != NULL)
    {
        Rafaga borrar = r->sig;
        r->sig = borrar->sig;
        free_bullet(borrar->b);
        free(borrar);
    }
    free(r);
}
void insert_burst(Rafaga r, Bala b)
{
    Rafaga nuevo = malloc(sizeof(struct NodoBala));
    nuevo->b = b;
    nuevo->sig = r->sig;
    r->sig = nuevo;
}
void move_burst_shot(Rafaga r, Mapa m, Camara cam)
{
    Rafaga aux = r;
    double x;
    double y;
    double rad;
    while(aux->sig != NULL)
    {
        move_bullet(aux->sig->b);
        x = get_bullet_x(aux->sig->b);
        y = get_bullet_y(aux->sig->b);
        rad = get_bullet_rad(aux->sig->b);
        if(x >= W+rad || x <=-rad || y >= H + rad || y <= -rad || map_collision(m, cam, x, y, rad*2, rad*2))
        {
            Rafaga borrar = aux->sig;
            aux->sig = borrar->sig;
            free_bullet(borrar->b);
            free(borrar);
        }
        else
        {
            aux = aux->sig;
        }
    }
}
void draw_burst_shot(Rafaga r, Camara cam)
{
    double offset_x = get_cam_x(cam);
    double offset_y = get_cam_y(cam);
    color_relleno(255, 0, 0, 255);
    Rafaga aux = r;
    while(aux->sig != NULL)
    {
        aux = aux->sig;
        dibuja_circulo(get_bullet_x(aux->b) - offset_x, get_bullet_y(aux->b) - offset_y, get_bullet_rad(aux->b));
    }
}
int burst_shot_lenght(Rafaga r)
{
    Rafaga aux = r;
    int contador = 0;
    while(aux->sig != NULL)
    {
        aux = aux->sig;
        contador = contador + 1;
    }
    return contador;
}
int burst_shot_collision(Rafaga r, double x, double y, double w, double h)
{
        Rafaga aux = r;
    while(aux->sig != NULL)
    {
        if(solape_circ_rect(get_bullet_x(aux->sig->b), get_bullet_y(aux->sig->b), get_bullet_rad(aux->sig->b), x, y, w, h))
        {
            Rafaga borrar = aux->sig;
            aux->sig = borrar->sig;
            free_bullet(borrar->b);
            free(borrar);
            return 1;
        }
        else
        {
            aux = aux->sig;
        }
    }
    return 0;
}
