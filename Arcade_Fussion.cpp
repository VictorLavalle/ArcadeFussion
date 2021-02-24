//Librerias Necesarias Para el Programa
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <ctype.h>
#include <string.h>
#include "jugar.h"
#include "mejorespuntuaciones.h"

#define fila 15
#define columna 15
using namespace std;
//Uso del codigo ASCII Para emplear el esas teclas en los juegos
#define UP 72
#define LEFT 75
#define DOWN 80
#define RIGHT 77
#define ESC 27
#define SALIR 27 // esc
#define JUGAR 32 // espacio
#define PUNTUACIONES 115 // s
#define PUNTUACIONES2 83 // S
#define CONTROLES 119 // w
#define CONTROLES2 87 // W  
//Estructura y registro
//Estructura y definicion de tipo de dato
typedef struct player{
	char nombre[20];
	int puntos;
}player;

player Jugador;

//Funciones a Utilizar
void titulo_principal();//declaracion de la funcion para mostrar la priera pantalla
void menu_principal();//declaracion de la funcion para mostrar las diferentes opciones
void instrucciones();//declaracion de la funcion para mostrar el menu de instrucciones de cada juego
void menu_juegos();//declaracion de la funcion para mostrar y seleccionar 
void juego_gato();//declaracion de la funcion para generar el juego de gato
void usuario();//declaracion para la funcion de guardar el usuario y sus puntaje
void cargando();//declaracion de la funcion para animacion
//void gotoxy(int x,int y);//declaracion de la funcion para utlizar sistema de coordenas y movimiento con las teclas
void juego_buscaminas();//declaracion de la funcion para el juego de buscaminas
void ahorcado();//declaracion de la funcion para el juego de ahorcado
void dibujo();//declaracion de la funcion para el dibujo del ahorcado
void dibujo2();//declaracion de la funcion para el dibujo del ahorcado
void titulo_principal_ahorcado();//declaracion de la funcion para la interfaz principal del ahorcado
void imprimir_menu_tetris();
void controles_tetris();
void tetris();
void highscores();
void pedir_nombre();
void pedir_nombre_buscaminas();
void asignar_puntos(int variable);
void guardar_registroSnake(player Jugador);
void guardar_registroBuscaminas(player Jugador);
void mostrar_regisS();
void mostrar_regisB();



//Codigo Principal
int main() {
	system("Arcade Fussion Project");
	
	{	system("color 0a");
		titulo_principal();
		cargando();
		//Cancion de Intro y Animacion de la Consola
//		Beep(300,500);system("color 1a");
//		Sleep(50);
//		Beep(300,500);system("color 2b");
//		Sleep(50);
//		Beep(300,500);system("color 7c");
//		Sleep(50);
//		
//		Beep(250,500);system("color 6d");
//		Sleep(50);
//		
//		Beep(350,250);system("color 4a");
//		Beep(300,500);system("color 1b");
//		Sleep(50);
//		
//		Beep(250,500);system("color 7d");
//		Sleep(50);
//		
//		Beep(350,250);system("color 2b");
//		Beep(300,500);system("color 0a");
//		Sleep(50);
	}
	menu_principal();//Llamar a la Interfaz Principal
	return 0;
}
//Funcion Que Muestra Animacion de Carga
void cargando(){
	system("cls");
	printf("\n\n\n\t\t\tPorfavor Espere. Cargando...\n\n");
	printf("\t\t\t\t");
	for (int i=0;i<=15;i++)
		printf("%c",177);
	Sleep(150);
	printf("\r ");
	printf("\t\t\t\t");
	for (int i=0;i<=15;i++)
	{
		printf("%c",219);
		Sleep(200);
	}
}
//Funciones y clases Para Snake
//Objetos
class Snake{//Creacion del cuerpo de la serpiente como objeto
public://Control de Acceso
	int x,y;
	int dx,dy;
	char cuerpo;
};

class Fruta{ //Creeacion de la fruta de la serpiente como objeto
public:
	int x,y;
	char cuerpo=64;//Codigo ASCII
	
};

class Juego{//Bloque de Creacion del Juego
public:
	void main();//Funcion subprincipal de Snake
private: //Acceso Privado
	int score,nivel,velocidad;//Declaracion de Variables Para Resultados
	Snake snake[100]; //Dimension de la Serpiente
	Fruta fruta;//Objetivo a Comer
	int tam=4;//Tamaao inicial de la Serpiente
	int c=21,f=64;//dimensiones del cuadro de juego
	bool gameover=false;//para ciclar
	void tablero();//declaracion de la funcion para dibujar el cuadro de juego
	//Funciones para que se genere el juego
	void genFruta();//declaracion de la funcion para generar la fruta en el juego
	void genSnake();//declaracion de la funcion para generar la serpiente en el juego
	void loop();//declaracion de la funcion para ciclar hasta que el usuario decida
	void tecla();//declaracion de la funcion para utilizar las teclas
	void actualizar();//declaracion de la funcion para las banderas y controlar los cambios de movimiento y resultados
	void imprimir();//declaracion de la funcion para imprimir la serpiente en 
	void cfruta();//declaracion de la funcion para aumentar la serpiente al comer la fruta 
	void muerte();//declaracion de la funcion para terminar el juego en caso de que se toquen bordes o a si mismo
	void puntos();////declaracion de la funcion para ir contando los puntos e ir subiendo de nivel
	//Interfaces();
	void portada();//declaracion de la funcion para mostrar la interfaz principal del juego snake
	void muerte2();//declaracion de la funcion para mostrar la interfaz final al perder
	
};

