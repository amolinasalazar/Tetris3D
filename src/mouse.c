/*
	modulo mouse.c
	Gestion de eventos de raton
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"

/**	 void clickRaton( int boton, int estado, int x, int y )

Procedimiento para gestionar los eventos de pulsacion de los botones del raton.

Argumentos:

boton: Codigo glut del boton que ha manipulado el usuario.

estado: Estado en el que esta el boton que se ha pulsado.

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

 void clickRaton( int boton, int pulsando, int x, int y ){
	
	// Si presionamos el boton izquierdo, rotamos la pieza
	if(boton==GLUT_LEFT_BUTTON && pulsando == GLUT_DOWN){
		if(pausa==0)
		  RotarPieza();
	}
	
	// Si presionamos el boton central, hacemos que la pieza caiga
	if(boton==GLUT_MIDDLE_BUTTON && pulsando == GLUT_DOWN){
		if(pausa==0)
		  flecha_abajo = 1;
	}
}


/**	void RatonMovido( int x, int y )

Procedimiento para gestionar los eventos de movimiento del raton.

Argumentos:

x,y: Posicion, en coordenadas de pantalla, en que se encuantra el cursor.

**/

void RatonMovido( int x, int y ){
  
  // Si movemos el raton a la derecha o a la izquierda, movemos la pieza actual con el
  if(x > pos_raton_X+15){
	 if(pausa==0)
		MoverPieza(1);
	 
	 pos_raton_X += 15;;
  }
  
  if(x < pos_raton_X-15){
	 if(pausa==0)
		MoverPieza(0);
	 
	 pos_raton_X -= 15;;
  }
}
