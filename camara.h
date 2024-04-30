#ifndef __camara_H__
#define __camara_H__

typedef struct CamaraRep * Camara;

double get_cam_x(Camara cam);

double get_cam_y(Camara cam);

Camara create_camera(double x, double y);

void camera_follow(Camara cam, double x, double y);

#endif
