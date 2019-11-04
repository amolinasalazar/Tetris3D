/*
	modulo modelo.c
	Dibujo del modelo
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>                   // Libreria de utilidades de OpenGL

#define __modelo__			// Hace que se asigne memoria a las variables globales

#include "tetris.h"

int COLORGRUA=0;


/**	void initModel()

Inicializa el modelo y de las variables globales

**/

void initModel()
{
/**
	Definicion de los colores usados.
**/
float colores[9][4]={{1,1,0,1.},{0.7,0.7,0.7,1},{1.0,0.3,0.3,1},
   		   {0.7,0.6,0.2,1},{0.2,1.0,1.0,1},{1.0,0.86,0.3,1},
		   {0.4,1,0.4,1.},{1,0.6,1,1.},{0,0,1,1.}};
int i,j;
	for(i=0;i<4;++i)
		for(j=0;j<9;++j)
			color[j][i]=colores[j][i];

	COLORGRUA=0;

/** 

Parametros iniciales de la camara

**/
	view_rotx=-15.0;	// Angulos de rotacion 
	view_roty=0;
	view_rotz=0.0;
	d=100.0;

	x_camara=0;		// Posicion de la camara
	y_camara=6;
	z_camara=20;

	VISTA_PERSPECTIVA=1;	// Flag perspectiva/paralela

	ventanaMundoParalela=25;	// Ventana para proyeccion paralela
	origenXVentanaMundoParalelo=0;	
	origenYVentanaMundoParalelo=0;

/**
Inicializamos parametros del tetris
**/

  // Datos de la matriz tablero
  fil = 20;
  col = 10;
  InicializaMatriz();
  
  // Parametros de configuracion del juego
  nueva_partida = 0;
  game_over = 0;
  juego_completado = 0;
  pausa = 0;
  puntuacion = 0;
  lineas_completadas = 0;
  velocidad_caida = 500; //(ms)
  flecha_abajo = 0;
  pos_raton_X = 280; // desde el centro del tablero

  // Inicializamos las matrices de cada pieza
  InicializaPiezas();
  
  // Asignamos la primera pieza
  pieza_siguiente = piezas[0];
  
  // Cargamos la primera pieza
  NuevaPieza();
}

//================================================  FUNCIONES MATRIZ TABLERO  =============================================

void InicializaMatriz(){
  
  //Variables
	int *aux, i, j;
	
	//Crea un vector de punteros a filas de tamaño fil.
	m_ptrfilas = malloc(fil * sizeof *m_ptrfilas); 
	
	//Crea fil nuevos vectores fila de tamaño col, y asigna los punteros del vector de punteros a fila a cada uno de ellos.
	for(i=0; i<fil; i++){
		aux = malloc(col * sizeof(int));

		m_ptrfilas[i] = aux;
	}
	
	//Asigna los elementos de la matriz a 0.
	for (i=0; i < fil; i++){
		for (j=0; j<col; j++){
			SetMatrizTablero(i,j,0);
		}
	}
}

void SetMatrizTablero (int i, int j, int v){
	int *aux;
	aux = m_ptrfilas[i];
	aux[j] = v;
}

int GetMatrizTablero (int i, int j){
	int *aux;
	int valor;
	aux = m_ptrfilas[i];
	valor = aux[j];
	return valor;
}

void EliminaIntercambia(int fila){
	//Variables.
	int *aux, f, j;
	
	//Elimina la fila indicada por 'fila'
	aux = m_ptrfilas[fila];
	free(aux);
	
	//Desplaza todas las filas por encima de ella (de de 'fila' hasta 0) una posición hacia el final del vector.
	for(f = fila - 1; f >= 0; f--){
		m_ptrfilas[f + 1] = m_ptrfilas[f];
	}
	
	//Crea una nueva fila, asigna a cero sus celdas, y la asigna al puntero del principio del vector.
	aux = malloc(col * sizeof *aux);
	
	for(j = 0; j < col; j++){
		aux[j] = 0;
	}
	
	m_ptrfilas[0] = aux;
}

//================================================  FUNCIONES PIEZA  =============================================

void SetMatrizPieza(int numero_pieza, int i, int j, int v){
	int *aux;
	aux = piezas[numero_pieza].matriz[i];
	aux[j] = v;
}

