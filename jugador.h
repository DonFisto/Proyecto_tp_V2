#ifndef __jugador_H__
#define __jugador_H__

typedef struct JugadorRep * Jugador;

void mover_jugador_2(Jugador j, NodoBalaPtr header);

void dibujar_jugador(Jugador j, int * r1, int * g1, int  * b1, int opp);

Jugador crea_jugador();

int get_lives(Jugador j);

int get_pts(Jugador j);

double get_player_pos_x(Jugador j);

double get_player_pos_y(Jugador j);

double get_player_width(Jugador j);

double get_player_height(Jugador j);

struct Rectangulo get_player_rect(Jugador j);

double get_player_aimx(Jugador j);

double get_player_aimy(Jugador j);

double get_player_inv(Jugador j);

double get_cooldown(Jugador j);

double get_energy(Jugador j);

void incrementa_puntuacion(Jugador j);

void dmg(Jugador j);

void set_inv(Jugador j, int t);

void set_energy(Jugador j, int e);

void set_lives(Jugador j, int l);

void set_pts(Jugador j, int p);

#endif
