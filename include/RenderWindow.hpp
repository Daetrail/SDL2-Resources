#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class RenderWindow
{
public:
    RenderWindow(std::string title, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);
    ~RenderWindow();
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::string title;
    unsigned int w_w, w_h;
};

