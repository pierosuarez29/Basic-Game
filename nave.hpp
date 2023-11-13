#include<iostream>
#include<conio.h>
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
#define ESCAPE 27
#define ENTER 13
//system("COLOR *pantalla*letra ")
using namespace std;	
///////////////////////////////////////////////////////////////////////////////

//declaras el nombre de las canciones para todo el cpp
//arreglo de cadenas
char *nombresonido[2] = {"cancion3.wav","cancion4.wav"};

/////////////////////////////////////////////////////////////

void limites(){// funcion que muestra los limites donde se podra mover la nave 
	for(int i=2; i<77; i++){
		gotoxy(i,3); printf("%c", 205);
		gotoxy(i,33); printf("%c", 205);	
	}
	for (int i=4; i<33; i++){
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	gotoxy(2,3); printf("%c",201);
	gotoxy(2,33); printf ("%c",200);
	gotoxy(77,3); printf ("%c",187);
	gotoxy(77,33); printf ("%c",188);
}

class nave{
	int x, y;
	int corazones;
	int salud;
	public:
		nave(int _x, int _y, int _corazones, int _salud):x(_x), y(_y), corazones(_corazones), salud(_salud){} //constructor de la clase nave
		int X(){return x;}
		int Y(){return y;}
		int vidas(){return salud;}
		void cor(){corazones--;}
		void dibujar_nave();
		void borrar();
		void mover();
		void dibujar_corazones();
		void muerte();	
};

void nave::dibujar_nave(){//funcion que mostrara en pantalla la nave 
	color(1);
	gotoxy(x,y); printf("  %c", 30);
	gotoxy(x,y+1); printf("%c%c%c%c%c",47, 174,15,175,92);
	gotoxy(x,y+2); printf(" %c %c",31,31);
}
void nave::borrar(){//funcion que lo que hace es que mientras la nave avance 
	gotoxy(x,y); cout<<"      ";
	gotoxy(x,y+1); cout<<"      ";
	gotoxy(x,y+2); cout<<"      ";
}
void nave::mover(){
	if(kbhit()){
			char tecla=getch();
			borrar();
			if(tecla == IZQUIERDA && x > 3)x--;
			if(tecla == DERECHA && x+6 < 77)x++;
			if(tecla == ARRIBA && y > 4)y--;
			if(tecla == ABAJO && y+3 < 33)y++;
			dibujar_nave();
			dibujar_corazones();
		}
}

void nave::dibujar_corazones(){//funicon que muestrara la salud y las vidas de la nave 
	 color( 3);
	gotoxy(50,2); printf("vidas %d", salud);
	 color(2);
	gotoxy(64,2); cout<<"SALUD";
	gotoxy(70,2); cout<<"     ";
	for(int i=0; i<corazones; i++){
		 color(4);
	gotoxy(70+i,2);printf("%c", 3); 
	}
	
}
void nave::muerte(){//funcio que recrea la animacion de la muerte al perder los corazones
	if (corazones==0){
		borrar();
		color(6);
		gotoxy(x,y);   cout<<"  *  ";
		gotoxy(x,y+1); cout<<" *** ";
		gotoxy(x,y+2); cout<<"  *  ";
		Sleep(200);
		
		borrar();
		color(6);
		gotoxy(x,y);   cout<<"* * *";
		gotoxy(x,y+1); cout<<" *** ";
		gotoxy(x,y+2); cout<<"* * *";
		Sleep(200);
		borrar();
		salud--;
		corazones=3;
		dibujar_corazones();
		dibujar_nave();
	}
}

class asteroides{
	int x, y;
	public:
		asteroides(int _x, int _y): x(_x), y(_y){}//constructor de la clase asteroides
		void dibujar_asteroides();
		void mover_asteroides();
		void colision(class nave &N);
		int X(){return x;}
		int Y(){return y;}
		
};

void asteroides::dibujar_asteroides(){//funcion que muestra en patanlla al asteroide
	color(10);
	gotoxy(x,y); printf("%c",207);
}

void asteroides::mover_asteroides(){//funcion que permite el movimiento del asteroide
	gotoxy(x,y); cout<<" ";
	y++;
	if(y>32){
		x=rand()%71+4; // el rand es para que los asteroides salgan de manera aleatoria dentro del limite permitido
		y=4; // los asteroides saldran desde de la posicon y=4
	}
	dibujar_asteroides();	
}

void asteroides::colision(class nave &N){
	if(x>=N.X() && x < N.X()+6 && y>= N.Y() && y<= N.Y()+2){
	N.cor();
	N.borrar();
	N.dibujar_nave();
	N.dibujar_corazones();
	x=rand()%71+4;
	y=4;
	}	
}

class proyectiles{
	int x, y;
	public:
		proyectiles(int _x, int _y): x(_x), y(_y){}//constructor de la clase proyectiles
		int X(){return x;}
		int Y(){return y;}
		void mover();
		bool limite();
			
};

void proyectiles::mover(){ //funcion que muestra en patanlla los proyectiles
	color(14);
	gotoxy(x,y); cout<<" ";
	if(y>4) y--;
	gotoxy(x,y); printf("%c",94);
}

bool proyectiles::limite(){//funcion que permite que los proyectiles solo lleguen hasta cuando esten en la posicon y=4
	if(y==4) return true;
	return false;
}

void juego_nave(){
	system ("cls");
	limites();
	nave N(37,30,3,3);
	N.dibujar_nave();
    N.dibujar_corazones();
	
	list<asteroides*> A;
	list<asteroides*>::iterator itA;
	for(int i=0; i<6; i++){
		A.push_back(new asteroides(rand()%75 +3, rand()%5+4));
	}
	
	list<proyectiles*> B;
	list<proyectiles*>::iterator it;
	
	bool juego_perdido = false;
	int puntos=0;
	while(!juego_perdido){
	    color(9);
		gotoxy(4,2); printf("Puntaje: %d", puntos);
		if(kbhit()){
			char tecla=getch();
			if(tecla=='w')
			B.push_back(new proyectiles(N.X()+2, N.Y()-1));
			if(tecla==ESCAPE){gotoxy(32,15);color(4);cout<<" Game over! :c "; juego_perdido = true;}
		}
	for(it = B.begin(); it != B.end(); it++){
		(*it)->mover();
		if((*it)->limite()){
			gotoxy((*it)->X(), (*it)->Y()); cout<<" ";
			delete(*it);
			it= B.erase(it);
		}
	}
	
	for(itA= A.begin(); itA != A.end(); itA++){
		(*itA)->mover_asteroides();
		(*itA)->colision(N);	
	}
	
	for(itA= A.begin(); itA != A.end(); itA++){
		for(it=B.begin(); it != B.end(); it++){
			if((*itA)->X()==(*it)->X() && ( (*itA)-> Y()+1 == (*it)->Y() ||(*itA)-> Y() == (*it)->Y() )){
				gotoxy((*it)->X(), (*it)->Y()); cout<<" ";
				delete (*it);
				it = B.erase(it);
				
				A.push_back(new asteroides(rand()%74+3, 4));
				gotoxy((*itA)->X(), (*itA)->Y()); cout<<" ";
				delete(*itA);
				itA = A.erase(itA);
				puntos++;
			}
		}	
	}
	if(N.vidas()==0 ){
		gotoxy(32,15);color(4);cout<<" Game over! :c ";
		juego_perdido = true;
		pararmusica();
	} 
	
	N.muerte();
	N.mover();
		Sleep(30);	
	}
	
	getch();	
}
/////////////////////////////////////////////////////////////////

void instrucciones(){
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
	
	//DISPAROS
	color(14);gotoxy(18,16); cout<<"DISPAROS";
 	gotoxy(13,16); cout<<"w";
 	gotoxy(10,15); printf("%c",201);
	gotoxy(10,16); printf("%c",186);	
	gotoxy(10,17); printf("%c",200);
	
	for( int a=11 ; a<16 ; a++)
		{
			gotoxy(a,15); printf("%c",205);
			gotoxy(a,17); printf("%c",205);	
		}
	
	gotoxy(16,15); printf("%c",187);
	gotoxy(16,16); printf("%c",186);	
	gotoxy(16,17); printf("%c",188);
	
	//ESCAPE
	color(14);gotoxy(52,16); cout<<"SALIR";
 	gotoxy(46,16); cout<<"Esc";
 	gotoxy(44,15); printf("%c",201);
	gotoxy(44,16); printf("%c",186);	
	gotoxy(44,17); printf("%c",200);
	
	for( int a=45 ; a<50 ; a++)
		{
			gotoxy(a,15); printf("%c",205);
			gotoxy(a,17); printf("%c",205);	
		}
	
	gotoxy(50,15); printf("%c",187);
	gotoxy(50,16); printf("%c",186);	
	gotoxy(50,17); printf("%c",188);
	
	//NOTA
	color(4);gotoxy(10,20);cout<<"PUNTUACION: por cada asteroide destruido, ganara un punto.";
	
	//
	color(14);	
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

void cuadronave(int& b)
{
	for (int c=0; c<2; c++ )
	{
			int vcolor=rand()%15+1;
			while(vcolor<8){	vcolor=rand()%15+1;	}
			color(vcolor);
					//IZQUIERDA								IZQUIERDA
			gotoxy(32,4); printf("%c",201);			gotoxy(47,4); printf("%c",187);
			gotoxy(32,5); printf("%c",186);			gotoxy(47,5); printf("%c",186);	
			gotoxy(32,6); printf("%c",200);			gotoxy(47,6); printf("%c",188);
					//LINEAS HORIZONTALES
			for( int a=33 ; a<47 ; a++)
				{	gotoxy(a,4); printf("%c",205);		gotoxy(a,6); printf("%c",205);	}	
	} 
	//OTRO COLOR
	int v2color=rand()%15+1;
	while(v2color<8)	{	v2color=rand()%15+1;	}
	Sleep(95);
		
	for (int c=0; c<1; c++){
		//PINTA ESPACIO
		gotoxy(20+b,22); cout<<"      ";
	    gotoxy(19+b,23); cout<<"      ";
	    gotoxy(20+b,24); cout<<"      ";
		
		//PINTA LA NAVE
		if(b == 30) b=0;
		gotoxy(20+b,22); printf("  %c", 30);
		gotoxy(20+b,23); printf("%c%c%c%c%c",47, 174,15,175,92);
		gotoxy(20+b,24); printf(" %c %c",31,31);
		b++;
	}
}


 void menu_nave(){
	
	do{
	musica(nombresonido[0]);
	int	b=0;
	system("cls");
	color(15); //BLACO PURO
	gotoxy(34,5); cout<<"INTERESTELAR"<<endl;
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
			cuadronave(b);
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
    	case 1: juego_nave(); break; //JUGAR
   		case 2: instrucciones(); break; //INSTRUCCIONES
		case 3: break;	//REGRESAR
		case 4: salir();break;	//SALIR
		}
	if(opcion==3) break;
	}while(true);
} 

