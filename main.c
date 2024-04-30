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
#include "mapa.h"
#include "camara.h"

int main( int argc, char *argv[] )
{

    crea_pantalla( "Ejemplo 2", CAMERA_W, CAMERA_H);
    printf("* * * * * INICIO JUEGO * * * * *\n\n\n\n\n");
    Mapa m = create_map();
    reset_map(m);
    generate_map(m, 200);
    Partida p = start_game();
    Jugador j = create_player();
    Ejercito e = create_army();
    Rafaga rj = create_burst_shot();
    Rafaga re = create_burst_shot();
    Caja c = create_box();
    Camara cam = create_camera(0, 0);
    end_game(p);
    int spam_check = 1;

    while ( pantalla_activa())
    {
        if(get_game_active(p))
        {
            if(!get_game_pause(p))
            {
            rellena_fondo( 255,255,255, 255 );
            game(p, j, e, rj, re, c, m, cam);
            draw_game(p, j, e, rj, re, c, m, cam);
            }
            else
            {
                if(get_game_pause(p))
                {
                draw_game(p, j, e, rj, re, c, m, cam);
                int outcome = pause_menu(p);
                   if(outcome == 1)
                   {
                        unpause(p);
                        spam_check = 1;
                   }
                   if(outcome == 2)
                   {
                       update_records(p);
                       end_game(p);
                       spam_check = 1;
                   }
                }
            }
            actualiza_pantalla();
            espera(15);


        }
        else if(spam_check)
        {
            if (!menu(p))
            {
                spam_check = 0;
            }
            espera(10);
        }
        else
        {

            rellena_fondo( 255,255,255, 255 );
            draw_minimap(m, 0, 0, 4);
            int result = menu(p);
            if(result == 1)
            {
                p = start_game();
                j = create_player();
                e = create_army();
                rj = create_burst_shot();
                re = create_burst_shot();
                c = create_box();
            }
            else if(result == 3)
            {
                save_map(m);
                free_player(j);
                free_army(e);
                free_burst_shot(rj);
                free_burst_shot(re);
                free_box(c);
                libera_pantalla();
            }
            else if(result == 4)
            {
                reset_map(m);
                generate_map(m, 200);
                spam_check = 1;
            }
            actualiza_pantalla();
            espera(10);
        }
    }
    libera_pantalla ();
    return 0;
}
