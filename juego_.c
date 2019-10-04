#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "batalla_.h"
//#include "perfil_.h"

int main(){
  juego_t juego;
  inicializar_juego( &juego);
  cargar_personajes(&juego);
  posicionar_personaje(&juego, juego.rohan[juego.cantidad_rohan]);
  posicionar_personaje(&juego, juego.isengard [juego.cantidad_isengard]);
  imprimir_matriz (juego.terreno);

return 0;
}
