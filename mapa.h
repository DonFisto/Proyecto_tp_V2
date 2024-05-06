#ifndef __mapa_H__
#define __mapa_H__
#include "camara.h"

/**
   \file mapa.h
   \brief  Fichero de cabecera para poder usar las funciones del módulo mapa
*/

/**
    \brief TDA Mapa
 */
typedef struct MapaRep * Mapa;

/**
  \brief Crea un mapa vacio.
  \return mapa creado.
 */
Mapa create_map();

/**
  \brief Libera un mapa.
  \param m mapa liberado.
 */
void free_map(Mapa m);

/**
  \brief Vacia un mapa.
  \param m mapa vaciado.
 */
void reset_map(Mapa m);

/**
  \brief Guarda un mapa en un archivo de texto.
  \param m mapa guardado.
 */
void save_map(Mapa m);

/**
  \brief Importa un mapa de un archivo de texto.
  \param m mapa donde se almacena el mapa leído.
 */
void read_map(Mapa m);

/**
  \brief Imprime un mapa en la consola de comandos.
  \param m mapa a imprimir.
 */
void print_map(Mapa m);

/**
  \brief Dibuja un mapa.
  \param m mapa a dibujar.
  \param cam cámara de la partida.
 */
void draw_map(Mapa m, Camara cam);

/**
  \brief Dibuja un mapa en una posición y escala determinados.
  \param m mapa a dibujar.
  \param x coordenada x de la esquina superior izquierda del mapa.
  \param y coordenada y de la esquina superior izquierda del mapa.
  \param scale escala a la que se dibuja el mapa.
 */
void draw_minimap(Mapa m, int x, int y, int scale);

/**
  \brief Genera un mapa de forma aleatoria.
  \param m mapa a modificar.
  \param cam cámara de la partida.
 */
void generate_map(Mapa m, int n);

/**
  \brief Comprueba la colisión de un mapa con un rectángulo.
  \param m mapa a comprobar.
  \param x coordenada x de la esquina superior izquierda del rectángulo.
  \param y coordenada y de la esquina superior izquierda del rectángulo.
  \param w anchura del rectángulo.
  \param h anchura del rectángulo.
  \return 0 si no hay solape.
  \return 1 si hay solape.
 */
int map_collision(Mapa m, double x, double y, double w, double h);

/**
  \brief Comprueba la intersección de un mapa con una recta.
  \param m mapa a comprobar.
  \param x1 coordenada x del punto 1 de la recta.
  \param y1 coordenada y del punto 1 de la recta.
  \param x2 coordenada x del punto 2 de la recta.
  \param y2 coordenada y del punto 2 de la recta.
  \return 0 si no hay solape.
  \return 1 si hay solape.
 */
int line_map_collision(Mapa m, double x1, double y1, double x2, double y2);

#endif