int GetMatrizPieza(int numero_pieza, int i, int j){
	int *aux;
	int valor;
	aux = piezas[numero_pieza].matriz[i];
	valor = aux[j];
	return valor;
}

void SetMatrizPiezaJuego(int i, int j, int v){
	int *aux;
	aux = pieza_en_juego.pieza.matriz[i];
	aux[j] = v;
}

int GetMatrizPiezaJuego(int i, int j){
	int *aux;
	int valor;
	aux = pieza_en_juego.pieza.matriz[i];
	valor = aux[j];
	return valor;
}

void InicializaPiezas(){
  int N=0, i, j, *aux;
  
	for(N=0; N<5; N++){
		
		// --------------------CUBO--------------------
		if(N == 0){
		  
		  piezas[N].fil = 2;
		  piezas[N].col = 2;
		  
		  //Creamos la matriz para la pieza.
		  piezas[N].matriz = malloc(2 * sizeof *piezas[N].matriz);
		  
		  for(i=0; i<2; i++){
				aux = malloc(2 * sizeof(int));

				piezas[N].matriz[i] = aux;
		  }
		  
		  //Asigna los elementos de la matriz a 0.
		  for (i=0; i < 2; i++){
				for (j=0; j<2; j++){
				  SetMatrizPieza(N,i,j,0);
				}
		  }
		  
		  piezas[N].tipo = N;
		  piezas[N].rotada = 0;
		
		  
		  SetMatrizPieza(N,0,0,color[azul]);
		  SetMatrizPieza(N,1,0,color[azul]);
		  SetMatrizPieza(N,0,1,color[azul]);
		  SetMatrizPieza(N,1,1,color[azul]);
		}
		
		// --------------------L--------------------
		else if(N == 1){	// L

		  piezas[N].fil = 2;
		  piezas[N].col = 3;
		  
		  //Creamos la matriz para la pieza.
		  piezas[N].matriz = malloc(2 * sizeof *piezas[N].matriz);;

		  
		  for(i=0; i<2; i++){
				aux = malloc(3 * sizeof(int));

				piezas[N].matriz[i] = aux;
		  }
		  
		  //Asigna los elementos de la matriz a 0.
		  for (i=0; i<2; i++){
				for (j=0; j<3; j++){
				  SetMatrizPieza(N,i,j,0);
				}
		  }
		  
		  piezas[N].tipo = N;
		  piezas[N].rotada = 0;
		
		  
		  SetMatrizPieza(N,0,0,color[violeta]);
		  SetMatrizPieza(N,0,1,color[violeta]);
		  SetMatrizPieza(N,0,2,color[violeta]);
		  SetMatrizPieza(N,1,2,color[violeta]);
		}		
		// --------------------I--------------------
		else if(N == 2){	// I

		  piezas[N].fil = 1;
		  piezas[N].col = 4;

		  //Creamos la matriz para la pieza.
		  piezas[N].matriz = malloc(1 * sizeof *piezas[N].matriz);

		  for(i=0; i<1; i++){
				aux = malloc(4 * sizeof(int));
				
				piezas[N].matriz[i] = aux;
		  }
		  
		  //Asigna los elementos de la matriz a 0.
		  for (i=0; i<1; i++){
				for (j=0; j<4; j++){
				  SetMatrizPieza(N,i,j,0);
				}
		  }
		  
		  piezas[N].tipo = N;
		  piezas[N].rotada = 0;
		
		  
		  SetMatrizPieza(N,0,0,color[rojo]);
		  SetMatrizPieza(N,0,1,color[rojo]);
		  SetMatrizPieza(N,0,2,color[rojo]);
		  SetMatrizPieza(N,0,3,color[rojo]);
		}
		
		// --------------------S--------------------
		else if(N == 3){	// S

		  piezas[N].fil = 2;
		  piezas[N].col = 3;

		  //Creamos la matriz para la pieza.
		  piezas[N].matriz = malloc(2 * sizeof *piezas[N].matriz);
		  
		  for(i=0; i<2; i++){
				aux = malloc(3 * sizeof(int));
				
				piezas[N].matriz[i] = aux;
		  }
		  
		  //Asigna los elementos de la matriz a 0.
		  for (i=0; i<2; i++){
				for (j=0; j<3; j++){
				  SetMatrizPieza(N,i,j,0);
				}
		  }
		  
		  piezas[N].tipo = N;
		  piezas[N].rotada = 0;
		
		  
		  SetMatrizPieza(N,0,0,color[amarillo]);
		  SetMatrizPieza(N,0,1,color[amarillo]);
		  SetMatrizPieza(N,1,1,color[amarillo]);
		  SetMatrizPieza(N,1,2,color[amarillo]);
		}
		
		// --------------------T--------------------
		else if(N == 4){	// T

		  piezas[N].fil = 2;
		  piezas[N].col = 3;

		  //Creamos la matriz para la pieza.
		  piezas[N].matriz = malloc(2 * sizeof *piezas[N].matriz);
		  
		  for(i=0; i<2; i++){
				aux = malloc(3 * sizeof(int));

				piezas[N].matriz[i] = aux;
		  }
		  
		  //Asigna los elementos de la matriz a 0.
		  for (i=0; i<2; i++){
				for (j=0; j<3; j++){
				  SetMatrizPieza(N,i,j,0);
				}
		  }
		  
		  piezas[N].tipo = N;
		  piezas[N].rotada = 0;
		
		  
		  SetMatrizPieza(N,0,0,color[verde]);
		  SetMatrizPieza(N,0,1,color[verde]);
		  SetMatrizPieza(N,0,2,color[verde]);
		  SetMatrizPieza(N,1,1,color[verde]);
		}
	}
}

