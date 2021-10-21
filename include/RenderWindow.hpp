#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

#include "Entity.hpp"

class RenderWindow
{
public:
    RenderWindow(std::string title, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT);
    void close();

    SDL_Renderer* getRenderer();

    void clear();
    void update();
    
    void drawEntity(Entity entity);
    void drawEntities(std::vector<Entity> entities);
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::string title;
    unsigned int w_w, w_h;
};

