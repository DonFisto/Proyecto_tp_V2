#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Pantalla.h"
#include "jugador.h"
#include "constantes.h"
#include "colisiones.h"
#include "rafaga.h"
#include "enemigos.h"

int main( int argc, char *argv[] )
{

    crea_pantalla( "Ejemplo 2", W,H );
    int jugando = 1;


    while ( pantalla_activa())
    {
        if(jugando)
        {
            rellena_fondo( 255,255,255, 255 );
            actualiza_pantalla();
            espera( 15 );


        }
        else
        {

            espera(10);
        }
    }
    libera_pantalla ();
    return 0;
}
