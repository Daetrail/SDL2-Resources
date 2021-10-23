#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Entity.hpp"
#include "Text.hpp"

Text::Text(std::string texText, std::array<int, 4> textColour, std::string fontFile, unsigned int fontSize, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer)
    :texText(texText), fontFile(fontFile), fontSize(fontSize)
{
    this->renderer = renderer;
    this->textColour.r = static_cast<uint8_t>(textColour[0]);
    this->textColour.g = static_cast<uint8_t>(textColour[1]);
    this->textColour.b = static_cast<uint8_t>(textColour[2]);
    this->textColour.a = static_cast<uint8_t>(textColour[3]);

    this->font = TTF_OpenFont(this->fontFile.c_str(), this->fontSize);
    if (this->font == nullptr)
        std::cout << "(Text) Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    else
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, this->texText.c_str(), this->textColour);
        if (textSurface == nullptr)
            std::cout << "(Text) Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        else
        {
            this->tex = SDL_CreateTextureFromSurface(this->renderer, textSurface);
            if (this->tex == nullptr)
                std::cout << "(Text) Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
            else
            {
                this->texWidth = textSurface->w;
                this->texHeight = textSurface->h;
            }

            SDL_FreeSurface(textSurface);
        }
    }

    this->src = nullptr;

    this->dst->x = dst[0];
    this->dst->y = dst[1];
    this->dst->w = this->texWidth;
    this->dst->h = this->texHeight;
}

Text::Text(std::string texText, std::array<int, 4> textColour, TTF_Font* font, unsigned int fontSize, std::array<int, 4> src, std::array<int, 2> dst, SDL_Renderer* renderer)
    :texText(texText), fontSize(fontSize)
{
    this->font = font;
    this->renderer = renderer;
    this->textColour.r = static_cast<uint8_t>(textColour[0]);
    this->textColour.g = static_cast<uint8_t>(textColour[1]);
    this->textColour.b = static_cast<uint8_t>(textColour[2]);
    this->textColour.a = static_cast<uint8_t>(textColour[3]);

    SDL_Surface* textSurface = TTF_RenderText_Solid(this->font, this->texText.c_str(), this->textColour);
    if (textSurface == nullptr)
        std::cout << "(Text) Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    else
    {
        this->tex = SDL_CreateTextureFromSurface(this->renderer, textSurface);
        if (this->tex == nullptr)
            std::cout << "(Text) Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
        else
        {
            this->texWidth = textSurface->w;
            this->texHeight = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
    

    this->src = nullptr;

    this->dst->x = dst[0];
    this->dst->y = dst[1];
    this->dst->w = this->texWidth;
    this->dst->h = this->texHeight;
}


void Text::closeFont()
{
    TTF_CloseFont(this->font);
    this->close();
}

TTF_Font* Text::getFont()
{
     return this->font;
}

void Text::changeText(std::string newText)
{
    // this->tex = nullptr;
    this->texText = newText;
    SDL_DestroyTexture(this->tex);
    this->tex = nullptr;
    SDL_Surface* newTextSurface = TTF_RenderText_Solid(this->font, this->texText.c_str(), this->textColour);
    if (newTextSurface == nullptr)
        std::cout << "(Text) Unable to render new text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    else
    {
        this->tex = SDL_CreateTextureFromSurface(this->renderer, newTextSurface);
        if (this->tex == nullptr)
            std::cout << "(Text) Unable to create new texture from new rendered text! SDL Error: " << SDL_GetError() << std::endl;
        else
        {
            this->texWidth = newTextSurface->w;
            this->texHeight = newTextSurface->h;
        }

        SDL_FreeSurface(newTextSurface);
    }
    
    this->dst->w = this->texWidth;
    this->dst->h = this->texHeight;
}
