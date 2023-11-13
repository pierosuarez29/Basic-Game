#include<conio.h>
#include<iostream>
#include<windows.h> //gotoxy
#include<stdlib.h> //system
#include<stdio.h>
#include<dos.h>
#include<list>
#include<string.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ENTER 13
#define ESCAPE 27
using namespace std;

//declaro el nombre de las canciones para todo el cpp
char *ssonido[3] = {"intro1","juego1","gameover1"};

/////////////////////////////////////////////////////////////

int cuerpo[200][2];//MATRIZ PARA GUARDAR LAS POSICIONES DE TODAS LAS PARTES DEL CUERPO
int n=1;
int tam =3;
int x=10, y=12;	//[][]
char tecla; 
int dir =3; //Direccion
int xc = 30, yc = 15; //COORDENADAS DE LA COMIDA
int velocidad = 100, h =1;
int score=0;
 

//FUNCION que nos pinta los limites del juego (MARCO)
void pintar()
{
	
	//Lineas Horizontales
	for(int i=2; i<77; i++)
	{
		//El primer codigo ACIL se pintara en la posicion (2.3)
		gotoxy(i,3); //INFERIOR
		printf("%c",205);
		gotoxy(i,33);//SUPERIOR
		printf("%c",205);
		
	}
		//Lineas Verticlaes
	for(int i=4; i<33; i++)
	{
		gotoxy(2,i);//IZQUIERDO
		printf("%c",186);
		gotoxy(77,i);//DERECHO
		printf("%c",186);
		
	}
	//Pinta un codigo especial para las esquinas
	gotoxy(2,3);printf("%c",201);  //Superior Izquierdo
	gotoxy(2,33);printf("%c",200);  //Inferior Izquierdo
	gotoxy(77,3);printf("%c",187);   //Superior Derecho
	gotoxy(77,33);printf("%c",188);   //Inferior Derecho
		
}
//Guarda la posicion de cada bolita que forma el cuerpo
void guardar_posicion()
{
	cuerpo[n][0] =x;
	cuerpo[n][1] =y;
	n++;
	if(n==tam)
	{
		n=1;
	}	
}
//Dibuja el cuerpo en las posiciones guardadas
void dibujar_cuerpo()
{
	for(int i=1; i<tam; i++)
	{
		gotoxy(cuerpo[i][0],cuerpo[i][1]);
		printf("*");
	}
}
//BORRA EL CUERPO CON ATERIORIDAD PARA QUE SE LA GUARDE POSICION
void borrar_cuerpo()
{
	for(int i=0; i<tam; i++)
	{
		gotoxy(cuerpo[i][0],cuerpo[i][1]);
		printf(" ");
	}
	
}

//FUNCION PARA EL MOVIMIENTO DE LA SERPIENTE A TRAVES DE TECLAS
void teclear ()
{
	if(kbhit())
	{
		tecla = getch();
		switch (tecla)
		{
			case ARRIBA:
				if(dir !=2)
				   dir=1;
				   break;
			case ABAJO:
				if(dir !=1)
			    dir=2;
				break;
			case DERECHA:
			     if(dir !=4)
				 dir =3;
				 break;
			case IZQUIERDA:
			     if(dir !=3)
				 dir =4;
				 break;	 			
		}
	}	
}
//FUNCION QUE CAMBIA LA VELOCIDAD DE ACUERDO AL PUNTAJE
void cambiar_velocidad()
{
	if(score== h*20)
	{
		velocidad-=10;
		h++;
	}
}
//FUNCION PARA LA APARICION DE LA COMIDA
void comida()
{
	if ( x==xc && y==yc)
	{
		xc = rand()%76;
		while(xc <3)	{	xc = rand()%76;	}
		yc = rand()%32;
		while(yc <4)	{	yc = rand()%32;	}
		tam++;
		score+=10;
		gotoxy(xc,yc);printf("%c",4);
		cambiar_velocidad();
	}
}
//FUNCION PARA CUADNO CUERPO CHOQUE CON LOS MUROS
bool game_over()
{
	if( y == 3 || y == 33 || x == 2 || x ==77)
	{
		n=1;
		tam =3;
		x=10, y=12;	//[][]
		dir =3; //Direccion
		xc = 30, yc = 15; //COORDENADAS DE LA COMIDA
		velocidad = 100, h =1;
		score=0;
		return false;
	}
	for( int j=tam-1; j>0; j--)
	{
		if(cuerpo[j][0] == x && cuerpo[j][1] == y )
		return false;
	}
		
	return true;
}
//FUNCION PARA ACUMULAR PUNTOS 
void puntos()
{
	gotoxy(3,1); printf("PUNTAJE: %d",score);
}

