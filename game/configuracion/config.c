#include "../configuracion/library.h"

int menu(void);
int battlepage(void);
void bala(Bullet mibala, Ship minave, ALLEGRO_COLOR white, int layout_alto);
void ataque(Bullet enemibala, Enemy enemigo, ALLEGRO_COLOR white, int lauuout_alto, int pos);
void enemigos(int count, Enemy enemigo, Enemyvida vidaenemy[], ALLEGRO_COLOR white, int bull);
void navefly(Ship minave, ALLEGRO_BITMAP *nave_im);
Ship confignave(Ship minave);
Enemy configenemigo(Enemy enemigo);

int main(void)
{
    // menu();
    battlepage();

    return 0;
}


int menu(void){

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *logo = NULL;
logo = al_load_bitmap(LOGO);
ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
al_register_event_source(event_queue, al_get_keyboard_event_source());


while (done_menu == 1)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(logo,0,0,0);
    al_flip_display();
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_SPACE:
            done_menu = 0;
            break;
        }
    }
  }
}


int battlepage(void){

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *logo = NULL;
    ALLEGRO_COLOR white;
    ALLEGRO_COLOR black;
    ALLEGRO_COLOR red;
    ALLEGRO_FONT *fuente = NULL;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    al_init_image_addon();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();

    display = al_create_display(ANCHO, ALTO);
    if (!display)
        {
            fprintf(stderr, "failed to create display!\n");
            return -1;
        }

    background = al_load_bitmap(BACKGROUND_FILE);
    if (!background)
    {
        fprintf(stderr, "failed to load background bitmap!\n");
        return -1;
    }
    if (!al_install_keyboard())
    {
        fprintf(stderr, "failed to install keyboard!\n");
        return -1;
    }

    logo = al_load_bitmap(LOGO);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    int res = 1;

    Ship minave;
    minave = confignave(minave);

    Bullet mibala;
    Bullet enemibala;

    Enemy enemigo;
    enemigo = configenemigo(enemigo);

    int bull = 0;

    white = al_map_rgb(255, 255, 255);
    black = al_map_rgb(0, 0, 0);
    // give me the red color
    red = al_map_rgb(255, 0, 0);

    

    fuente = al_load_font("../assets/EmiliaKerenDemo.otf", 18, 0);

    Enemyvida vidaenemy[3];
    for (int i = 0; i < 3; i++)
    {
        vidaenemy[i].vida = 1;
        vidaenemy[i].pos = i + 1;
    }
    ALLEGRO_BITMAP *nave_im = al_load_bitmap(SHIP);

    while (done == 1)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(background, 0, 0, 0);

        // al_draw_bitmap(logo,0,0,0);
        enemigos(3, enemigo, vidaenemy, white, bull);

        al_draw_text(fuente, white, 50, 50, 0, "RESUELVE LA SIGUIENTE MULTIPLICACION");
        al_draw_text(fuente, white, 50, 80, 0, "5X7");

        navefly(minave, nave_im);

        al_flip_display();

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_RIGHT:
                if (minave.pos < 3)
                {
                    minave.pos = minave.pos + 1;
                }
                break;
            case ALLEGRO_KEY_LEFT:
                if (minave.pos > 1)
                {
                    minave.pos = minave.pos - 1;
                }
                break;
            case ALLEGRO_KEY_SPACE:
                bala(mibala, minave, red, layout_alto);
                if (minave.pos == res)
                {
                    vidaenemy[res - 1].vida = 0;
                }
                else
                {

                    ataque(enemibala, enemigo, white, layout_alto, minave.pos);
                }
                break;
            case ALLEGRO_KEY_ESCAPE:
                done= 0;
                break;
            }
        }
    }

    al_destroy_display(display);
    al_destroy_bitmap(background);
    al_uninstall_keyboard();
    al_uninstall_system();
}

Ship confignave(Ship minave){
    minave.y = (ALTO * 4);
    minave.ancho = 30;
    minave.alto = 30;
    minave.vida = 3;
    minave.pos = 2;
    return minave;
}

Enemy configenemigo(Enemy enemigo){
    enemigo.x = layout_ancho;
    enemigo.y = layout_alto;
    enemigo.ancho = 30;
    enemigo.alto = 30;
    return enemigo;
}


//funciones

void bala(Bullet mibala, Ship minave, ALLEGRO_COLOR white, int layout_alto)
{
    ALLEGRO_BITMAP *bullet = NULL;
    bullet = al_load_bitmap(BULLET);
    mibala.x = minave.x;
    mibala.y = minave.y;
    mibala.r = 5;

    while (mibala.y > (layout_alto * 2) + 30)
    {

        al_draw_bitmap(bullet, (mibala.x + 15), mibala.y, 0);
        al_flip_display();
        mibala.y = mibala.y - 10;
    }
}

void ataque(Bullet enemibala, Enemy enemigo, ALLEGRO_COLOR white, int lauuout_alto, int pos)
{
    ALLEGRO_BITMAP *mete = NULL;
    mete = al_load_bitmap(METE);
    if (pos == 1)
    {
        enemibala.x = enemigo.x - 15;
    }
    if (pos == 2)
    {
        enemibala.x = enemigo.x * 3 - 15;
    }
    if (pos == 3)
    {
        enemibala.x = enemigo.x * 5 - 15;
    }

    enemibala.y = enemigo.y * 2;
    enemibala.r = 3;

    while (enemibala.y < (layout_alto * 4))
    {
        al_draw_bitmap(mete, enemibala.x - 15, enemibala.y, 0);
        al_flip_display();
        enemibala.y = enemibala.y + 5;
    }

    // al_destroy_bitmap(mete);
}

void enemigos(int count, Enemy enemigo, Enemyvida vidaenemy[], ALLEGRO_COLOR white, int bull)
{
    ALLEGRO_BITMAP *mete = NULL;
    mete = al_load_bitmap(METE);
    int aux;
    switch (count)
    {
    case 2:
        aux = 2;
        for (int i = 0; i < count; i++)
        {

            if (vidaenemy[i].vida == 1)
            {
                al_draw_bitmap(mete, (enemigo.x * aux) - 30, (enemigo.y * 2) - 30, 0);
            }

            aux = aux + 2;
        }
        break;
    case 3:
        aux = 1;
        for (int i = 0; i < count; i++)
        {
            if (vidaenemy[i].vida == 1)
            {
                al_draw_bitmap(mete, (enemigo.x * aux) - 30, (enemigo.y * 2) - 30, 0);
            }
            aux = aux + 2;
        }
        break;
    case 5:
        aux = 1;
        for (int i = 0; i < count; i++)
        {
            if (vidaenemy[i].vida == 1)
            {
                al_draw_bitmap(mete, (enemigo.x * aux) - 30, (enemigo.y * 2) - 30, 0);
            }
            aux = aux + 1;
        }
        break;
        
    default:
        break;
    }
}

void navefly(Ship minave, ALLEGRO_BITMAP *nave_im){
        if (minave.pos == 2)
        {
            minave.x = (layout_ancho * 3) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
        if (minave.pos == 1)
        {
            minave.x = (layout_ancho * 1) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
        if (minave.pos == 3)
        {
            minave.x = (layout_ancho * 5) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
}


// gcc main.c -o 1 $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5  --libs --cflags)