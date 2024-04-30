#ifndef __consumibles_H__
#define __consumibles_H__

/**
   \file consumibles.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo consumibles
*/

/**
    \brief TDA Caja
 */
typedef struct CajaRep * Caja;

/**
  \brief Indica el tipo de consumible que es una caja
  \param c caja de la que se devuelve la información.
  \return 0 si la caja recarga la munición del jugador.
  \return 1 si la caja da un escudo al jugador.
  \return 2 si la caja incrementa las vidas del jugador.
  \return 3 si la caja habilita temporalmente el triple disparo para el jugador.

 */
int get_box_type(Caja c);

/**
  \brief Devuelve la coordenada x de una caja
  \param c caja de la que se devuelve la información.
  \return coordenada x de la caja.
 */
double get_box_x(Caja c);

/**
  \brief Devuelve la coordenada y de una caja
  \param c caja de la que se devuelve la información.
  \return coordenada y de la caja.
 */
double get_box_y(Caja c);


/**
  \brief Crea e inicializa un consumible.
  \return consumible con los valores inicializados.
 */
Caja create_box();

/**
  \brief Libera una caja.
  \param c caja a liberar.
 */
void free_box(Caja c);

/**
  \brief Detecta la colisión de una caja con un rectángulo.
  \param c caja a comprobar.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h altura del rectángulo.
  \return 0 si no hay colisión.
  \return 1 si hay colisión.
 */
int box_collision(Caja c, double x, double y, double w, double h);

/**
  \brief Cambia de posición una caja.
  \param c caja a mover.
  \param cam cámara de la partida.
 */
void move_box(Caja c);

/**
  \brief Dibuja una caja.
  \param c caja a dibujar.
 */
void draw_box(Caja c, Camara cam);

#endif