void juego_snake(){ //juego_snake
	system ("cls");
	musica(ssonido[1]);
	pintar();
	gotoxy(xc,yc);printf("%c",4);
	while(game_over()) //Va a contener la rutina del juego
	{
		pintar();
		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		comida();
		puntos();
		cambiar_velocidad();

		teclear();
		teclear();
		
     	if(dir == 1) y--;
    	if(dir == 2) y++;
    	if(dir == 3) x++;
    	if(dir == 4) x--;
	
		Sleep(velocidad); 
	}
	pararmusica();
	musica(ssonido[2]);
	gotoxy(32,15);color(4);cout<<"Game Over! :c ";
		do{
		color(8);//plomo
		gotoxy(27,35); cout<<"Presiona ENTER para regresar...";
		
		if(kbhit()){
			char tecla = getch();
			if(tecla == ENTER){	break;	}
			}
		Sleep(700);
		gotoxy(27,35); cout<<"                               ";
		
		if(kbhit()){
			char tecla = getch();
			if(tecla == ENTER){	break;	}
			}
		Sleep(400);
		
		}while(true);
	pararmusica();

}

void instrucciones_snake(){
	bool bandera=true;
	do{
		system("cls");
		//TITULO
 	color(4);gotoxy(28,3); printf("%c",175);
 	color(11);gotoxy(30,3); cout<<"INSTRUCCIONES";
 	color(4);gotoxy(44,3); printf("%c",174);

 	
 	//ARRIBA
 	color(14);gotoxy(18,8); cout<<"ARRIBA";
 	gotoxy(13,8); printf("%c",30);
 	gotoxy(10,7); printf("%c",201);
	gotoxy(10,8); printf("%c",186);	
	gotoxy(10,9); printf("%c",200);
	
	for( int a=11 ; a<16 ; a++)
		{
			gotoxy(a,7); printf("%c",205);
			gotoxy(a,9); printf("%c",205);	
		}
	
	gotoxy(16,7); printf("%c",187);
	gotoxy(16,8); printf("%c",186);	
	gotoxy(16,9); printf("%c",188);
	
	//ABAJO
	color(14);gotoxy(52,8); cout<<"ABAJO";
 	gotoxy(47,8); printf("%c",31);
 	gotoxy(44,7); printf("%c",201);
	gotoxy(44,8); printf("%c",186);	
	gotoxy(44,9); printf("%c",200);
	
	for( int a=45 ; a<50 ; a++)
		{
			gotoxy(a,7); printf("%c",205);
			gotoxy(a,9); printf("%c",205);	
		}
	
	gotoxy(50,7); printf("%c",187);
	gotoxy(50,8); printf("%c",186);	
	gotoxy(50,9); printf("%c",188);
	
	//IZQUIERDA
	color(14);gotoxy(18,12); cout<<"IZQUIERDA";
 	gotoxy(13,12); printf("%c",17);
 	gotoxy(10,11); printf("%c",201);
	gotoxy(10,12); printf("%c",186);	
	gotoxy(10,13); printf("%c",200);
	
	for( int a=11 ; a<16 ; a++)
		{
			gotoxy(a,11); printf("%c",205);
			gotoxy(a,13); printf("%c",205);	
		}
	
	gotoxy(16,11); printf("%c",187);
	gotoxy(16,12); printf("%c",186);	
	gotoxy(16,13); printf("%c",188);
	
	//DERECHA
	color(14);gotoxy(52,12); cout<<"DERECHA";
 	gotoxy(47,12); printf("%c",16);
 	gotoxy(44,11); printf("%c",201);
	gotoxy(44,12); printf("%c",186);	
	gotoxy(44,13); printf("%c",200);
	
	for( int a=45 ; a<50 ; a++)
		{
			gotoxy(a,11); printf("%c",205);
			gotoxy(a,13); printf("%c",205);	
		}
	
	gotoxy(50,11); printf("%c",187);
	gotoxy(50,12); printf("%c",186);	
	gotoxy(50,13); printf("%c",188);
	
	
	//ESCAPE
	color(14);gotoxy(40,16); cout<<"SALIR";
 	gotoxy(34,16); cout<<"Esc";
 	gotoxy(32,15); printf("%c",201);
	gotoxy(32,16); printf("%c",186);	
	gotoxy(32,17); printf("%c",200);
	
	for( int a=33 ; a<38 ; a++)
		{
			gotoxy(a,15); printf("%c",205);
			gotoxy(a,17); printf("%c",205);	
		}
	
	gotoxy(38,15); printf("%c",187);
	gotoxy(38,16); printf("%c",186);	
	gotoxy(38,17); printf("%c",188);
	
		gotoxy(20,25); cout<<"Regresar";//opcion 1	
		gotoxy(60,25); cout<<"Salir";  // opcion 2
		int opcion=1;
	color(14);
	while(true){
				if(opcion==1)
				{	gotoxy(17,25); printf("%c",175); 	gotoxy(18,25); printf("%c",175);	//izquierda
					gotoxy(29,25); printf("%c",174);	gotoxy(30,25); printf("%c",174);}	//derecha
				else
				{	gotoxy(57,25); printf("%c",175); 	gotoxy(58,25); printf("%c",175);	//izquierda
					gotoxy(66,25); printf("%c",174);	gotoxy(67,25); printf("%c",174);}	//derecha
					
		if(kbhit()){ //knhit() es una funcion que sirve para que el programa sepa si hemos presionado una tecla
		//si presionamos una tecla, el siguiente if borra las flechas
				if(opcion==1)
				{	gotoxy(17,25); cout<<' ';			gotoxy(18,25); cout<<' ';	//izquierda
					gotoxy(29,25); cout<<' ';			gotoxy(30,25); cout<<' ';}	//derecha
				else
				{	gotoxy(57,25); cout<<' ';			gotoxy(58,25); cout<<' '; //izquierda
					gotoxy(66,25); cout<<' ';			gotoxy(67,25); cout<<' ';}	//derecha
					
				char tecla = getch();
				if(tecla == DERECHA)
				{	opcion=opcion+1; 
						if (opcion==3) opcion=1;  }
				if(tecla == IZQUIERDA)
				{	opcion=opcion-1;
						if(opcion==0) opcion=2;}
				if(tecla == ENTER)	{	break;	}
			}   
			Sleep(40); }
			
	switch(opcion){
		case 1:  bandera=false; break;
		case 2: salir();break;
		}
	}while(bandera);
		
}

