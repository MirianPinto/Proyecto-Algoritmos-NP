#include "grafos.h"
#include <iostream>
#include <windows.h>
#include <algorithm>  
#include <algorithm>  
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

void Grafo::colorearGrafoWelshPowell() {
    int numVertices = vertices.size();
    int numColoresDisponibles = sizeof(coloresDisponibles) / sizeof(coloresDisponibles[0]);
    std::cout << "Colores disponibles: " << numColoresDisponibles << std::endl;
    // Verificar si hay suficientes colores para colorear el grafo
    if (numVertices > numColoresDisponibles) {
        MessageBox(NULL, TEXT("No se pudo colorear el grafo con los colores disponibles."), TEXT("WelshPowell"), MB_OK);
        return;
    }

    std::vector<int> orden(numVertices);
    for (int i = 0; i < numVertices; i++) {
        orden[i] = i;
    }
    std::sort(orden.begin(), orden.end(), [this](int a, int b) {
        return adj[a].size() > adj[b].size();
        });

    std::vector<int> colores(numVertices, -1);

    int color = 0;
    for (int i : orden) {
        if (colores[i] == -1) {
            colores[i] = color;
            // Asignar el mismo color a todos los vértices no adyacentes que aún no han sido coloreados
            for (int j : orden) {
                if (colores[j] == -1) {
                    bool adyacente = false;
                    for (int k : adj[j]) {
                        if (colores[k] == color) {
                            adyacente = true;
                            break;
                        }
                    }
                    if (!adyacente) {
                        colores[j] = color;
                    }
                }
            }
            color++; 
        }
    }

    // Asignar los colores a los vértices
    for (int i = 0; i < numVertices; i++) {
        vertices[i].color = coloresDisponibles[colores[i]];
    }
}


const std::vector<Vertice>& Grafo::getVertices() const {
    return vertices;
}

const std::vector<std::vector<int>>& Grafo::getAdj() const {
    return adj;
}



