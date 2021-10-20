#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "Entity.hpp"

Entity::Entity(std::string texFile, SDL_Renderer* renderer)
    :texFile(texFile), renderer(renderer)
{
    SDL_Surface* loadedSurface = IMG_Load(this->texFile.c_str());
    if (loadedSurface == nullptr)
        std::cout << "(Entity) Unable to load image! SDL_image Error: " << IMG_GetError() << std::endl;
    else
    {
        this->tex = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
        if (this->tex == nullptr)
            std::cout << "(Entity) Unable to create texture from image! SDL_image Error: " << IMG_GetError() << std::endl;
        
        this->texWidth = loadedSurface->w;
        this->texHeight = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);
    }
}

void Entity::close()
{
    SDL_DestroyTexture(this->tex);
    this->tex = nullptr;
}

SDL_Rect* Entity::getSrcRect()
{   
    return src;
}

SDL_Rect* Entity::getDstRect()
{   
    return dst;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

void Entity::setColour(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetTextureColorMod(this->tex, r, g, b);
}

void Entity::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(this->tex, blending);
}

void Entity::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(this->tex, alpha);
}