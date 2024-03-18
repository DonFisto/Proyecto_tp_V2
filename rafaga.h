#ifndef __rafaga_H__
#define __rafaga_H__
#include"colisiones.h"
typedef struct NodoBala * Rafaga;

Rafaga create_burst_shot();

void free_burst_shot(Rafaga r);

void insert_burst(Rafaga r, Bala b);

void move_burst_shot(Rafaga r);

void draw_burst_shot(Rafaga r);

int burst_shot_lenght(Rafaga r);

int burst_shot_collision(Rafaga r, double x, double y, double w, double h);

#endif