//Muestra la interfaz al Perder
void Juego::muerte2(){// :: Empleo de una funcion orientada a un objeto
	system("cls");
	int c=24,f=79,r;//dimensiones del cuadro 
	char key;//Para obtener tecla de respuesta 
	for(int i=0 ; i<f ; i++){//impresion del cuadro
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//impresion del cuadro
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
	
	string g4meover[]={"  ____                       ___"," / ___| __ _ _ __ ___   ___ / _ \\__   _____ _ __ ",
		"| |  _ / _` | '_ ` _ \\ / _ \\ | | \\ \\ / / _ \\ '__|","| |_| | (_| | | | | | |  __/ |_| |\\ V /  __/ | ",
		" \\____|\\__,_|_| |_| |_|\\___|\\___/  \\_/ \\___|_|"}; //Dibujo de Game Over
	r=2;//coordena en la que se empieza a dibujar game over
	for(int i=0;i<5;i++){//Generacion del dibujo Game Over
		gotoxy(15,r);
		r++;
		cout<<g4meover[i]<<endl;
	}
	
	for(int i=0;i<11;i++){//Dibujo para el espacio dentro del cuadro
		gotoxy(20,r);
		r++;
		
	}
	gotoxy(33,14);//Muestra los resultados en pantalla a lo del cuadro de juego
	cout<<"Score: "<<score;
	r++;
	gotoxy(33,16);
	cout<<"Nivel: "<<nivel;
	
	
	pedir_nombre();
	asignar_puntos(score);
	guardar_registroSnake(Jugador);
	
	gotoxy(5,22);cout<<"Presione ESC para Salir o Cualquier otra Tecla para Seguir Jugando";
	key=getch();
	if(key==27){//en caso de no querer volver a jugar regresa al menu principal
		system("cls");
		return menu_principal();}
}


//Funcion Para Generar y Mostrar la Interfazz Principal de Snake
void Juego::portada(){
	system("cls");
	int c=24,f=79,r;//Declaracion de las dimensiones
	for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
	//Espacio donde se empezara a generar el dibujo de "SNAKE"
	r=0;  
	for(int i=0;i<14;i++){
		gotoxy(20,r);
		r++;
	}
	r=10;
	string snkl[]={"                     __     ","   _________  ____ _/ /_____","  / ___/ __ \\/ __ `/ //_/ _ \\",
		" (__  ) / / / /_/ / ,< /  __/","/____/_/ /_/\\__,_/_/|_|\\___/"}; //Dibujo del titulo SNAKE
	for(int i=0;i<5;i++){//Generador del dibujo
		gotoxy(26,r);
		r++;
		cout<<snkl[i]<<endl;
	}
	gotoxy(23,21);
	cout<<"Presione Cualquier Tecla Para Empezar";
	system("pause>null");
}


//Funcion Para Mostrar Progreso del Juego
void Juego::puntos(){
	gotoxy(f+2,2);
	cout<<"Score: "<<(score)*1;
	gotoxy(f+2,4);
	cout<<"Level: "<<nivel;
	gotoxy(f+2,6);
	cout<<"Length: "<<tam;
}
//Funcion que Genera el Cuadro de Juego
void Juego::tablero(){
	for(int i=1 ; i<f ; i++){
		gotoxy(i,1);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=1 ; i<=c ; i++){
		gotoxy(1,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
}

//Funcion que Genera la posician de la Fruta Aleatoriamente Dentro del Cuadro de Juego
void Juego::genFruta(){
	
	//Declaracian de las coordenas de la fruta
	fruta.x = 2+( rand() % (f-2) );
	fruta.y = 2+(rand() % (c-2));
	gotoxy(fruta.x,fruta.y);
	cout<<fruta.cuerpo;//Impresian de la Fruta
	
}

//Funcion Para Determinar cuando es que se pierde en el Snake
void Juego::muerte(){
	//Si la Serpiente Toca algun borde se pierde automaticamente
	if(snake[0].x==1 || snake[0].x==f || snake[0].y==1 || snake[0].y==c)
		gameover=true;
	//Si la Serpiente se Toca a si misma, se pierde automaticamente
	for(int i=1;i<tam && gameover==false;i++){
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
			gameover=true;
		}
		
	}
}

//Funcion Para Declarar el uso de las Flechas 
void Juego::tecla(){
	
	char key;//Variable Para Recibir el Uso de las teclas
	
	if (!gameover){//Si no se ha perdido, entonces sigue aceptando las teclas de movimiento
		if (kbhit()==1){
			key=getch();
			
		}
		if((key==72) && snake[0].dy !=1){//Mover la Serpiente Hacia Arriba
			snake[0].dx=0;
			snake[0].dy=-1;
		}
		if((key==80) && snake[0].dy !=-1){//Mover la Serpiente Hacia Abajo
			
			snake[0].dx=0;
			snake[0].dy=1;
		}
		if((key==75) && snake[0].dx !=1){//Mover la Serpiente Hacia la Izquierda
			
			snake[0].dx=-1;
			snake[0].dy=0;
		}
		if((key==77) && snake[0].dx !=-1){//Mover la Serpiente Hacia la Derecha
			
			snake[0].dx=1;
			snake[0].dy=0;
		}
	}
}
//Funcion para ir Generando el cuerpo de la serpiente  
void Juego::genSnake(){
	int i;
	snake[0].x=30;
	snake[0].y=10;
	snake[0].dx=1;
	snake[0].dy=0;
	snake[0].cuerpo=220;//Cabeza de la Serpiente
	
	
	
	for(i=1;i < tam; i++){//Cuerpo de la Serpiente
		snake[i].x=snake[i-1].x-1;
		snake[i].y=snake[i-1].y;
		snake[i].cuerpo=220;
	}
	
	
	for(i=0; i<tam; i++){
		gotoxy(snake[i].x,snake[i].y);
		cout<<snake[i].cuerpo;
	}
}

//Funcion Para Aumentar el Tamaao de la Serpiente Cuando Coma una Fruta
void Juego::cfruta(){
	if(snake[0].x==fruta.x && snake[0].y==fruta.y){
		genFruta();//llamado a la funcion para generar la fruta en el juego
		tam+=1;//Al "comer" la Fruta aumenta en 1 el tamaao de la serpiente
		snake[tam-1].cuerpo=220;
		score+=1;//Aumenta el Score por Cada Fruta Comida
		if(tam%10==0){//El nivel y la Velocidad aumenta cada que el tamaao de la serpiente llegue a multiplo de 10
			nivel++;
			velocidad-=26;
		}
		
	}
}
//Funcion Para ir Cambiando las banderas (posicion de las coordenas al moverse de la serpiente)
void Juego::actualizar(){
	int i;
	gotoxy(snake[tam-1].x,snake[tam-1].y);
	cout<<" ";//Rastro de Movimiento de la Serpiente
	
	for (i= tam-1; i>0; i--){
		snake[i].x=snake[i-1].x;
		snake[i].y=snake[i-1].y;
	}
	snake[0].x += snake[0].dx;
	snake[0].y += snake[0].dy;
	
}

//Funcion que va imprmiendo el cuerpo de la Serpiente
void Juego::imprimir(){
	int i;
	for(i= tam-1; i>=0; i--){
		gotoxy(snake[i].x,snake[i].y);
		cout<<snake[i].cuerpo;
	}
}
//Funcion Para entrar en ciclo hasta que el usuario decida
void Juego::loop(){
	while(!gameover){//Mientras no se pierda llama a las demas funciones para realizar el proceso del juego
		cfruta();
		puntos();
		actualizar();
		imprimir();
		tecla();
		tecla();
		tecla();
		muerte();
		Sleep(velocidad);
	}
}

//Funcion SubPrincipal Para dar valores iniciales al juego en el llamado de las funciones
void Juego::main(){
	system("color 0a");//color del ejecutable
	gameover=false;//Ciclo booleano
	portada();//Interfaz principal del snake
	system("cls");//Limpia la pantalla
	score=1;//Incializador de puntos
	velocidad=90;//Velocidad de Movimiento la Serpiente
	tam=4;//Tamaao inicial de la Serpiente
	nivel=1;//Inicializador del nivel alcanzdo
	tablero();//Llama a la funcion para imprimir el tablero en pantalla
	srand(time(NULL));//funcion de tiempo
	genSnake();//LLama a la Funcion para ir generando el cuerpo de la serpiente
	genFruta();//Llama a laFuncion Para ir generando las frutas
	loop();//Llama a la Funcion Para repetir en caso de ser indicado poir el usuario
	muerte2();//Impresion de interfaz de resultados al morir
	main();//Funcion principal
}
//Interfaces Principales
//Muestra Las Instrucciones
void instrucciones(){
	//Declaracion de Variables
	bool repetir=true;  //Para controlar el bucle del menu
	int c=22,f=78;//Declaracion de las dimensiones
	int opcion;  //Variables para seleccionar aplicando switch
	system("color 0b");
	do{
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(5,1);
		printf("\t\t   **************** COMO JUGAR ****************  \n");  //Titulo
		//Opciones
		gotoxy(26,4);printf("1. GATO (Tic Tac Toe)");
		gotoxy(26,6);printf("2. BUSCAMINAS(Minesweeper)");
		gotoxy(26,8);printf("3. SNAKE");
		gotoxy(26,10);printf("4. AHORCADO (Hangman)");
		gotoxy(26,12);printf("5. TETRIS");
		gotoxy(26,14);printf("0. Regresar al Menu Principal");
		gotoxy(21,18);printf("opcion: ");
	
	do{
		fflush(stdin);
		gotoxy(30,18);
		scanf("%d",&opcion);
	}while(opcion>=6 || opcion<0);
	fflush(stdin);
	system("cls");
	switch(opcion){
		
	case 1: //Instrucciones gato
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(7,1);
		printf("\t\t   **************** GATO ****************  \n"); 
		printf("\n\t\t\t   Juego Para 2 Personas.\n\n\t El jugador 1 tendra la ficha 'X' y el Jugador 2 la Ficha 'O'.\n\t Deberan Escribir el Numero Que Deesen de Acuerdo a la Plantilla\n\t Mostrada en Pantalla. Gana la Persona que Logre Juntar 3 de sus\n\t Fichas en Linea Horizontal, Vertical o Diagonal. El Resultado se\n\t Mostrara en la Parte Superior. En Caso de Querer Volver a jugar\n\t Escriba 'y', sino, 'n' para Regresar Al menu de Juegos.");
		printf("\n\n\n\tPresione Cualquier Tecla Para Regresar");
		system("pause>null");
		break;	
		
	case 2:	//Instrucciones Buscaminas
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(7,1);
		printf("\n\t\t   **************** BUSCAMINAS ****************\n"); 
		printf("\n\t\t\t       Juego de 1 Persona.\n\n\tEl Jugador Decidira que Dificultad Jugar y Este\n\tComenzara en Seguida. Para Marcar la Casilla Deseada\n\tSe debe Escribir Primero la Coordenada X y Presionar Enter;\n\tSeguidamente Escribir la Coordenada Y y Presionar Enter\n\tPor Cada Acierto, obtienes 25 puntos. Pierdes Cuando se\n\tHaya Seleccionado una Bomba.");		
		printf("\n\n\n\tPresione Cualquier Tecla Para Regresar");
		system("pause>null");
	break;
	case 3 :
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(7,1);
		printf("\n\t\t   **************** SNAKE ****************\n"); 
		gotoxy(29,4);printf("Juego de 1 Persona."); 
		gotoxy(3,6);printf("El Juego Comienza Automaticante Despuas de Presionar Culquier Tecla");
		gotoxy(3,7);printf("Se Controla el Movimiento Con las Flechas del Teclado el Objetivo");
		gotoxy(3,8);printf("es Comer los Frutos, Hasta Obtener el Tamaao Maximo. Se Pierde");
		gotoxy(3,9);printf("Tocando los Bordes o Si la Serpiente se Toca asa Misma.");
		gotoxy(3,10);printf("El Tiempo y el Puntaje se Muestra en la Parte Superior.");
		gotoxy(3,15);printf("Presione Cualquier Tecla Para Regresar");
		system("pause>null");
	break;
	case 4 :
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(5,1);
		printf("\n\t\t   **************** AHORCADO ****************\n"); 
		gotoxy(27,4);printf("Juego de 2 o Mas Personas."); 
		gotoxy(3,6);printf("El Juego Comienza Automaticante Despuas de Preionar Culquier Tecla");
		gotoxy(3,7);printf("Cualquier Jugador Debera Ingresar la Palabra a Adivinar por el Jugador ");
		gotoxy(3,8);printf("Contrario. El Jugador Contario Debera Adivinar la Palabra Ingresando");
		gotoxy(3,9);printf("Letra x Letra. Cuenta con 10 Vidas, por Cada Palabra Acertada Obtiene");
		gotoxy(3,10);printf("10 Puntos, por cada Vida Perdida se le restan 2 Puntos.");
		gotoxy(3,15);printf("Presione Cualquier Tecla Para Regresar");
		system("pause>null");
		break;
	case 5:	
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(5,1);
		printf("\n\t\t   **************** TETRIS ****************\n");
		gotoxy(27,4);printf("Juego de 1 Persona."); 
		gotoxy(3,6);printf("El Juego Comienza Automaticante Despuas de Preionar la Tecla Espacio");
		gotoxy(3,7);printf("Las Piezas son Controladas con las Teclas A-W-S-D-O-P");
		gotoxy(3,8);printf(" ");
		gotoxy(3,9);printf("A: Izquierda.   D: Derecha.  W: Caada Rapida  S: Bajar Pieza ");
		gotoxy(3,10);printf("             O: Rotar Pieza.               P: Guardar Pieza");
		gotoxy(3,11);printf(" ");
		gotoxy(3,12);printf("Iran cayendo un Montan de Piezas de Diferentes Tamaaos y Formas");
		gotoxy(3,13);printf("Debes Encajarlas Unas con Otras de la Forma Mas Perfecta Posible");
		gotoxy(3,14);printf("Cuando Conseguimos Hacer una Lanea Perfecta esa Lanea se Eliminara");
		gotoxy(3,15);printf("y Conseguiremos Puntos. A Medida que se Vayan Eliminando Laneas");
		gotoxy(3,16);printf("Conseguiremos ir Subiendo de Nivel, en Cada Nivel se ira Aumentando la");
		gotoxy(3,17);printf("Velocidad a la que las Piezas Caen, lo que lo Hace Mas Complicado.");
		gotoxy(3,20);printf("Presione Cualquier Tecla Para Regresar");
		system("pause>null");
	case 0:
		system("cls");
		repetir=false;
		break;
	}
	}while(repetir);
}
//Funcion Para mostrar el menu principal
void menu_principal(){
	//Declaracion de Variables
	bool repetir=true;  //Para controlar el bucle del menu
	int c=22,f=78;//Declaracion de las dimensiones
	int opcion;  //Variables para seleccionar en switch
	//Interfaz Principal
	

	do{
	system("color 0a");
	system("cls");//Limpiar Pantalla
	for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
	gotoxy(7,1);
	printf("\n\t\t   **************** ARCADE ****************  \n");  //Titulo
	//Opciones
	gotoxy(31,4);printf("1. Menu de Juegos");
	gotoxy(31,6);printf("2. Instrucciones");
	gotoxy(31,8);printf("3. Creditos");
	gotoxy(31,10);printf("4. Jugadores y Puntajes");
	gotoxy(31,12);printf("0. Salir");
	gotoxy(26,16);printf("Opcion: ");
	
	 do{
	 fflush(stdin);
	 gotoxy(35,16);
	 scanf("%d",&opcion);
	 }while(opcion>=5 || opcion<0);
	 fflush(stdin);
	 system("cls");
	 
	 
	 //Acciones a Realizar Segun la Opcion Seleccionada
	 switch(opcion){
		 
	 case 1:
		 //Comenzar Juego
		 system("cls");
		 menu_juegos();
	
	 break;
	 case 2://Instrucciones
		 system("cls");
		 instrucciones();
		 break;
	 case 3: //Creditos
		 system("cls");
		 system("color 0e");
		 for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			 gotoxy(i,0);
			 printf("%c",178);
			 gotoxy(i,c);
			 printf("%c",178);
		 }
		 for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			 gotoxy(0,i);
			 printf("%c",178);
			 gotoxy(f,i);
			 printf("%c",178);
		 }
		 gotoxy(5,1);
		 printf("\n\n\t\t\t      A Project Made By:\n\n\t\t\t        *Victor Lavalle\n\n\t\t\t        *Eberth Mezeta\n\n\t\t\t        *Alan Morales\n\n\n\t\tProgramacion Estructurada 2do Sem. UADY, FMAT 2019");
		 gotoxy(5,20); printf("Presione Cualquier Tecla Para Regresar");
		 system("pause>nul");
	 break;
	 case 4: //HighScores
		 system("cls");
		 system("color 0a");
		 highscores();
		 break;
	 //Se Termina el Programa
	 case 0:
		 system("cls");
		 printf("\n\n\n\n\t\t\t        GRACIAS POR UTILIZAR!      ");
		 system("pause>nul");//Para No Finalizar Enseguida
		 repetir=false;
		 exit(1);
	 break;
	 
	 }
	
	}while(repetir);
	
}
 

