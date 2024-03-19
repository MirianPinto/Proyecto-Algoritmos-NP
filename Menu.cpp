#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::LoadMenu(SDL_Window* window, SDL_Renderer* renderer, int mousex, int mousey)
{
	
	background = IMG_Load("Assets/FrameMenu2.png");
	TextureBc = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);

	SrcMenu.y = 0;
	SrcMenu.w = 249;
	SrcMenu.h = 188;
	DestMenu.x = 0;
	DestMenu.y = 0;
	DestMenu.w = 1000;
	DestMenu.h = 650;

	background = IMG_Load("Assets/BotonesMenu.png");
	SDL_Texture* Botones = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);
	SDL_Rect srcBotones;
	SDL_Rect DestBotones;

	srcBotones.x = 0;
	srcBotones.y = 0;
	srcBotones.w = 926;
	srcBotones.h = 642;
	DestBotones.x = 50;
	DestBotones.y = 300;
	DestBotones.w = 450;
	DestBotones.h = 312;


	background = IMG_Load("Assets/TituloMenu.png");
	SDL_Texture* Titulo = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);
	SDL_Rect srcTitulo;
	SDL_Rect DestTitulo;

	srcTitulo.x = 0;
	srcTitulo.y = 0;
	srcTitulo.w = 1125;
	srcTitulo.h = 222;
	DestTitulo.x = 125;
	DestTitulo.y = 43;
	DestTitulo.w = 800;
	DestTitulo.h = 158;

	background = IMG_Load("Assets/ManoMenu2.png");
	SDL_Texture* Mano = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);
	

	
	srcMano.y = 0;
	srcMano.w = 112;
	srcMano.h = 40;
	DestMano.x = -25;
	
	DestMano.w = 170;
	DestMano.h = 61;


	
	SDL_RenderCopy(renderer, TextureBc, &SrcMenu, &DestMenu);
	SDL_RenderCopy(renderer, Titulo, &srcTitulo, &DestTitulo);
	SDL_RenderCopy(renderer, Botones, &srcBotones, &DestBotones);
	
	

	if (mousexboton >= 137 && mousexboton <= 414 && mouseyboton >= 318 && mouseyboton <= 385)
	{
		DestMano.y = 321;
		SDL_RenderCopy(renderer, Mano, &srcMano, &DestMano);
		

	}
	else if (mousexboton >= 137 && mousexboton <= 414 && mouseyboton >= 421 && mouseyboton <= 488)
	{
		DestMano.y = 424;
		SDL_RenderCopy(renderer, Mano, &srcMano, &DestMano);

	}
	else if (mousexboton >= 137 && mousexboton <= 414 && mouseyboton >= 524 && mouseyboton <= 596)
	{
		DestMano.y = 527;
		SDL_RenderCopy(renderer, Mano, &srcMano, &DestMano);
	}

}

void Menu::updateMenu(int mousex, int mousey)
{

	if (mousex >= 137 && mousex <= 414 && mousey >= 318 && mousey <= 385)
	{
		mousexboton = mousex;
		mouseyboton = mousey;
	}
	else if (mousex >= 137 && mousex <= 414 && mousey >= 421 && mousey <= 488)
	{
		mousexboton = mousex;
		mouseyboton = mousey;
	}
	else if (mousex >= 137 && mousex <= 414 && mousey >= 524 && mousey <= 596)
	{
		mousexboton = mousex;
		mouseyboton = mousey;
	}


	frameindex = int(((SDL_GetTicks() / 200) % 32));
	SrcMenu.x = ((frameindex) * 249);

	frameindex2 = int(((SDL_GetTicks() / 200) % 4));
	srcMano.x = ((frameindex2) * 112);;

}

int Menu::handleEvents(int mousex, int mousey)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		return isRunning;
		break;
	default:
		break;
	}

}

void Menu::render()
{
}


void Menu::Mochila()
{
	//llama la funcion init del algoritmo mochila
	cout << "Mochila";
}

void Menu::Grafos()
{
	//llama la funcion init del algoritmo Grafos
	cout << "Grafos";
}

void Menu::Subconjuntos()
{
	//llama la funcion init del algoritmo Subdet
	cout << "Sub";
}

