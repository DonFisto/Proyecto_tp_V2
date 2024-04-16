#ifndef __partida_H__
#define __partida_H__

typedef struct PartidaRep * Partida;

int get_game_active(Partida p);

int get_game_round(Partida p);

int get_game_time(Partida p);

int get_game_pts(Partida p);

void add_game_pts(Partida p, int n);

struct Leaderboard read_records();

Partida start_game();

int check_end_game(Partida p, Jugador j);

void army_generation(Partida p, Ejercito e, Jugador j);

void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re);

void box_behavior(Partida p, Caja c, Jugador j);

void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c);

void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c);

int button_click(double x, double y, double w, double h);

int menu(Partida p);


#endif
