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

struct CamaraRep
{
    double x;
    double y;
};
double get_cam_x(Camara cam)
{
    return cam->x;
}
double get_cam_y(Camara cam)
{
    return cam->y;
}
Camara create_camera(double x, double y)
{
    Camara nuevo = malloc(sizeof(struct CamaraRep));
    double cx = x - CAMERA_W/2;
    double cy = y - CAMERA_H/2;
    if (cx < 0) cx = 0;
    if (cy < 0) cy = 0;
    if (cx > W - CAMERA_W) cx = W - CAMERA_W;
    if (cy > H - CAMERA_H) cx = H - CAMERA_H;
    nuevo->x = cx;
    nuevo->y = cy;
    return nuevo;
}

void camera_follow(Camara cam, double x, double y)
{
    double mx = (x - CAMERA_W/2 - cam->x);
    double my = (y - CAMERA_H/2 - cam->y);
    if(abs(mx) > CAMERA_TRACKING_SPEED)
    {
        cam->x = cam->x + mx/100 * CAMERA_TRACKING_SPEED;
    }
    if(abs(my) > CAMERA_TRACKING_SPEED)
    {
        cam->y = cam->y + my/100 * CAMERA_TRACKING_SPEED;
    }
    if(cam->x < 0)cam->x = 0;
    if(cam->y < 0)cam->y = 0;
    if(cam->x > W - CAMERA_W)cam->x = W - CAMERA_W;
    if(cam->y > H - CAMERA_H)cam->y = H - CAMERA_H;
    //cam->x = x - CAMERA_W/2;
    //cam->y = y - CAMERA_H/2;

}
