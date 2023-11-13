#include<iostream>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<cmath>
#include<cstdlib>
#include<conio.h>

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESCAPE 27
#define ENTER 13

using namespace std;


//declaras el nombre de las canciones para todo el cpp
char *dsonido[2] = {"cancionSG","cancionSM"};

void cuadrodino()
{
		 for (int c=0; c<2; c++ )
		{
			int vcolor=rand()%15+1;
			while(vcolor<8) {	vcolor=rand()%15;	}
			color(vcolor);
			gotoxy(32,4); printf("%c",201);
			gotoxy(32,5); printf("%c",186);	
			gotoxy(32,6); printf("%c",200);
				for( int a=33 ; a<50 ; a++)
				{
					gotoxy(a,4); printf("%c",205);
					gotoxy(a,6); printf("%c",205);		
				}
			gotoxy(50,4); printf("%c",187);
			gotoxy(50,5); printf("%c",186);	
			gotoxy(50,6); printf("%c",188);	
		}   
		Sleep(95);
		
}

///////////////////////////////////////	
////////////JUEGO DINOSAURIO///////////
///////////////////////////////////////	

//DIMENSIONES DE LA PANTALLA
const int WIDTH=600, HEIGHT=400;
//DIMENSIONES DE LOS PIXELES
const int dW=6, dH=12;
//800/8=100 y 600/16=37.5

char dino[2][11][21]={
						{
							"        ????????    ",
							"        ????????    ",
							"        ????????    ",
							"        ????????    ",
							"?      ????????     ",
							"?     ??????        ",
							"???  ?????????      ",
							"???????????? ?      ",
							" ???????????        ",
							"  ?????????         "
						},
						{
							"                    ",
							"                    ",
							"                    ",
							"                    ",
							"?           ????????",
							"???  ?????? ????????",
							"????????????????????",
							" ?????????????????? ",
							"  ????????????      ",
							"   ????????????     "
						}
};

char saltod[3][2][15]={//PATITAS CARACTERES
						{
							"   ??? ??     ",//PARA EL SALTO
							"    ??  ??    "
						},
						{
							"   ??? ??     ",//PARA CAMINAR
							"        ??    "
						},
						{
							"   ???? ???   ",//PARA CAMINAR
							"    ??        "
						}
};

char trees[5][9][23]={
						{
							"          ?           ",
							"    ?     ??          ",
							" ? ??   ? ?? ?   ?    ",
							" ? ?? ? ? ?? ?   ?? ? ",
							" ? ?? ? ? ?? ? ? ?? ? ",
							" ???? ? ?????? ? ???? ",
							"   ????   ??   ????   ",
							"   ??     ??     ??   ",
							"   ??     ??     ??   "
						},
						{
							"   ?                  ",
							"   ?? ?               ",
							" ? ?? ?               ",
							" ? ?? ?               ",
							" ? ?? ?               ",
							" ??????               ",
							"   ??                 ",
							"   ??                 ",
							"   ??                 "
						},
						{
							"                      ",
							"           ?          ",
							"   ?    ? ??          ",
							"   ?? ? ? ?? ?        ",
							" ? ?? ? ? ?? ?        ",
							" ? ???? ???? ?        ",
							" ????     ????        ",
							"   ??     ??          ",
							"   ??     ??          "
						},
						{
							"    ?     ?           ",
							"   ??   ? ??          ",
							"   ?? ? ? ?? ?        ",
							" ? ?? ? ? ?? ?        ",
							" ? ?? ? ? ?? ?   ??   ",
							" ? ???? ???? ? ? ?? ? ",
							" ????     ???? ?????? ",
							"   ??     ??     ??   ",
							"   ??     ??     ??   "
						},
						{
							"                      ",
							"                      ",
							"                      ",
							"                      ",
							"   ??                 ",
							" ? ?? ?               ",
							" ?????? ?             ",
							"   ??  ???            ",
							"   ??   ?             "
						}
};
char pajaro[2][12][21]={
						{
							"                    ",
							"                    ",
							"                    ",
							"   ?                ",
							"  ???               ",
							" ?????              ",
							"??????????????????? ",
							"    ??????????????  ",
							"       ????         ",
							"       ???          ",
							"       ??           ",
							"                    "
						},
						{
							"                    ",
							"                    ",
							"                    ",
							"   ?   ??           ",
							"  ???  ???          ",
							" ????? ????         ",
							"??????????????????? ",
							"    ??????????????  ",
							"                    ",
							"                    ",
							"                    ",
							"                    "
						}
};

