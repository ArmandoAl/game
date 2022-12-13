#include "../configuracion/library.h"

Ship confignave(Ship minave){
    minave.y = (ALTO * 4);
    minave.ancho = 30;
    minave.alto = 30;
    minave.vida = 3;
    minave.pos = 2;
    return minave;
}

Enemy configenemigo(Enemy enemigo){
    enemigo.x = LAYOUTANCHO;
    enemigo.y = LAYOUTALTO;
    enemigo.ancho = 30;
    enemigo.alto = 30;
    return enemigo;
}
