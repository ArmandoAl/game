#include "main.c"

void bala(Bullet mibala, Ship minave, ALLEGRO_COLOR white, int layoutalto)
{
    ALLEGRO_BITMAP *bullet = NULL;
    bullet = al_load_bitmap(BULLET);
    mibala.x = minave.x;
    mibala.y = minave.y;
    mibala.r = 5;

    while (mibala.y > (LAYOUTALTO * 2) + 30)
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

    while (enemibala.y < (LAYOUTALTO * 4))
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
            minave.x = (LAYOUTANCHO * 3) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
        if (minave.pos == 1)
        {
            minave.x = (LAYOUTANCHO * 1) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
        if (minave.pos == 3)
        {
            minave.x = (LAYOUTANCHO * 5) - 15;
            al_draw_bitmap(nave_im, minave.x, minave.y, 0);
        }
}