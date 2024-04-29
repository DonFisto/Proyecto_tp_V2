#ifndef __rafaga_H__
#define __rafaga_H__
#include "colisiones.h"
#include "mapa.h"
/**
   \file rafaga.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo rafaga
*/

/**
    \brief TDA Rafaga
 */
typedef struct NodoBala * Rafaga;

/**
  \brief Crea e inicializa una ráfaga.
  \return ráfaga inicializada.
 */
Rafaga create_burst_shot();

/**
  \brief Libera una ráfaga.
  \param r ráfaga a liberar.
 */
void free_burst_shot(Rafaga r);

/**
  \brief Añade una bala a una ráfaga.
  \param r ráfaga a la que se añade la bala.
  \param b bala a añadir.
 */
void insert_burst(Rafaga r, Bala b);

/**
  \brief Mueve una ráfaga.
  \param r ráfaga a mover.
  \param m terreno sobre el que se mueve la ráfaga.
 */
void move_burst_shot(Rafaga r, Mapa m);

/**
  \brief Dibuja una ráfaga.
  \param r ráfaga a dibujar.
 */
void draw_burst_shot(Rafaga r);

/**
  \brief Devuelve la longitud de una ráfaga.
  \param r ráfaga de la que se devuelve la información.
  \return número de elementos de la ráfaga.
 */
int burst_shot_lenght(Rafaga r);

/**
  \brief Detecta la colisión de una ráfaga con un rectángulo.
  \param r ráfaga a comprobar.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h altura del rectángulo.
  \return 0 si no hay colisión.
  \return 1 si hay colisión.
 */
int burst_shot_collision(Rafaga r, double x, double y, double w, double h);

#endif
