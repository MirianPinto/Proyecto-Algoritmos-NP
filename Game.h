#pragma once

#include "SDL.h"
#include "SDL_ttf.h" // Incluir SDL_ttf para trabajar con fuentes de texto
#include <iostream>
#include <vector>
#include <string>
#include "subsetsum.h" // Incluir la clase SubsetSumSolver

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    bool running() { return isRunning; }
    void render();
    void clean();

private:
    bool isRunning = true;
    int cnt = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font; // Agregar un miembro para la fuente de texto
    std::vector<int> numbers = { 3, 34, 4, 12, 5, 2, 14, 19, 7 }; // Conjunto de números
    int targetSum = 9; // Objetivo de suma
    void renderText(const char* text, int x, int y);
    double subsetSumTime; // Almacenar el tiempo de ejecución del subset sum en segundos
};

