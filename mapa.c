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
#include "string.h"
struct MapaRep
{
    int terreno[H/BLOCK_SIZE*2][W/BLOCK_SIZE*2];

};
Mapa create_map()
{
    Mapa nuevo = malloc(sizeof(struct MapaRep));
    return nuevo;
}
void reset_map(Mapa m)
{
    for(int i = 0; i < H/BLOCK_SIZE*2; i = i + 1)
    {
        for(int j = 0; j < W/BLOCK_SIZE*2; j = j + 1)
        {
            m->terreno[i][j] = 0;
        }
    }
}
void save_map(Mapa m)
{
    FILE * fp = NULL;
    fp = fopen("mapa.txt", "w");
    if (fp != NULL)
    {
        for(int i = 0; i < H/BLOCK_SIZE; i = i + 1)
        {
            for(int j = 0; j < W/BLOCK_SIZE; j = j + 1)
            {
                fprintf(fp, "%d", m->terreno[i][j]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}


void read_map(Mapa m)
{
    FILE * fp = NULL;
    fp = fopen("mapa.txt", "r");
    if (fp != NULL)
    {
        for(int i = 0; i < H/BLOCK_SIZE; i = i + 1)
        {
            for(int j = 0; j < W/BLOCK_SIZE; j = j + 1)
            {
                fscanf(fp, "%d", &m->terreno[i][j]);
            }
        }
    }
}
void print_map(Mapa m)
{
    int n = 0;
    for(int i = 0; i < H/BLOCK_SIZE; i = i + 1)
    {
        for(int j = 0; j < W/BLOCK_SIZE; j = j + 1)
        {
            n++;
            printf("%d",m->terreno[i][j]);
        }
        printf("\n");
    }
    printf("%d \n\n", n);
}
void check_free_3x3(Mapa m, int x, int y, int pos[9])
{
    if(y == 0 || x == 0 || m->terreno[y-1][x-1] != 0)pos[0] = 1;
    else pos[0] = 0;
    if(y == 0 || m->terreno[y-1][x] != 0)pos[1] = 1;
    else pos[1] = 0;
    if(y == 0 || x == 99 || m->terreno[y-1][x+1] != 0)pos[2] = 1;
    else pos[2] = 0;
    if(x == 0 || m->terreno[y][x-1] != 0)pos[3] = 1;
    else pos[3] = 0;
    if(m->terreno[y][x] != 0)pos[4] = 1;
    else pos[4] = 0;
    if(x == 99 || m->terreno[y][x+1] != 0)pos[5] = 1;
    else pos[5] = 0;
    if(y == 49 || x == 0 || m->terreno[y+1][x-1] != 0)pos[6] = 1;
    else pos[6] = 0;
    if(y == 49 || m->terreno[y+1][x] != 0)pos[7] = 1;
    else pos[7] = 0;
    if(y == 49 || x == 99 || m->terreno[y+1][x+1] != 0)pos[8] = 1;
    else pos[8] = 0;
}
void generate_map(Mapa m, int n)
{
    int placed = 0;
    int structure_pieces_left;
    int x;
    int y;
    int posiciones[9];
    while (placed < n)
    {
        structure_pieces_left = 100;
        x = rand()%100;
        y = rand()%50;
        check_free_3x3(m, x, y, posiciones);
        if (posiciones[4] == 0)
        {
            m->terreno[y][x] = 1;
            int dir = rand()%4;
            int structure_type = rand()%2;
            while(placed < n && structure_pieces_left > 0)
            {
                check_free_3x3(m, x, y, posiciones);

                if(dir == 0)
                {
                    if(structure_type == 0)
                    {
                        if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                        {
                            y = y - 1;
                        }
                        else
                        {
                            structure_type = 1;
                        }
                    }
                    if(structure_type == 1)
                    {
                        int way = rand()%2;
                        if (way == 0)
                        {
                            if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                            {
                                x = x - 1;
                                dir = 3;
                            }
                            else
                            {
                                way = 1;
                            }
                        }
                        if (way == 1)
                        {
                            if(posiciones[2]==0 && posiciones[5]==0 && posiciones[8]==0)
                            {
                                x = x + 1;
                                dir = 1;
                            }
                            else
                            {
                                if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                                {
                                    x = x - 1;
                                    dir = 3;
                                }
                                else
                                {
                                    if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                                    {
                                        y = y - 1;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }
                else if (dir == 1)
                {
                    if(structure_type == 0)
                    {
                        if(posiciones[2]==0 && posiciones[5]==0 && posiciones[8]==0)
                        {
                            x = x + 1;
                        }
                        else
                        {
                            structure_type = 1;
                        }
                    }
                    if(structure_type == 1)
                    {
                        int way = rand()%2;
                        if (way == 0)
                        {
                            if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                            {
                                y = y - 1;
                                dir = 0;
                            }
                            else
                            {
                                way = 1;
                            }
                        }
                        if (way == 1)
                        {
                            if(posiciones[6]==0 && posiciones[7]==0 && posiciones[8]==0)
                            {
                                y = y + 1;
                                dir = 2;
                            }
                            else
                            {
                                if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                                {
                                    y = y - 1;
                                    dir = 0;
                                }
                                else
                                {
                                    if(posiciones[2]==0 && posiciones[5]==0 && posiciones[8]==0)
                                    {
                                        x = x + 1;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }
                else if (dir == 2)
                {
                    if(structure_type == 0)
                    {
                        if(posiciones[6]==0 && posiciones[7]==0 && posiciones[8]==0)
                        {
                            y = y + 1;
                        }
                        else
                        {
                            structure_type = 1;
                        }
                    }
                    if(structure_type == 1)
                    {
                        int way = rand()%2;
                        if (way == 1)
                        {
                            if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                            {
                                x = x - 1;
                                dir = 3;
                            }
                            else
                            {
                                way = 0;
                            }
                        }
                        if (way == 0)
                        {
                            if(posiciones[2]==0 && posiciones[5]==0 && posiciones[8]==0)
                            {
                                x = x + 1;
                                dir = 1;
                            }
                            else
                            {
                                if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                                {
                                    x = x - 1;
                                    dir = 3;
                                }
                                else
                                {
                                    if(posiciones[6]==0 && posiciones[7]==0 && posiciones[8]==0)
                                    {
                                        y = y + 1;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }
                else if (dir == 3)
                {
                    if(structure_type == 0)
                    {
                        if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                        {
                            x = x - 1;
                        }
                        else
                        {
                            structure_type = 1;
                        }
                    }
                    if(structure_type == 1)
                    {
                        int way = rand()%2;
                        if (way == 1)
                        {
                            if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                            {
                                y = y - 1;
                                dir = 0;
                            }
                            else
                            {
                                way = 1;
                            }
                        }
                        if (way == 0)
                        {
                            if(posiciones[6]==0 && posiciones[7]==0 && posiciones[8]==0)
                            {
                                y = y + 1;
                                dir = 2;
                            }
                            else
                            {
                                if(posiciones[0]==0 && posiciones[1]==0 && posiciones[2]==0)
                                {
                                    y = y - 1;
                                    dir = 0;
                                }
                                else
                                {
                                    if(posiciones[0]==0 && posiciones[3]==0 && posiciones[6]==0)
                                    {
                                        x = x - 1;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                            }
                        }

                    }
                }
                m->terreno[y][x] = 1;
                structure_pieces_left = structure_pieces_left - 1;
                placed = placed + 1;
                structure_type = rand()%2;
            }
        }
    }
}
void draw_map(Mapa m)
{
    for(int i = 0; i < H/BLOCK_SIZE; i = i + 1)
    {
        for(int j = 0; j < W/BLOCK_SIZE; j = j + 1)
        {
            if(m->terreno[i][j]==1)
            {
                color_relleno(255, 255, 255, 255);
                dibuja_rectangulo(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            }
        }

    }
}
void draw_map_menu(Mapa m, int x, int y)
{
    for(int i = 0; i < H/BLOCK_SIZE; i = i + 1)
    {
        for(int j = 0; j < W/BLOCK_SIZE; j = j + 1)
        {
            if(m->terreno[i][j]==1)
            {
                color_relleno(255, 0, 0, 255);
                dibuja_rectangulo(x + j * BLOCK_SIZE/3, y + i * BLOCK_SIZE/3, BLOCK_SIZE/3, BLOCK_SIZE/3);
            }
        }

    }
}

int map_collision(Mapa m, double x, double y, double w, double h)
{
    int cord_x = x/BLOCK_SIZE;
    int cord_y = y/BLOCK_SIZE;
    if (cord_x <= 99 && cord_x > 0 && cord_y <= 49 && cord_y > 0)
    {
        if (solape_rectangulos(cord_x * BLOCK_SIZE, cord_y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, x, y, w, h)&& m->terreno[cord_y][cord_x] == 1)return 1;
        for(int i = cord_y; i < y; i = i + 1)
        {
            for(int j = cord_x; j < x; j = j + 1)
            {
                if (solape_rectangulos(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, x, y, w, h) && m->terreno[i][j] == 1)return 1;
            }
        }
    }

    return 0;
}
int line_map_collision(Mapa m, double x1, double y1, double x2, double y2)
{
    if(x1 < 0) x1 = 0;
    if(y1 < 0) y1 = 0;
    if(x2 < 0) x2 = 0;
    if(y2 < 0) y2 = 0;

    int x;
    int y;
    int a;
    int b;
    int z;
    int t;
    if(x1 < x2)
    {
        x = x1;
        y = y1;
        z = x1;
        t = y1;
        a = x2;
        b = y2;
    }
    else
    {
        x = x2;
        y = y2;
        z = x2;
        t = y2;
        a = x1;
        b = y1;
    }
    while (z < a)
    {
        //(a-x)/(b-y) = (z-x)/(t-y)
        t = ((b-y) * (z-x) / (a-x) + y);
        color_relleno(0, 0, 255, 255);
        dibuja_rectangulo(z , t, BLOCK_SIZE, BLOCK_SIZE);
        int coordx = z/BLOCK_SIZE;
        int coordy = t/BLOCK_SIZE;
        if(solape_rectangulos(z, t, BLOCK_SIZE, BLOCK_SIZE, coordx * BLOCK_SIZE, coordy * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE) && m->terreno[coordy][coordx] == 1)
        {
            dibuja_rectangulo(coordx * BLOCK_SIZE , coordy * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            return 1;
        }

        z = z + BLOCK_SIZE;

    }
    return 0;
}

int line_map_collision2(Mapa m, double x1, double y1, double x2, double y2)
{
    if(x1 < 0) x1 = 0;
    if(y1 < 0) y1 = 0;
    if(x2 < 0) x2 = 0;
    if(y2 < 0) y2 = 0;

    int x;
    int y;
    int a;
    int b;
    if(x1<x2)
    {
        x = x1/BLOCK_SIZE - 1;
        y = y1/BLOCK_SIZE - 1;
        a = x2/BLOCK_SIZE + 1;
        b = y2/BLOCK_SIZE + 1;
    }
    else
    {
        a = x1/BLOCK_SIZE;
        b = y1/BLOCK_SIZE;
        x = x2/BLOCK_SIZE;
        y = y2/BLOCK_SIZE;
    }

    while (x < a)
    {
        dibuja_linea(x*BLOCK_SIZE, y*BLOCK_SIZE, a*BLOCK_SIZE, b*BLOCK_SIZE);
        dibuja_rectangulo(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        if(solape_recta_rect(x * BLOCK_SIZE,y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, x1, y1, x2, y2))
        {
            color_relleno(0, 0, 255, 255);
            dibuja_linea(x1, y1, x2, y2);

            printf("%d, %d \n%d, %d\n\n", x, y, a, b);
            if(m->terreno[y][x] == 1)
            {
                printf("BLOCK\n");
                return 1;
            }
            else
                {
                    while(!solape_recta_rect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, x1, y1, x2, y2))
                    {
                        printf("%d, %d \n%d, %d\n\n", x, y, a, b);
                        if(y < b)
                        {
                            y = y + 1;
                        }
                        else if(y > b)
                        {
                            y = y - 1;
                        }
                    }
                    x = x + 1;
                }
        }
        else
        {
            x = x + 1;
        }



    }
    return 0;


}
