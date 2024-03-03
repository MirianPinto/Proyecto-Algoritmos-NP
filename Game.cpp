#include "Game.h"
//#include"SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string_view>

#include <vector>


SDL_Texture* imagetext;

Game::Game()
{
   
}

Game::~Game()
{}


void Game::init(const char* title, int xpos, int ypos,int WIDTH, int HEIGHT, bool fullscreen)
{
	int flahs = 0;
	if(fullscreen)
	{
		flahs = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		std::cout << "subsis";

		window = SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flahs);
		if (window) 
		{
			std::cout << "created win";
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			std::cout << "created rednder";
		}
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}

	SDL_Surface* tmpSurface = IMG_Load("Assets/Slime.png");
	imagetext = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Game::handleEvents() 
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	cnt++;
	//std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, imagetext, NULL, NULL);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit;
}

