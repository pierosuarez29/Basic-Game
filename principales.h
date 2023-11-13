#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>



#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESCAPE 27
#define ENTER 13

using namespace std;


void gotoxy(int x, int y){
	 
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon,dwPos);
}

void color(int x){ //color de letras y objetos -- x es un color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);

}

void salir(){
	
 system("cls");
	color(15);
	gotoxy(28,12); cout<<"Desea salir del programa?";
	gotoxy(17,18); cout<<"Si"; //opc 1
	gotoxy(57,18); cout<<"Regresar"; //opc 2
	int opcion=1, x1,x2;
	color(14);
	while(true){
			switch(opcion){
					case 1: x1=14, x2=20; break;
					case 2: x1=53, x2=66 ;break;
				}
				gotoxy(x1,18); printf("%c",175);		gotoxy(x1+1,18); printf("%c",175);	//izquierda
				gotoxy(x2,18); printf("%c",174);		gotoxy(x2+1,18); printf("%c",174);	//derecha
				
		if(kbhit()){ 
				gotoxy(x1,18); cout<<" ";				gotoxy(x1+1,18); cout<<" ";	//izquierda
				gotoxy(x2,18); cout<<" ";				gotoxy(x2+1,18); cout<<" ";	//derecha	
				
				char tecla = getch();
				if(tecla == DERECHA){
					opcion=opcion+1; 
						if (opcion==3) opcion=1;  }
				if(tecla == IZQUIERDA){
					opcion=opcion-1;
						if(opcion==0) opcion=2;}
				if(tecla == ENTER){	break;	}
			}   
			Sleep(40); 
	}
			
	switch(opcion){
		case 1:  system("cls"); gotoxy(28,18);cout<<"Gracias por Jugar.";
								gotoxy(28,19); cout<<"Vuelva pronto :D"; Sleep(2500); 
				exit(0); break;
		
		case 2: break;
	}

}



void ocultar_cursor(){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 2;
	cci.bVisible = false;
	
	SetConsoleCursorInfo(hCon, &cci);}



void AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	// Obtener el handle de la consola
	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ajustar el buffer al nuevo tamaño
	SetConsoleScreenBufferSize(hConsola, Coordenada);

	// Cambiar tamaño de consola a lo especificado en el buffer
	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
}
//funcion con la musica
void musica(char *nombresonido){
	//invocas la funcion interna
	PlaySound(nombresonido,NULL,SND_FILENAME | SND_ASYNC);

	
}

void pararmusica(){
	
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC);
}


