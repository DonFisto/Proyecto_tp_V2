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
void move_burst_shot(Rafaga r)
{
    Rafaga aux = r;
    while(aux->sig != NULL)
    {
        move_bullet(aux->sig->b);
        if(get_bullet_x(aux->sig->b) >= W+get_bullet_rad(aux->sig->b) || get_bullet_x(aux->sig->b) <=-get_bullet_rad(aux->sig->b) || get_bullet_y(aux->sig->b) >= H + get_bullet_rad(aux->sig->b) || get_bullet_y(aux->sig->b) <= -get_bullet_rad(aux->sig->b))
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
void draw_burst_shot(Rafaga r)
{
    color_relleno(255, 0, 0, 255);
    Rafaga aux = r;
    while(aux->sig != NULL)
    {
        aux = aux->sig;
        dibuja_circulo(get_bullet_x(aux->b), get_bullet_y(aux->b), get_bullet_rad(aux->b));
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
