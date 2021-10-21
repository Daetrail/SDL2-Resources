#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(std::string title, const unsigned int WINDOW_WIDTH, const unsigned int WINDOW_HEIGHT)
    :title{title}, w_w(WINDOW_WIDTH), w_h(WINDOW_HEIGHT)
{
    this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_w, w_h, SDL_WINDOW_SHOWN);
    if (this->window == nullptr) 
        std::cout << "(RenderWindow) Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    else
    {
        this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (this->renderer == nullptr)
            std::cout << "(RenderWindow) Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        else
        {
            SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
    }
}

void RenderWindow::close()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    this->renderer = nullptr;
    this->window = nullptr;
}

SDL_Renderer* RenderWindow::getRenderer()
{
    return this->renderer;
}

void RenderWindow::clear()
{
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->renderer);
}

void RenderWindow::update()
{
    SDL_RenderPresent(this->renderer);
}

void RenderWindow::drawEntity(Entity entity)
{
    SDL_Rect* src = entity.getSrcRect();
    SDL_Rect* dst = entity.getDstRect();
    SDL_Texture* tex = entity.getTex();

    SDL_RenderCopy(this->renderer, tex, src, dst);
}

void RenderWindow::drawEntities(std::vector<Entity> entities)
{
    for (auto entity : entities)
        drawEntity(entity);
}