//Funcion Para mostrar el menu de Juegos
void menu_juegos(){
	//Declaracion de Variables
	bool repetir=true;  //Para controlar el bucle del menu
	int opcion;  //Variables para seleccionar en switch
	
	//Interfaz Principal
	
	do{
		system("cls");//Limpiar Pantalla
		system("color 0f");
		int c=22,f=78;//Declaracion de las dimensiones
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(9,1);
		printf("\n\t\t  **************** JUEGOS ****************  \n");  //Titulo
		//Opciones
		gotoxy(31,4);printf("1. GATO (Tic Tac Toe)");
		gotoxy(31,6);printf("2. BUSCAMINAS(Minesweeper)");
		gotoxy(31,8);printf("3. SNAKE");
		gotoxy(31,10);printf("4. AHORCADO (Hangman)");
		gotoxy(31,12);printf("5. TETRIS");
		gotoxy(31,14);printf("0. Regresar");
		gotoxy(26,18);printf("Opcion: ");

		do{
			fflush(stdin);
			gotoxy(35,18);
			scanf("%d",&opcion);
		}while(opcion>=6 || opcion<0);
		fflush(stdin);
		system("cls");
		
		
		//Acciones a Realizar Segun la Opcion Seleccionada
		switch(opcion){
			
		//Comenzar Juego de Tetris
		case 5:
			system("cls");
			cargando();
			tetris();
			break;
		//Comenzar Juego de Ahorcado	
		case 4:
		system("cls");
		cargando();
		ahorcado();
		break;
		//Se Regresa al menu Principal
		case 0:
			system("cls");
			menu_principal();
			break;
			
		case 1:
			//Comenzar Juegode Gato
			system("cls");
			cargando();
			juego_gato();
			break;
			
			
		case 2: //Buscaminas
			system("cls");
			cargando();
			juego_buscaminas();
			break;
			
		case 3: //Juego de Snake
			system("cls");
			cargando();
			Juego j;
			j.main();
			break;
		}
		
	}while(repetir);
	
}