char sunmoon[2][6][13]={
						{
							"    @@@@    ",
							"  @@@@@@@@  ",
							" @@@@@@@@@@ ",
							" @@@@@@@@@@ ",
							"  @@@@@@@@  ",
							"    @@@@    "
						},
						{
							"      @@    ",
							"       @@@  ",
							"        @@@ ",
							"        @@@ ",
							"       @@@  ",
							"      @@    "
						}
};

struct coord//para coordenadas
{
	int x;
	int y;
};
struct pieza
{
	coord peri[93];
	char D[93]; //almacenar los caracteres de los dibujos de dinosaurio
};

pieza car1[2];
pieza car2[3];
pieza car3[7];
pieza car4[2];
pieza choqueD[2];//usado para colision del dinosaurio
pieza choqueO[7];//usado para colision de obstaculos
pieza choqueO2[7];

void convertir(int p[2], float x, float y)
{
	p[0]=int(x)/dW;
	p[1]=int(y)/dH;
}
void convertir(int p[2], int x, int y)
{
	p[0]=x/dW;
	p[1]=y/dH;
}
//FUNCION PARA DIBUJAR TODO
//Se pasa coordenadas A y B convertidas a entero
//Agarrar el valor de B y darle un nuevo valor
void drawpoint(char plano[HEIGHT/dH][WIDTH/dW+1], int A, int B, char c)
{
	B=HEIGHT/dH-1-B;
	if(A<0 || B<0 || A>=WIDTH/dW || B>=HEIGHT/dH) return;//Si cumple se sale de la funcion
	plano[B][A]=c;
}
class map
{
	private:
		float n(float x)
		{
			return 0.25*sin(x*0.5);
			//return 0;
		}
	public:
		float f(float x)//0
		{
			return 150*(n(x)+1.0f)/2.0f;//75
		}
		void dibujar(char plano[HEIGHT/dH][WIDTH/dW+1], float des)
		{
			for(int i=0;i<WIDTH/dW;i++)
			{
				int p[2];
				int j_inicio=f(i*dW+des)/dH;//se aumenta el des(plazamiento)para que se vea como si se mueve el escenario
				for(int j=j_inicio;j>=0;j--)
				{
					convertir(p,i*dW,j*dH);//convertir los valores a enteros
					drawpoint(plano,p[0],p[1],'o');//Va a pintar en las posiciones 0,1 /i=posiciones de y & j=posiciones de x
				}
				convertir(p,i*dW,j_inicio*dH);
				drawpoint(plano,p[0],p[1],'@');
			}
		}
		
		void sunmon(char plano[HEIGHT/dH][WIDTH/dW+1], float dsm, int DN)//cambiar dia y noche
		{
			int sm[2]={44,16}; //numero de caracteres de sol y luna
			const float y3=300.0f;
			int p[2]; //se almacena la posicion de x, y
			convertir(p,dsm,y3);
			
			for(int i=0;i<sm[DN];i++)//para imprimir el sol y la luna
			{
				drawpoint(plano,p[0]+car4[DN].peri[i].x,p[1]+car4[DN].peri[i].y,car4[DN].D[i]);
			}
		}
		
