#include "../configuracion/library.h"

typedef struct node{
    char question[150];
    char op1[15];
    char op2[15];
    char op3[15];
    int correct;
} Question;

Question pre[10];



int inicio(int ancho, int alto, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *logo, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display);
int battlepage(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background, int opcion);
void bala(Bullet mibala, Ship minave, ALLEGRO_COLOR white, int layout_alto);
void ataque(Bullet enemibala, Enemy enemigo, ALLEGRO_COLOR white, int lauuout_alto, int pos);
void enemigos(int count, Enemy enemigo, Enemyvida vidaenemy[], ALLEGRO_COLOR white, int bull);
Ship navefly(Ship minave, ALLEGRO_BITMAP *nave_im, int layout_ancho);
Ship confignave(Ship minave, int alto);
Enemy configenemigo(Enemy enemigo, int ancho, int alto);
int menu(int ancho, int alto, ALLEGRO_BITMAP *background, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR red);
Ship controllerfly(Ship minave, int ancho, int alto, ALLEGRO_COLOR red);
Question config_game_options(FILE* archivo, Question pre[], int option);
void question(int auxi, Question aux, ALLEGRO_COLOR white, ALLEGRO_FONT *fuente);

int main(void)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *logo = NULL;
    ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);

    int ancho = 854;
    int alto = 480;
    int opcion = 0;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    al_init_image_addon();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();

    display = al_create_display(ancho, alto);
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

    inicio(ancho, alto, background, logo, event_queue, display);

    opcion = menu(ancho, alto, background, display, red);

    battlepage(display, background, opcion);
    return 0;
}


int inicio(int ancho, int alto, ALLEGRO_BITMAP *background, ALLEGRO_BITMAP *logo, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display){

ALLEGRO_FONT *fuente = NULL;

fuente = al_load_font("../assets/XTypewriter-Bold.otf", 40, 0);

while (done_menu == 1)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(logo,0,0,0);

    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho / 2, alto - 100, ALLEGRO_ALIGN_CENTRE, "Presiona espacio para comenzar");
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

    al_destroy_display(display);
    al_destroy_bitmap(background);
    al_uninstall_keyboard();
    al_uninstall_system();  
}

int menu(int ancho, int alto, ALLEGRO_BITMAP *background, ALLEGRO_DISPLAY *display, ALLEGRO_COLOR red){

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

    display = al_create_display(ancho, alto);
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

    fuente = al_load_font("../assets/XTypewriter-Bold.otf", 40, 0);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    Ship minave;
    minave.ancho = 15;
    minave.alto = 15;
    minave.vida = 3;
    minave.pos = 1;


while (done_opc == 1)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_bitmap(background, 0, 0, 0);

    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho / 2, (alto / 4) - 80, ALLEGRO_ALIGN_CENTRE, "SUMAS");
    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho / 2, ((alto/4) * 2) - 80, ALLEGRO_ALIGN_CENTRE, "MIXTA");
    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho / 2, ((alto/4) * 3) - 80, ALLEGRO_ALIGN_CENTRE, "MULTIPLICACION");
    al_draw_text(fuente, al_map_rgb(255, 255, 255), ancho / 2, ((alto)) - 80, ALLEGRO_ALIGN_CENTRE, "MAYOR O MENOR");

    minave = controllerfly(minave, ancho, alto, red);


    al_flip_display();

    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch (ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_UP:
            if (minave.pos > 1)
            {
                minave.pos--;
            }
            break;
        case ALLEGRO_KEY_DOWN:
            if (minave.pos < 4)
            {
                minave.pos++;
            }
            break;
        case ALLEGRO_KEY_ENTER:
            done_opc = 0;
            break;
        }
    }
  }

    al_destroy_display(display);
    al_destroy_bitmap(background);
    al_uninstall_keyboard();
    al_uninstall_system();

    return minave.pos;  
}


