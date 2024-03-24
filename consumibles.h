#ifndef __consumibles_H__
#define __consumibles_H__

typedef struct CajaRep * Caja;

int get_box_type(Caja c);

Caja create_box();

void free_box(Caja c);

int box_collision(Caja c, double x, double y, double w, double h);

void move_box(Caja c);

#endif
