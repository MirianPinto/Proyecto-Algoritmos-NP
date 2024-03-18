#pragma once
#ifndef GUI_H
#define GUI_H

#include <SDL.h>
#include <vector>
#include "subsetsum.h"
#include <stdio.h>
#include <iostream>

class GUI {
public:
    GUI(const std::vector<int>& numbers, int targetSum);
    void run();

private:
    bool initSDL();
    void close();
    void render();
    bool processEvents();
    void drawText(const std::string& text, int x, int y);
    std::vector<int> numbers;
    int targetSum;
    SubsetSumSolver solver;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit;
};

#endif // GUI_H