		void pasar()
		{
			for(int t=0;t<2;t++)
			{
				int q=0;
				int y=0;
				for(int i=0;i<6;i++)
				{
					y=6-i;
					for(int j=0;j<13;j++)
					{
						if(sunmoon[t][i][j] == '@')
						{
							car4[t].peri[q] = {j,y};
							car4[t].D[q] = '@';
							q++;
						}
					}
				}
			}
		}	
};
class personaje
{
	private:
		int sal=0;
		float ag=1.0f;
		float x,y;
		float vy;
		float salto=700.0f;
		float resultado;
		float yy;
		map* mapa;//pasar la clase mapa por puntero (direccion de memoria de un dato)
	
	public:
		personaje(float x, map* mapa):x(x),mapa(mapa)//Se asigna las variables de la clase personaje a las de la funcion declarada
		{
			y=mapa->f(x);//y va a tener el valor que retorne f(x);
			yy=y;
		}
		
		void dibujar(char plano[HEIGHT/dH][WIDTH/dW+1], int offcam, pieza choqueD[2])
		{
			int r, t;
			int p[2];//almacena 2 espacios
			convertir(p,x,y);
			p[1]++;//el dato en y aumenta en 1
			
			if(ag>=1.0f)
			{
				r=0;
				t=93;//Numero exacto de caracteres de dinosaurio parado
			}
			else
			{
				r=1;
				t=88;//Numero exacto de caracteres de dinosaurio agachado
			}
			for(int i=0; i<t;i++)
			{
				drawpoint(plano,(p[0]+car1[r].peri[i].x),(p[1]+car1[r].peri[i].y),car1[r].D[i]);//dibujar en plano
				choqueD[r].peri[i].x=(p[0]+car1[r].peri[i].x);//Guardar las variables del dinosaurio en choque;
				choqueD[r].peri[i].y=(p[1]+car1[r].peri[i].y);
			}
			if(sal==1)
			{
				for(int i=0;i<9;i++)//Imprimir patas del dinosaurio
				{
					drawpoint(plano,(p[0]+car2[0].peri[i].x),(p[1]+car2[0].peri[i].y),car2[0].D[i]);
				}
			}
			if(offcam==0 && sal==0)//imprimir patas moviendose 1
			{
				for(int i=0;i<7;i++)
				{
					drawpoint(plano,(p[0]+car2[1].peri[i].x),(p[1]+car2[1].peri[i].y),car2[1].D[i]);
				}
			}
			if(offcam==1 && sal==0)//imprimir patas moviendose 2
			{
				for(int i=0;i<9;i++)
				{
					drawpoint(plano,(p[0]+car2[2].peri[i].x),(p[1]+car2[2].peri[i].y),car2[2].D[i]);
				}
			}
		}
		
		void dibujartrees(char plano[HEIGHT/dH][WIDTH/dW+1], float X, int ran, int cam, pieza choqueO[7])
		{
			int p[2];
			convertir(p,X,yy);
			// 73, 28, 46, 72, 21 Numero de caracteres de cada cactus
			int numc[6]={73,28,46,72,21,51};
			int numd[6]={0,1,2,3,4,5};
			
			if(ran!=5)
			{
				for(int i=0;i<numc[ran];i++)//se genera aletaoriamente el cactus a dibujar
				{
					drawpoint(plano,p[0]+car3[numd[ran]].peri[i].x,p[1]+car3[numd[ran]].peri[i].y,car3[numd[ran]].D[i]);//Dibujar cactus
					choqueO[ran].peri[i].x=p[0]+car3[numd[ran]].peri[i].x;
					choqueO[ran].peri[i].y=p[1]+car3[numd[ran]].peri[i].y;
				}
			}
			else
			{
				if(cam==0)
				{
					for(int i=0;i<numc[ran];i++)//se genera aletaoriamente el pajaro a dibujar
					{
						drawpoint(plano,p[0]+car3[5].peri[i].x,(p[1]+car3[5].peri[i].y)+7,car3[5].D[i]);//Dibujar pajaro
						choqueO[5].peri[i].x=p[0]+car3[5].peri[i].x;
						//choqueO[5].peri[i].y=(p[1]+car3[5].peri[i].y)+7;
					}
				}
				if(cam==1)
				{
					for(int i=0;i<numc[ran];i++)//se genera aletaoriamente el pajaro a dibujar
					{
						drawpoint(plano,p[0]+car3[6].peri[i].x,(p[1]+car3[6].peri[i].y)+7,car3[6].D[i]);//Dibujar pajaro
						choqueO[6].peri[i].x=p[0]+car3[6].peri[i].x;
						//choqueO[6].peri[i].y=(p[1]+car3[6].peri[i].y)+7;
					}
				}
			}
		}
		
