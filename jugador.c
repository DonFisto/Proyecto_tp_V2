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

struct JugadorRep
{
    double x;
    double y;
    double w;
    double h;
    double vx;
    double vy;
    double aimx;
    double aimy;
    double ang;
    int energy;
    int vidas;
    int invincibility;
    int triple_shot;
    int cdown;
    int r;
    int g;
    int b;
    Imagen img;
};
double get_player_pos_x(Jugador j)
{
    return j->x;
}
double get_player_pos_y(Jugador j)
{
    return j->y;
}
double get_player_width(Jugador j)
{
    return j->w;
}
double get_player_height(Jugador j)
{
    return j->h;
}
double get_player_aimx(Jugador j)
{
    return j->aimx;
}
double get_player_aimy(Jugador j)
{
    return j->aimy;
}
int get_player_energy(Jugador j)
{
    return j->energy;
}
int get_player_lives(Jugador j)
{
    return j->vidas;
}
int get_player_inv(Jugador j)
{
    return j->invincibility;
}
int get_player_cooldown(Jugador j)
{
    return j->cdown;
}
void dmg(Jugador j)
{
    j->vidas = j->vidas - 1;
    j->invincibility = 100;
}
void set_inv(Jugador j, int t)
{
    j->invincibility = t;
}
void set_energy(Jugador j, int e)
{
    j->energy = e;
    j->triple_shot = 0;
}
void set_triple_shot(Jugador j)
{
    j->triple_shot = 1;
}
void set_lives(Jugador j, int l)
{
    j->vidas = l;
}
void color_change(Jugador j)
{
    if (j->r>0 && j->b==0)
    {
        j->r = j->r - 1;
        j->g = j->g + 1;
    }
    else if (j->g>0 && j->r==0)
    {
        j->g = j->g - 1;
        j->b = j->b + 1;
    }
    else if (j->b>0 && j->g==0)
    {
        j->b = j->b - 1;
        j->r = j->r + 1;
    }
}

