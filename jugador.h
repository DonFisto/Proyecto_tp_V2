#ifndef __jugador_H__
#define __jugador_H__
#include "rafaga.h"
typedef struct JugadorRep * Jugador;

double get_player_pos_x(Jugador j);

double get_player_pos_y(Jugador j);

double get_player_width(Jugador j);

double get_player_height(Jugador j);

double get_player_aimx(Jugador j);

double get_player_aimy(Jugador j);

int get_player_energy(Jugador j);

int get_player_lives(Jugador j);

int get_player_pts(Jugador j);

int get_player_inv(Jugador j);

int get_player_cooldown(Jugador j);

void incr_pts(Jugador , int p);

void dmg(Jugador j);

void set_inv(Jugador j, int t);

void set_energy(Jugador j, int e);

void set_lives(Jugador j, int l);

void set_pts(Jugador j, int p);

void color_change(Jugador j);

Jugador crea_jugador();

void dibujar_jugador(Jugador j);

void mover_jugador_2(Jugador j, Rafaga r);

#endif
