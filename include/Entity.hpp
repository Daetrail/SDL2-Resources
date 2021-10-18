#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Entity
{
public:
    Entity(std::string texFile, SDL_Renderer* renderer);
    ~Entity();
private:
    std::string texFile;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* tex = nullptr;

    SDL_Rect* src;
    SDL_Rect* dst;

    unsigned int texWidth;
    unsigned int texHeight;
};