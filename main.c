#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "jugador.h"
#include "constantes.h"
#include "colisiones.h"
#include "rafaga.h"
#include "enemigos.h"
#include "consumibles.h"
#include "partida.h"

int main( int argc, char *argv[] )
{

    crea_pantalla( "Ejemplo 2", W,H );
    Partida p = start_game();
    Jugador j = create_player();
    Ejercito e = create_army();
    Rafaga rj = create_burst_shot();
    Rafaga re = create_burst_shot();
    Caja c = create_box();

    while ( pantalla_activa())
    {
        if(get_game_active(p))
        {
            rellena_fondo( 255,255,255, 255 );
            game(p, j, e, rj, re, c);
            draw_game(p, j, e, rj, re, c);
            actualiza_pantalla();
            espera( 15 );


        }
        else
        {
            rellena_fondo( 255,255,255, 255 );
            actualiza_pantalla();
            espera(10);
        }
    }
    libera_pantalla ();
    return 0;
}