void NuevaPieza(){
	int punto, tipo_aleatorio, i;
	int resultado=1;
	
	//Comprueba si ya hay una pieza en la parte superior del tablero.
	for (i = (col / 2) - 2; i < (col / 2) + 2 && resultado; i++){
		punto = GetMatrizTablero(0, col / 2);
		if(punto != 0)
		  resultado = 0;
	}
	
	//Si no hay pieza, coloca la pieza obtenida de la cola en el tablero.
	if (resultado==1){
		// Asignamos la pieza siguiente a la pieza en juego
		pieza_en_juego.pieza = pieza_siguiente;
		pieza_en_juego.x1 = (col / 2)-1;
		pieza_en_juego.x2 = (pieza_en_juego.x1 + pieza_en_juego.pieza.col)-1;
		pieza_en_juego.posX = -1;
		pieza_en_juego.y1 = 0;
		pieza_en_juego.y2 = pieza_en_juego.y1 + pieza_en_juego.pieza.fil;
		pieza_en_juego.posY = 0;
		
		// Hallamos la siguiente pieza aleatoriamente
		srand(time(NULL));
		tipo_aleatorio = rand()%5; // Numeros aleatorios entre 1-5
		pieza_siguiente = piezas[tipo_aleatorio];
		
		pieza_cargada = 1;
	}
	else
	  game_over = 1;
}

