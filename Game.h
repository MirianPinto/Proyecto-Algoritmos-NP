#pragma once

#include "SDL_image.h"
#include "SDL_ttf.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string_view>

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Game
{
public:
	Game();
	~Game();
	
	void init(const char* title,int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();
	void Mochila();
	void Updatemochila();
	void EventMochila();
	int existe();
	void renderMochila();
	int* CasosM();
	int* Casos1();
	int* Casos2();
	int* Casos3();
	void Grafos();
	void SubConjuntos();

	int menor();
	int mayor();
	



private:
	bool isRunning = true;
	int cnt = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int MouseX=0;
	int MouseY=0;
	SDL_Rect posInicial;
	SDL_Rect posFinal;


	//pantalla mirian
	SDL_Window* window2;
	SDL_Renderer* renderer2;
	int pantalla=0;
	int* ObjeYa = new int[10];
	int frameindex = 0;
	int* pesoObj = new int[10];
	int* ValorObj = new int[10];
	int* casoM = new int[11];
	int* caso1 = new int[11];
	int* caso2 = new int[11];
	int* caso3 = new int[11];

	int* Mayores = new int[10];
	int* Menores = new int[10];
	string scaso1 = "[ ";
	string scaso2 = "[ ";
	string scaso3 = "[ ";
	string scasoM = "[ ";
	string scasoU = "[ ";
	string sValor1 = "a";
	string sValor2 = "a";
	string sValor3 = "a";
	string sValorM = "a";

	int SizeMochila = 0;
	int ValorMochila = 0;
	int SizeObjMochi = 0;
	int Resultados = 0;
	int Avisos = 0;

	SDL_Rect RestFinal;
	SDL_Rect RestInicial;
	SDL_Rect SrcSkanp;
	SDL_Rect DestSkanp;
	
	SDL_Texture* TexObj1;
	SDL_Texture* TexObj2;
	SDL_Texture* TexObj3;
	SDL_Texture* TexObj4;
	SDL_Texture* TexObj5;
	SDL_Texture* TexObj6;
	SDL_Texture* TexObj7;
	SDL_Texture* TexObj8;
	SDL_Texture* TexObj9;
	SDL_Texture* TexObj10;
	SDL_Texture* TextureBc;

	SDL_Rect DsetObj1;
	SDL_Rect DsetObj2;
	SDL_Rect DsetObj3;
	SDL_Rect DsetObj4;
	SDL_Rect DsetObj5;
	SDL_Rect DsetObj6;
	SDL_Rect DsetObj7;
	SDL_Rect DsetObj8;
	SDL_Rect DsetObj9;
	SDL_Rect DsetObj10;
	SDL_Rect DsetMochi;
	SDL_Rect DsetMochiValor;

	SDL_Texture* Texttext1;
	SDL_Texture* Texttext2;
	SDL_Texture* Texttext3;
	SDL_Texture* Texttext4;
	SDL_Texture* Texttext5;
	SDL_Texture* Texttext6;
	SDL_Texture* Texttext7;
	SDL_Texture* Texttext8;
	SDL_Texture* Texttext9;
	SDL_Texture* Texttext10;
	SDL_Texture* TexttextMochi;
	SDL_Texture* TexttextMochiValor;
	SDL_Texture* TexttextValor1;
	SDL_Texture* TexttextValor2;
	SDL_Texture* TexttextValor3;
	SDL_Texture* TexttextValor4;
	SDL_Texture* TexttextValor5;
	SDL_Texture* TexttextValor6;
	SDL_Texture* TexttextValor7;
	SDL_Texture* TexttextValor8;
	SDL_Texture* TexttextValor9;
	SDL_Texture* TexttextValor10;

	SDL_Texture* Aviso1;
	SDL_Texture* Aviso2;
	SDL_Texture* Aviso3;
	SDL_Texture* Aviso4;
	SDL_Rect Avisorect;

	SDL_Rect textrec;
	SDL_Rect textrecValor;
	SDL_Rect TextResult;
	SDL_Rect TextResult0;
	SDL_Rect TextResult1;
	SDL_Rect TextResult2;
	SDL_Rect TextResult3;
	SDL_Rect TextResult12;
	SDL_Rect TextResult22;
	SDL_Rect TextResult32;
	SDL_Rect TextResultM;
	SDL_Rect TextResultM2;

	TTF_Font* font2;
	SDL_Texture* ResultadosPan;
	SDL_Texture* ResultadosTitulo;
	SDL_Texture* RestTextRob;
	SDL_Texture* RestTextRob2;
	SDL_Texture* ResulTextC1;
	SDL_Texture* ResulTextC2;
	SDL_Texture* ResulTextC3;
	SDL_Texture* ResulTextC12;
	SDL_Texture* ResulTextC22;
	SDL_Texture* ResulTextC32;
	SDL_Texture* ResulTextCM;
	SDL_Texture* ResulTextCM2;


	string tiempoEjeM = "";
	string tiempoEje1 = "";
	string tiempoEje2 = "";
	string tiempoEje3 = "";

};

