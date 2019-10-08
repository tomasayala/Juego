#include <stdio.h>
#include "perfil_.h"
#include <stdlib.h>
#include <time.h>
#include "batalla_.h"
#include <stdbool.h>

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
const int FILA_LLEGADAS_ROHAN = 0;
const int FILA_LLEGADAS_ISENGARD = 9;  /* Cambiar si cambia el numero maximo de MAX_TERRENO_FIL (MAX_TERRENO_FIL -1) */
const int VIDA_ELFOS_URUKHAI = 200;
const int VIDA_HOMBRES_ORCOS = 100;
const int SIN_VIDA = 0;
const int ATAQUE_ELFOS_URUKHAI = 10;
const int ATAQUE_HOMBRES_ORCOS = 50;
const int RANGO_ARQUEROS_MANHATTAN = 3;

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
  jugador1->gano = false;
  jugador2->gano = false;
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
    rohan[i].muerto = false;
    rohan[i].llego = false;
  }for (size_t j = 0; j < tope_isengard; j++) {
    isengard [j]. codigo = URUKHAI;
    isengard [j]. vida = VIDA_ELFOS_URUKHAI - plus_isengard;
    isengard [j]. ataque = ATAQUE_ELFOS_URUKHAI + plus_isengard;
    isengard [j]. fila = rand() % RANGO_ALEATORIO_INICIALES_FILAS + FILA_MINIMA_URUKHAI;
    isengard [j]. columna = rand() % RANGO_ALEATORIO_INICIALES_COLUMNAS;
    isengard[j].muerto = false;
    isengard[j].llego = false;
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

void validar_filas_columnas(  )

 void cargar_hombres_orcos(personaje_t unidades[MAX_PERSONAJES], int tope_unidades, int plus, char personaje_cargar){
   unidades[tope_unidades]. codigo = personaje_cargar;
   unidades[tope_unidades]. codigo = personaje_cargar;
   unidades[tope_unidades]. vida = VIDA_HOMBRES_ORCOS - plus;
   unidades[tope_unidades]. ataque = ATAQUE_HOMBRES_ORCOS + plus;
   unidades[tope_unidades]. muerto = false;
   unidades[tope_unidades]. llego = false;
   printf("En que columna arrancara la infateria? Elija un numero del 0 al 9 para elegir su columna, siendo 0 la 1era y 9 la ultima\n");
   scanf("%i",&unidades[tope_unidades].columna );
 }

 void cargar_elfos_urukhai (personaje_t unidades[MAX_PERSONAJES], int tope_unidades, int plus, char personaje_cargar){
  unidades[tope_unidades]. codigo = personaje_cargar;
  unidades[tope_unidades]. vida = VIDA_ELFOS_URUKHAI - plus;
  unidades[tope_unidades]. ataque = ATAQUE_ELFOS_URUKHAI + plus;
  unidades[tope_unidades]. muerto = false;
  unidades[tope_unidades]. llego = false;
  ingresar_filas_columnas( &unidades[tope_unidades].fila, &unidades[tope_unidades].columna );
  validar_filas_columnas( unidades[tope_unidades].codigo, &unidades[tope_unidades].fila, &unidades[tope_unidades].columna );
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


bool esta_muerto(int vida){
if (vida <= SIN_VIDA){
  return true;
}else
  return false;
}
int modulo(int numero){
  if (numero < 0)
  return -numero;
}

bool rango_amplio( int fila_atacante, int columna_atacante, int fila_objetivo, int columna_objetivo ){
  int diferencia_fila = fila_atacante - fila_objetivo;
  int diferencia_columna = columna_atacante - columna_objetivo;
  if ( ( modulo(diferencia_fila) + modulo (diferencia_columna)) <= 3 )
    return true;
  else
    return false;
}

bool rango_corto(int fila_atacante, int columna_atacante, int fila_objetivo, int fila_objetivo){

}

void evaluar_llegadas(int* llegadas_rohan, int* llegadas_isengard, personaje_t* personaje ){
  if (personaje->codigo == HOMBRES){
    if(personaje->fila == FILA_LLEGADAS_ROHAN &&  personaje->llego = false){
      personaje->llego = true;
      personaje->ataque = 0;
      personaje->vida = 0;
      llegadas_rohan++;
    }
  }else{
    if(personaje->fila == FILA_LLEGADAS_ISENGARD &&  personaje->llego = false){
      personaje->llego = true;
      personaje->ataque = 0;
      personaje->vida = 0;
      llegadas_isengard++;
    }
  }
}

void morir(personaje_t* caido, char terreno){
  caido.muerto = true;
  caido.ataque = 0;
  caido.vida = 0;
  terreno[caido.fila][caido.columna] = '_'
}

void atacar_elfo_urukhai ( personaje_t atacante, personaje_t enemigos[MAX_PERSONAJES],int tope_enemigos, char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL] ){
  bool en_rango;
  if( atacante.codigo == ELFOS ){
    for (int i =0; i <tope_enemigos; i++){
      enemigos[i].muerto = esta_muerto(enemigos[i].vida);
      en_rango = rango_amplio( atacante.fila, atacante.columna, enemigos[i].fila, enemigos[i].columna);
      if (enemigos[i].muerto = false && en_rango = true){
        enemigos[i].vida= enemigos[i].vida - atacante.ataque;
      }if(enemigos[i].vida <= SIN_VIDA){
          morir(&enemigos[i], terreno);
        }
      }
    }else{
      for(int i = 0; i <tope_enemigos; i++){
        enemigos[i].muerto = esta_muerto(enemigos[i].vida);
        en_rango = rango_amplio( atacante.fila, atacante.columna, enemigos[i].fila, enemigos[i].columna);
        if (enemigos[i].muerto = false && en_rango = true){
          enemigos[i].vida= enemigos[i].vida - atacante.ataque;
        }if(enemigos[i].vida <= SIN_VIDA){
            morir(&enemigos[i], terreno);
        }
      }
    }
}

void mover_hombres_orcos( char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL], personaje_t* personaje ){
  if(personaje->codigo == HOMBRES){
    personaje->fila--;
    if(terreno[personaje->fila][personaje->columna] == ELFOS ){
      personaje->fila --;
    }
  }else{
    personaje->fila ++;
    if(terreno[personaje->fila][personaje->columna] == URUKHAI){
      personaje->fila ++;
    }
  }
}