void RotarPieza(){
	int *aux, *aux_2, valor, aux_int, sentido=0, i, j;
	
	// Si es el cubo o las dimensiones de la pieza son mayores que la del tablero
	if (pieza_en_juego.pieza.fil != pieza_en_juego.pieza.col && pieza_en_juego.x1 > 0 && pieza_en_juego.x2 < col){
	 
		// ---Programacion Basica---
		int **matriz_aux;

		// Hacemos la matriz TRASPUESTA, intercambiamos filas por columnas
		matriz_aux = malloc(pieza_en_juego.pieza.col * sizeof *matriz_aux);

		for(i=0; i<pieza_en_juego.pieza.col; i++){
		  aux = malloc(pieza_en_juego.pieza.fil * sizeof(int));

		  matriz_aux[i] = aux;
		}

		//Recorre la matriz auxiliar asignando los valores en sus posiciones.
		for(i = 0; i < pieza_en_juego.pieza.col; i++){
			 for(j = 0; j < pieza_en_juego.pieza.fil; j++){
				aux = matriz_aux[i];
				aux[j] = GetMatrizPiezaJuego(j,i);
			 }
		}
		
		// Intercambia filas
		for(i = 0; i < pieza_en_juego.pieza.col; i++){
			aux = matriz_aux[i];
			valor = aux[0];
			aux_int = valor;
			
			aux_2 = matriz_aux[i];
			valor = aux_2[pieza_en_juego.pieza.fil-1];
			aux = matriz_aux[i];
			aux[0] = valor;
			
			aux = matriz_aux[i];
			aux[pieza_en_juego.pieza.fil-1] = aux_int;
			
		}
		
		// Guardamos los nuveos valores de las filas y las columnas
		aux_int = pieza_en_juego.pieza.fil;
		pieza_en_juego.pieza.fil = pieza_en_juego.pieza.col;
		pieza_en_juego.pieza.col = aux_int;
		
		//free(pieza_en_juego.pieza.matriz);
		pieza_en_juego.pieza.matriz = matriz_aux;
		//free(aux);
		
		// ---Programacion Grafica---
		if(pieza_en_juego.pieza.tipo==1 || pieza_en_juego.pieza.tipo==4){
			 if(pieza_en_juego.pieza.rotada == 3)
				pieza_en_juego.pieza.rotada = 0;
			 else
				pieza_en_juego.pieza.rotada++;
		}
		else{
		  if(pieza_en_juego.pieza.rotada == 0)
				pieza_en_juego.pieza.rotada = 1;
		  else
				pieza_en_juego.pieza.rotada = 0;
		} 
	  
		//Ajusta las nuevas coordenadas
		pieza_en_juego.x2 = pieza_en_juego.x1 + pieza_en_juego.pieza.col;
		pieza_en_juego.y2 = pieza_en_juego.y1 + pieza_en_juego.pieza.fil;
		
		//Si la pieza colisiona, la devuelve a su estado original.
		if(CheckColisiones(3)==1){
			RotarPieza();
		}
	}
}

// Devuelve 1 si es true, 0 si es false
int CheckColisiones(int movimiento){
	int resultado=0, i, j;
	
	//Según el tipo de movimiento, busca la colisión y ajusta resultado a true si la encuentra.
	if (movimiento == 0){			//Movimiento vertical hacia abajo.
		for (i = 0; i < pieza_en_juego.pieza.fil; i++){
			for (j = 0; j < pieza_en_juego.pieza.col; j++){
				if (GetMatrizPiezaJuego(i,j) != 0 && GetMatrizTablero(pieza_en_juego.y1 + 1 + i, pieza_en_juego.x1 + j) != 0){
					resultado = 1;
				}
			}
		}
	}
	else if (movimiento == 1){		//Movimiento horizontal hacia la izquierda.		
		for (i = 0; i < pieza_en_juego.pieza.fil; i++){
			for (j = 0; j < pieza_en_juego.pieza.col; j++){
				if (GetMatrizPiezaJuego(i,j) != 0 && GetMatrizTablero(pieza_en_juego.y1 + i, pieza_en_juego.x1 - 1 + j) != 0){ 
					resultado = 1;
				}
			}
		}
	}
	else if (movimiento == 2){		//Movimiento horizontal hacia la derecha.
		for (i = 0; i < pieza_en_juego.pieza.fil; i++){
			for (j = 0; j < pieza_en_juego.pieza.col; j++){
				if (GetMatrizPiezaJuego(i,j) != 0 && GetMatrizTablero(pieza_en_juego.y1 + i, pieza_en_juego.x1 + 1 + j) != 0){ 
					resultado = 1;
				}
			}
		}
	}
	else if (movimiento == 3){		//Movimiento giratorio en ambos sentidos.
		for (i = 0; i < pieza_en_juego.pieza.fil; i++){
			for (j = 0; j < pieza_en_juego.pieza.col; j++){
				if (GetMatrizPiezaJuego(i,j) != 0 && GetMatrizTablero(pieza_en_juego.y1 + i, pieza_en_juego.x1 + j) != 0){ 
					resultado = 1;
				}
			}
		}
	}
	
	return resultado;
}

void MoverPieza(int sentido){
	//Mueve la pieza a izquierda o derecha ajustando sus coordenadas, siempre y cuando no colisione.
	if (CheckColisiones(sentido + 1)==0){
		if(sentido == 0 && pieza_en_juego.x1 > 0){
			pieza_en_juego.x1 -= 1;
			pieza_en_juego.x2 -= 1;
			pieza_en_juego.posX -= 1;
		}
		if(sentido == 1 && pieza_en_juego.x2 < col){
			pieza_en_juego.x1 += 1;
			pieza_en_juego.x2 += 1;
			pieza_en_juego.posX += 1;
		}
	}
}

