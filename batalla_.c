#include <stdio.h>
#include "perfil_.h"
#include <stdlib.h>
#include <time.h>
#include "batalla_.h"

const char ISENGARD = 'I'; // Valor ofensivo reprensentado por Isengrad
const char ROHAN = 'R'; // Valor defensivo representado por Rohan
const char HOMBRES = 'H';
const char ELFOS = 'E';
const char URUKHAI = 'U';
const char ORCOS = 'O';
const int RANGO_PLUS = 5;
const int ENERGIA_INICIAL = 5;
const int ENERGIA_MAXIMA = 10;
const int ENERGIA_HOMBRES_ORCOS = 3;
const int ENERGIA_ELFOS_URUKHAI = 5;
const int UNIDADES_INICIALES = 3;
const int LLEGADAS_INICIALES = 0;
const int LLEGADAS_GANAR = 5;
const int RANGO_ALEATORIO_INICIALES_FILAS = 3;	/*  (MAX_TERRENO_FIL /2 ) - 2  */
const int RANGO_ALEATORIO_INICIALES_COLUMNAS = 9; /* MAX_TERRENO_COL - 1 */
const int FILA_MINIMA_ROHAN = 5; /* Cambia si cambia el numero de MAX_TERRENO_FIL, (MAX_TERRENO_FIL/2) */
const int FILA_MINIMA_URUKHAI = 1;
const int FILA_INICIAL_ORCOS = 0;
const int FILA_INICIAL_HOMBRE = 9; /* Cambiar si cambia el numero maximo de MAX_TERRENO_FIL (MAX_TERRENO_FIL -1) */
const int VIDA_ELFOS_URUKHAI = 200;
const int VIDA_HOMBRES_ORCOS = 100;
const int ATAQUE_ELFOS_URUKHAI = 10;
const int ATAQUE_HOMBRES_ORCOS = 50;

void asignar_plus ( jugador_t jugador1, jugador_t jugador2, int* plus_rohan, int* plus_isengard  ){
  int num_random_rohan = rand() % RANGO_PLUS;
  int num_random_isengard = rand () % RANGO_PLUS;
  if( jugador1.bando == ROHAN ){
    *plus_rohan = jugador1.intensidad * num_random_rohan;
    *plus_isengard = jugador2.intensidad * num_random_isengard;
  }else{
    *plus_rohan = jugador2.intensidad * num_random_rohan;
    *plus_isengard = jugador1. intensidad * num_random_isengard;
  }
}

void inicilizar_jugadores ( jugador_t* jugador1, jugador_t* jugador2 , int* plus_rohan, int* plus_isengard ){
  perfil( &(jugador1 -> bando), &(jugador1 -> intensidad) );
  (*jugador2).intensidad = 10 - (jugador1 -> intensidad);
  if( jugador1 -> bando == ISENGARD ){
    jugador2 -> bando = ROHAN;
  }else{
    jugador2-> bando = ISENGARD;
  } asignar_plus ( *jugador1, *jugador2, plus_rohan, plus_isengard );
  jugador1 ->energia = ENERGIA_INICIAL;
  jugador2 -> energia = ENERGIA_INICIAL;
  if ( jugador1->bando == ROHAN ){
    jugador1->plus = *plus_rohan;
    jugador2->plus = *plus_isengard;
  } else{
    jugador1->plus = *plus_isengard;
    jugador2->plus = *plus_rohan;
  }
}

void inicializar_unidades_iniciales ( personaje_t rohan [MAX_PERSONAJES], personaje_t isengard [MAX_PERSONAJES], int tope_rohan, int tope_isengard, int plus_rohan, int plus_isengard ){
  for ( int i = 0; i < tope_rohan; i++ ){
    rohan [i]. codigo = ELFOS;
    rohan [i]. vida = VIDA_ELFOS_URUKHAI - plus_rohan;
    rohan[i]. ataque = ATAQUE_ELFOS_URUKHAI + plus_rohan;
    rohan [i]. fila = rand() % RANGO_ALEATORIO_INICIALES_FILAS + FILA_MINIMA_ROHAN ;
    rohan [i]. columna = rand() % RANGO_ALEATORIO_INICIALES_COLUMNAS;
  }for (size_t j = 0; j < tope_isengard; j++) {
    isengard [j]. codigo = URUKHAI;
    isengard [j]. vida = VIDA_ELFOS_URUKHAI - plus_isengard;
    isengard [j]. ataque = ATAQUE_ELFOS_URUKHAI + plus_isengard;
    isengard [j]. fila = rand() % RANGO_ALEATORIO_INICIALES_FILAS + FILA_MINIMA_URUKHAI;
    isengard [j]. columna = rand() % RANGO_ALEATORIO_INICIALES_COLUMNAS;
  }
}