Jugador create_player()
{
    Jugador j = malloc(sizeof (struct JugadorRep));
    j->x = 0;
    j->y = 0;
    j->w = 40;
    j->h = 80;
    j->vx = 0;
    j->vy = 0;
    j->aimx = 0;
    j->aimy = 1;
    j->ang = 0;
    j->energy = 120;
    j->vidas = 5;
    j->invincibility = 100;
    j->triple_shot = 0;
    j->cdown = 10;
    j->r = 255;
    j->g = 0;
    j->b = 0;
    j->img = lee_imagen("turret.bmp", 55);
    return j;
}
void free_player(Jugador j)
{
    free(j);
}
void draw_player(Jugador j)
{
    int opacidad = 255;
    if (j->invincibility)
    {
        opacidad = opacidad/4;
        color_relleno(20, 209, 218, 70);
        dibuja_circulo(j->x + j->w/2, j->y + j->h/2, j->h/3*2);
    }
    if (j->triple_shot)
    {
        color_relleno(255, 0, 0, 70);
        dibuja_rectangulo(j->x - j->w/5, j->y - j->w/5, j->w + j->w*2/5, j->h + j->w*2/5);
    }
    color_change(j);
    color_relleno( j->r, j->g, j->b, opacidad );
    dibuja_rectangulo( j->x,j->y, j->w,j->h );
    color_relleno(6, 150, 150, 255);
    dibuja_rectangulo(j->x, j->y-10, j->energy/120.0 * j->w, 5);
    dibuja_imagen_transformada(j->img,(j->x + j->w/2 + 19*j->aimx - 19),(j->y + j->h/2 + 19*j->aimy - 42),38,84,j->ang*360/(2*PI) + 90, 1 );

}
void apuntar2(Jugador j)
{
    if(j->ang > 2*PI)
    {
        j->ang = j->ang - 2*PI;
    }
    if(j->ang < 0)
    {
        j->ang = j->ang + 2*PI;
    }
    if(tecla_pulsada(SDL_SCANCODE_RIGHT))
    {
        j->ang = j->ang + PI/45;
    }
    if(tecla_pulsada(SDL_SCANCODE_LEFT))
    {
        j->ang = j->ang - PI/45;
    }
    j->aimx = cos(j->ang);
    j->aimy = sin(j->ang);

}
void apuntar3(Jugador j)
{
    double dp = distancia_punto_punto(x_raton(), y_raton(), j->x, j->y);
    j->aimx = (j->x-x_raton())/dp*-1;
    j->aimy = (j->y-y_raton())/dp*-1;

}
void check_bounds (Jugador j)
{
    if(j->x >= W )
    {
        j->x = -j->w + 1;
    }
    if(j->x <= -j->w )
    {
        j->x = W - 1;
    }
    if(j->y <= -j->h )
    {
        j->y = H - 1;
    }
    if(j->y >= H )
    {
        j->y = -j->h + 1;
    }
}
void move_player(Jugador j, Rafaga r, Mapa m)
{

    if(!map_collision( m, j->x + j->vx*2/5, j->y, j->w, j->h))
    {
        j->x = j->x + j->vx*2/5;
    }
    if(!map_collision( m, j->x, j->y + j->vy*2/5, j->w, j->h))
    {
        j->y = j->y + j->vy*2/5;
    }
    /*
    j->x = j->x + j->vx*2/5;
    j->y = j->y + j->vy*2/5;
    */
    check_bounds(j);
    apuntar2(j);

    if(j->vx < 20 && tecla_pulsada(SDL_SCANCODE_D) && !map_collision( m, j->x + (j->vx+5)*2/5, j->y, j->w, j->h))
    {
        j->vx = j->vx + 5;
    }
    if(j->vx > -20 && tecla_pulsada(SDL_SCANCODE_A) && !map_collision( m, j->x + (j->vx-5)*2/5, j->y, j->w, j->h))
    {
        j->vx = j->vx - 5;
    }
    if(j->vy > -20 && tecla_pulsada(SDL_SCANCODE_W) && !map_collision( m, j->x, j->y + (j->vy-5)*2/5, j->w, j->h))
    {
        j->vy = j->vy - 5;
    }
    if(j->vy < 20 && tecla_pulsada(SDL_SCANCODE_S) && !map_collision( m, j->x, j->y + (j->vy+5)*2/5, j->w, j->h))
    {
        j->vy = j->vy + 5;
    }
    else
    {

        if (j->vx > 0)
        {
            j->vx--;
        }
        else if(j->vx < 0)
        {
            j->vx++;
        }
        if (j->vy > 0)
        {
            j->vy--;
        }
        else if(j->vy < 0)
        {
            j->vy++;
        }
    }
    if (j->cdown>0)
    {
        j->cdown--;
    }
    if (tecla_pulsada(SDL_SCANCODE_SPACE) && j->cdown==0 && j->energy>0)
    {
        Bala b = create_bullet(j->x+j->w/2,j->y + j->h/2, j->aimx, j->aimy, 45);
        insert_burst(r, b);
        if(j->triple_shot)
        {
            Bala b1 = create_bullet(j->x+j->w/2,j->y + j->h/2, cos(j->ang + PI/45), sin(j->ang + PI/45), 45);
            insert_burst(r, b1);
            Bala b2 = create_bullet(j->x+j->w/2,j->y + j->h/2, cos(j->ang - PI/45), sin(j->ang - PI/45), 45);
            insert_burst(r, b2);
        }
        j->energy = j->energy - 5;

        j->cdown = 10;
    }
    if (j->triple_shot && j->energy <= 0)
    {
        j->energy = 0;
        j->triple_shot = 0;
    }
    if(j->invincibility > 0)
    {
        j->invincibility = j->invincibility - 1;
    }
    else
    {
        j->invincibility = 0;
    }
}