		int colision(int ran, int cam, pieza choqueD[2], pieza choqueO[7], int &score)
		{
			int ran1;
			int r;
			if(ag>=1.0f)
				r=0;
			else
				r=1;
				
			if(ran!=5)
			{
				ran1=ran;
			}
			if(ran==5)
			{
				if(cam==0)
					ran1=5;
				if(cam==1)
					ran1=6;
			}	
					
			int ndin[2]={93,88};//Dimensiones del dinosaurio
			int ndip[2]={0,1};
			int numc[6]={73,28,46,72,21,51};
			int numd[6]={0,1,2,3,4,5};
			
			for(int i=0;i<numc[ran1];i++)
			{
				for(int j=0;j<ndin[r];j++)
				{
					if(choqueD[r].peri[j].x == choqueO[ran1].peri[i].x && choqueD[r].peri[j].y == choqueO[ran1].peri[i].y)
					{
						score=0;
						gotoxy(90,5);cout<<"     ";
						gotoxy(0,10);
						return 1;
					}
				}
			}
		}
		
		void pasar1()//todos los valores de posicionamiento de los caracteres y el caracter en si
		{
			for(int t=0;t<2;t++)
			{
				int q=0;
				int y;
				for(int i=0;i<11;i++)
				{
					y=11-i;//en vez de iniciar desde 0, inicia de la parte superior 11 y lo va recuciendo
					for(int j=0;j<21;j++)
					{
						if(dino[t][i][j]=='?')
						{
							car1[t].peri[q]={j,y};
							car1[t].D[q]='?';
							q++;
						}
						if(dino[t][i][j]=='?')
						{
							car1[t].peri[q]={j,y};
							car1[t].D[q]='?';
							q++;
						}
						if(dino[t][i][j]=='?')
						{
							car1[t].peri[q]={j,y};
							car1[t].D[q]='?';
							q++;
						}
					}
				}
			}
		}
		
		void pasar2()
		{
			for(int t=0;t<3;t++)
			{
				int q=0;
				int y;
				for(int i=0;i<2;i++)
				{
					y=1-i;//en vez de iniciar desde 0, inicia de la parte superior 11 y lo va recuciendo
					for(int j=0;j<15;j++)
					{
						if(saltod[t][i][j]=='?')
						{
							car2[t].peri[q]={j,y};
							car2[t].D[q]='?';
							q++;
						}
						if(saltod[t][i][j]=='?')
						{
							car2[t].peri[q]={j,y};
							car2[t].D[q]='?';
							q++;
						}
						if(saltod[t][i][j]=='?')
						{
							car2[t].peri[q]={j,y};
							car2[t].D[q]='?';
							q++;
						}
					}
				}
			}
		}
		void pasar3()
		{
			for(int t=0;t<5;t++)
			{
				int q=0;
				int y=0;
				for(int i=0;i<9;i++)
				{
					y=8-i;//en vez de iniciar desde 0, inicia de la parte superior 9 y lo va recuciendo
					for(int j=0;j<23;j++)
					{
						if(trees[t][i][j]=='?')
						{
							car3[t].peri[q]={j,y};
							car3[t].D[q]='?';
							q++;
						}
					}
				}
			}
			int r=5;
			for(int t=0;t<2;t++)
			{
				int q=0;
				int y=0;
				for(int i=0;i<12;i++)
				{
					y=12-i;//en vez de iniciar desde 0, inicia de la parte superior 11 y lo va recuciendo
					for(int j=0;j<21;j++)
					{
						if(pajaro[t][i][j]=='?')
						{
							car3[r].peri[q]={j,y};
							car3[r].D[q]='?';
							q++;
						}
						if(pajaro[t][i][j]=='?')
						{
							car3[r].peri[q]={j,y};
							car3[r].D[q]='?';
							q++;
						}
						if(pajaro[t][i][j]=='?')
						{
							car3[r].peri[q]={j,y};
							car3[r].D[q]='?';
							q++;
						}
					}
				}
				r++;
			}
		}
		
