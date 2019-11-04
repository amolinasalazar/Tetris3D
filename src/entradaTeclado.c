/*	
	modulo entradaTeclado.c
	Gestion de eventos de teclado
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"

/** 

Imprime en la consola las instrucciones del programa

**/
void printHelp(){
  	
	printf("\n\n ------TetrisGL v1.1------ \n");
  	printf("\n\n ----Alejandro Molina Salazar DNI 76652724A----");
  	printf("\n");
   printf("\n Controles: \n\n");
  	printf("h, H: Imprime informacion de ayuda \n");
	
	printf("\n Teclado: \n\n");
  	printf("w: Rota la pieza\n");
	printf("d: Mueve a la derecha\n");
  	printf("a: Mueve a la izquierda\n");
	printf("s: Hace caer rapido a la pieza\n");
	printf("p: Pausa el juego\n");
	printf("\n Raton: \n\n");
	printf("Mover el raton a la izquierda: Mueve la pieza a la izquierda \n");
	printf("Mover el raton a la derecha: Mueve la pieza a la derecha \n");
	printf("Boton izquierdo: Rota la pieza \n");
	printf("Boton central: Hace caer rapido la pieza \n");
  	printf("\n");
	
	printf("\n Camaras: \n\n");
	printf("1: Camara con perspectiva frontal al tablero. \n");
	printf("2: Camara con perspectiva oblicua hacia el tablero. \n");
  	printf("	En este modo:\n");
  	printf("	+,-: zoom\n");
  	printf("	x,X,z,Z: mueven la camara\n\n");
  	printf("3: Camara con proyeccion paralela mirando desde arriba. \n");
  	printf("	En este modo:\n");
  	printf("	x,X,y,Y,z,Z: mueven la camara\n\n");
	printf("	PgUp, PgDn: mueven la camara hacia delante / atras \n\n");
  	printf("	Teclas de movimiento de cursor: giran la camara\n");
        printf("\n Boton derecho del raton activa el menu");
 
 // Anyade la informacion de las opciones que introduzcas aqui !! 	
	
	printf("\n Escape: Salir");
  	printf("\n\n\n");
}




/* @teclado ---------------------------------------------------------------- */

/** 		void letra (unsigned char k, int x, int y)

Este procedimiento es llamado por el sistema cuando se pulsa una tecla normal
El codigo k es el ascii de la letra

Para anyadir nuevas ordenes de teclado coloca el correspondiente case.

Parametros de entrada:

k: codigo del caracter pulsado

x:

y:

**/

void letra (unsigned char k, int x, int y){
  switch (k) {
  case 'h':
  case 'H':
           printHelp(); // H y h imprimen ayuda
  	break;
  case '1':
	// Cambiamos parametros de la camara
	view_rotx=-15.0;	// Angulos de rotacion 
	view_roty=0;
	view_rotz=0.0;
	d=100.0;

	x_camara=0;		// Posicion de la camara
	y_camara=6;
	z_camara=20;
	 
	VISTA_PERSPECTIVA= 1; 
	estado= paseando;
	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	fijaProyeccion();
	break;
  case '2':
	// Cambiamos parametros de la camara
	view_rotx=40.0;	// Angulos de rotacion 
	view_roty=-50.0;
	view_rotz=-20.0;
	d=100.0;

	x_camara=15;		// Posicion de la camara
	y_camara=25;
	z_camara=10;
	 
	VISTA_PERSPECTIVA= 1; 
	estado= paseando;
	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
	fijaProyeccion();
	break;
  case '3':
	VISTA_PERSPECTIVA= 0;
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	fijaProyeccion();
	 break;
  case 's':
	 if(pausa==0)
		flecha_abajo = 1;
	 break;
  case 'd':
	 if(pausa==0)
		MoverPieza(1);
	 break;
  case 'a':
	 if(pausa==0)
		MoverPieza(0);
	 break;
  case 'w':
	 if(pausa==0)
		RotarPieza();
	 break;
  case 'p':
	 if(pausa == 0)
		pausa = 1;
	 else
		pausa = 0;
	 break;
  case 'x':	// desplaza la camara en X
     if(VISTA_PERSPECTIVA) x_camara -= 5.0;   
     else origenXVentanaMundoParalelo-=5;
    break;
  case 'X':
     if(VISTA_PERSPECTIVA) x_camara += 5.0;   
     else origenXVentanaMundoParalelo+=5;
    break;
  case 'y':	// desplaza la camara en X
     if(VISTA_PERSPECTIVA) y_camara -= 5.0;   
     //else origenXVentanaMundoParalelo-=5;
    break;
  case 'Y':
     if(VISTA_PERSPECTIVA) y_camara += 5.0;   
     //else origenXVentanaMundoParalelo+=5;
    break;
  case 'z':	// desplaza la camara en Z
     if(VISTA_PERSPECTIVA) z_camara -= 5.0;   
     else origenYVentanaMundoParalelo-=5;
    break;
  case 'Z':
    if(VISTA_PERSPECTIVA) z_camara += 5.0;   
    else origenYVentanaMundoParalelo+=5;
    break;
  case '+':             // + Camara mas cerca
    if(ventanaMundoParalela>10) ventanaMundoParalela = ventanaMundoParalela*0.75;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fijaProyeccion();
    break;
  case '-':             // - Camara mas lejos
    ventanaMundoParalela =ventanaMundoParalela* 1.25;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    fijaProyeccion();
    break;
  case 27:  // Escape  Terminar
    exit(0);
    break;  
  default:
    return;
  }
glutPostRedisplay();  	// Algunas de las opciones cambian paramentros
}                       // de la camara. Es necesario actualziar la imagen

/**		void especial(int k, int x, int y)
Este procedimiento es llamado por el sistema cuando se pulsa una tecla
especial. El codigo k esta definido en glut mediante constantes

Parametros de entrada:

k: codigo del caracter pulsado (definido en glut mediante constantes).

x:

y:

**/
void especial(int k, int x, int y)

{
  switch (k) {
  case GLUT_KEY_UP:
    if(VISTA_PERSPECTIVA)     view_rotx += 5.0;   // Cursor arriba + rotacion x
    break;
  case GLUT_KEY_DOWN:
    if(VISTA_PERSPECTIVA)    view_rotx -= 5.0;
    break;
  case GLUT_KEY_LEFT:
    if(VISTA_PERSPECTIVA) {
	view_roty += 5.0;
    	if(view_roty>360) view_roty-=360;
	}
    break;
  case GLUT_KEY_RIGHT:
    if(VISTA_PERSPECTIVA) {
    	view_roty -= 5.0;
    	if(view_roty<0) view_roty+=360;
	}
    break;
  case GLUT_KEY_PAGE_DOWN:  	// Avanza en la direccion en la que se mira
     if(VISTA_PERSPECTIVA) {
     	x_camara+=-sin(3.14159*view_roty/180.0);
     	z_camara+= cos(3.14159*view_roty/180.0);
	}
     break;
  case GLUT_KEY_PAGE_UP:
    if(VISTA_PERSPECTIVA) {
     	x_camara+= sin(3.14159*view_roty/180.0);
     	z_camara+=-cos(3.14159*view_roty/180.0);
	}
     break;
  default:
    return;
  }
   glutPostRedisplay();  // Actualiza la imagen (ver proc. letra)
}
 