int BajaPieza(){
	int ha_caido = 0, lineas;
	//Mientras la pieza no llegue al final del tablero o se apoye sobre otra, la baja una unidad.
		if(pieza_en_juego.y2 < fil){
			if(CheckColisiones(0) == 0){
				pieza_en_juego.y1++;
				pieza_en_juego.y2++;
				pieza_en_juego.posY--;
			}
			else {
				// LA PIEZA HA CAIDO
				AniadeAcumulaciones();
				lineas = LimpiaLineas();
				lineas_completadas += lineas;
				puntuacion += 100*lineas;
				// Si hemos eliminado mas de una linea a la vez, ganamos puntuacion extra
				if(lineas>1)
				  puntuacion += 50*(lineas-1);
				nivel = lineas_completadas/5;
				if(nivel == 50)
				  juego_completado = 1;
				dibujarAcumulacionPiezas();
				ha_caido = 1;
				pieza_cargada = 0;
				NuevaPieza();
				
			}
		}
		else {
			// LA PIEZA HA CAIDO
			AniadeAcumulaciones();
			lineas = LimpiaLineas();
			lineas_completadas += lineas;
			puntuacion += 100*lineas;
			// Si hemos eliminado mas de una linea a la vez, ganamos puntuacion extra
			if(lineas>1)
			  puntuacion += 50*(lineas-1);
			nivel = lineas_completadas/5;
			if(nivel == 50)
			  juego_completado = 1;
			dibujarAcumulacionPiezas();
			ha_caido = 1;
			pieza_cargada = 0;
			NuevaPieza();
		}
		
		return ha_caido;
}

void AniadeAcumulaciones(){
	int i, j;
	for (i = 0; i < pieza_en_juego.pieza.fil; i++){
		for (j = 0; j < pieza_en_juego.pieza.col; j++){
			if(GetMatrizTablero(pieza_en_juego.y1 + i, pieza_en_juego.x1 + j) == 0){
				SetMatrizTablero(pieza_en_juego.y1 + i, pieza_en_juego.x1 + j, GetMatrizPiezaJuego(i,j));
			}
		}
	}
}

int LimpiaLineas(){
	//Variables
	int llena = 0;
	int lineas = 0;
	int indice_linea;
	int j;
	
	//Recorre las lineas comprobando si estan o no completas, y eliminandolas si es necesario.
	for (indice_linea = 0; indice_linea < fil && llena==0; indice_linea++){
		llena = 1;
		for (j = 0; j < col && llena; j++){
			if (GetMatrizTablero(indice_linea,j) == 0){
				llena = 0;
			}
		}
		if(llena){
			EliminaIntercambia(indice_linea);
			lineas++;
		}
	}
	
	//Calcula las lineas completadas.
	if (indice_linea < fil){
		lineas += LimpiaLineas();
	}
	
	return lineas;
}

//================================================  FUNCIONES GRAFICAS  =============================================

void dibujaEscenario(){
 
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron]);
  glTranslatef(-6,0,0);
  caja(1,20,1);
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron]);
  //glTranslatef(5,0,0);
  caja(11,1,1);
  glPopMatrix();
  
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[marron]);
  glTranslatef(5,0,0);
  caja(1,20,1);
  glPopMatrix();
  
}

void dibujarPieza(){
  
  glPushMatrix();
  glTranslatef(pieza_en_juego.posX,pieza_en_juego.posY,0);

  if(pieza_en_juego.pieza.tipo == 0)
	 CUBO();
  else if (pieza_en_juego.pieza.tipo==1)	// L
	 L(pieza_en_juego.pieza.rotada);
  else if (pieza_en_juego.pieza.tipo==2)	// I
	 I(pieza_en_juego.pieza.rotada);
  else if (pieza_en_juego.pieza.tipo==3)	// S
	 S(pieza_en_juego.pieza.rotada);
  else if (pieza_en_juego.pieza.tipo==4)	// T
	 T(pieza_en_juego.pieza.rotada);
  
  glPopMatrix();
  
}

