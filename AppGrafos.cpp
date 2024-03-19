#include "AppGrafos.h"
#include <iostream>
#include <chrono>
#include <SDL_ttf.h>
#include <string> 
#include <SDL_image.h> 

void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

Aplicacion::Aplicacion() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Coloracion de Grafos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

   
    SDL_Surface* imageSurface = IMG_Load("Assets/pngwing.png");
    if (!imageSurface) {
        std::cout << "Error al cargar la imagen: " << IMG_GetError() << "\n";
       
    }
    imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); 

    SDL_Surface* imageSurface2 = IMG_Load("Assets/regresar.png");
    if (!imageSurface2) {
        std::cout << "Error al cargar la segunda imagen: " << IMG_GetError() << "\n";
   
    }
    imageTexture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2);
    SDL_FreeSurface(imageSurface2);
}

Aplicacion::~Aplicacion() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Aplicacion::renderizarTexto(const std::string& texto, int x, int y, SDL_Renderer* renderer) {
    TTF_Font* fuente = TTF_OpenFont("Assets/Fonts/SegoeUIItalic.ttf", 24);
    SDL_Color color = { 255, 255, 255, 255 }; 

    SDL_Surface* superficie = TTF_RenderText_Solid(fuente, texto.c_str(), color); 
    SDL_Texture* textura = SDL_CreateTextureFromSurface(renderer, superficie); 

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(textura, NULL, NULL, &rect.w, &rect.h); 

    SDL_RenderCopy(renderer, textura, NULL, &rect); 

    SDL_Rect borderRect = { rect.x - 5, rect.y - 5, rect.w + 10, rect.h + 10 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &borderRect);

    SDL_DestroyTexture(textura);
    SDL_FreeSurface(superficie);
    TTF_CloseFont(fuente);
}


void Aplicacion::ejecutar() {
    bool running = true;
    int firstVertice = -1;
    double ultimoTiempoEjecucion = 0.0;
    SDL_Rect textArea = { 10, 480 - 65, 230, 115 };

  
    int imageWidth, imageHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &imageWidth, &imageHeight); // Obtiene las dimensiones de la imagen

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight); 

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                bool isInsideTextArea = x >= textArea.x && x <= textArea.x + textArea.w && y >= textArea.y && y <= textArea.y + textArea.h;
                if (event.button.button == SDL_BUTTON_RIGHT) { // Si se presiona el botón derecho del ratón
                    for (int i = 0; i < g.getVertices().size(); i++) {
                        Vertice v = g.getVertices()[i];
                        if (abs(v.x - x) < 10 && abs(v.y - y) < 10) {
                            if (firstVertice == -1) {
                                firstVertice = i;
                            }
                            else {
                                g.addArista(firstVertice, i);
                                firstVertice = -1;
                            }
                            break;
                        }
                    }
                }
                else {
                    bool vertexExists = false;
                    for (const Vertice& v : g.getVertices()) {
                        if (abs(v.x - x) < 10 && abs(v.y - y) < 10) {
                            vertexExists = true;
                            break;
                        }
                    }
                    // Comprobar si el clic está dentro del rectángulo de la imagen
                    if (x >= windowWidth - 50 && x <= windowWidth && y >= 0 && y <= 50) {
                        mostrarInstrucciones();
                        vertexExists = true;
                    }
                    // Comprobar si el clic está dentro del rectángulo de la segunda imagen
                    if (x >= 0 && x <= 50 && y >= 0 && y <= 50) {
                        printf("Regresar\n");
                        vertexExists = true;
                    }
                    if (!vertexExists && x > 10 && x < 630 && y > 10 && y < 470 && !isInsideTextArea) {
                        g.addVertice(x, y, { 255, 255, 255, 255 });
                    }
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_c) {
                    if (g.getVertices().empty()) {
                        std::cout << "No hay grafo para colorear.\n";
                    }
                    else {
                        auto start = std::chrono::high_resolution_clock::now();
                        g.colorearGrafo();
                        auto end = std::chrono::high_resolution_clock::now();

                        // Cálculo de la duración en milisegundos
                        std::chrono::duration<double, std::milli> diff = end - start;

                        // Actualizar el último tiempo de ejecución
                        ultimoTiempoEjecucion = diff.count();

                        auto start2 = std::chrono::high_resolution_clock::now();
                        g.colorearGrafoWelshPowell();
                        auto end2 = std::chrono::high_resolution_clock::now();

                        std::cout << "Algoritmo aproximado: " << ultimoTiempoEjecucion << " ms\n";
                        std::cout << "Algoritmo optimo: " << std::chrono::duration<double, std::milli>(end2 - start2).count() << " ms\n";
                    }
                }
                else if (event.key.keysym.sym == SDLK_r) {
                    g = Grafo(); 
                    ultimoTiempoEjecucion = 0.0; 
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        std::string convertDiff = "T ejec.: " + std::to_string(ultimoTiempoEjecucion) + "ms";
        renderizarTexto(convertDiff, 20, 480 - 50, renderer); // texto a la parte inferior de la pantalla

        for (const Vertice& v : g.getVertices()) {
            SDL_SetRenderDrawColor(renderer, v.color.r, v.color.g, v.color.b, v.color.a);
            SDL_RenderDrawCircle(renderer, v.x, v.y, 10);
        }

        for (int i = 0; i < g.getVertices().size(); i++) {
            for (int j : g.getAdj()[i]) {
                Vertice v1 = g.getVertices()[i];
                Vertice v2 = g.getVertices()[j];
                if ((v1.x < textArea.x || v1.x > textArea.x + textArea.w || v1.y < textArea.y || v1.y > textArea.y + textArea.h) &&
                    (v2.x < textArea.x || v2.x > textArea.x + textArea.w || v2.y < textArea.y || v2.y > textArea.y + textArea.h)) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
                }
            }
        }

        int grosor = 5; // Grosor del marco
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        for (int i = 0; i < grosor; i++) {
            SDL_Rect rect = { i, i, 640 - i * 2, 480 - i * 2 };
            SDL_RenderDrawRect(renderer, &rect);
        }



        SDL_Rect dstRect;
        dstRect.x = windowWidth - 50;
        dstRect.y = 0;
        dstRect.w = 50; 
        dstRect.h = 50;

        SDL_RenderCopy(renderer, imageTexture, NULL, &dstRect);

        SDL_Rect dstRect2;
        dstRect2.x = 0; 
        dstRect2.y = 0;
        dstRect2.w = 50; 
        dstRect2.h = 50;
        SDL_RenderCopy(renderer, imageTexture2, NULL, &dstRect2);
        SDL_RenderPresent(renderer);
    }
}



void Aplicacion::mostrarInstrucciones() {
    std::string instrucciones =
        "Click izquierdo: Agregar vertice\n"
        "Click derecho: Agregar arista\n"
        "Tecla 'r': Reiniciar todo\n"
        "Tecla 'c': Colorear";

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
        "Instrucciones",
        instrucciones.c_str(),
        window);
}

