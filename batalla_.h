#ifndef __BATALLA_H__
#define __BATALLA_H__
#include <stdbool.h>


#define MAX_TERRENO_FIL 10
#define MAX_TERRENO_COL 10
#define MAX_PERSONAJES 60

const int LLEGADAS_GANAR = 5;
const int LLEGADAS_GANAR = 5;
const int ENERGIA_HOMBRES_ORCOS = 3;
const int ENERGIA_ELFOS_URUKHAI = 8;
const int UNIDADES_INICIALES = 3;

typedef struct jugador{
  char bando;
  int intensidad;
  int energia;
  int plus;
  // Puede haber mas
}jugador_t;

typedef struct personaje {
	char codigo;
	int vida;
	int ataque;
	int fila;
	int columna;
  bool muerto;
  bool llego;
	// Pueden agregar los campos que deseen
} personaje_t;

typedef struct juego{
	char terreno[MAX_TERRENO_FIL][MAX_TERRENO_COL];
	personaje_t rohan[MAX_PERSONAJES];
	int cantidad_rohan;
	int llegadas_rohan;
	int plus_rohan;
	personaje_t isengard[MAX_PERSONAJES];
	int cantidad_isengard;
	int llegadas_isengard;
	int plus_isengard;
	// Pueden agregar los campos que deseen
	jugador_t jugador1;
	jugador_t jugador2;
}juego_t;

/*
 * Inicializará todos los valores del juego, dejándolo en un estado
 * inicial válido.
 */
void inicializar_juego(juego_t* juego);

/*
 * Recibirá un personaje, con todos sus campos correctamente cargados y
 * lo dará de alta en el juego, sumándolo al vector correspondiente,
 * posicionándolo también en la matriz.
 */
void posicionar_personaje(juego_t* juego, personaje_t personaje);

/*
 * Realizará la jugada del personaje del bando recibido que
 * se encuentra en la posición posicion_personaje.
 * Se moverá o atacará dependiento lo que corresponda.
 * Actualizará el juego según los efectos del movimiento del
 * personaje, matar rivales, actualizar la matriz, restar vida, etc.
 */
void jugar(juego_t* juego, char bando, int posicion_personaje);

/*
*
*/
void cargar_personajes( juego_t* juego);

/*
*
*/
void imprimir_matriz(char terreno [MAX_TERRENO_FIL][MAX_TERRENO_COL]);

#endif /* __BATALLA_H__ */
