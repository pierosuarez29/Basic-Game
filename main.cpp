#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include "principales.h"	//LIBRERIA CREADA CON LAS FUNCIONES MAS USADAS
#include "nave.hpp" 		//CREADO COMO HPP PARA EVITAR PROBLEMAS EN EL DEV C++ AL CREAR UN PROYECTO
#include "snake.hpp"
#include "dino.hpp"
#include "pong.hpp"

//NORMALMENTE SE CREA CON CPP(TODAS LAS FUNCIONES CON SUS VALORES) Y HPP (SE DECLARAN LAS FUNCIONES)
//SE HIZO SOLO EN HPP PARA EVITAR CREAR TANTOS ARCHIVOS


#include <pthread.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESCAPE 27
#define ENTER 13

using namespace std;

//declaras el nombre de las canciones para todo el cpp
//arreglo de cadenas
char *sonido[2] = {"menu1","creditos1"};

///////////////////////////////////////

void creditos(){
	fflush(stdin);
	system("cls");
	int a=0, tiempo=200;
	musica(sonido[1]);
	//arreglo de cadenas
	char *nombre[6]={"PIERO SUAREZ CHAVEZ","FACUNDO VENTURA HERRERA","JERRY MENDOZA LLAJA",
				    "ALAN GONZALEZ NEIRA","MIGUEL CORDOVA ORUNA","ADRIAN BENITES BARBOZA"};
	char *cargo[5]={"DISE\xA5O Y MONTAJE","INTERESTELAR","SNAKE","DINOAVENTURE","PING PONG"};
	do{	
		color(11);//celeste							
			gotoxy(33,37-a); cout<<"DESARROLLADORES"; 
			gotoxy(33,38-a); cout<<"               ";
		if(a>1)
		{color(12);//rojo
			gotoxy(36,38-a);cout<<"(GRUPO 5)";
			gotoxy(36,39-a);cout<<"         ";}
		if(a>4)
		{	color(10);//verde
			gotoxy(33,41-a); cout<<cargo[0];//
			gotoxy(33,42-a); cout<<"                   ";} 
		if(a>6)//blanco
		{	color(15);
			gotoxy(31,43-a); cout<<nombre[0];
			gotoxy(31,44-a); cout<<"                          ";}
		if(a>8)
		{	color(15);
			gotoxy(29,45-a); cout<<nombre[1];
			gotoxy(29,46-a); cout<<"                            ";}		
		if(a>11)
		{	color(10);
			gotoxy(35,48-a); cout<<cargo[1];//
			gotoxy(35,49-a); cout<<"                   ";}
		if(a>13)
		{	color(15);
			gotoxy(31,50-a); cout<<nombre[2];
			gotoxy(31,51-a); cout<<"                                   ";}
		if(a>16)
		{	color(10);
			gotoxy(38,53-a); cout<<cargo[2];//
			gotoxy(38,54-a); cout<<"                   ";}
		if(a>18)
		{	color(15);
			gotoxy(31,55-a); cout<<nombre[3];
			gotoxy(31,56-a); cout<<"                                   ";}
		if(a>21)
		{	color(10);
			gotoxy(35,58-a); cout<<cargo[3];//
			gotoxy(35,59-a); cout<<"                   ";}
		if(a>23)
		{	color(15);
			gotoxy(31,60-a); cout<<nombre[4];
			gotoxy(31,61-a); cout<<"                                   ";}
		if(a>26)
		{	color(10);
			gotoxy(36,63-a); cout<<cargo[4];//
			gotoxy(36,64-a); cout<<"                   ";}
		if(a>28)
		{	color(15);
			gotoxy(29,65-a); cout<<nombre[5];
			gotoxy(29,66-a); cout<<"                                   ";}
		
		a++;
		if(kbhit()){
			char tecla = getch();
			if(tecla != '\0'){	tiempo=0;}
			}
		Sleep(tiempo);
		
	}while(a<35);
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

pthread_cond_t condicion = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int seguir_ejecutando = 1;

string flecha_D=">>", flecha_I="<<";
int opcion=1, Y;
void *cuadro_color(void* arg){
	int b = 0;
	int old_y = y;
	while(seguir_ejecutando){
		pthread_mutex_lock(&mutex);
		color(14);
			if(old_y != Y){
				gotoxy(32,9); cout<<"  "; 		gotoxy(49,9); cout<<"  ";
				gotoxy(32,12); cout<<"  "; 		gotoxy(49,12); cout<<"  ";
				gotoxy(32,15); cout<<"  "; 		gotoxy(49,15); cout<<"  ";
				gotoxy(32,18); cout<<"  "; 		gotoxy(49,18); cout<<"  ";
				gotoxy(32,21); cout<<"  "; 		gotoxy(49,21); cout<<"  ";
				gotoxy(32,24); cout<<"  "; 		gotoxy(49,24); cout<<"  ";
				old_y = Y;
			}
			gotoxy(32, Y); printf(">>"); gotoxy(49, Y); printf("<<");
		
	
			int vcolor=rand()%15;
			while(vcolor<8) {	vcolor=rand()%15;	}
			color(vcolor);
			fflush(stdin);
			gotoxy(36,4); printf("%c",201);
			gotoxy(36,5); printf("%c",186);	
			gotoxy(36,6); printf("%c",200);
			
			gotoxy(37,4); printf("%c",205);
			gotoxy(38,4); printf("%c",205);
			gotoxy(39,4); printf("%c",205);
			gotoxy(40,4); printf("%c",205);
			gotoxy(41,4); printf("%c",205);
			gotoxy(42,4); printf("%c",205);
			gotoxy(43,4); printf("%c",205);
			gotoxy(44,4); printf("%c",205);
			
			gotoxy(37,6); printf("%c",205);
			gotoxy(38,6); printf("%c",205);
			gotoxy(39,6); printf("%c",205);
			gotoxy(40,6); printf("%c",205);
			gotoxy(41,6); printf("%c",205);
			gotoxy(42,6); printf("%c",205);
			gotoxy(43,6); printf("%c",205);
			gotoxy(44,6); printf("%c",205);
		
			gotoxy(45,4); printf("%c",187);
			gotoxy(45,5); printf("%c",186);	
			gotoxy(45,6); printf("%c",188);
	
			Sleep(100);
					//abajo							arriba
			gotoxy(30+b,31); cout<<"      "; gotoxy(30+b,29); cout<<"        ";
			gotoxy(31+b,31); cout<<"      "; gotoxy(31+b,29); cout<<"        ";
			gotoxy(32+b,31); cout<<"      "; gotoxy(32+b,29); cout<<"        ";		
			if(b == 20) b=0;
			gotoxy(31+b,31); printf("%c",175); gotoxy(31+b,29); printf("%c",175);
			gotoxy(32+b,31); printf("%c",175); gotoxy(32+b,29); printf("%c",175);
			gotoxy(33+b,31); printf("%c",175); gotoxy(33+b,29); printf("%c",175);
		
			b++;
				
			int v2color=rand()%15;
			while(v2color<8) {	v2color=rand()%15;}
			color(v2color);
			gotoxy(37,30); printf("V. 1.02");  	
			
	        pthread_mutex_unlock(&mutex);
	}
	
}

void detener_hilo() {
    pthread_mutex_lock(&mutex);
    seguir_ejecutando = 0;
    pthread_mutex_unlock(&mutex);

    // Despertar al hilo si está bloqueado esperando la condición
    pthread_cond_signal(&condicion);
}

 int main(){//81, 38

	AjustarVentana(1080,1080);
	ocultar_cursor();
	pthread_t hilo;
	do{

	system("cls");	color(15);
	musica(sonido[0]);
	gotoxy(38,5); cout<<"ARCADE"<<endl;
	//opciones
    gotoxy(35,9);	cout<<"INTERESTELAR";	//OPC1
    gotoxy(38,12);  cout<<"SNAKE";     		//OPC2
    gotoxy(35,15);	cout<<"DINOAVENTURE";	//OPC3
    gotoxy(37,18);	cout<<"PING PONG";		//OPC4
    gotoxy(37,21);  cout<<"CREDITOS";		//OPC5
    gotoxy(38,24);	cout<<"SALIR"; 			//OPC6
    
//	gotoxy(37,30); cout<<"V. 1.02";
	
    
  	pthread_create(&hilo,NULL,&cuadro_color,NULL);
	seguir_ejecutando = 1;
	
	
		while(true){
				
				switch(opcion){
					case 1: Y=9  ;break;
					case 2: Y=12 ;break;
					case 3: Y=15 ;break;
					case 4: Y=18 ;break;
					case 5: Y=21 ;break;
					case 6: Y=24 ;break;
				}
		//	cuadro_color();
		//	color(14);//amarillo
			//izquierda										derecha
		//	gotoxy(32,y); cout<<flecha_D;		gotoxy(49,y); cout<<flecha_I;
    		//fflush(stdin);
  			
			Sleep(5);
			if(kbhit()){
				//izquierda								derecha
			//	gotoxy(32,y); cout<<"  "; 		gotoxy(49,y); cout<<"  ";

				char tecla = getch();
				if(tecla == ARRIBA) { 
					opcion=opcion-1;
				 	if(opcion==0) opcion=6;}
				if(tecla == ABAJO ) { 
					opcion=opcion+1;
					if(opcion==7) opcion=1;	}
				if(tecla == ENTER ) {	break;	}
			}	   
		}
		detener_hilo();
		pthread_join(hilo, NULL);
		pararmusica();
    switch (opcion){
  		case 1: menu_nave(); break;
	 	case 2: menu_snake(); break;
   		case 3: menu_dino(); break;
		case 4: menu_pong(); break;
		case 5:	creditos(); break;
		case 6:	salir(); break;
		}
	}while(true);
} 

