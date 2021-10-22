#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <array>

class Entity
{
public:
    Entity(std::string texFile, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer);
    Entity(std::string texFile, std::nullptr_t, SDL_Renderer* renderer);
    Entity(std::string texText, SDL_Color textColour, std::string fontFile, SDL_Renderer* renderer);
    Entity();
    void close();

    SDL_Rect* getSrcRect();
    SDL_Rect* getDstRect();
    SDL_Texture* getTex();

    void setColour(uint8_t r, uint8_t g, uint8_t b);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(uint8_t alpha);

    void setPos(std::array<int, 2> pos);
    void setSrc(std::array<int, 4> src);
protected:
    std::string texFile;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* tex = nullptr;

    SDL_Rect* src = new SDL_Rect();
    SDL_Rect* dst = new SDL_Rect();

    unsigned int texWidth;
    unsigned int texHeight;
};