		bool suelo()
		{
			float tem=0.0001f;
			float resultado=mapa->f(x);
			//Si y es 75 regresa un verdadero sino un falso
			return resultado-tem <=y && y<=resultado+tem;
		}
		void saltar()
		{
			if(suelo())
			{
				if(ag>=1.0f)//si es mayor o igual a 1.0 se puede ejecutar el salto
					vy=salto;//si el dino esta agachado no se puede saltar
				sal=1;
			}
		}
		void abajo()
		{
			if(suelo())//si regresa un verdadero
			{
				y=mapa->f(x);//y toma el valor de mapa = 75
				ag=0.0f;
			}
		}
		void ejecucion(float dt)
		{
			ag+=0.2f;
			//resultado=75
			vy-=1150.0f*dt;//Valor para que el salto sea mas o menos alto
			//gotoxy(10,0);cout<<vy;
			resultado=mapa->f(x);
			y+=dt*vy;//velocidad del salto/ que tan rapido salta y baja
			//gotoxy(10,1);cout<<vy;
			//gotoxy(10,2);cout<<y;
			if(y<resultado)
			{
				y=resultado;
				sal=0;//cuando el personaje se encuentre en el juego se asigna 0
			}
		}
						
};

void gameover(bool &game, int &score)
{
			int r=0;
			system("cls");
			pararmusica();			
			gotoxy(20,8);cout<<"\t\t---------   G A M E  O V E R   -----------"<<endl;
			
			while(r==0)
			{	gotoxy(20,12);cout<<"\t\tREINTENTAR              PRESIONA ENTER"<<endl;
				gotoxy(20,16);cout<<"\t\t----------------------------------------"<<endl;
				gotoxy(20,20);cout<<"\t\tSALIR                  PRESIONA ESCAPE"<<endl;
				gotoxy(20,24);cout<<"\t\t----------------------------------------"<<endl;
				char tecla = getch();
				if(tecla == ENTER)
				{	
					r++;
					score=0;
					system("cls");
					break;	
				}
				if(tecla == ESCAPE)
				{	
					game=false;//se cierra el juego
					r++;
					system("cls");
					break;	
				}
			}
}

