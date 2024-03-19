#pragma once
#ifndef GRAFOS_H
#define GRAFOS_H

#include <vector>
#include "Vertice.h"

class Grafo {
public:
    Grafo();
    void addVertice(int x, int y, SDL_Color color);
    void addArista(int v, int w);
    void colorearGrafo();
    void colorearGrafoWelshPowell();
    const std::vector<Vertice>& getVertices() const;
    const std::vector<std::vector<int>>& getAdj() const;
    SDL_Color coloresDisponibles[2] = {
    {255, 0, 0, 255},   // Rojo
    {0, 255, 0, 255},   // Verde
    {0, 0, 255, 255},   // Azul
    {255, 255, 0, 255}, // Amarillo
    {0, 255, 255, 255}, // Cian
    {255, 0, 255, 255}  // Magenta
    };
private:
    std::vector<Vertice> vertices;
    std::vector<std::vector<int>> adj;

};

#endif


