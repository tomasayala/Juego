#include <stdio.h>

const int MAXIMO_SIGNOS_ZODICACO = 12;
const int ARIES = 1;
const int TAURO = 2;
const int GEMINIS = 3;
const int CANCER = 4;
const int LE0 = 5;
const int VIRGO = 6;
const int LIBRA = 7;
const int ESCORPIO = 8;
const int SAGITARIO = 9;
const int CAPRICORNIO = 10;
const int ACUARIO = 11;
const int PISCIS = 12;
const char DRAMA = 'D';
const char ACCION = 'A';
const char TERROR = 'T';
const char COMEDIA = 'C';
const int MAXIMO_DE_MALDADES = 99;
const int MAXIMO_MASCOTAS = 5;
const int TIERRA = 1;
const int AGUA = 2;
const int AIRE = 3;
const int FUEGO = 4;
const char OFENSIVO = 'I'; // Ofensivo por Isengrad
const char DEFENSIVO = 'R'; // Defensivo por Rohan
const int LIMITE_NIVEL_1_DEFENSIVO = 9;
const int LIMITE_NIVEL_2_DEFENSIVO = 19;
const int LIMITE_NIVEL_3_DEFENSIVO = 29;
const int LIMITE_NIVEL_4_DEFENSIVO = 39;
const int LIMITE_MALDADES_DEFENSIVO = 49;
const int LIMITE_NIVEL_1_OFENSIVO = 59;
const int LIMITE_NIVEL_2_OFENSIVO = 69;
const int LIMITE_NIVEL_3_OFENSIVO = 79;
const int LIMITE_NIVEL_4_OFENSIVO = 89;

// pre condiciones: Requiere numeros enteros entre el 1 y el 12
// post condiciones: Numero positivo entre 1 y 12 que representa su signo del zodiaco
void preguntar_signo_del_zodiaco (int* signo_del_zodiaco){
  printf(" Por favor elija el numero que corresponda a su signo del zodiaco\n" );
  printf(" 1.Aries\n 2.Tauro\n 3.Geminis\n 4.Cancer\n 5.Leo\n 6.Virgo\n 7.Libra\n 8.Escoprio\n 9.Sagitario\n 10.Capricornio\n 11.Acuario\n 12.Piscis\n" );
  scanf("%i", signo_del_zodiaco );
  while ((*signo_del_zodiaco <= 0) || ( *signo_del_zodiaco > MAXIMO_SIGNOS_ZODICACO  ) ) {
    printf(" Por favor elija el numero que corresponda a su signo del zodiaco\n" );
    printf(" 1.Aries\n 2.Tauro\n 3.Geminis\n 4.Cancer\n 5.Leo\n 6.Virgo\n 7.Libra\n 8.Escoprio\n 9.Sagitario\n 10.Capricornio\n 11.Acuario\n 12.Piscis\n" );
    scanf("%i", signo_del_zodiaco );
  }
}

// Pre: Numeros enteros positivos entre 1 y 12
// Post: Numero entero entre 1 y 4 que representa su elemento del zodiaco
int asignar_elemento_del_zodiaco ( int elemento ){
  int signo_del_zodiaco = 0;
   preguntar_signo_del_zodiaco (&signo_del_zodiaco );
  if ( ( (signo_del_zodiaco == TAURO) || (signo_del_zodiaco == VIRGO) ) || (signo_del_zodiaco == CAPRICORNIO ) ){
    return  TIERRA;
  } else if ( ( (signo_del_zodiaco == CANCER ) || (signo_del_zodiaco == ESCORPIO ) ) || (signo_del_zodiaco == PISCIS ) ) {
    return AGUA;
  } else if ( ( (signo_del_zodiaco == GEMINIS ) || (signo_del_zodiaco == LIBRA ) ) || (signo_del_zodiaco == ACUARIO ) ) {
    return AIRE;
  } else{
    return FUEGO;
  }
}

// Pre:  Un caracter en mayuscula que sea A, C, D y T
//Post: Asigna unos de los caracteres de las pre al main
void preguntar_genero_favorito_cine (char* genero){
  printf("Por favor elija su genero de cine favorito, utilice por favor una letra en mayuscula en una de las opciones que se indica.\n " );
    printf("A. Accion\n C. Comedia\n D. Drama\n T. Terror\n" );
  scanf (" %c", genero );
  while ( ( (*genero != DRAMA) && ( *genero != ACCION ) )  && ( ( *genero != TERROR ) &&  ( *genero != COMEDIA ) ) ) {
      printf("Por favor elija su genero de cine favorito, utilice por favor una letra en mayuscula en una de las opciones que se indica\n" );
      printf("A. Accion\n C. Comedia\n D. Drama\n T. Terror\n" );
      scanf (" %c", genero );
    }
  }

// Pre: Numero entero positivos mayores que 0 y menores que 100
// Post : Asigna el numero a una variable del main
void preguntar_maldades_del_mes (int* maldades){
  printf("Por favor ingrese el numero de maldades que ha hecho este mes\n" );
  scanf("%i", maldades );
  while ((*maldades < 0) || ( *maldades > MAXIMO_DE_MALDADES  ) ) {
    printf("Por favor vuelva a ingresar un numero de maldades, si su numero de maldades es mayor que 100 ingrese 99.\n" );
    scanf("%i", maldades );
  }
}

