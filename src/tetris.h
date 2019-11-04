/*
	modulo tetris.h
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>


#ifndef __tetrisH__ // Para evitar doble inclusion
#define __tetrisH__


/* El siguiente bloque comprueba que modulo se esta compilando de forma que las variables
globales solo se inicialicen cuando se compile el modulo "modelo.c"
*/

#ifndef __modelo__ // No esta compilando modelo, las variables globales son extern

#define ambito extern

#else // Esta compilando  modelo, las variables globales no son extern (se les asigna memoria)

#define ambito

#endif

// ====================================== DEFINES ========================================================


/**
Definicion de identificadores de colores. Los valores se corresponden con la
posicion en la matriz color.
**/
#define amarillo 0
#define gris 1
#define rojo 2
#define marron 3
#define celeste 4
#define naranja 5
#define verde 6
#define colorfeedback 7
#define azul 8
#define violeta 7


#define MAXNAMES 10
#define MAXOBJETOS 10

#define NGruas 20
#define NCajones 50


//========================================  ESTRUCTURAS DE DATOS ==========================================

typedef enum {neutro,paseando,vistaArriba} ESTADO;

typedef enum{SALIR, DESDEARRIBA, PRINCIPAL, OBLICUA, NUEVA_PARTIDA} opciones_menu;  	// Ident. de opciones del menu

//================================================  VARIABLES  =============================================

ambito float color[9][4];	// Paleta de colores (se inicializa en initModel)	

ambito int estado;		// Estado en el que se encuentra el programa

ambito int menu;     		// Identificador del menu glut

// ---Matriz Tablero---

ambito int fil;			///< Filas de la matriz.
ambito int col;			///< Columnas de la matriz.
ambito int **m_ptrfilas;	///< Vector de datos.

// ---Pieza---

typedef struct{
  int **matriz;					// Matriz para almacenar las celdas de la pieza.
  int fil;
  int col;
  int tipo;							// Tipo de pieza. Valores de 0 a 4.
  int rotada;						// Indica el nivel de rotacion de la pieza.
} Pieza;

typedef struct{
  Pieza pieza;						// Pieza en juego.
  int x1;							// Posicion X izquierda.
  int y1;							// Posicion Y superior.
  int x2;							// Posicion X derecha.
  int y2;							// Posicion Y inferior.
			
  float posX, posY;				// Posiciones para el dibujado grafico
} PiezaEnJuego;

// Vector de piezas definidas
ambito Pieza piezas[5];

// Datos de la pieza en juego
ambito PiezaEnJuego pieza_en_juego;

// Pieza siguiente ha entrar en juego
ambito Pieza pieza_siguiente;

// Flag que indica si hemos empezado o no una nueva partida
ambito nueva_partida;

// Flag que indica si hemos empezado perdido
ambito game_over;

// Flag que indica si hemos empezado perdido
ambito juego_completado;

// Nivel actual del jugador
ambito nivel;

// Puntuacion total del jugador
ambito puntuacion;

// Lineas totales completadas por el jugador
ambito lineas_completadas;

// Velocidad de caida de las piezas
ambito velocidad_caida;

// Flag que avisa si se ha activado la pausa
ambito pausa;

// Flag para saber si se ha pulsado S
ambito flecha_abajo;

// Flag que avisa si la pieza esta cargada (cerrojo para proteger secciones criticas)
ambito pieza_cargada;

// Guarda la posicion del raton para controlar el movmiento horizontal de las piezas
ambito pos_raton_X;

//================================================  FUNCIONES MATRIZ TABLERO  =============================================

// Inicializa la matriz que representa al tablero de juego
void InicializaMatriz();

void SetMatrizTablero (int i, int j, int v);

int GetMatrizTablero (int i, int j);

// Elimina e intercambia filas de la matriz
void EliminaIntercambia(int fila);

//================================================  FUNCIONES PIEZA  =============================================

void SetMatrizPieza (int numero_pieza, int i, int j, int v);

int GetMatrizPieza (int numero_pieza, int i, int j);

void SetMatrizPiezaJuego (int i, int j, int v);

int GetMatrizPiezaJuego (int i, int j);

// Inicializa las matriz de las piezas definidas en el juego
void InicializaPiezas();

// Funcion que lanza una nueva pieza
void NuevaPieza();

// Funcion que rota la pieza en juego
void RotarPieza();

// Comprueba si la pieza en juego choca
int CheckColisiones(int movimiento);

// Baja la pieza en juego
int BajaPieza();

// Mueve la pieza horizontal
void MoverPieza(int sentido);

// Elimina las lineas completadas
int LimpiaLineas();

// Añade las piezas caidas a la matriz del tablero
void AniadeAcumulaciones();

//================================================  FUNCIONES CAMARA  =============================================
/**

Angulos de rotacion de la camara.

**/

ambito float view_rotx, view_roty, view_rotz;

/**

Indica el tipo de proyeccion que se esta realizando. Si esta a uno 
se hace proyeccion perspectiva, en caso contrario se hace paralela.

**/
ambito int VISTA_PERSPECTIVA;

/**

Tamanyo para la ventana del mundo en proyeccion paralela.

**/
ambito float ventanaMundoParalela;

/**

Coordenadas x,y de la esquina inferior de la ventana del mundo en vista
paralela.
 
**/
ambito float origenXVentanaMundoParalelo;
ambito float origenYVentanaMundoParalelo;

/**

Distancia de la camara al centro de coordenadas del modelo.

**/
ambito float d;

ambito float x_camara,y_camara,z_camara;

ambito float anchoVentana,altoVentana;

// ============================================== FUNCIONES MODELO.C ================================================

/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja( void );

/**
	Funcion de fondo
**/
void idle();

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel();

// entradaTeclado.c

/**	
	Funcion de captura de eventos pulsacion de tecla correspondiente a caracter alfanumerico
	K: codigo ascii del caracter
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void letra (unsigned char k, int x, int y);

/**
	Funcion de captura de eventos pulsacion de caracteres especiales y de control
	K: codigo del control pulsado (se definen como constantes en glut.h)
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void especial(int k, int x, int y);

// mouse.c

/**
	Funcion de captura de eventos de pulsacion de botones del raton
	boton: identificador del boton pulsado
	estado: estado del boton
	x: posicion del cursor en coordenadas de pantalla
	y: posicion del cursor en coordenadas de pantalla
**/
void clickRaton( int boton, int pulsando, int x, int y );

/**
	Funcion de captura de eventos de desplazamiento de raton
	x: posicion del cursor en coordenadas de pantalla
	y: posicion del cursor en coordenadas de pantalla
**/
void RatonMovido( int x, int y );

// entradaMenu.c

void seleccionMenu( int opcion );
// Este procedimiento es llamado por el sistema cuando se selecciona una
// opcion del menu glut. El parametro contiene el identificador de la opcion

 
void CreaMenu();
// Este proc. se usa para definir el menu glut. Se llama desde main.


// estructura.c

void caja( float a, float b, float m);

// =========================== Funciones de dibujado de piezas ==========================================

void I(int pos);

void L(int pos);

void CUBO();

void S(int pos);

void T(int pos);

// visual.c

void fijaProyeccion();

void transformacionVisualizacion();

void inicializaVentana(GLsizei ancho,GLsizei alto);

void creaIU();

#endif
#undef ambito

