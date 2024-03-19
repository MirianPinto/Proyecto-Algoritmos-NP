#pragma once
#ifndef VERTICE_H
#define VERTICE_H

#include "SDL.h"

class Vertice {
public:
    int x, y;
    SDL_Color color;
    Vertice(int x, int y, SDL_Color color) : x(x), y(y), color(color) {}
};

#endif