//Funcion Para mostrar el Titulo principal
void titulo_principal(){
	system("cls");
	system("color 0a");
	int c=22,f=78;//Declaracion de las dimensiones
	for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}

	gotoxy(1,4);
	puts("           d8888 8888888b.   .d8888b.        d8888 8888888b.  8888888888 ");
	gotoxy(1,5);
	puts("          d88888 888   Y88b d88P  Y88b      d88888 888   Y88b 888       ");
	gotoxy(1,6);
	puts("         d88P888 888    888 888    888     d88P888 888    888 888  ");
	gotoxy(1,7);
	puts("        d88P 888 888   d88P 888           d88P 888 888    888 8888888 ");
	gotoxy(1,8);
	puts("       d88P  888 8888888P'  888          d88P  888 888    888 888  ");
	gotoxy(1,9);
	puts("      d88P   888 888 T88b   888    888  d88P   888 888    888 888  ");
	gotoxy(1,10);
	puts("     d8888888888 888  T88b  Y88b  d88P d8888888888 888  .d88P 888   ");
	gotoxy(1,11);
	puts("    d88P     888 888   T88b  'Y8888P' d88P     888 8888888P'  8888888888");
	gotoxy(2,17);
	puts("                     Oprima Cualquier Tecla Para Comenzar              \n");
	system("pause>null");
	system("cls");
	//usuario();system("pause>null");
	
}

//Gato
//Funcion Para el Juego Tic Tac Toe
void juego_gato(){
	//Declaracian de Variables	
	int jugador=1,error,empate=0,ganar=0;
	char c1='1',c2='2',c3='3',c4='4',c5='5',c6='6',c7='7',c8='8',c9='9',tiro,marca,respuesta='y';
	int c=22,f=78;//Declaracion de las dimensiones
	do{
		system("cls");// Limpia la Pantalla
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		system("color 0a");//Color de texto de la consola
		error=1;//Booleano
		
		//Impresian de Tablero
		gotoxy(5,1);printf("\t\t\t  ***JUEGO DE GATO***\n\n");
		printf("\n\t\t\t     %c | %c | %c\n",c1,c2,c3);
		printf("\t\t\t    ---+---+---\n");
		printf("\n\t\t\t     %c | %c | %c\n",c4,c5,c6);
		printf("\t\t\t    ---+---+---\n");
		printf("\n\t\t\t     %c | %c | %c\n\n\n",c7,c8,c9);

		//Asignacon de Marca Para Cada Jugador
		if(jugador==1){marca='X';}
		else{marca='O';}
		
		printf("\tTurno del Jugador %d:  ",jugador);//Muestra el turno del Jugador Actual
		fflush(stdin);//Limpia el Buffer
		do{
		scanf("%c",&tiro);//Entrada de Dato
		fflush(stdin);//Limpia el Buffer
		}while(tiro>'9'||tiro<'1');
		//Condicionales Para Cambiar el Namero Puesto Por la Ficha del Jugador Actual
		if (tiro=='1' && c1=='1') {c1=marca;}
		else if (tiro=='2' && c2=='2') {c2=marca;}
		else if (tiro=='3' && c3=='3') {c3=marca;}
		else if (tiro=='4' && c4=='4') {c4=marca;}
		else if (tiro=='5' && c5=='5') {c5=marca;}
		else if (tiro=='6' && c6=='6') {c6=marca;}
		else if (tiro=='7' && c7=='7') {c7=marca;}
		else if (tiro=='8' && c8=='8') {c8=marca;}
		else if (tiro=='9' && c9=='9') {c9=marca;}
		else {printf("\n\tError! Movimiento No Valido\n");Sleep(400); error=2;}
		
		
		
		//Condicionales para Detectar 3 Marcas Iguales en Fila y Ganar el Juego
		if(c1=='X'||c1=='O'){
			if(c2==c1&&c3==c1){
				ganar=1;
			}
			if(c4==c1&&c7==c1){
				ganar=1;
			}
		}
		//Condicionales para Detectar 3 Marcas Iguales en Diagonal y Ganar el Juego
		if(c5=='X'||c5=='O'){
			if (c1 == c5 && c9 == c5)
			{ganar=1;}
			if (c2 == c5 && c8 == c5)
			{ganar=1;}
			if (c4 == c5 && c6 == c5)
			{ganar=1;}
			if (c3 == c5 && c7 == c5)
			{ganar=1;}
		}
		//Condicionales para Detectar 3 Marcas Iguales en Columna y Ganar el Juego
		if(c9=='X'||c9=='O'){
			if (c6 == c9 && c3 == c9)
			{ganar=1;}
			if (c7 == c9 && c8 == c9)
			{ganar=1;}
		}
		//Condicioanles Para Detectar Si Hay Empate
		if ((c1 != '1' && c2 != '2' && c3 != '3' &&
			 c4 != '4' && c5 != '5' && c6 != '6' &&
			 c7 != '7' && c8 != '8' && c9 != '9') &&
			ganar == 0){
			empate=1;
		}
		
		if (ganar==1||empate==1){
			system("cls");//Limpia La Pantalla yMuestra Resultado Final
			if (ganar==1)
			{
				for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
					gotoxy(i,0);
					printf("%c",178);
					gotoxy(i,c);
					printf("%c",178);
				}
				for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
					gotoxy(0,i);
					printf("%c",178);
					gotoxy(f,i);
					printf("%c",178);
				}
				gotoxy(5,2);printf("\t\t\taJUGADOR: %d HA GANADO!\n\n",jugador);
				printf("\n\t\t\t      %c | %c | %c\n",c1,c2,c3);
				printf("\t\t\t     ---+---+---\n");
				printf("\n\t\t\t      %c | %c | %c\n",c4,c5,c6);
				printf("\t\t\t     ---+---+---\n");
				printf("\n\t\t\t      %c | %c | %c\n\n",c7,c8,c9);
				
			}
			
			if (empate==1){
				for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
					gotoxy(i,0);
					printf("%c",178);
					gotoxy(i,c);
					printf("%c",178);
				}
				for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
					gotoxy(0,i);
					printf("%c",178);
					gotoxy(f,i);
					printf("%c",178);
				}
				gotoxy(5,1);printf("\t\t\t    aaEMPATE!! \n");
				printf("\n\t\t\t     %c | %c | %c\n",c1,c2,c3);
				printf("\t\t\t    ---+---+---\n");
				printf("\n\t\t\t     %c | %c | %c\n",c4,c5,c6);
				printf("\t\t\t    ---+---+---\n");
				printf("\n\t\t\t     %c | %c | %c\n\n\n",c7,c8,c9);
				
			}
			
			gotoxy(3,15);printf("  aDesea Jugar de Nuevo: Si.(Oprima 'y')    No. (Cualquier Otra Tecla)?  ");
			fflush(stdin);//Limpia el Buffer de los Datos Almacenados
			gotoxy(75,15);scanf("%c",&respuesta);
			
			
			//Si se Decide Volver a Jugar se Vueleve a imprimir el tablero sin marcas y se reinicia contadore
			if (respuesta=='y'||respuesta=='Y')
			{
				empate=0;
				jugador=2;
				ganar=0;
				c1='1';c2='2';c3='3';c4='4';c5='5';c6='6';c7='7';c8='8';c9='9';
			}
		}

		//Para Cambiar de Turno
		if(error==1)
		{
			if (jugador==1)
			{
				jugador=2;
			}
			else
			{
				jugador=1;
			}
		}
		
	}while(respuesta=='y'||respuesta=='Y');//Se Va a repeitr el juego hasta que el usuario desee salir
}