void atacar_mover_hombres_orcos( juego_t* juego, personaje_t* atacante ){
  bool en_rango = false;
  int i = 0;
  int j = 0;
  if(atacante.codigo == HOMBRES){
    while ( ( (juego->isengard[i].muerto = false) && (en_rango = false) ) || i < juego->cantidad_isengard ){
      juego->isengard[i].muerto = esta_muerto(juego->isengard[i].vida);
      en_rango = rango_corto( atacante.fila, atacante.columna, juego->isengard[i].fila, juego->isengard[i].columna );
      i++;
    }
    if ( juego->isengard[i].muerto = false && en_rango = true ){
      juego->isengard[i].vida = juego.isengard[i].vida - atacante.ataque;
      if (juego->isengard[i].vida <= SIN_VIDA){
        morir(&juego->isengard[i], juego.terreno);
      }
    }else{
      mover_hombres_orcos(juego.terreno, &atacante);
    }
  }else{
    while ( ( (juego->rohan[i].muerto = false) && (en_rango = false) ) || i < juego->cantidad_rohan ){
      juego->rohan[i].muerto = esta_muerto(juego->rohan[i].vida);
      en_rango = rango_corto( atacante.fila, atacante.columna, juego->rohan[i].fila, juego->rohan[i].columna );
      i++;
    }
    if ( juego->rohan[i].muerto = false && en_rango = true ){
      juego->rohan[i].vida = juego.rohan[i].vida - atacante.ataque;
      if (juego->rohan[i].vida <= SIN_VIDA){
        morir(&juego->rohan[i], juego.terreno);
      }
    }else{
      mover_hombres_orcos(juego.terreno, &atacante);
    }
  }
}

void jugar(juego_t* juego, char bando, int posicion_personaje){
  if(bando== ROHAN){
    juego->rohan[posicion_personaje].muerto = esta_muerto(juego.rohan[posicion_personaje].vida);
    if (juego->rohan[posicion_personaje].muerto = false && juego->rohan[posicion_personaje].codigo == ELFOS){
      atacar_elfo_urukhai( juego->rohan[posicion_personaje], juego->isengard, juego->cantidad_isengard, juego.terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL] );
    }else if(juego.rohan[posicion_personaje].muerto = false){
      atacar_mover_hombres_orcos( &juego, &juego->rohan[posicion_personaje]);
      evaluar_llegadas( &juego->llegadas_rohan, &juego->llegadas_isengard, &juego->rohan[posicion_personaje] );
    }
  }else{
    juego.isengard[posicion_personaje].muerto = esta_muerto( juego->isengard[posicion_personaje].vida );
    if (juego->isengard[posicion_personaje].muerto = false && juego->isengard[posicion_personaje].codigo == URUKHAI){
      atacar_elfo_urukhai ( juego->isengard[posicion_personaje], juego->rohan );
    }else if (juego->isengard[posicion_personaje].muerto = false){
      atacar_mover_hombres_orcos(&juego, &juego->isengard[posicion_personaje]);
      evaluar_llegadas( &juego->llegadas_rohan, &juego->llegadas_isengard, &juego->isengard[posicion_personaje] );
    }
  }
}
