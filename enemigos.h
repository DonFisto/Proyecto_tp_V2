#ifndef __enemigos_H__
#define __enemigos_H__

typedef struct EjercitoRep * Ejercito;

int get_army_ealive(Ejercito e);

void set_ealive(Ejercito e, int n);

Ejercito create_army();

void free_army(Ejercito e);

void insert_enemy(Ejercito e, double x, double y, int type);

void move_army(Ejercito e, double jx, double jy, int jinv, Rafaga r);

void draw_army(Ejercito e);

int object_army_collision(Ejercito e, double x, double y, double w, double h);

int army_burst_shot_collision(Ejercito e, Rafaga r);

#endif