int battlepage(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *background, int opcion){
    FILE* archivo;
    int controller = 0;
    switch (opcion)
    {
    case 1:
        archivo = fopen("../archivos/MS_Suma.txt", "r");
        controller = 1;
        break;
    case 2:
        archivo = fopen("../archivos/MS_Mixta.txt", "r");
        controller = 1;
        break;
    case 3:
        archivo = fopen("../archivos/MS_Multiplicacion.txt", "r");
        controller = 1;
        break;
    case 4:
        archivo = fopen("../archivos/MS_HighLow.txt", "r");
        controller = 2;
        break;
    default:
        break;
    }

    ALLEGRO_BITMAP *logo = NULL;
    ALLEGRO_COLOR white;
    ALLEGRO_COLOR black;
    ALLEGRO_COLOR red;
    ALLEGRO_FONT *fuente = NULL;

    int some = 0;
    int ancho = 854;
    int alto = 480;

    int layout_ancho = ancho/6;
    int layout_alto = alto/5;

    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    al_init_image_addon();
    al_init_font_addon();
    al_init_primitives_addon();
    al_init_ttf_addon();

    display = al_create_display(ancho, alto);
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

    Ship minave;
    minave.y = (layout_alto * 4);
    minave.ancho = 30;
    minave.alto = 30;
    minave.vida = 3;
    minave.pos = 2;

    Bullet mibala;
    Bullet enemibala;

    Enemy enemigo;
    enemigo = configenemigo(enemigo, layout_ancho, layout_alto);

    int bull = 0;

    white = al_map_rgb(255, 255, 255);
    black = al_map_rgb(0, 0, 0);
    // give me the red color
    red = al_map_rgb(255, 0, 0);

    fuente = al_load_font("../assets/XTypewriter-Bold.otf", 18, 0);

    Enemyvida vidaenemy[3];
    for (int i = 0; i < 3; i++)
    {
        vidaenemy[i].vida = 1;
        vidaenemy[i].pos = i + 1;
    }
    ALLEGRO_BITMAP *nave_im = al_load_bitmap(SHIP);

    Question aux;

    // aux = config_game_options(archivo, aux, controller);

        if(archivo != NULL){
        int i = 0;
        if(controller == 1){
            while (!feof(archivo))
            {
            fscanf(archivo, "%s %s %s %s %d", aux.question, aux.op1, aux.op2, aux.op3, &aux.correct);

            pre[i] = aux;

            i++;
            }
        }
        else{
            while (!feof(archivo))
            {
            fscanf(archivo, "%s %s %s %d", aux.question, aux.op1, aux.op2, &aux.correct);
            pre[i] = aux;
            i++;
            }
        }
        fclose(archivo);
    }

    int k = 0;
    int res = 3;

    while (done == 1)
    {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_bitmap(background, 0, 0, 0);

        // al_draw_bitmap(logo,0,0,0);
        enemigos(3, enemigo, vidaenemy, white, bull);

        question(controller, pre[k], white, fuente);        

        minave =  navefly(minave, nave_im, layout_ancho);

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

Ship confignave(Ship minave, int alto){
    minave.y = (alto * 4);
    minave.ancho = 30;
    minave.alto = 30;
    minave.vida = 3;
    minave.pos = 2;
    return minave;
}

Enemy configenemigo(Enemy enemigo, int ancho, int alto){
    enemigo.x = ancho;
    enemigo.y = alto;
    enemigo.ancho = 30;
    enemigo.alto = 30;
    return enemigo;
}   


//funciones
// Question config_game_options(FILE* archivo, Question pre[], int option){
//         if(archivo != NULL){
//         int i = 0;
//         if(option == 1){
//             while (!feof(archivo))
//             {
//             fscanf(archivo, "%s %s %s %s %d", aux.question, aux.op1, aux.op2, aux.op3, &aux.correct);

//             pre[i] = aux;
//             pre[i].id = i;

//             i++;
//             }
//         }
//         else{
//             while (!feof(archivo))
//             {
//             fscanf(archivo, "%s %s %s %d", aux.question, aux.op1, aux.op2, &aux.correct);

//             pre[i] = aux;
//             pre[i].id = i;

//             i++;
//             }
//         }
//         fclose(archivo);
//     }

//     return pre;
// }

void question(int auxi, Question aux, ALLEGRO_COLOR white, ALLEGRO_FONT *fuente){
    if(auxi == 2){
        al_draw_text(fuente, white, 50, 50, 0, aux.question);
        al_draw_text(fuente, white, 50, 80, 0, aux.op1);
        al_draw_text(fuente, white, 50, 110, 0, aux.op2);
    }
    else{
        al_draw_text(fuente, white, 200, 50, 0, aux.question);
        al_draw_text(fuente, white, 120, 130, 0, aux.op1);
        al_draw_text(fuente, white, 410, 130, 0, aux.op2);
        al_draw_text(fuente, white, 750, 130, 0, aux.op3);
    }
}

Ship navefly(Ship minave, ALLEGRO_BITMAP *nave_im, int layout_ancho){
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
        return minave;
}

void bala(Bullet mibala, Ship minave, ALLEGRO_COLOR white, int layout_alto)
{
    ALLEGRO_BITMAP *bullet = NULL;
    bullet = al_load_bitmap(BULLET);
    mibala.x = minave.x;
    mibala.y = minave.y;
    mibala.r = 5;

    while (mibala.y > (layout_alto * 2) + 30)
    {

        al_draw_bitmap(bullet, (mibala.x + 25), mibala.y, 0);
        al_flip_display();
        mibala.y = mibala.y - 10;
    }
}

void ataque(Bullet enemibala, Enemy enemigo, ALLEGRO_COLOR white, int layout_alto, int pos)
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

Ship controllerfly(Ship minave, int ancho, int alto, ALLEGRO_COLOR red){

    
    if (minave.pos == 1)
    {
        minave.x = ((ancho/6) * 2);
        minave.y = ((alto/5) * 1) - 22;
        al_draw_filled_circle(minave.x, minave.y, 15, red);

    }
    if (minave.pos == 2)
    {
        minave.x = ((ancho/6) * 2);
        minave.y = ((alto/5) * 2) - 12;
        
        al_draw_filled_circle(minave.x, minave.y, 15, red);
    }
    if (minave.pos == 3)
    {
        minave.x = ((ancho/6) * 2) - 75;
        minave.y = ((alto/5) * 3) + 10;
        al_draw_filled_circle(minave.x, minave.y, 15, red);
    }
    if(minave.pos == 4){
        minave.x = ((ancho/6) * 2) - 75;
        minave.y = ((alto/5) * 4) + 30;
        al_draw_filled_circle(minave.x, minave.y, 15, red);
    }

    return minave;
}

// gcc main.c -o 1 $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_ttf-5  --libs --cflags)
