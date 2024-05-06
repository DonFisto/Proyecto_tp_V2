#ifndef __partida_H__
#define __partida_H__
#include "camara.h"
#include "rafaga.h"
#include "mapa.h"
#include "jugador.h"
#include "enemigos.h"
#include "consumibles.h"
/**
\mainpage Proyecto

Este proyecto consiste en el desarrollo de un videojuego empleando las metodologías y tecnicas estudiadas en la asignatura.
El proyecto está programado usando el lenguaje C, desarrollado en el entorno Code::Blocks y hace uso de la biblioteca de funciones gráficas SDL.

Proyecto realizado por Daniel Martínez - Cabeza de Vaca Guillén curso 2023/2024 Tecnología de la programación


*/
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
  \return 1 si el juego está activo.
  \return 0 si el juego no está activo.

 */
int get_game_active(Partida p);

/**
  \brief Devuelve el estado de pausa de la partida.
  \param p partida de la que se devuelve la información.
  \return 1 si el juego está pausado.
  \return 0 si el juego no está pausado.
*/
int get_game_pause(Partida p);

/**
  \brief Indica en qué ronda se encuentra la partida.
  \param p partida de la que se devuelve la información.
  \return numero de la ronda actual.
 */
int get_game_round(Partida p);

/**
  \brief Indica el tiempo restante hasta que empiece una nueva ronda.
  \param p partida de la que se devuelve la información.
  \return tiempo restante en la ronda actual.
 */
int get_game_time(Partida p);

/**
  \brief Indica la puntuación conseguida.
  \param p partida de la que se devuelve la información.
  \return puntuación conseguida.
 */
int get_game_pts(Partida p);

/**
  \brief Incrementa la puntuación de una cantidad n.
  \param p partida en la que se realizan los cambios.
  \param n cantidad en la que se incrementa la puntuación
 */
void add_game_pts(Partida p, int n);

/**
  \brief Termina el estado de pausa de la partida.
  \param p partida en la que se realizan los cambios.
 */
void unpause(Partida p);

/**
  \brief Termina la partida actual.
  \param p partida en la que se realizan los cambios.
 */
void end_game(Partida p);

/**
  \brief Lee la información del fichero record.txt, que almacena las mejores puntuaciones conseguidas.
  \return la tabla de records leída.
 */
struct Leaderboard read_records();

/**
  \brief Compara las mejores puntuaciones con la puntuación actual y actualiza la tabla de puntuaciones acordemente.
  \param p partida en la que se realizan los cambios.
 */
void update_records(Partida p);

/**
  \brief Crea e inicializa una partida.
  \return partida con los valores inicializados.
 */
Partida start_game();

/**
  \brief Libera una partida.
  \param partida a liberar.
 */
void free_game(Partida p);

/**
  \brief Indica si el juego está en curso en una partida
  \param p partida de la que se devuelve la información.
  \param j jugador principal de la partida
  \return 1 si la partida ha terminado
  \return 0 si la partida continua
 */
int check_end_game(Partida p, Jugador j);

/**
  \brief Regula la generación de enemigos.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param m terreno en el que se desarrolla la partida.
  \param cam cámara de la partida.
 */
void army_generation(Partida p, Ejercito e, Jugador j, Mapa m);

/**
  \brief Regula el comportamiento de los enemigos.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
  \param m terreno en el que se desarrolla la partida.
 */
void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re, Mapa m);

/**
  \brief Regula el comportamiento del tesoro consumible.
  \param p partida actual.
  \param c tesoro consumible por el jugador.
  \param j jugador principal de la partida.
  \param m terreno en el que se desarrolla la partida.
 */
void box_behavior(Partida p, Caja c, Jugador j, Mapa m);

/**
  \brief Dibuja todos los elementos visibles del juego y el HUD.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
  \param m terreno en el que se desarrolla la partida.
  \param cam cámara de la partida.
 */
void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m, Camara cam);

/**
  \brief Regula el transcurso de la partida y coordina sus elementos.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
  \param m terreno en el que se desarrolla la partida.
  \param cam cámara de la partida.
 */
void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m, Camara cam);

/**
  \brief Detecta cuando se hace click sobre un botón.
  \param x coordenada x de la esquina superior izquierda del botón.
  \param y coordenada y de la esquina superior izquierda del botón.
  \param w anchura del botón.
  \param h altura del botón.
 */
int button_click(double x, double y, double w, double h);

/**
  \brief Gestiona el menu de inicio.
  \param p partida activa.
  \return 0 no se han realizado acciones en el menu.
  \return 1 si se ha pulsado el botón que inicia el juego.
  \return 2 si se ha pulsado el botón que lleva al tutorial.
  \return 3 si se ha pulsado el botón de salida.
  \return 4 si se ha pulsado el botón cambio de mapa.
 */
int menu(Partida p);

/**
  \brief Gestiona el menu de pausa.
  \param p partida activa.
  \return 0 no se han realizado acciones en el menu.
  \return 1 si se ha pulsado el botón que continua el juego.
  \return 2 si se ha pulsado el botón que lleva al menu de inicio.
 */
int pause_menu(Partida p);

void ayuda(Partida p, Jugador j, Ejercito e, Rafaga r, Camara cam);


#endif