// Pre: Numero positivo mayores que 0
// Post: Numero postivio entre 1 y 5
void preguntar_cantidad_mascotas (int* mascotas){
  printf("Por favor ingrese el numero de mascota que posee\n" );
  scanf("%i", mascotas );
  while (*mascotas < 0 || *mascotas > MAXIMO_MASCOTAS ) {
    printf("Por favor ingrese cuantas mascotas, tiene sino tiene ninguna por favor ingrese 0, si tiene mas de 5, por favor ingrese 5\n" );
    scanf("%i", mascotas );
  }
}

void reasignar_parametros ( int* elemento, char* cine, int* maldades, int* mascotas ){
  printf("Esta siendo muy dificil asignarle su bando, por favor vuelva a responder las preguntas. \n" );
  *elemento = asignar_elemento_del_zodiaco( *elemento);
  preguntar_genero_favorito_cine ( cine);
  preguntar_maldades_del_mes ( maldades);
  preguntar_cantidad_mascotas( mascotas);

}

// Pre: Un numero entero entre 1 y 4; Un caracter que sea A,C,D,T; Numero entero entre 0 y 100
// Post : Un numero entero que es  100 o 200
char asignar_bando (int elemento, char cine, int* maldades, int* mascotas ){
  char bando = 'A';
  if ( ( ( (elemento == AIRE) || (elemento == FUEGO) ) && ( (cine == TERROR) || (cine == COMEDIA) )  ) && (*maldades > LIMITE_MALDADES_DEFENSIVO) ){
    return OFENSIVO;
  } else if (  ( ( (elemento == TIERRA) || (elemento == AGUA) ) && ( (cine == ACCION) || (cine== DRAMA) )  ) && (*maldades <= LIMITE_MALDADES_DEFENSIVO) ){
    return DEFENSIVO;
  } else{
        reasignar_parametros ( &elemento, &cine, maldades, mascotas  );
        bando =  asignar_bando (elemento, cine, maldades, mascotas);
      }
      if (bando == DEFENSIVO) {
        return DEFENSIVO;
      } else {
        return OFENSIVO;
      }
  }

// Pre: Un numero entero positivo entre 0 y 100; Un numero entero positivo entre 1 y 5
// Post: Un numero positivo entre 2 y 10
int asignar_intesidad (int maldades, int mascotas){
  int intensidad;
  if ( ( maldades <= LIMITE_NIVEL_1_DEFENSIVO )|| ( maldades > LIMITE_MALDADES_DEFENSIVO && maldades <= LIMITE_NIVEL_1_OFENSIVO ) ) {
    maldades = 1;
  } else if( (maldades >LIMITE_NIVEL_1_DEFENSIVO && maldades <= LIMITE_NIVEL_2_DEFENSIVO) || ( maldades > LIMITE_NIVEL_1_OFENSIVO && maldades <= LIMITE_NIVEL_2_OFENSIVO )  ){
    maldades = 2;
  } else if ( ( maldades > LIMITE_NIVEL_2_DEFENSIVO && maldades <= LIMITE_NIVEL_3_DEFENSIVO ) || ( maldades > LIMITE_NIVEL_2_OFENSIVO && maldades <= LIMITE_NIVEL_3_OFENSIVO ) ){
    maldades = 3;
  } else if ( ( maldades > LIMITE_NIVEL_3_DEFENSIVO && maldades <= LIMITE_NIVEL_4_DEFENSIVO ) || ( maldades > LIMITE_NIVEL_3_OFENSIVO && maldades <= LIMITE_NIVEL_4_OFENSIVO ) ) {
    maldades = 4;
  } else {
    maldades = 5;
  }
  intensidad = maldades + mascotas;
  return intensidad;
}

// Pre: Un numero entero positvo que es 100 o 200; Un numero positvo entre 2 y 10
// Post: Un mensaje que indica el bando y la intensidad.
void mostrar_bando_e_instensidad (int bando, int intensidad ){
  if ( bando == DEFENSIVO ){
    printf("Debido a su espíritu defensivo (nivel %i) usted luchará codo a codo con Aragorn , esperamos lo haga con honor. \n", intensidad );
  } else{
    printf("Debido a su poder ofensivo (nivel %i) usted luchará para las fuerzas de Sauron, esperamos que le demuestre al mundo el poder del señor oscuro \n", intensidad );
  }
}

void perfil ( char * tipo , int * intensidad ){
  int elemento_zodiaco = 0;
  char genero_cine_favorito;
  int maldades_del_mes;
  int cantidad_mascotas;
  elemento_zodiaco = asignar_elemento_del_zodiaco(elemento_zodiaco);
  preguntar_genero_favorito_cine (&genero_cine_favorito);
  preguntar_maldades_del_mes (&maldades_del_mes);
  preguntar_cantidad_mascotas (&cantidad_mascotas);
  *tipo = asignar_bando ( elemento_zodiaco, genero_cine_favorito, &maldades_del_mes, &cantidad_mascotas );
  *intensidad = asignar_intesidad ( maldades_del_mes, cantidad_mascotas );
  mostrar_bando_e_instensidad ( *tipo, *intensidad );
}
