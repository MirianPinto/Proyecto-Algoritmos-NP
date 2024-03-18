#include "Game.h"
#include"SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string_view>
#include <chrono>
#include <vector>


SDL_Texture* imagetext;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            }
            else {
                isRunning = false;
            }
        }
        else {
            isRunning = false;
        }
    }
    else {
        isRunning = false;
    }

    // Inicializar SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        isRunning = false;
    }

    // Cargar la fuente
    font = TTF_OpenFont("C:\\Dev\\OpenSans-Light.ttf", 24); // Cambia la ruta a tu fuente y el tamaño según sea necesario
    if (font == nullptr) {
        std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update() {
    // Tu lógica de actualización aquí
}

void Game::render() {
    SDL_RenderClear(renderer);

    // Renderizar un marco blanco alrededor de la pantalla
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco

    // Definir las dimensiones del marco
    int frameWidth = 10; // Ancho del marco en píxeles
    SDL_Rect frameRect = { frameWidth, frameWidth, 800 - 2 * frameWidth, 600 - 2 * frameWidth }; // Rectángulo interior que representa el área del marco

    // Dibujar el marco blanco
    SDL_RenderFillRect(renderer, &frameRect);

    // Dibujar un rectángulo interior más pequeño para representar el área principal de la pantalla
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color negro para el interior
    SDL_Rect innerRect = { 2 * frameWidth, 2 * frameWidth, 800 - 4 * frameWidth, 600 - 4 * frameWidth }; // Rectángulo interior más pequeño
    SDL_RenderFillRect(renderer, &innerRect);

    // Renderizar la imagen en el centro de la pantalla
    SDL_Surface* imageSurface = IMG_Load("Assets\\Pizarra.jpg");
    if (imageSurface == nullptr) {
        std::cerr << "Error al cargar la imagen: " << IMG_GetError() << std::endl;
        // Manejar el error adecuadamente
    }
    else {
        SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if (imageTexture == nullptr) {
            std::cerr << "Error al crear la textura de la imagen: " << SDL_GetError() << std::endl;
            // Manejar el error adecuadamente
        }
        else {
            SDL_Rect imageRect; // Rectángulo para definir la posición y tamaño de la imagen
            imageRect.w = imageSurface->w;
            imageRect.h = imageSurface->h;
            imageRect.x = (800 - imageSurface->w) / 2; // Centrar horizontalmente
            imageRect.y = (600 - imageSurface->h) / 2; // Centrar verticalmente

            SDL_RenderCopy(renderer, imageTexture, nullptr, &imageRect);

            SDL_DestroyTexture(imageTexture);
        }
        SDL_FreeSurface(imageSurface);
    }

    // Renderizar título "Problema del subconjunto"
    std::string titleText = "Problema del subconjunto";
    renderText(titleText.c_str(), (800 - titleText.length() * 10) / 2, 50); // Centrado horizontalmente

    // Renderizar conjunto de números
    std::string numbersText = "Conjunto de números: ";
    for (size_t i = 0; i < numbers.size(); ++i) {
        numbersText += std::to_string(numbers[i]);
        if (i != numbers.size() - 1) {
            numbersText += ", ";
        }
    }
    renderText(numbersText.c_str(), 100, 100); // Renderizar conjunto de números en (100, 100)

    // Verificar si el subconjunto existe y calcular el tiempo de ejecución
    SubsetSumSolver solver(numbers, targetSum);
    bool existsSubset;
    double subsetSumTime;
    {
        auto start = std::chrono::high_resolution_clock::now();
        existsSubset = solver.existsSubset();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        subsetSumTime = elapsed_seconds.count(); // Almacenar el tiempo de ejecución en segundos
    }
    std::string subsetResultText = existsSubset ? "El subconjunto con la suma objetivo existe." : "El subconjunto con la suma objetivo no existe.";
    renderText(subsetResultText.c_str(), 100, 150); // Renderizar resultado de la verificación en (100, 150)

    // Renderizar tiempo de ejecución del subset sum
    std::string timeText = "Tiempo de ejecucion: " + std::to_string(subsetSumTime) + " segundos";
    renderText(timeText.c_str(), 100, 200); // Renderizar tiempo de ejecución en (100, 200)

    SDL_RenderPresent(renderer);
}


void Game::renderText(const char* text, int x, int y) {
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    // Cerrar SDL_ttf al finalizar
    TTF_CloseFont(font);
    TTF_Quit();
}