void cuadrosnake()
{
		 for (int c=0; c<2; c++ )
		{
			int vcolor=rand()%15+1;
			while(vcolor<8){
				vcolor=rand()%15+1;
			}
			
			vcolor=rand()%15+1;
			color(vcolor);
			gotoxy(32,4); printf("%c",201);
			gotoxy(32,5); printf("%c",186);	
			gotoxy(32,6); printf("%c",200);
				for( int a=33 ; a<47 ; a++)
				{
					gotoxy(a,4); printf("%c",205);
					gotoxy(a,6); printf("%c",205);	
				}
			gotoxy(47,4); printf("%c",187);
			gotoxy(47,5); printf("%c",186);	
			gotoxy(47,6); printf("%c",188);
			int v2color=rand()%15+1;
			while(v2color<8){
				v2color=rand()%15+1;
			}
		} 
		Sleep(95);
}
			

 void menu_snake(){
	do{	
	musica(ssonido[0]);
	system("cls");
	color(15);
	gotoxy(37,5); cout<<"SNAKE"<<endl;
	//opciones
    gotoxy(37,9);  cout<<"Jugar"; 			//OPC1
    gotoxy(34,12); cout<<"Instrucciones";	//OPC 2
    gotoxy(36,15); cout<<"Regresar"; 		//OPC 3
	gotoxy(37,18); cout<<"SALIR"; 			//OPC4
	int opcion=1, y;
	while(true){
				switch(opcion){
					case 1: y=9  ;break;
					case 2: y=12 ;break;
					case 3: y=15 ;break;
					case 4: y=18 ;break;
					
				}
			cuadrosnake();
			color(14);//amarillo
			//izquierda										derecha
			gotoxy(32,y); printf("%c",175);		gotoxy(48,y); printf("%c",174);
			gotoxy(31,y); printf("%c",175); 	gotoxy(49,y); printf("%c",174);
		
			if(kbhit()){ //ESTA FUNCION PREGUNTA AL PROGRAMA SI SE PRESIONO UNA TECLA
						//SI SE PRESION0 (1)   SI NO PRESIONO (0)
				//izquierda								derecha
				gotoxy(32,y); cout<<' '; 		gotoxy(48,y); cout<<' ';
				gotoxy(31,y); cout<<' '; 		gotoxy(49,y); cout<<' ';
				
				char tecla = getch();
				if(tecla == ARRIBA) { 
					opcion=opcion-1;
				 	if(opcion==0) opcion=4;}
				if(tecla == ABAJO ) { 
					opcion=opcion+1;
					if(opcion==5) opcion=1;	}
				if(tecla == ENTER ) {	break;	}
			}	   
		}
    switch (opcion){
    	case 1: juego_snake(); break;
   		case 2: instrucciones_snake(); break;
		case 3: break;
		case 4: salir();break;
		}
	if(opcion==3) break;
	}while(true);
} 