void dibujarAcumulacionPiezas(){
 int i=0, j=0;
 
  //Leemos el tablero, por cada casilla ocupada dibujamos una caja
  for(i=0; i<fil; i++){
	 for(j=0; j<col; j++){
		if(GetMatrizTablero(i,j) != 0){
		  glPushMatrix();
		  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,GetMatrizTablero(i,j));
		  glTranslatef(j,-i,0);
		  //printf("ACUMULACION EN X = %d Y = %d\n", i, j);
		  caja(1,1,1);
		  glPopMatrix();
		}
	 }
  }
}

void dibujarPiezaSiguiente(){
 
  glPushMatrix();
  glTranslatef(7,-5,0);
  //printf("POSX = %f, POSY = %F\n",pieza_en_juego.posX,pieza_en_juego.posY);
  if(pieza_siguiente.tipo == 0)
	 CUBO();
  else if (pieza_siguiente.tipo==1)	// L
	 L(0);
  else if (pieza_siguiente.tipo==2)	// I
	 I(0);
  else if (pieza_siguiente.tipo==3)	// S
	 S(0);
  else if (pieza_siguiente.tipo==4)	// T
	 T(0);
  
  glPopMatrix();
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja( void )
{
	 static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0 };		// Posicion de la fuente de luz
	 int i;
	 
	 glPushMatrix();		// Apila la transformacion geometrica actual
  
	 glClearColor(0,0,0,1);	// Fija el color de fondo a negro
	 
	 glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );	 // Inicializa el buffer de color
  
	 transformacionVisualizacion();	 // Carga transformacion de visualizacion
  
	 glLightfv( GL_LIGHT0, GL_POSITION, pos );	// Declaracion de luz. Colocada aqui esta fija en la escena

	 // Dibuja el suelo
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color[gris]);
    glTranslatef(0,-0.5,0);
    caja(200,0.5,200);
	 
	 // ----------- NUCLEO DEL DIBUJADO DEL JUEGO ------------- //
	 
	 dibujaEscenario();
	 
	 // Si hemos empezado una nueva partida
	 if(nueva_partida==1){
	 
		// Nos colocamos en la esquina (0,0) del tablero para dibujar la acumulacion de piezas
		glPushMatrix();
		glTranslatef(-5,20,0);
		dibujarAcumulacionPiezas();
		glPopMatrix();

		// Nos colocamos en la zona de generacion de piezas y desde alli generamos la actual
		glPushMatrix();
		glTranslatef(0,20,0);
		dibujarPieza();
		dibujarPiezaSiguiente();
		glPopMatrix();
	 
	 }
	 
    glPopMatrix(); 		// Desapila la transformacion geometrica

    glutSwapBuffers();	// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(){
  
  // Si no hemos completado el juego
  if(juego_completado==0){
		// Si no hemos perdido
		if(game_over == 0){
			 // Si hemos empezado una nueva partida
			 if(nueva_partida==1){
				
				  // Si el juego no esta pausado
				  if(pausa == 0){
					 // Muestra en pantalla el nivel actual y las lineas completadas
					 char buffer[100];
					 sprintf (buffer, "Nivel: %d Lineas: %d Puntuacion: %d", nivel, lineas_completadas, puntuacion);
					 gluiOutput(buffer);

					 // Hace bajar una pieza rapido y volver a la velocidad normal cuando halla caido
					 // pieza_cargada nos sirve como cerrojo para proteger la funcion NuevaPieza
					 if(pieza_cargada == 1){
						int caido = BajaPieza();
						if(caido == 1)
						  flecha_abajo = 0;
					 }
					 
					 gluiPostRedisplay();			// Redibuja
				}
				else
				  gluiOutput("PAUSA");
			 }
			 
		}
		else
			 gluiOutput("GAME OVER :(");
	}
	else
	  gluiOutput("HAS COMPLETADO EL JUEGO :)");
	  
	  
	if(flecha_abajo==0)
	  glutTimerFunc(velocidad_caida-(nivel*10),idle,0);		// Vuelve a lanzar otro evento de redibujado en velocidad_caida
	else{
	  if(nivel < 47) // Si el nivel es menor que 47 conservamos la opcion de bajar rapido, luego no tendra sentido
		 glutTimerFunc(30,idle,0);		// Vuelve a lanzar otro evento de redibujado en 30 ms (velocidad rapida)
	}
  
	 
		
 
}


