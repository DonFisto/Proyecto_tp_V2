#ifndef __colisiones_H__
#define __colisiones_H__

typedef struct BalaRep * Bala;

int dentro_rectangulo( double x, double y, double w, double h, double px, double py );

double distancia_punto_punto( double x1, double y1, double x2, double y2 );

int solape_rectangulos( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

int solape_circunferencias( double x1, double y1, double r1, double x2, double y2, double r2 );

int solape_circ_rect(double cx, double cy, double r, double x, double y, double w, double h);

Bala create_bullet(double x, double y, double dx, double dy, double v);

void free_bullet(Bala b);

void move_bullet(Bala b);

void draw_bullet(Bala b);

double get_bullet_x(Bala b);

double get_bullet_y(Bala b);

double get_bullet_rad(Bala b);

#endif
