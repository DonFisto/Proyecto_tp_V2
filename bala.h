#ifndef __bala_H__
#define __bala_H__

/**
   \file bala.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo bala
*/

/**
    \brief TDA Bala
 */
typedef struct BalaRep * Bala;

/**
  \brief Crea e inicializa una bala con los valores especificados.
  \param cx coordenada x del centro de la bala.
  \param cy coordenada y del centro de la bala.
  \param r radio de la bala.
  \param dx dirección en el eje x de la bala (valores entre 0 y 1).
  \param dy dirección en el eje y de la bala (valores entre 0 y 1).
  \param v velocidad de la bala.
  \return bala con los valores inicializados.
 */
Bala create_bullet(double x, double y, double dx, double dy, double v);

/**
  \brief Libera una bala.
  \param b bala a liberar.
 */
void free_bullet(Bala b);

/**
  \brief Mueve una bala.
  \param b bala a mover.
 */
void move_bullet(Bala b);

/**
  \brief Dibuja una bala.
  \param b bala a dibujar.
 */
void draw_bullet(Bala b);

/**
  \brief Devuelve la coordenada x del centro de una bala.
  \param b bala de la que se devuelve la información.
  \return valor de la coordenada x de la bala.
 */
double get_bullet_x(Bala b);

/**
  \brief Devuelve la coordenada y del centro de una bala.
  \param b bala de la que se devuelve la información.
  \return valor de la coordenada y de la bala.
 */
double get_bullet_y(Bala b);

/**
  \brief Devuelve el radio de una bala.
  \param b bala de la que se devuelve la información.
  \return valor del radio de la bala.
 */
double get_bullet_rad(Bala b);

#endif