//Buscaminas
//Funcian Para LLenar el Tablero de Buscaminas
void llenar_matriz(int matriz[][15]){
	for (int i=0;i<fila;i++){
		for (int j=0;j<columna;j++){
			matriz[i][j]=2;
		}
	}
}
//Funcian para dar la bienvenida al usuario
void imprimir_titulo(){
	int c=22,f=78;//Declaracion de las dimensiones
	for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
	gotoxy(5,1);printf("\t\t **************** BUSCAMINAS ****************  \n");  //Titulo
	gotoxy(7,3);printf("\t\t   >>Ingrese el Nivel de su Preferencia");
	//Opciones
	gotoxy(31,6);printf("1. Facil");
	gotoxy(31,8);printf("2. Medio");
	gotoxy(31,10);printf("3. Dificil");
	gotoxy(31,12);printf("4. Imposible");
	gotoxy(31,14);printf("0. Regresar al Menu Principal");
	gotoxy(26,17);printf("Opcion: ");
}

//Funcian para seleccionar el nivel y la cantidad de bombas
int total_de_bombas(int x){
	switch(x){
	case 1:
		return 10;
		break;	
	case 2:
		return 25;
		break;
	case 3:
		return 50;
		break;
	case 4:
		return 100;
		break;	
	}
	return 0;
}
//Funcian para colocar las bombas
void colocar_bombas (int matriz[][15],int bomb){
	int i, dominio, codominio;
	
	for(i = 1; i <= bomb; i++)
	{
		dominio = 0 + rand() % 14;
		codominio = 0 + rand() % 14;
		
		matriz[dominio][codominio] = 3;
	}
}
//Funcian para imprimir el tablero
void imprimir_interfaz(int matriz[][15],int status){
	int i, j;
	
	for(i = 0; i <= fila-1; i++)  //encabezado
		printf("%d ", i);
	
	printf("\n");  //nueva linea
	
	for(i = 0; i <=columna; i++)
		printf ("%c%c",205,205);
	
	printf("\n");
	
	for(i = 0; i <= fila -1; i++){
		printf ("%c ",186);
		for(j = 0; j <= columna - 1; j++){
			
			if(matriz[i][j] == 1)
				printf("%d ", matriz[i][j]);
			else if((matriz[i][j] == 3) && (status == 0))
				printf("%c ",157);
			else
				printf("%c ",254);         
		}
		
		printf("%c %d", 186,i);    
		printf("\n");  
		
	}
	for(i = 0; i <=fila; i++){
		printf ("%c%c",205,205);
	}	
	printf ("\n");
}
//Funcian Para Aumentar los puntos en caso de acertar
void puntos_busc(int cont){
//funcian Para Llevar el tiempo en la partida hasta perder
	int auxiliar;
	auxiliar=cont*25;
	printf ("\n\t\t\t\tPuntaje: %d \n\n",auxiliar);
	
}

