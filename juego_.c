#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "batalla_.h"
#include <stdbool.h>
//#include "perfil_.h"

void turnos(juego_t* juego){
  cargar_personajes(&juego);
  posicionar_personaje(&juego, juego.rohan[juego.cantidad_rohan]);
  posicionar_personaje(&juego, juego.isengard [juego.cantidad_isengard]);
  imprimir_matriz (juego.terreno);
  int i = 0;
  while ( i <juego.cantidad_rohan || i<juego.cantidad_isengard || juego.llegadas_rohan < LLEGADAS_GANAR || juego.llegadas_isengard < LLEGADAS_GANAR){
    if(i < juego.cantidad_rohan ){
      jugar ( &juego, juego.jugador1.bando, i);
    }if (i < juego.cantidad_isengard){
      jugar ( &juego, juego.jugador2.bando, i );
    }
    i++;
  }

}

int main(){
  juego_t juego;
  inicializar_juego( &juego);
  while (juego.llegadas_rohan < LLEGADAS_GANAR || juego.llegadas_isengard < LLEGADAS_GANAR){
    turnos(&juego);
  }if (llegadas_rohan >= LLEGADAS_GANAR){
    mensaje_rohan_ganador();
  }else{
    mensaje_isengard_ganador();
  }
return 0;
}
