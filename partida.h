#ifndef __partida_H__
#define __partida_H__
/**
\mainpage Proyecto

La biblioteca pantalla es un wrapper de la biblioteca SDL 2.0.
Permite la escritura de programas gráficos interactivos sin necesidad de conocer muchos de los
detalles de la visualización gráfica y de la programación dirigida por eventos típicos de SDL.
Evidentemente, utilizando SDL directamente se pueden escribir programas más potentes y eficientes.

   El esquema básico para hacer una animación interactiva con esta biblioteca es el siguiente:<br/>
 <br/>mientras ( pantalla_activa( ) ) {
 <br/> &nbsp;&nbsp;&nbsp; Detectar los eventos que se hayan producido usando las funciones tecla_pulsada() o boton_raton_pulsado().
 <br/> &nbsp;&nbsp;&nbsp; Modificar el estado de la animación en función de los evantos detectados.
 <br/> &nbsp;&nbsp;&nbsp; Componer el siguiente frame de la animación usando las funciones de dibujo: dibuja_rectangulo(), dibuja_circulo(), dibuja_imagen(), etc.
 <br/> &nbsp;&nbsp;&nbsp; Mostrar el frame que se acaba de componer usando la función actualiza_pantalla().
 <br/> &nbsp;&nbsp;&nbsp; Esperar unos milisegundos utilizando la función espera() (40 para conseguir unos 25fps) para que de tiempo al ojo a ver lo que ha pasado.
 <br/>}

Copyright © 2022 by Juan A. Sánchez Laguna

Permission to use, copy, modify, and distribute this software and its documentation under the terms of the GNU General Public License is hereby granted. No representations are made about
the suitability of this software for any purpose. It is provided "as is" without express or implied warranty. See the <a href="https://www.gnu.org/licenses/gpl.txt">GNU General Public License</a> for more details.


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
 */
void army_generation(Partida p, Ejercito e, Jugador j);

/**
  \brief Regula el comportamiento de los enemigos.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
 */
void army_behavior(Partida p, Ejercito e, Jugador j, Rafaga rj, Rafaga re, Mapa m);

/**
  \brief Regula el comportamiento del tesoro consumible.
  \param p partida actual.
  \param c tesoro consumible por el jugador.
  \param j jugador principal de la partida.
 */
void box_behavior(Partida p, Caja c, Jugador j);

/**
  \brief Dibuja todos los elementos visibles del juego y el HUD.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
 */
void draw_game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m);

/**
  \brief Regula el transcurso de la partida y coordina sus elementos.
  \param p partida actual.
  \param e conjunto de enemigos de la partida.
  \param j jugador principal de la partida.
  \param rj rafaga disparada por el jugador.
  \param re rafaga disparada por los enemigos.
 */
void game(Partida p, Jugador j, Ejercito e, Rafaga rj, Rafaga re, Caja c, Mapa m);

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


#endif