void instruccionesdino(){
	bool bandera=true;
	do{
		system("cls");
		//TITULO
 	color(4);gotoxy(28,3); printf("%c",175);
 	color(11);gotoxy(30,3); cout<<"INSTRUCCIONES";
 	color(4);gotoxy(44,3); printf("%c",174);

 	
 	//ARRIBA
 	color(14);gotoxy(28,8); cout<<"SALTAR";
 	gotoxy(23,8); printf("%c",30);
 	gotoxy(20,7); printf("%c",201);
	gotoxy(20,8); printf("%c",186);	
	gotoxy(20,9); printf("%c",200);
	
	for( int a=21 ; a<26 ; a++)
		{
			gotoxy(a,7); printf("%c",205);
			gotoxy(a,9); printf("%c",205);	
		}
	
	gotoxy(26,7); printf("%c",187);
	gotoxy(26,8); printf("%c",186);	
	gotoxy(26,9); printf("%c",188);
	
	//ABAJO
	color(14);gotoxy(52,8); cout<<"AGACHARSE";
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
		
		
	//ESCAPE
	color(14);gotoxy(42,16); cout<<"SALIR";
 	gotoxy(36,16); cout<<"Esc";
 	gotoxy(34,15); printf("%c",201);
	gotoxy(34,16); printf("%c",186);	
	gotoxy(34,17); printf("%c",200);
	
	for( int a=35 ; a<40 ; a++)
		{
			gotoxy(a,15); printf("%c",205);
			gotoxy(a,17); printf("%c",205);	
		}
	
	gotoxy(40,15); printf("%c",187);
	gotoxy(40,16); printf("%c",186);	
	gotoxy(40,17); printf("%c",188);
	gotoxy(19,20);cout<<"Esquiva los obstaculos para subir puntaje!";
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

void juego_dino(){
	map mapa;
	personaje jugador(50.0f,&mapa);//almacena los datos de x y de mapa(direccion de mapa)
	personaje jugador1(50.0f,&mapa);
	char plano[HEIGHT/dH][WIDTH/dW+1];//altura 37 / ancho tiene 100+1=101
	
	float fps=24.0f;
	float dt=1.0f/fps;//0.0416
	float acumulador=0.0f;
	float cambio=0.0f;
	float des=0.0f;
	int offcam=0;
	float X=1200.0f;
	float X1=1200.0f;
	int cam=0;
	float cambio1=0.0f;
	int ran=rand()%6;
	int ran1=rand()%6;
	int score=0;
	int con=0;
	int sal=0;
	int DN=0;
	float dsm=1200.0f;
	int ad=0;
	bool game=true;
					
	int hi=0;
							
	clock_t inicio = clock();
	////////////
	pararmusica();
  	system("cls");
  	musica(dsonido[1]);				
	jugador.pasar1();
	jugador.pasar2();
	jugador.pasar3();
	mapa.pasar();
				
				
	fps=24.0f;
	dt=1.0f/fps;//0.0416
	acumulador=0.0f;
	cambio=0.0f;
	des=0.0f;
	offcam=0;
	X=1200.0f;
	X1=1200.0f;
	cam=0;
	cambio1=0.0f;
	ran=rand()%6;
	ran1=rand()%6;
	score=0;
	con=0;
	sal=0;
	DN=0;
	dsm=1200.0f;
	ad=0;
	game=true;
												
				
	for(int i=0; i<HEIGHT/dH;i++)
	{
		plano[i][WIDTH/dW]='\n';//plano[i][en la ultima posicion]= tiene un salto de linea
	}
	plano[HEIGHT/dH+1][WIDTH/dW]='\0';//plano en su altura + 1 va a determinar el final del array
					
	//calcula el tiempo de procesamiento (tiempo en ejecutarse)
				
	while(game)
	{
		if(ad==0 && DN==0)
			{
				system("color F0");//cambiar color fondo a blanco para dia
				ad=1;
			}
		if(ad==1 && DN==1)
			{
				system("color 0F");//cambiar color fondo para negro en noche
				ad=0;
			}
	clock_t final = clock();
	acumulador+=float(final-inicio)/CLOCKS_PER_SEC;//se pasa el valor del procesamiento
	cambio+=float(final-inicio)/CLOCKS_PER_SEC;
	cambio1+=float(final-inicio)/CLOCKS_PER_SEC;
	inicio=final;
					
	if(acumulador>=0.2f) acumulador=2.0f;
					
	if(cambio>=0.09f)
		{
			offcam=!offcam;//si offcam es 0 le asigna 1 & si es 1 le asigna 0//sirve para cambiar el movimiento de los pies
			cambio=0.0f;
		}
					
	if(cambio1>=0.13f)
		{
			cam=!cam;//si offcam es 0 le asigna 1 & si es 1 le asigna 0//movimiento de las alas del pajaro
			cambio1=0.0f;
		}
					
	while(acumulador>=dt)
		{
			if(GetKeyState(VK_UP)&0x8000)//detectar las tecla que presionas
				{
					jugador.saltar();//Si presiona la tecla arriba el dino salta
				}
			if(GetKeyState(VK_DOWN)&0x8000)
				{
					jugador.abajo();//Si presiona la tecla abajo el dino se agacha
				}
			if(GetKeyState(VK_ESCAPE)&0x800)
				{
					game=false;
					break;
				}
						
			dsm-=60.0f*dt;//desplazamiento del sol y la luna
			if(dsm<=(-200.0f))//cuando el sol/luna llega al extremo izquierdo
				{
					dsm=1200.0f;//regresa a la derecha
					DN=!DN; //si vale 1, pasa a 0 y si es 0, pasa a 1
				}
						
			des+=500*dt; //peque?o aumento//minusculo desplazamiento
			X-=500*dt;// desplazamiento de cactus
			if(X<=(-200.0f))//cuando el cactus llega al extremo izquierdo
				{
					X=1200.0f;//aparezca otra vez por la derecha
					ran=rand()%6;//tome un numero aleatorio 
				}
			if(X<=650.0f) sal=1;
			if(sal==1) X1-=500*dt;
			if(X1<=(-200.0f))//cuando el cactus llega al extremo izquierdo
				{
					X1=1200.0f;//aparezca otra vez por la derecha
					ran1=rand()%6;//tome un numero aleatorio 
				}
					
			jugador.ejecucion(dt);
			acumulador-=dt;
		}
		gotoxy(60,1);cout<<"MAX Puntaje: ";
		gotoxy(75,1);cout<<hi;
		gotoxy(40,1);cout<<"Puntaje: ";
		gotoxy(50,1);cout<<score;
							
		gotoxy(0,3);
		for(int i=0;i<HEIGHT/dH;i++)
			{
				for(int j=0;j<WIDTH/dW;j++)
				{
					plano[i][j]=' ';
				}
			}
					
			if(con>=20)//para que cada 20 ciclos aumente el puntaje
				{
					score++;
					con=0;
				}
			if(score == 0)//cuando hay una colision nuevamente aparecen obstaculos de la derecha
				{
					X=1200.0f;
					ran=rand()%6;
					X1=1200.0f;
					ran1=rand()%6;
					sal=0;
					dsm=1200.0f;
					DN=0;
					gotoxy(0,10);
				}
			
			if(hi<score)
				hi=score;//almacenar el puntaje maximo
					
								
			mapa.dibujar(plano,des);
			mapa.sunmon(plano,dsm,DN);
			jugador.dibujartrees(plano,X,ran,cam,choqueO);
			if(sal==1)jugador1.dibujartrees(plano,X1,ran1,cam,choqueO2);
			jugador.dibujar(plano,offcam,choqueD);
			//jugador.colision(ran,cam,choqueD,choqueO,score);
			//jugador1.colision(ran1,cam,choqueD,choqueO2,score);
			if(jugador.colision(ran,cam,choqueD,choqueO,score)==1 || jugador1.colision(ran1,cam,choqueD,choqueO2,score)==1 && con!=0){
				gameover(game,score);
			}
			puts(plano[0]);//Funcion dibuja(imprime) un array
				con++;
				}
	system("cls");	

}

int menu_dino()
{
	//////////////////////////
	do{	
	system("cls");	
	system("color 07");;
	color(15);
	musica(dsonido[0]);
	gotoxy(35,5); 	cout<<"DINOADVENTURE"<<endl;
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
  		case 1: juego_dino(); break;
	 	case 2:	instruccionesdino();break;
   		case 3: break;
		case 4: salir(); break;
		}
	if(opcion==3) break;
	}while(true);
}

