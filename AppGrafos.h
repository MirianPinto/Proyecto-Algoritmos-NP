#pragma once
#ifndef APLICACION_H
#define APLICACION_H

#include <SDL.h>
#include "Grafos.h"
#include <SDL_ttf.h> 
#include <string> 
class Aplicacion {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* imageTexture;
    SDL_Texture* imageTexture2;
    Grafo g;

public:
    Aplicacion();
    ~Aplicacion();
    void ejecutar();
    void renderizarTexto(const std::string& texto, int x, int y, SDL_Renderer* renderer);
    
    void mostrarInstrucciones();
};

#endif