void inicializar_terreno ( char terreno [MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t rohan[MAX_PERSONAJES], personaje_t isengard[MAX_PERSONAJES], int tope_rohan, int tope_isengard ){
  for (size_t i = 0; i < MAX_TERRENO_COL; i++) {
    for (size_t j = 0; j < MAX_TERRENO_FIL; j++) {
      terreno [i][j] = '_';
    }
  }for (size_t k = 0; k < tope_rohan; k++) {
    terreno [ rohan[k].fila ][ rohan[k].columna ] = rohan[k].codigo;
  }for (size_t l = 0; l < tope_isengard; l++) {
    terreno [ isengard[l].fila ][ isengard[l].columna] = isengard[l].codigo;
  }for (size_t m = 0; m < MAX_TERRENO_COL; m++) {
    for (size_t n = 0; n < MAX_TERRENO_FIL; n++) {
      printf(" %c", terreno [m][n]);
    }printf("\n\n" );
  }
}

void mostrar_jugadores( jugador_t jugador1, jugador_t jugador2 ){
  printf("Jugador 1 (el que tomo el cuestionario) su bando es %c, Intensidad: %i y su plus %i \n", jugador1.bando, jugador1.intensidad, jugador1.plus );
  printf("Jugador 2 su bando es %c, Intensidad %i y su plus es %i \n", jugador2.bando, jugador2.intensidad, jugador2.plus );
}

void inicializar_juego(juego_t* juego){
  srand (( unsigned ) time ( NULL ) ) ;
  inicilizar_jugadores ( &juego->jugador1, &juego->jugador2, &juego->plus_rohan, &juego->plus_isengard );
  system ("clear");
	juego -> llegadas_rohan = LLEGADAS_INICIALES;
	juego -> llegadas_isengard = LLEGADAS_INICIALES;
  juego -> cantidad_rohan = UNIDADES_INICIALES;
  juego -> cantidad_isengard = UNIDADES_INICIALES;
  inicializar_unidades_iniciales ( juego->rohan, juego->isengard, juego->cantidad_rohan, juego->cantidad_isengard, juego->plus_rohan, juego->plus_isengard );
  mostrar_jugadores ( juego->jugador1, juego->jugador2);
  inicializar_terreno ( juego->terreno, juego->rohan, juego->isengard, juego->cantidad_rohan, juego->cantidad_isengard );
}




 void ingresar_filas_columnas ( int* fila,int* columna ){
   printf("En que fila se posicionara los arqueros?\n" );
   scanf(" %i", fila);
   printf("En que columna se poscionaran los arqueros?\n" );
   scanf(" %i", columna);
 }

 void cargar_hombres_orcos(personaje_t unidades[MAX_PERSONAJES], int tope_unidades, int plus, char personaje_cargar){
   unidades[tope_unidades]. codigo = personaje_cargar;
   unidades[tope_unidades]. codigo = personaje_cargar;
   unidades[tope_unidades]. vida = VIDA_HOMBRES_ORCOS - plus;
   unidades[tope_unidades]. ataque = ATAQUE_HOMBRES_ORCOS + plus;
   printf("En que columna arrancara la infateria? Elija un numero del 0 al 9 para elegir su columna, siendo 0 la 1era y 9 la ultima\n");
   scanf("%i",&unidades[tope_unidades].columna );
 }

 void cargar_elfos_urukhai (personaje_t unidades[MAX_PERSONAJES], int tope_unidades, int plus, char personaje_cargar){
  unidades[tope_unidades]. codigo = personaje_cargar;
  unidades[tope_unidades]. vida = VIDA_ELFOS_URUKHAI - plus;
  unidades[tope_unidades]. ataque = ATAQUE_ELFOS_URUKHAI + plus;
  ingresar_filas_columnas( &unidades[tope_unidades].fila, &unidades[tope_unidades].columna );
}

void cargar_personajes_rohan ( jugador_t* jugador, personaje_t rohan[MAX_PERSONAJES], int tope_rohan, int plus ){
  char personaje_cargar;
  if(jugador->energia >= ENERGIA_ELFOS_URUKHAI){
    printf("Desea colocar un Elfo (E), un Hombre (H) o no desea colocar nada(N)?\n" );
    scanf(" %c", &personaje_cargar );
    if(personaje_cargar == ELFOS){
      cargar_elfos_urukhai (rohan, tope_rohan, plus, personaje_cargar );
    }else if (personaje_cargar == HOMBRES){
      cargar_hombres_orcos( rohan, tope_rohan, plus, personaje_cargar);
      rohan[tope_rohan].fila = FILA_INICIAL_HOMBRE;
    }else
      printf("De acuerdo, luego del siguiente turno podras volver a elegir si colocar un elfo o un hombre.\n" );
  }else if (jugador->energia >= ENERGIA_HOMBRES_ORCOS && jugador-> energia < ENERGIA_ELFOS_URUKHAI){
    printf("Desea colocar un Hombre (H) o no desea colocar nada (N)\n" );
    scanf(" %c", &personaje_cargar );
    if (personaje_cargar == HOMBRES){
      cargar_hombres_orcos( rohan, tope_rohan, plus,personaje_cargar);
      rohan[tope_rohan].fila = FILA_INICIAL_HOMBRE;
    }else{
      printf("De acuerdo, luego del siguiente turno podras volver a elegir si deseas colocar una unidad.\n" );
    }
  }else{
    printf("No posees suficiente energia para colocar una unidad, espera un par de turnos hasta que sea posible\n" );
  }
}

void cargar_personajes_isengard ( jugador_t* jugador, personaje_t isengard[MAX_PERSONAJES], int tope_isengard, int plus ){
  char personaje_cargar;
  if(jugador->energia >= ENERGIA_ELFOS_URUKHAI){
    printf("Desea colocar un Urukhai (U), un Orco (O) o no desea colocar nada(N)?\n" );
    scanf(" %c", &personaje_cargar );
    if(personaje_cargar == URUKHAI){
      cargar_elfos_urukhai (isengard, tope_isengard, plus, personaje_cargar );
    }else if (personaje_cargar == ORCOS){
      cargar_hombres_orcos( isengard, tope_isengard, plus, personaje_cargar);
      isengard[tope_isengard].fila = FILA_INICIAL_ORCOS;
    }else
      printf("De acuerdo, luego del siguiente turno podras volver a elegir si colocar un elfo o un hombre.\n" );
  }else if (jugador->energia >= ENERGIA_HOMBRES_ORCOS && jugador-> energia < ENERGIA_ELFOS_URUKHAI){
    printf("Desea colocar un Orco (O) o no desea colocar nada (N)\n" );
    scanf(" %c", &personaje_cargar );
    if (personaje_cargar == ORCOS){
      cargar_hombres_orcos( isengard, tope_isengard, plus, personaje_cargar);
      isengard[tope_isengard].fila =FILA_INICIAL_ORCOS;
    }else{
      printf("De acuerdo, luego del siguiente turno podras volver a elegir si deseas colocar una unidad.\n" );
    }
  }else{
    printf("No posees suficiente energia para colocar una unidad, espera un par de turnos hasta que sea posible\n" );
  }
}

void cargar_personajes(juego_t* juego){
  if (juego -> jugador1.bando == ROHAN ) {
    cargar_personajes_rohan ( &juego->jugador1, juego->rohan, juego->cantidad_rohan, juego->plus_rohan );
    cargar_personajes_isengard ( &juego->jugador2, juego->isengard, juego->cantidad_isengard, juego->plus_isengard );
  }else{
    cargar_personajes_rohan ( &juego->jugador2, juego->rohan, juego->cantidad_rohan, juego->plus_rohan );
    cargar_personajes_isengard ( &juego->jugador1, juego->isengard, juego->cantidad_isengard, juego->plus_isengard );
  }
}

void imprimir_matriz(char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL]){
  for (size_t m = 0; m < MAX_TERRENO_COL; m++) {
    for (size_t n = 0; n < MAX_TERRENO_FIL; n++) {
      printf(" %c", terreno [m][n]);
    }printf("\n\n" );
  }
}

void posicionar_personaje(juego_t* juego, personaje_t personaje){
  juego->terreno[personaje.fila][personaje.columna] = personaje.codigo;
  if (personaje.codigo == ELFOS || personaje.codigo == HOMBRES){
    juego->cantidad_rohan ++;
  }else if (personaje.codigo == URUKHAI || personaje.codigo == ORCOS ){
    juego -> cantidad_isengard ++;
  }else{
    juego->terreno[personaje.fila][personaje.columna] = '_';

  }
}