//Funcion Para Llevar el Tiempo
void cronometro(int status){
	int horas=0,min=0,sec=0,x;
	
	while (status!=1 && status !=0){
		x=1000;
		sec++;
		if(sec==60){
			sec=0;
			min++;
		}if (min==60){
			min=0;
			horas++;
		}
		printf ("Tiempo: %.2d:%.2d:%.2d",horas,min,sec);
		Sleep(x);
	}
	
}
//Unificacian de Funciones Para Desarrollar el Buscaminas
void juego_buscaminas(){
	int buscaminas[fila][columna];
	int nivel,bombas,repetir;//Variables que determinan de la dificultad del juego
	int decision;
	do{
		system("cls");	
		//Estadisticas del juego
		int i,j,contador=0;
		int estatus=-1;
		//Se imprime y llena el tablero del buscaminas	
		llenar_matriz(buscaminas);	
		imprimir_titulo();
		//Se captura el nivel
		do{
			scanf("%d",&nivel);
			fflush(stdin);
			if(nivel==0){
				return menu_principal();
			}
			if(nivel<0 || nivel>4){
				printf ("\n <<Caracter No Valido>>\n   Opcion: ");
			}
		}while(nivel<0 || nivel>4);
		bombas=total_de_bombas(nivel);
		srand(time(NULL)); 
		
		colocar_bombas(buscaminas,bombas);
		system("cls");
		printf("\n\t\t\t>>Try Your Best<<\t\t\t\n\n");puntos_busc(contador);
		imprimir_interfaz(buscaminas,estatus); 
		do{
			puts("Ingrese su tiro: (x,y)");
			
				do{
				printf("X=");scanf("%d",&i);
				if ((i<0 || i>14)){
					printf ("<<Tiro No Valido>> \n Ingrese su Tiro Nuevamente\n");
				}
				fflush(stdin);	
				}while(!(i>=0 &&  i<=14) );
				
				do{
				printf("Y=");scanf("%d",&j);
				if ((j<0 || j>14)){
					printf ("<<Tiro No Valido>> \n Ingrese su Tiro Nuevamente\n");
				}
				fflush(stdin);	
				}while(!(j>=0 &&  j<=14) );
				
			system("cls");
			
			if (buscaminas[i][j]==3){
				
				printf("\t\t\t>>'BUSCAMINAS.EXE'<<\t\t\t\t\n\n");
				estatus=0;
				imprimir_interfaz(buscaminas,estatus); 
				puntos_busc(contador);
				puts("\n!!!!Usted Ha Perdido!!!!\n");
			}else{
				
				if (buscaminas[i][j]==2){
					
					printf("\n\t\t\t\t\t>>'BUSCAMINAS.EXE'<<\t\t\t\t\t\n\n");
					buscaminas[i][j]=1;
					contador++;
					estatus=-1;
					puntos_busc(contador);
					imprimir_interfaz(buscaminas,estatus); 
				}
			} if (contador== (255-bombas)){
				
				printf("\n\t\t\t\t\t\t>>'BUSCAMINAS.EXE'<<\t\t\t\t\t\n\n");
				puntos_busc(contador);
				estatus=1;
				imprimir_interfaz(buscaminas,estatus);
				puts("\n!!!Usted Ha Ganado!!!\n");
			}
			
		}while(estatus!=1 && estatus!=0);
		//Se pregunta si el jugador desea seguir jugando
		printf("aDesea Jugar de Nuevo?: 1 - Si    0 - No: ");
		fflush(stdin);//Limpia el Buffer de los Datos Almacenados
		do{
		scanf("\t%d",&decision);
		fflush(stdin);
		if(decision==1){
			repetir=1;
			break;
		}
		if(decision==0){
			repetir=0;
			
			pedir_nombre_buscaminas();
			asignar_puntos(contador*25);
			guardar_registroBuscaminas(Jugador);
			
			menu_juegos();
		}
		if(decision!=1||decision!=0){
			puts("\n<<Caracter No Valido>>\n");
		}
		}while(decision!=1||decision!=0);
		system("cls");	
	}while(repetir);
	
}
//Ahorcado
//Unificacion de sus Funciones
void ahorcado(){
	system("color 0b");
	fflush(stdout);
	// la palabra o frase y sus espacios en Memoria
	char palabra[40],rep[100],temporal[100];
	//letra
	char pal;
	int oportunidades,victoria,puntos=0,repetir;
	int inicial,i,j,longitud,bien=0,temp, repetido,i1,i2,i3,answer;
	titulo_principal_ahorcado();
	do{
	oportunidades=10;
	system("cls");
	fflush(stdin);
	// preguntamos a el jugador la palabra que guste y contamos la cantidad de caracteres 
	dibujo();
	gotoxy(24,3);
	printf(" Ingrese Su Palabra:\n");
	gotoxy(28,5);
	fflush(stdin);
	gets(palabra);
	longitud = 0,inicial = 0,j = 0;
	
	rep[0] = ' ';
	rep[1] = '\0';
	
	
	do {
		fflush(stdin);
		system("cls");
		dibujo();
		temp=0;
		// aqui leemos cuantos caracteres va a tener la palabra, y ponemos un espaco en blanco
		if(inicial == 0) {
			i1=strlen(palabra);
			for(i=0;i<i1;i++) {
				if(palabra[i] == ' ') {
					temporal[i] = ' ';
					longitud++;
				}
				else {
					temporal[i] = '_';       
					longitud++;
				}
			}
		}
		//cambiamos el valor inicial para seguir corriendo el programa
		inicial = 1;
		
		temporal[longitud] = '\0';
		//verificamos si la letra esta repetida o escribimos la letra
		i2=strlen(rep);
		for(i=0;i<i2;i++) {
			if(rep[i] == pal) {
				repetido = 1;
				break;
			}
			else {
				repetido = 0;
			}
		}
		// si no esta repetida la letra la imprimimos en temporal y aumentamos el contador de bien
		if(repetido == 0) {
			for(i=0;i<i1;i++) {
				if(palabra[i] == pal) {
					temporal[i] = pal;
					bien++;
					puntos= puntos+10;
					temp=1;
				}
			}
		}
		// si n se escribio nada se quita una de mis  oportunidades
		if(repetido == 0) {
			puntos=puntos-2;
			if(temp == 0) {
				oportunidades = oportunidades - 1;
			}
		}
		else {
			printf("Ya se ha introducido este caracter");
			printf("\n\n");
		}
		printf("\n");
		// imprimimos la letra
		gotoxy(35,6);
		i3=strlen(temporal);
		for(i=0;i<i3;i++) {
			printf(" %c ",temporal[i]);
		}
		
		printf("\n");
		//checamos si gana
		if(strcmp(palabra,temporal) == 0) {
			victoria = 1;
			break;
		}
		do{
		gotoxy(45,1);
		printf("Letras Bien: %d",bien);
		gotoxy(63,1);
		printf("Puntaje: %d",puntos+2);
		//Barra de Vida
		gotoxy(23,1);
		printf("Vidas Restantes: %d",oportunidades);
		rep[j] = pal;
		j++;
		}while(!(oportunidades<10));
		//chacamos si pierde
		if (oportunidades==0)
		{
			puntos=0;
			bien=0;
			oportunidades=10;
			break;
		}
		gotoxy(32,4);
		printf("Introduzca una letra:");
		scanf("\n%c",&pal);
		
	}while(oportunidades != 0);
	
	
	if(victoria==1) {
		system("cls");
		gotoxy(2,6);
		printf("Y88b   d88P                     888       888 d8b \n");  
		gotoxy(2,7);
		printf(" Y88b d88P                      888   o   888 Y8P \n");  
		gotoxy(2,8);
		printf("  Y88o88P                       888  d8b  888           \n"); 
		gotoxy(2,9);
		printf("   Y888P  .d88b.  888  888      888 d888b 888 888 88888b.\n");
		gotoxy(2,10);
		printf("    888  d88''88b 888  888      888d88888b888 888 888 '88b\n");
		gotoxy(2,11);
		printf("    888  888  888 888  888      88888P Y88888 888 888  888 \n");
		gotoxy(2,12);
		printf("    888  Y88..88P Y88b 888      8888P   Y8888 888 888  888 \n");
		gotoxy(2,13);
		printf("    888   'Y88P'   'Y88888      888P     Y888 888 888  888 \n");
		gotoxy(28,17);
		gotoxy(28,17);printf("Desea Jugar de Nuevo: 1 - Si    0 - No ?\n");
		fflush(stdin);//Limpia el Buffer de los Datos Almacenados
		do{
			scanf("%d",&answer);
			fflush(stdin);
			if(answer==1){
				repetir=1;
				system("cls");
				puntos=0;
				oportunidades=10;
				victoria=0;
				inicial=1;
				i=0;j=0;
				longitud=0;
				bien=0;
				temp=0;i1=0;i2=0;i3=0;
				ZeroMemory(palabra, sizeof(palabra));
				ZeroMemory(rep, sizeof(rep));
				ZeroMemory(temporal, sizeof(temporal));
				break;
			}
			if(answer==0){
				ZeroMemory(palabra, sizeof(palabra));
				ZeroMemory(rep, sizeof(rep));
				ZeroMemory(temporal, sizeof(temporal));
				repetir=0;
				menu_juegos();
			}
			if(answer!=1||answer!=0){
				puts("\n<<Caracter No Valido>>\n");
			}
		}while(answer!=1||answer!=0);
		system("cls");	
	}
	else {
		dibujo2();
		system("cls");
		gotoxy(2,6);
		printf("Y88b   d88P  .d88888b.  888     888      888      .d88888b.   .d8888b.  8888888888 \n");  
		gotoxy(2,7);
		printf(" Y88b d88P  d88P' 'Y88b 888     888      888     d88P' 'Y88b d88P  Y88b 888\n");  
		gotoxy(2,8);
		printf("  Y88o88P   888     888 888     888      888     888     888 Y88b.      888   \n"); 
		gotoxy(2,9);
		printf("   Y888P    888     888 888     888      888     888     888  'Y888b.   8888888\n");
		gotoxy(2,10);
		printf("    888     888     888 888     888      888     888     888     'Y88b. 888\n");
		gotoxy(2,11);
		printf("    888     888     888 888     888      888     888     888       '888 888        \n");
		gotoxy(2,12);
		printf("    888     Y88b. .d88P Y88b. .d88P      888     Y88b. .d88P Y88b  d88P 888 \n");
		gotoxy(2,13);
		printf("    888      'Y88888P'   'Y88888P'       88888888 'Y88888P'   'Y8888P'  8888888888\n");
		gotoxy(28,17);printf("Desea Jugar de Nuevo: 1 - Si    0 - No ?\n");
		fflush(stdin);//Limpia el Buffer de los Datos Almacenados
		do{
			scanf("%d",&answer);
			fflush(stdin);
			if(answer==1){
				repetir=1;
				system("cls");
				puntos=0;
				oportunidades=10;
				victoria=0;
				inicial=1;
				i=0;j=0;
				longitud=0;
				bien=0;
				temp=0;i1=0;i2=0;i3=0;
				ZeroMemory(palabra, sizeof(palabra));
				ZeroMemory(rep, sizeof(rep));
				ZeroMemory(temporal, sizeof(temporal));
				break;
			}
			if(answer==0){
				ZeroMemory(palabra, sizeof(palabra));
				ZeroMemory(rep, sizeof(rep));
				ZeroMemory(temporal, sizeof(temporal));
				repetir=0;
				menu_juegos();
			}
			if(answer!=1||answer!=0){
				puts("\n<<Caracter No Valido>>\n");
			}
		}while(answer!=1||answer!=0);
		system("cls");	
	}
	}while(repetir);//Se Va a repeitr el juego hasta que el usuario desee salir
}
//Dibujo del Ahorcado 
void dibujo(){
	system("color 0f");
	int c=22,f=20;//Declaracion de las dimensiones
	
	for(int i=0 ; i<f ; i++){//Ancho de Borde
		gotoxy(i,1);
		printf("%c",176);
	}
	for(int i=0 ; i<=c ; i++){//Alto de Borde
		gotoxy(1,i);
		printf("%c",176);
	}
	for(int i=2 ; i<=5 ; i++){//Cuerda
		gotoxy(16,i);
		printf("%c\n",186);
	}
	gotoxy(6,6);
	printf("         ***             \n");
	gotoxy(6,7);
	printf("        *****         \n");
	gotoxy(6,8);
	printf("       *0***0*       \n");
	gotoxy(6,9);
	printf("       *******     \n");
	gotoxy(6,10);
	printf("        *****    \n");
	gotoxy(6,11);
	printf("         ***             \n");
	
	for(int i=12 ; i<=17 ; i++){//Torso
		gotoxy(16,i);
		printf("*\n");
	}
	for(int i=12 ; i<17 ; i++){//Brazo Izq
		gotoxy(i,13);
		printf("*");
	}
	for(int i=15 ; i<21 ; i++){//Brazo derecho
		gotoxy(i,13);
		printf("*");
	}
	//Piernas
	gotoxy(15,18);
	printf("* *");
	gotoxy(14,19);
	printf("*   *");
	gotoxy(13,20);
	printf("*     *");
	gotoxy(12,21);
	printf("*       *");
}
//Dibujo del Ahorcado al Perder
void dibujo2(){
//Interfaz Principal de Carga
	system("color 0f");
	int c=22,f=20;//Declaracion de las dimensiones
	
	for(int i=0 ; i<f ; i++){//Ancho de Borde
		gotoxy(i,1);
		printf("%c",176);
	}
	for(int i=0 ; i<=c ; i++){//Alto de Borde
		gotoxy(1,i);
		printf("%c",176);
	}
	for(int i=2 ; i<=5 ; i++){//Cuerda
		gotoxy(16,i);
		printf("%c\n",186);
	}
	gotoxy(6,6);
	printf("         ***             \n");
	gotoxy(6,7);
	printf("        *****         \n");
	gotoxy(6,8);
	printf("       *X***X*       \n");
	gotoxy(6,9);
	printf("       *******     \n");
	gotoxy(6,10);
	printf("        *****    \n");
	gotoxy(6,11);
	printf("         ***             \n");
	
	for(int i=12 ; i<=17 ; i++){//Torso
		gotoxy(16,i);
		printf("*\n");
	}
	for(int i=12 ; i<17 ; i++){//Brazo Izq
		gotoxy(i,13);
		printf("*");
	}
	for(int i=15 ; i<21 ; i++){//Brazo derecho
		gotoxy(i,13);
		printf("*");
	}
	//Piernas
	gotoxy(15,18);
	printf("* *");
	gotoxy(14,19);
	printf("*   *");
	gotoxy(13,20);
	printf("*     *");
	gotoxy(12,21);
	printf("*       *");
	//Texto
	gotoxy(35,6);
	printf("8888888b.      8888888     8888888b. \n");  
	gotoxy(35,7);
	printf("888   Y88b       888       888   Y88b\n");  
	gotoxy(35,8);
	printf("888    888       888       888    888\n"); 
	gotoxy(35,9);
	printf("888   d88P       888       888   d88P \n");
	gotoxy(35,10);
	printf("8888888P'        888       8888888P'  \n");
	gotoxy(35,11);
	printf("888 T88b         888       888   \n");
	gotoxy(35,12);
	printf("888  T88b  d8b   888   d8b 888     d8b \n");
	gotoxy(35,13);
	printf("888   T88b Y8P 8888888 Y8P 888     Y8P \n");
	
	system("pause>null");
}

