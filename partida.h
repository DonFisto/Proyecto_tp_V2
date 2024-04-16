#ifndef __partida_H__
#define __partida_H__

/**
   \file partida.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo partida
*/

/**
    \brief TDA Partida
 */
typedef struct PartidaRep * Partida;

/**
  \brief Indica si el juego está en curso en una partida
  \param p partida de la que se devuelve la información.
 */
int get_game_active(Partida p);

int get_game_pause(Partida p);

/**
  \brief Indica en qué ronda se encuentra la partida
  \param p partida de la que se devuelve la información.
 */
int get_game_round(Partida p);

/**
  \brief Indica el tiempo restante hasta que empiece una nueva ronda
  \param p partida de la que se devuelve la información.
 */
int get_game_time(Partida p);

/**
  \brief Indica la puntuación conseguida
  \param p partida de la que se devuelve la información.
 */
int get_game_pts(Partida p);

/**
  \brief Incrementa la puntuación de una cantidad n
  \param p partida de la que se devuelve la información.
  \param n cantidad en la que se incrementa la puntuación
 */
void add_game_pts(Partida p, int n);

void unpause(Partida p);

void end_game(Partida p);

/**
  \brief Lee la información del fichero record.txt, que almacena las mejores puntuaciones conseguidas
  \return la tabla de records leida
 */
struct Leaderboard read_records();

void update_records(Partida p);

/**
  \brief Crea e inicializa una partida
  \return partida con los valores inicializados
 */
Partida start_game();

/**
  \brief Indica si el juego está en curso en una partida
  \param p partida de la que se devuelve la información.
  \param j jugador principal de la partida
  \return 1 si la partida ha terminado
  \return 0 si la partida continua
 */
int check_end_game(Partida p, Jugador j);

/**
  \brief Regula la generación de enemigos
  \param p partida de la que se devuelve la información.
  \param e conjunto de enemigos de la partida
  \param j jugador principal de la partida
 */
void army_generation(Partida p, Ejercito e, Jugador j);

void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re);

void box_behavior(Partida p, Caja c, Jugador j);

void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c);

void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c);

int button_click(double x, double y, double w, double h);

int menu(Partida p);

int pause_menu(Partida p);


#endif
