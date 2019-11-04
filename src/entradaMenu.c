/*
	modulo entradaMenu.c
	Gestion de eventos de menu

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"


/** 			void seleccionMenu( int opcion )

Este procedimiento es llamado por glut cuando ocurre un evento de seleccion de una 
opcion del menu. El parametro contiene el identificador de la opcion
 
 Cuando se anyanden opciones se debe anyadir un case en el switch para esa opcion.
 
 **/
 void seleccionMenu( int opcion )
{
   gluiSetCanvasWindow();
   gluiOutput( "");			// Borra el mensaje actual
   switch ( opcion )
   {   
	case NUEVA_PARTIDA:
		if(nueva_partida==0){
		  nueva_partida=1;
		  game_over = 0;
		}
		else{
		  juego_completado = 0;
		  game_over = 0;
		  pausa = 0;
		  puntuacion = 0;
		  lineas_completadas = 0;
		  velocidad_caida = 500; //(ms)
		  flecha_abajo = 0;
		  // Asignamos la primera pieza
		  pieza_siguiente = piezas[0];
		  
		  InicializaMatriz();
  
		  NuevaPieza();
		}
	break;
   case PRINCIPAL:
		// Cambiamos parametros de la camara
		view_rotx=-15.0;	// Angulos de rotacion 
		view_roty=0;
		view_rotz=0.0;
		d=100.0;

		x_camara=0;		// Posicion de la camara
		y_camara=6;
		z_camara=20;
		
   	estado= paseando;
   	VISTA_PERSPECTIVA= 1; 			// Fija perspectiva y recalcula proyeccion
		glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
		fijaProyeccion();
		gluiOutput( "Se ha cambiado a Vista Principal");	// Muestra mensaje en interfaz
	break;
	case OBLICUA:
		// Cambiamos parametros de la camara
		view_rotx=40.0;	// Angulos de rotacion 
		view_roty=-50.0;
		view_rotz=-20.0;
		d=100.0;

		x_camara=15;		// Posicion de la camara
		y_camara=25;
		z_camara=10;
		
   	estado= paseando;
   	VISTA_PERSPECTIVA= 1; 			// Fija perspectiva y recalcula proyeccion
		glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
		fijaProyeccion();
		gluiOutput( "Se ha cambiado a Vista Oblicua");	// Muestra mensaje en interfaz
	break;
   case DESDEARRIBA: 
   	estado = vistaArriba; 
   	VISTA_PERSPECTIVA= 0; 			// Fija proyeccion paralela y recalcula proyeccion
		glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
		fijaProyeccion();
		gluiOutput( "Se ha cambiado a Vista Aerea "); 	// Muestra mensaje en interfaz
   break;
   case SALIR:
   	  exit(0);      // Salir del programa
   }
	gluiPostRedisplay(); 	// Si se ha modificado algo que cambia el estado del
				// modelo se debe actualizar la pantalla
}


/** 

Crea el menu.pop-up de la ventana grafica

Este procedimiento debe llamarse para crear el menu pop-up de glut (normalmente al inicializar el
programa).
 
Para anyadir opciones al menu anyadir una llamada glutAddMenuEntry e incluir valores del tipo enumerado en la declaracion de opciones_menu.

 **/
void CreaMenu()
{

   	menu = glutCreateMenu( seleccionMenu );
    	
    	glutAddMenuEntry("Vista Principal",PRINCIPAL);		// y el identificador que se devuelve al usarla
		glutAddMenuEntry("Vista Oblicua",OBLICUA);
		glutAddMenuEntry("Vista Aerea",DESDEARRIBA);	// Cada llamada lleva el nombre de la oopcion 
   	glutAddMenuEntry( "Exit", SALIR );

   	glutAttachMenu( GLUT_RIGHT_BUTTON );	// Indica que el boton derecho abre el menu.

}

