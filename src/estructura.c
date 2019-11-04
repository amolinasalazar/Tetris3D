/*
	modulo  estructura.c
	Dibujo de elementos geometricos
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL
#include "tetris.h"


/**
 Seccion de los perfiles para la estructura
**/
#define seccion 0.1 

/**
Calcula el modulo del vector (x,y,z)
**/

float modulo(float x,float y,float z)
{
return sqrt(x*x+y*y+z*z);
}


/** 	void caja( float a, float b, float m)

Construye un paralelepipedo alineado con los ejes de
dimension a x b x m. El objeto se construye en el semiespacio y>=0, con el origen en el
centro de la base. 

**/
void caja( float a, float b, float m)

{
	float x,y,z;
	
	x= a/2;
	z= m/2;
	y = b;

   glShadeModel( GL_FLAT );

   /* Caras transversales */
   glBegin( GL_QUAD_STRIP );{
      glNormal3f( 0.0, 0.0, -1.0 );   /* Vertical hacia atras */

      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );


      glVertex3f( x, y, -z );
      glVertex3f( -x, y, -z );

glNormal3f( 0.0, 1.0, 0.0 );       /* Superior, horizontal */

      glVertex3f( x, y, z );
      glVertex3f( -x, y, z );
glNormal3f( 0.0, 0.0, 1.0 );       /*Vertical delantera*/
      glVertex3f( x, 0, z );
      glVertex3f( -x, 0, z );

glNormal3f( 0.0, -1.0, 0.0 );       /*Inferior */
      glVertex3f( x, 0, -z );
      glVertex3f( -x, 0, -z );  }
    glEnd();

   /* Costados */
   glBegin( GL_QUADS );{
      glNormal3f( 1.0, 0.0, 0.0 );
      glVertex3f( x, 0, -z );
      glVertex3f( x, y, -z );
      glVertex3f( x, y, z );
      glVertex3f( x, 0, z ); }
   glEnd();


   glBegin( GL_QUADS );{
      glNormal3f( -1.0, 0.0, 0.0 );
      glVertex3f( -x, 0, -z );
      glVertex3f( -x, 0, z );
      glVertex3f( -x, y, z );
      glVertex3f( -x, y, -z ); }
   glEnd();
}

// ----------------------- Piezas del Juego -------------------------- //

void I(int pos){
  
  if(pos == 0){
	 // HORIZONTAL
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
	 //glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  
  else{
	 // VERTICAL
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[rojo]);
	 glTranslatef(0,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
}

void L(int pos){
  if(pos == 0){
	 // TUMBADA PICO ABAJO
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	 //glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  else if(pos == 1){
	 // DE PIE L
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	 glTranslatef(1,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(-1,0,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  else if(pos == 2){
	 // TUMBADA PICO ARRIBA
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	 //glTranslatef(-1,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  else{
	 // DE PIE EN PICO
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[violeta]);
	 glTranslatef(1,1,0);
	 caja(1,1,1);

	 glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
}

void CUBO(){
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[azul]);
  //glTranslatef(0,0,0);
  caja(1,1,1);

  glTranslatef(1,0,0);
  caja(1,1,1);

  glTranslatef(0,-1,0);
  caja(1,1,1);

  glTranslatef(-1,0,0);
  caja(1,1,1);
  glPopMatrix();
}

void S(int pos){
  if(pos == 0){
	 // TUMBADA
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
	 //glTranslatef(-1,1,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  else{
	 // DE PIE S
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[amarillo]);
	 glTranslatef(1,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
}

void T(int pos){
  
  if(pos==0){
	 // T ABAJO
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde]);
	 //glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,-1,0);
	 caja(1,1,1);

	 glTranslatef(1,1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  
  else if(pos==1){
	 // DE PIE FORMA 3
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde]);
	 //glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-2,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  
  else if (pos==2){
	 
	 // TUMBADA PICO ARRIBA
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde]);
	 //glTranslatef(-1,0,0);
	 caja(1,1,1);

	 glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,1,0);
	 caja(1,1,1);

	 glTranslatef(1,-1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
  
  else{
	 // DE PIE FORMA E
	 glPushMatrix();
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[verde]);
	 //glTranslatef(1,0,0);
	 caja(1,1,1);

	 glTranslatef(0,1,0);
	 caja(1,1,1);

	 glTranslatef(0,-2,0);
	 caja(1,1,1);

	 glTranslatef(1,1,0);
	 caja(1,1,1);
	 glPopMatrix();
  }
}
