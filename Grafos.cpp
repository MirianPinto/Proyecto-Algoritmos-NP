#include "grafos.h"
#include <iostream>
#include <windows.h>
using namespace std;

Grafo::Grafo() {}

void Grafo::addVertice(int x, int y, SDL_Color color) {
    vertices.push_back(Vertice(x, y, color));
    adj.push_back(std::vector<int>());
}

void Grafo::addArista(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Grafo::colorearGrafo() {
    int numVertices = vertices.size();
    vector<int> colores(numVertices, -1);  

    colores[0] = 0;

    int numColores = sizeof(coloresDisponibles) / sizeof(coloresDisponibles[0]);

    for (int u = 1; u < numVertices; u++) {
        
        for (int i = 0; i < adj[u].size(); i++) {
            if (colores[adj[u][i]] != -1) {
                coloresDisponibles[colores[adj[u][i]]].a = 0;  
            }
        }

        
        int cr;
        for (cr = 0; cr < numColores; cr++) {
            if (coloresDisponibles[cr].a != 0) {
                break;
            }
        }

        if (cr == numColores) {
            MessageBox(NULL, TEXT("No se pudo colorear el grafo con los colores disponibles."), TEXT("Error"), MB_OK);
            return;
        }

        colores[u] = cr; 

  
        for (int i = 0; i < adj[u].size(); i++) {
            if (colores[adj[u][i]] != -1) {
                coloresDisponibles[colores[adj[u][i]]].a = 255;  
            }
        }
    }


    for (int u = 0; u < numVertices; u++) {
        vertices[u].color = coloresDisponibles[colores[u]];
    }
}

const std::vector<Vertice>& Grafo::getVertices() const {
    return vertices;
}

const std::vector<std::vector<int>>& Grafo::getAdj() const {
    return adj;
}



