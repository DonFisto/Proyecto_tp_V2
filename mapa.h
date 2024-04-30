#ifndef __mapa_H__
#define __mapa_H__

typedef struct MapaRep * Mapa;

Mapa create_map();

void reset_map(Mapa m);

void save_map(Mapa m);

void read_map(Mapa m);

void print_map(Mapa m);

void draw_map(Mapa m, Camara cam);

void draw_minimap(Mapa m, int x, int y, int scale);

void generate_map(Mapa m, int n);

int map_collision(Mapa m, Camara cam, double x, double y, double w, double h);

int line_map_collision(Mapa m, double x1, double y1, double x2, double y2);

#endif