//Interfaz Principal del Ahorcado 
void titulo_principal_ahorcado(){
	int c=20,f=95;//Declaracion de las dimensiones
	system("color 0a");
	system("cls");
	for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
		gotoxy(i,0);
		printf("%c",178);
		gotoxy(i,c);
		printf("%c",178);
	}
	for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
		gotoxy(0,i);
		printf("%c",178);
		gotoxy(f,i);
		printf("%c",178);
	}
	gotoxy(2,6);
	printf("d8888 888    888  .d88888b.  8888888b.   .d8888b.        d8888 8888888b.   .d88888b.\n");  
	gotoxy(2,7);
	printf("d8888 888    888  .d88888b.  8888888b.   .d8888b.        d8888 8888888b.   .d88888b.\n");  
	gotoxy(2,8);
	printf("d88888 888    888 d88P' 'Y88b 888   Y88b d88P  Y88b      d88888 888  'Y88b d88P' 'Y88b \n"); 
	gotoxy(2,9);
	printf("d88P888 888    888 888     888 888    888 888    888     d88P888 888    888 888     888 \n");
	gotoxy(2,10);
	printf("d88P 888 8888888888 888     888 888   d88P 888           d88P 888 888    888 888     888 \n");
	gotoxy(2,11);
	printf("d88P  888 888    888 888     888 8888888P0'  888          d88P  888 888    888 888     888 \n");
	gotoxy(2,12);
	printf("d88P   888 888    888 888     888 888 T88b   888    888  d88P   888 888    888 888     888 \n");
	gotoxy(2,13);
	printf("d8888888888 888    888 Y88b. .d88P 888  T88b  Y88b  d88P d8888888888 888  .d88P Y88b. .d88P \n");
	gotoxy(2,14);
	printf("d88P     888 888    888  'Y88888P'  888   T88b  'Y8888P' d88P     888 8888888P'   'Y88888P'  \n");
	gotoxy(28,17);
	printf("Oprima Cualquier Tecla Para Comenzar");
	system("pause>null");
}
//Funciones Para Crear Archivos de Texto Donde Se Registren los Puntajes Mas Altos
//Interfaz Donde Se Muestra el menu para los Puntajes
void highscores(){
	//Declaracion de Variables
	bool repetir=true;  //Para controlar el bucle del menu
	int opcion;  //Variables para seleccionar aplicando switch
	int c=22,f=78;//Declaracion de las dimensiones
	system("color 0c");
	do{
		system("cls");
		for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
			gotoxy(i,0);
			printf("%c",178);
			gotoxy(i,c);
			printf("%c",178);
		}
		for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
			gotoxy(0,i);
			printf("%c",178);
			gotoxy(f,i);
			printf("%c",178);
		}
		gotoxy(1,2);
		printf("\t   **************** JUGADORES RECIENTES ****************  \n");  //Titulo
		//Opciones
		gotoxy(26,4);printf("1. BUSCAMINAS(Minesweeper)");
		gotoxy(26,6);printf("2. SNAKE");
		gotoxy(26,8);printf("0. Regresar al Menu Principal");
		gotoxy(21,11);printf("Opcion: ");
		
		do{
			fflush(stdin);
			gotoxy(30,11);
			scanf("%d",&opcion);
		}while(opcion>=3 || opcion<0);
		fflush(stdin);
		system("cls");
		switch(opcion){
			
		case 1:	//Instrucciones 			system("cls");
			for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
				gotoxy(i,0);
				printf("%c",178);
				gotoxy(i,c);
				printf("%c",178);
			}
			for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
				gotoxy(0,i);
				printf("%c",178);
				gotoxy(f,i);
				printf("%c",178);
			}
			gotoxy(7,1);
			printf("\n\t\t   **************** BUSCAMINAS ****************\n"); 
			gotoxy(20,3);printf("\t     Jugador");gotoxy(39,3);printf("\t   Score");
			mostrar_regisB();
			gotoxy(20,20);printf("Presione Cualquier Tecla Para Regresar");
			system("pause>null");
			break;
		case 2:
			system("cls");
			for(int i=0 ; i<f ; i++){//Generar los bordes del cuadro de la interfaz
				gotoxy(i,0);
				printf("%c",178);
				gotoxy(i,c);
				printf("%c",178);
			}
			for(int i=0 ; i<=c ; i++){//Genera los bordes del Cuadro de la Interfaz
				gotoxy(0,i);
				printf("%c",178);
				gotoxy(f,i);
				printf("%c",178);
			}
			gotoxy(7,1);
			printf("\n\t\t   **************** SNAKE ****************\n"); 
			gotoxy(20,3);printf("\t    Jugador");gotoxy(39,3);printf("\t Score");
			mostrar_regisS();
			gotoxy(20,20);printf("Presione Cualquier Tecla Para Regresar");
			system("pause>null");
			break;
			

		case 0:
			system("cls");
			repetir=false;
			break;
		}
	}while(repetir);
}
//Funcion Para Pedir su Nickname al Usuario en el Juego de Snake
void pedir_nombre(){
	fflush(stdin);//Limpia el Buffer
	gotoxy(25,19);printf("Inserte Su Nickname:");
	gotoxy(47,19);gets(Jugador.nombre);//Se Guarda en La Estructurada de Datos
}
//Funcion Para Pedir su Nickname al Usuario en el Juego de Snake
void pedir_nombre_buscaminas(){
	fflush(stdin);//Limpia el Buffer
	gotoxy(46,10);printf("Inserte Su Nickname:");
	gotoxy(66,10);gets(Jugador.nombre);//Se Guarda en La Estructurada de Datos
}
//Funcion Para Asignar los datos en la Estructura de Datos
void asignar_puntos(int variable){
	fflush(stdin);
	Jugador.puntos=variable;
	
}
//Funcion que Crea un Archivo de Texto donde se Guarda la Estructurada de Datos del Juego de Snake
void guardar_registroSnake(player Jugador){
	FILE *f;//Apuntador al Archivo
	//En Caso de No Existir el Archivo lo Crea y si Existe lo Abre
	f=fopen("SnakeRegistro.txt","a+");//a+ Sirve Para Que sea un Archivo Binario de Lectura y Escritura
	if (f == NULL){
		printf("No se pudo abrir el archivo.\n");
	}else{
		//Formato de Guardado en el Archivo de Texto
		gotoxy(3,5);fprintf(f, "\n\t\t\t\t%s.........",Jugador.nombre); gotoxy(17,5);fprintf (f,"%d",Jugador.puntos);
	}
	fclose(f);//Cierra el fichero
}
//Funcion que Crea un Archivo de Texto donde se Guarda la Estructurada de Datos del Juego de Buscaminas
void guardar_registroBuscaminas(player Jugador){
	FILE *f;//Apuntador al Archivo
	//En Caso de No Existir el Archivo lo Crea y si Existe lo Abre
	f=fopen("RegistroBuscaminas.txt","a+");
	if (f == NULL){
		printf("No se pudo abrir el archivo.\n");
	}else{
		//Formato de Guardado en el Archivo de Texto
		gotoxy(3,5);fprintf(f, "\n\t\t\t\t%s.........",Jugador.nombre); gotoxy(17,5);fprintf (f,"%d",Jugador.puntos);
	}
	fclose(f);//Cierra el fichero
}
//Funcion Para Imprimir el Registro de los Datos de Snake en Pantalla
void mostrar_regisS(){
	FILE *f;//Apuntador al Archivo
	char frase[21];
	f = fopen("SnakeRegistro.txt", "a+");//Abre el Archivo
	if (f == NULL)
		printf("No se pudo abrir el archivo.\n");
	else
	{
		do{
			fgets(frase,21, f);
			puts(frase);
		}
		while (!feof(f));//Negamos la Condicional Para que al Llegar al Final del Fichero se Salga del Bucle
	}
}
//Funcion Para Imprimir el Registro de los Datos de Buscaminas en Pantalla
void mostrar_regisB(){
	FILE *f;//Apuntador al Archivo
	char frase[21];
	f = fopen("RegistroBuscaminas.txt", "a+");//Abre el Archivo
	if (f == NULL)
		printf("No se pudo abrir el archivo.\n");
	else
	{
		do
		{
			fgets(frase,21, f);
			puts(frase);
		}
		while (!feof(f));//Negamos la Condicional Para que al Llegar al Final del Fichero se Salga del Bucle
	}
}
//Funcion Para Imprimir el Menu Principal del Tetris
void imprimir_menu_tetris(){
	
	gotoxy (5,5);  printf(" ___________    _________    ___________    _________    ____    _________   ");
	gotoxy (5,6);  printf("|___     ___|  |   ______|  |___     ___|  |   __    |  |    |  |         |  ");
	gotoxy (5,7);  printf("    |   |      |  |______       |   |      |  |  |   |  |    |   |      _|   ");
	gotoxy (5,8);  printf("    |   |      |   ______|      |   |      |  |__|  |   |    |    |    |     ");
	gotoxy (5,9);  printf("    |   |      |  |             |   |      |       |    |    |     |    |    ");
	gotoxy (5,10); printf("    |   |      |  |______       |   |      |  ||    |   |    |      |    |   ");
	gotoxy (5,11); printf("    |   |      |         |      |   |      |  | |    |  |    |   __|    |    ");
	gotoxy (5,12); printf("    |___|      |_________|      |___|      |__|  |____| |____|  |______|     ");
	
	//laneas horizontales.
	for (int i=25; i<=60; i++){
		gotoxy(i,15); printf("%c", 205);
		gotoxy(i,25); printf("%c", 205);
	}
	
	//laneas verticales.
	for (int j=15; j<=25; j++){
		gotoxy(25,j); printf("%c", 186);
		gotoxy(60,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(25,15); printf("%c", 201);
	gotoxy(60,15); printf("%c", 187);
	gotoxy(25,25); printf("%c", 200);
	gotoxy(60,25); printf("%c", 188);
	
	gotoxy(31, 17); printf("     Jugar(espacio)    ");
	gotoxy(31, 19); printf("Mejores Puntuaciones(s)");
	gotoxy(31, 21); printf("      Controles(w)     ");
	gotoxy(31, 23); printf("       Salir(esc)      ");
}
//Funcion Para imprimir los Controles en Pantalla
void controles_tetris(){
	
	char tecla;
	
	//Tablero para mostrar controles.
	//laneas horizontales.
	for (int i=15; i<=53; i++){
		gotoxy(i,5); printf("%c", 205);
		gotoxy(i,19); printf("%c", 205);
	}
	
	//laneas verticales.
	for (int j=5; j<=19; j++){
		gotoxy(15,j); printf("%c", 186);
		gotoxy(53,j); printf("%c", 186);
	}
	
	// Esquinas.
	gotoxy(15,5); printf("%c", 201);
	gotoxy(53,5); printf("%c", 187);
	gotoxy(15,19); printf("%c", 200);
	gotoxy(53,19); printf("%c", 188);
	
	// texto
	gotoxy(17,7); printf("A --------- Izquierda");
	gotoxy(17,8); printf("D --------- Derecha");
	gotoxy(17,9); printf("W --------- Caida Rapida");
	gotoxy(17,10); printf("S --------- Bajar Pieza Lentamente");
	gotoxy(17,13); printf("O --------- Rotar Pieza");
	gotoxy(17,14); printf("P --------- Guardar Pieza");
	gotoxy(17,17); printf("Esc ------- Menu de Pausa");
	
	gotoxy(16, 21); printf("Regresar(esc)");
	
	// ciclamos hasta que el usuario quiera salir.
	do {
		tecla = getch();
		delay(50);
	} while(tecla != REGRESAR);
}

void tetris(){
	char tecla;	
	//abrimos el fichero de puntajes. sino existe se creara uno, si existe se mantendra.
	FILE *ficheropuntuaciones = fopen("puntuaciones.txt", "a");
	// lo cerramos.
	fclose(ficheropuntuaciones);
	// esto solo es para que, en caso de no existir un fichero, se cree uno. 
	system("cls");
	do{
		
		imprimir_menu_tetris();
		tecla = getch(); // pedimos la tecla.
		
		switch(tecla){
		case JUGAR:
			system("cls");
			jugar(); // entramos al juego. 
			system("cls");
			break;
		case PUNTUACIONES: case PUNTUACIONES2:
			system("cls");
			mejores_puntuaciones();
			system("cls");
			break;
		case CONTROLES: case CONTROLES2:
			system("cls");
			controles_tetris();
			system("cls");
			break;
		}
		
	} while(tecla != SALIR);
	
}

