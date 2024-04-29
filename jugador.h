#ifndef __jugador_H__
#define __jugador_H__
#include "rafaga.h"
#include "mapa.h"

/**
   \file jugador.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo jugador
*/

/**
    \brief TDA Jugador
 */
typedef struct JugadorRep * Jugador;

/**
  \brief Devuelve la coordenada x de la posición de un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la coordenada x del jugador.
 */
double get_player_pos_x(Jugador j);

/**
  \brief Devuelve la coordenada y de la posición de un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la coordenada y del jugador.
 */
double get_player_pos_y(Jugador j);

/**
  \brief Devuelve la anchura de un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la anchura del jugador.
 */
double get_player_width(Jugador j);

/**
  \brief Devuelve la altura de un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la altura del jugador.
 */
double get_player_height(Jugador j);

/**
  \brief Devuelve la coordenada x de la dirección a la que apunta un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la coordenada x de la dirección a la que apunta el jugador.
 */
double get_player_aimx(Jugador j);

/**
  \brief Devuelve la coordenada y de la dirección a la que apunta un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la coordenada y de la dirección a la que apunta el jugador.
 */
double get_player_aimy(Jugador j);

/**
  \brief Devuelve la munición restante de un jugador.
  \param j jugador del que se devuelve la información.
  \return valor de la munición del jugador.
 */
int get_player_energy(Jugador j);

/**
  \brief Devuelve el número de vidas de un jugador.
  \param j jugador del que se devuelve la información.
  \return número de vidas del jugador.
 */
int get_player_lives(Jugador j);

/**
  \brief Devuelve el tiempo restante de invencibilidad de un jugador.
  \param j jugador del que se devuelve la información.
  \return tiempo restante de invencibilidad del jugador.
 */
int get_player_inv(Jugador j);

/**
  \brief Devuelve el tiempo restante de enfriamiento al disparar de un jugador.
  \param j jugador del que se devuelve la información.
  \return tiempo restante de enfriamiento al disparar del jugador.
 */
int get_player_cooldown(Jugador j);

/**
  \brief Inflinge daño a un jugador.
  \param j jugador al que se inflinge daño.
 */
void dmg(Jugador j);

/**
  \brief Modifica el tiempo de invencibilidad del jugador.
  \param j jugador al que se modifican los parámetros.
  \param t tiempo de invencibilidad.
 */
void set_inv(Jugador j, int t);

/**
  \brief Modifica la munición del jugador.
  \param j jugador al que se modifican los parámetros.
  \param e munición.
 */
void set_energy(Jugador j, int e);

/**
  \brief Activa el disparo triple del jugador.
  \param j jugador al que se modifican los parámetros.
 */
void set_triple_shot(Jugador j);


/**
  \brief Modifica el número de vidas del jugador.
  \param j jugador al que se modifican los parámetros.
  \param l número de vidas.
 */
void set_lives(Jugador j, int l);

/**
  \brief Modifica el color del jugador de forma gradual.
  \param j jugador al que se modifican los parámetros.
 */
void color_change(Jugador j);

/**
  \brief Crea e inicializa un jugador.
  \return jugador con los valores inicializados.
 */
Jugador create_player();

/**
  \brief Libera un jugador.
  \param jugador a liberar.
 */
void free_player(Jugador j);

/**
  \brief Dibuja un jugador.
  \param jugador a dibujar.
 */
void draw_player(Jugador j);

/**
  \brief Mueve un jugador.
  \param j jugador a mover.
  \param r rafaga disparada por los jugadores.
  \param m terreno en el que se desarrolla la partida.
 */
void move_player(Jugador j, Rafaga r, Mapa m);

#endif
