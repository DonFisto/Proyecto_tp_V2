#ifndef __colisiones_H__
#define __colisiones_H__

/**
   \file colisiones.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo colisiones
*/

/**
  \brief Detecta si un punto está contenido en un rectángulo.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h altura del rectángulo.
  \param px coordenada x del punto.
  \param py coordenada y del punto.
  \return 0 si no está dentro.
  \return 1 si está dentro.
 */
int dentro_rectangulo( double x, double y, double w, double h, double px, double py );

/**
  \brief Detecta la intersección de una recta con un rectángulo.
  \param rx coordenada x de la esquina superior izquierda del rectángulo.
  \param ry coordenada y de la esquina superior izquierda del rectángulo.
  \param rw anchura del rectángulo.
  \param rh altura del rectángulo.
  \param x1 coordenada x del punto 1 de la recta.
  \param y1 coordenada y del punto 1 de la recta.
  \param x2 coordenada x del punto 2 de la recta.
  \param y2 coordenada y del punto 2 de la recta.
  \return 0 si no hay intersección.
  \return 1 si hay intersección.
 */
int solape_recta_rect(double rx, double ry, double rw, double rh, double x1, double y1, double x2, double y2);

/**
  \brief Devuelve la distancia entre dos puntos.
  \param x1 coordenada x del punto 1.
  \param y1 coordenada y del punto 1.
  \param x2 coordenada x del punto 2.
  \param y2 coordenada y del punto 2.
  \return distancia entre punto 1 y punto 2.
 */
double distancia_punto_punto( double x1, double y1, double x2, double y2 );

/**
  \brief Detecta la intersección de dos rectángulos.
  \param x1 coordenada x de la esquina superior izquierda del rectángulo 1.
  \param y1 coordenada y de la esquina superior izquierda del rectángulo 1.
  \param w1 anchura del rectángulo 1.
  \param h1 altura del rectángulo 1.
  \param x2 coordenada x de la esquina superior izquierda del rectángulo 2.
  \param y2 coordenada y de la esquina superior izquierda del rectángulo 2.
  \param w2 anchura del rectángulo 2.
  \param h2 altura del rectángulo 2.
  \return 0 si no hay intersección.
  \return 1 si hay intersección.
 */
int solape_rectangulos( double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);

/**
  \brief Detecta la intersección de dos circunferencias.
  \param x1 coordenada x del centro de la circunferencia 1.
  \param y1 coordenada y del centro de la circunferencia 1.
  \param r1 radio de la circunferencia 1.
  \param x2 coordenada x del centro de la circunferencia 2.
  \param y2 coordenada y del centro de la circunferencia 2.
  \param r2 radio de la circunferencia 2.
  \return 0 si no hay intersección.
  \return 1 si hay intersección.
 */
int solape_circunferencias( double x1, double y1, double r1, double x2, double y2, double r2 );

/**
  \brief Detecta la intersección de una circunferencia con un rectángulo.
  \param cx coordenada x del centro de la circunferencia.
  \param cy coordenada y del centro de la circunferencia.
  \param r radio de la circunferencia.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h altura del rectángulo.
  \return 0 si no hay intersección.
  \return 1 si hay intersección.
 */
int solape_circ_rect(double cx, double cy, double r, double x, double y, double w, double h);

#endif
