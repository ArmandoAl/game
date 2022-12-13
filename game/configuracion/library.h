#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BACKGROUND_FILE "../assets/MathAndShips_BG.png"
#define LOGO "../assets/MathAndShips2.png"
#define METE "../assets/Mete.png"
#define METEX "../assets/Meteor_Destroyed.png"
#define SHIP "../assets/Ship.png"
#define BULLET "../assets/Bullet_Boy.png"
#define FPS 60

typedef struct nave
{
    int x;
    int y;
    int ancho;
    int alto;
    int vida;
    int pos;
} Ship;

typedef struct enemigo
{
    int x;
    int y;
    int ancho;
    int alto;
} Enemy;

typedef struct vida
{
    int vida;
    int pos;
} Enemyvida;

typedef struct bala
{
    int x;
    int y;
    int r;
} Bullet;

int done_menu = 1;
int done_opc = 1;
int done = 1;