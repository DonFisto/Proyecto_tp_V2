#ifndef __enemigos_H__
#define __enemigos_H__

/**
   \file enemigos.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo enemigos
*/

/**
    \brief TDA Ejercito
 */
typedef struct EjercitoRep * Ejercito;

/**
  \brief Devuelve el número de enemigos vivos del ejército
  \param e ejército del que se devuelve la información.
  \return número de enemigos vivos.
 */
int get_army_ealive(Ejercito e);

/**
  \brief Modifica el número de enemigos vivos
  \param e ejército en el que se modifican los parametros.
  \param n valor del parametro que se modifica.
 */
void set_ealive(Ejercito e, int n);

/**
  \brief Crea e inicializa un ejército.
  \return ejército inicializada.
 */
Ejercito create_army();

/**
  \brief Libera un ejercito.
  \param r ráfaga a liberar.
 */
void free_army(Ejercito e);

/**
  \brief Añade un enemigo a un ejército con los parametros indicados.
  \param e ejército al que se añade el enemigo.
  \param x coordenada x de la esquina superior izquierda del enemigo.
  \param y coordenada y de la esquina superior izquierda del enemigo.
  \param type tipo de enemigo.
 */
void insert_enemy(Ejercito e, double x, double y, int type);

/**
  \brief Mueve el ejército.
  \param e ejército a mover.
  \param jx coordenada x de la esquina superior izquierda del jugador.
  \param jy coordenada y de la esquina superior izquierda del jugador.
  \param jinv parámetro de invencibilidad del jugador.
  \param r rafaga disparada por los enemigos.
  \param m terreno en el que se desarrolla la partida.
  \param cam cámara de la partida.
 */
void move_army(Ejercito e, double jx, double jy, int jinv, Rafaga r, Mapa m, Camara cam);

/**
  \brief Dibuja un ejército.
  \param e ejército a dibujar.
  \param cam cámara de la partida.
 */
void draw_army(Ejercito e, Camara cam);

/**
  \brief Detecta la colisión de un ejército con un rectángulo.
  \param e ejercito a comprobar.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h altura del rectángulo.
  \return 0 si no hay colisión.
  \return 1 si hay colisión.
 */
int object_army_collision(Ejercito e, double x, double y, double w, double h);

/**
  \brief Detecta el número de colisiones de un ejército con una ráfaga.
  \param e ejército a comprobar.
  \param r rafaga a comprobar.
  \return número de colisiones.
 */
int army_burst_shot_collision(Ejercito e, Rafaga r);

#endif
