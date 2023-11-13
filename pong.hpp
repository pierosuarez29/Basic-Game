#include <stdio.h>
#include<conio.h>
#include <iostream>
#include <windows.h>
#include <string.h>


#define ESCAPE 27
#define ENTER 13
using namespace std;


//declaras el nombre de las canciones para todo el cpp
char *psonido[1] = {"CAMBIOMiCORAZON1.wav"};

void instrucciones_pong(){
	bool bandera=true;
	do{
		system("cls");
		//TITULO1
 	color(4);gotoxy(25,3); printf("%c",175);
 	color(11);gotoxy(26,3); cout<<"INSTRUCCIONES 1 JUAGADOR";
 	color(4);gotoxy(50,3); printf("%c",174);

 	
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
	
	//TITULO 2
 	color(4);gotoxy(19,11); printf("%c",175);
 	color(11);gotoxy(20,11); cout<<"INSTRUCCIONES PARA EL 2DO JUAGADOR";
 	color(4);gotoxy(55,11); printf("%c",174);
	
	//ARRIBA 2 JUADORES
	color(14);gotoxy(18,16); cout<<"IZQUIERDA";
 	gotoxy(13,16); printf("Q");
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
	
	//AJABO DOS JUGADORES
	color(14);gotoxy(52,16); cout<<"ABAJO";
 	gotoxy(47,16); printf("A");
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
	
	
	//ESCAPE
	color(14);gotoxy(40,21); cout<<"SALIR";
 	gotoxy(34,21); cout<<"Esc";
 	gotoxy(32,20); printf("%c",201);
	gotoxy(32,21); printf("%c",186);	
	gotoxy(32,22); printf("%c",200);
	
	for( int a=33 ; a<38 ; a++)
		{
			gotoxy(a,20); printf("%c",205);
			gotoxy(a,22); printf("%c",205);	
		}
	
	gotoxy(38,20); printf("%c",187);
	gotoxy(38,21); printf("%c",186);	
	gotoxy(38,22); printf("%c",188);
	
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

void pintar_marco()       // funcion que pinta los limites del escenario
{
     // Lineas horizontals
     for(int i=2; i < 78; i++){
        gotoxy (i, 3); printf ("%c", 205);
        gotoxy(i, 23); printf ("%c", 205);
     }
     //Lineas verticales
     for(int v=4; v < 23; v++){
        gotoxy (2,v);  printf ("%c", 186);
        gotoxy(77,v);  printf ("%c", 186);
     }
     // Esquinas
     gotoxy  (2,3);    printf ("%c", 201);
     gotoxy (2,23);    printf ("%c", 200);
     gotoxy (77,3);    printf ("%c", 187);
     gotoxy(77,23);    printf ("%c", 188);
}


class JUGADOR{
    int x,y;
 public:
      JUGADOR (int _x, int _y);//constructor de la clase
      void pintar() const;
      void borrar() const;
      void mover_cpu(int _x, int _y, int _dx);
      void Y(int _y){y+=_y;}
      int RY(){return y; }
      int RX(){return x; }

};

JUGADOR::JUGADOR(int _x, int _y) : x(_x), y(_y){}

 void JUGADOR::pintar() const{
     gotoxy(x , y-1); printf("%c",219);
     gotoxy(x , y ); printf("%c",219);
     gotoxy(x , y+1); printf("%c",219);
 }

 void JUGADOR::borrar() const{
     gotoxy(x , y-1); printf(" ");
     gotoxy(x , y); printf(" ");
     gotoxy(x , y+1); printf(" ");
 }

 void JUGADOR::mover_cpu(int _x, int _y, int _dx){
   if( _x > 65 && _dx>0){
      borrar();
      if(_y > y && y+1 < 22) y++;
      if(_y < y && y-1 > 4) y--;
      pintar();

   }

 }

 class PELOTA{
   int x,y;
   int dx,dy;
 public:
     PELOTA(int _x, int _y, int _dx, int _dy);
     void pintar() const;
     void borrar() const;
     void mover(JUGADOR A, JUGADOR B);
     void asign(int _x, int _y) {x = _x; y = _y; }
     int PX(){return x; }
     int PY(){return y; }
     int DX() {return dx; }

 };
 
 PELOTA::PELOTA(int _x, int _y, int _dx, int _dy): x(_x),y(_y),dx(_dx),dy(_dy){}

 void PELOTA::pintar() const{

     gotoxy(x,y); printf("%c",184);
 }

 void PELOTA::borrar() const{

     gotoxy(x,y); printf(" ");
 }
 void PELOTA::mover(JUGADOR A, JUGADOR B){
     borrar();
     x+= dx; y+=dy;
     pintar();
     if(x+ dx == 3 || x+dx==76){
        borrar();
        asign(38,14);
        dx= -dx;
     }
     if(y+ dy == 3 || y+dy==23) dy = -dy;

     if(x+ dx == A.RX() && y >= A.RY() -2 && y <= A.RY() +2 ){dx=-dx;}
     if(x+ dx == B.RX() && y >= B.RY() -2 && y <= B.RY() +2 ){dx=-dx;}
 }


 class MENU{
 public:
  void pintar_portada(int &a);
 };


void MENU::pintar_portada(int &a){
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(hConsole, 2);  
     char portada[18][71] =
    {
    "                                                                      ",
    "     aaaaaaaas                                                        ",
    "   aaaaaaaaaaass                             1.- 1 VS 1               ",
    "   aa       aass                             2.- Contra el CPU        ",
    "   aa       aass                             				           ",
    "   aa       aass                             			               ",
    "   aaaaaaaaaass                              			               ",
    "   aaaaaaaaas                                                         ",
    "   aass                                                               ",
    "   aass    aaaas    aaas   aas   aaaaas                               ",
    "   aass  aa    aas  aasas  aas  aa    as                              ",
    "   aass  aa    aas  aas as aas  aa                                    ",
    "   aass  aa    aas  aas  asaas  aa  aaaa                              ",
    "   aass  aa    aas  aas   aaas  aa    aas                             ",
    "   aass  aa    aas  aas    aas  aaaaaaaas                             ",
    "   aass    aaaas    aas    aas   aaaaa a                              ",

    };

for(int i=0; i<16; i++){
for(int j=0; j<70; j++){
    gotoxy(j+5,i+5);
    printf("%c",portada[i][j]);
}
}

a=getch();

for(int i=0; i<16; i++){
for(int j=0; j<70; j++){
    gotoxy(j+5,i+5);
    printf(" ");
}
}
}


//FUNCIÓN PRINCIPIAL//
int juego_pong(){
	
	ocultar_cursor();
    char tecla;
	do{
	system("cls");
    int cont=0, op_juego;
    pintar_marco();

    MENU M; M.pintar_portada(op_juego);
   
    JUGADOR A(6,15); A.pintar();
    JUGADOR B(74,15); B.pintar();
    PELOTA P(38,14,1,1);


    M.pintar_portada(op_juego);

    
	while(true){
       
       //Función que hace que si presiones una tecla pase algo
       if(kbhit() ){
           A.borrar(); B.borrar();
           tecla=getch();
           if(tecla==ESCAPE) break;
           if(tecla=='q' && A.RY() > 5) A.Y(-1); else if(tecla =='a' && A.RY() < 21) A.Y(1);
           if(op_juego== '1'){
               if(tecla=='o'&& B.RY() > 5) B.Y(-1);
               else if(tecla =='l'&& B.RY() < 21) B.Y(1);
           }
           A.pintar(); B.pintar();
       }

       if(op_juego =='2'&& !cont) B.mover_cpu(P.PX(),P.PY(),P.DX());
       if(!cont++)P.mover(A,B);
       if(cont>5) cont=0;
       Sleep(10);
	}
	
	if(tecla==ESCAPE) break;
	
	}while(true);

}


int menu_pong()
{
	//////////////////////////
	do{	
	musica(psonido[0]);
	system("cls");	
	system("color 07");;
	color(15);
	gotoxy(37,5); 	cout<<"PING PONG"<<endl;
	//opciones
    gotoxy(38,9);	cout<<"JUGAR";	//OPC1
    gotoxy(35,12);  cout<<"INSTRUCCIONES";     		//OPC2
    gotoxy(37,15);	cout<<"REGRESAR";	//OPC3
    gotoxy(38,18);	cout<<"SALIR";		//OPC4
      
	int opcion=1, y;
	
		while(true){
			//	AjustarVentana(81,38);
				switch(opcion){
					case 1: y=9  ;break;
					case 2: y=12 ;break;
					case 3: y=15 ;break;
					case 4: y=18 ;break;
				}
			cuadrodino();
			color(14);//amarillo
			//izquierda										derecha
			gotoxy(33,y); printf("%c",175);		gotoxy(49,y); printf("%c",174);
			gotoxy(32,y); printf("%c",175); 	gotoxy(50,y); printf("%c",174);
			
			if(kbhit()){
				//izquierda								derecha
				gotoxy(33,y); cout<<' '; 		gotoxy(49,y); cout<<' ';
				gotoxy(32,y); cout<<' '; 		gotoxy(50,y); cout<<' ';
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
  		case 1: juego_pong(); break;
	 	case 2:	instrucciones_pong();break;
   		case 3: break;
		case 4: salir(); break;
		}
	if(opcion==3) { pararmusica(); break;}
	}while(true);
}



