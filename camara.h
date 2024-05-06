#ifndef __camara_H__
#define __camara_H__

/**
   \file camara.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo cámara
*/

/**
    \brief TDA Mapa
 */
typedef struct CamaraRep * Camara;

/**
  \brief Devuelve la coordenada x de la cámara.
  \param cam cámara de la que se devuelve la información.
  \return valor de la coordenada x de la cámara.
 */
double get_cam_x(Camara cam);

/**
  \brief Devuelve la coordenada y de la cámara.
  \param cam cámara de la que se devuelve la información.
  \return valor de la coordenada y de la cámara.
 */
double get_cam_y(Camara cam);

/**
  \brief Crea e inicializa una cámara con los valores especificados.
  \param x coordenada x de la cámara.
  \param y coordenada y de la cámara.
  \return cámara con los valores inicializados.
 */
Camara create_camera(double x, double y);

/**
  \brief Libera una cámara.
  \param cam cámara liberada.
 */
void free_cam(Camara cam);

/**
  \brief Mueve la cámara en relación a un punto.
  \param x coordenada x del punto.
  \param y coordenada y del punto.
 */
void camera_follow(Camara cam, double x, double y);

#endif
