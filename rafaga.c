#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "jugador.h"
#include "constantes.h"
#include "colisiones.h"
#include "rafaga.h"

struct NodoBala
{
    Bala b;
    struct NodoBala * sig;
};

Rafaga create_burst_shot()
{
    
}
void insert_burst(Rafaga r, Bala b)
{

}

void free_burst_shot(Rafaga r)
{

}
void move_burst_shot(Rafaga r)
{

}
void draw_burst_shot(Rafaga r)
{

}
int burst_shot_lenght(Rafaga r)
{

}
int burst_shot_collision(Rafaga r, double x, double y, double, w, double h)
{

}
