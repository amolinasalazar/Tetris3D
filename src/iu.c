/*
	modulo iu.c
	Gestion de interfaz de usuario (menus de persiana)
	*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"


/**	void  creaIU()

	Define la interfaz. Creando los menus de persianas e iconos

**/

void  creaIU(){
// ==================== Toolbar
  gluiCreateToolbar();					// Crea el toolbar
  gluiCreateMenu("Jugar", seleccionMenu );
  gluiAddMenuEntry("Nueva Partida",NUEVA_PARTIDA);
  gluiCreateMenu("Vista", seleccionMenu );
  gluiAddMenuEntry("Principal",PRINCIPAL);
  gluiAddMenuEntry("Oblicua",OBLICUA);
  gluiAddMenuEntry("Aerea",DESDEARRIBA);
  gluiCreateMenu("Salir", seleccionMenu );
  glutAddMenuEntry( "Confirmar", SALIR );		

  gluiCreateCanvas();

}








