#include "Mochila.h"

Mochila::Mochila(SDL_Renderer* rendererp, int mousexp, int mouseyp)
{
	renderer = rendererp;
	mousexboton = mousexp;
	mouseyboton = mouseyp;
}

void Mochila::init()
{
	background = IMG_Load("Assets/FondoMochila.png");
	TextureBc = SDL_CreateTextureFromSurface(renderer, background);
	SDL_FreeSurface(background);

	/*SrcMenu.y = 0;
	SrcMenu.w = 249;
	SrcMenu.h = 188;
	DestMenu.x = 0;
	DestMenu.y = 0;
	DestMenu.w = 1000;
	DestMenu.h = 650;*/

	SDL_RenderCopy(renderer, TextureBc, NULL, NULL);
}

void Mochila::updateMochila()
{
}

void Mochila::renderMochila()
{
}
