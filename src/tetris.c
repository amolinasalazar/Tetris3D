/*
	modulo tetris.c
	Programa principal
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"



/*=================================================*/ 

/**	int main( int argc, char *argv[] )	
	Programa principal.
	
	Inicializa glut y openGL
	Crea la ventana X
	Inicializa las variables globales
	Crea la interfaz de usuario
	lanza los gestores de eventos	
**/

int main( int argc, char *argv[] )
{
// Inicializa glu y openGL
   glutInit( &argc, argv );

// Crea una ventana X para la salida grafica en la posicion 0,0 con tamaño 600x600, con colores RGB-alfa, con doble buffer, y 
// buffer de profundidad
   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 600, 600 );
   glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
   gluiCreateWindow("Alejandro Molina Salazar. Curso 2011/12");

// Inicializa las variables globales
   initModel();

// Crea la interfaz de usuario
   creaIU();

// Inicializa las funciones de dibujo y cambio de tamanyo de la ventana X
   glutDisplayFunc( Dibuja );
   glutReshapeFunc( inicializaVentana );

// FUNCIONES DE INTERACCION
	
	// Teclado
   glutKeyboardFunc(letra);
   glutSpecialFunc(especial);
	
   // Raton
   glutMouseFunc( clickRaton );
   glutPassiveMotionFunc( RatonMovido );

// Funcion de fondo
   glutTimerFunc(200,idle,0);

// Crea el menu pop-up
   CreaMenu();

// Inicializa parametros de openGL
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable( GL_LIGHTING );
   glEnable( GL_LIGHT0 );

// Lanza el gestor de eventos de glut
   glutMainLoop();
   return 0;
}
