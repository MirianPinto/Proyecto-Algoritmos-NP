#pragma once
#include "Game.h"


class Menu
{
public:
	Menu();
	~Menu();

	void LoadMenu(SDL_Window* window, SDL_Renderer* renderer,int mousex, int mousey);
	void updateMenu(int mousex, int mousey);
	int handleEvents(int mousex, int mousey);
	void render();
	void Mochila();
	void Grafos();
	void Subconjuntos();
	
private:
	SDL_Surface* background;
	SDL_Texture* TextureBc;
	
	SDL_Rect SrcMenu;
	SDL_Rect DestMenu;

	SDL_Rect srcMano;
	SDL_Rect DestMano;
	int frameindex = 0;
	int frameindex2 = 0;

	int mousexboton = 0;
	int mouseyboton = 0;
	int isRunning=0;
	
	SDL_Surface* Ventana;
	SDL_Renderer* renderer;

	
};
