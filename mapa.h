#ifndef __mapa_H__
#define __mapa_H__

typedef struct MapaRep * Mapa;

Mapa create_map();

void reset_map(Mapa m);

void save_map(Mapa m);

void read_map(Mapa m);

void print_map(Mapa m);

void draw_map(Mapa m);

void generate_map(Mapa m, int n);

#endif
