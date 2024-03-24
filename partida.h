#ifndef __partida_H__
#define __partida_H__

typedef struct PartidaRep * Partida;

int get_game_active(Partida p);

int get_game_round(Partida p);

int get_game_time(Partida p);

int get_game_pts(Partida p);

struct Leaderboard read_records();

Partida start_game();

int check_end_game(Jugador j);

void army_generation(Partida p, Ejercito e, Jugador j);

void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re);

void box_behavior(Caja c, Jugador j);

void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c);

#endif
