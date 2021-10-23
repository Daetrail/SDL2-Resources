#include <SDL2/SDL.h>

#include <array>
#include <vector>

#include "Animations.hpp"

Animation::Animation(std::array<int, 2> startPoint, std::array<int, 2> dimensions, int numberOfFrames, bool backAndForth) 
    : startPoint(startPoint), dimensions(dimensions), numberOfFrames(numberOfFrames), backAndForth(backAndForth)
{
    dimensionXOneSprite = dimensions[0] / numberOfFrames;
    int x = startPoint[0];
    int y = startPoint[1];
    std::vector<SDL_Rect> tempSprite;
    for (int i = 0; i < numberOfFrames; i++)
    {
        SDL_Rect newSrc;
        newSrc.x = x;
        newSrc.y = y;
        newSrc.w = dimensionXOneSprite;
        newSrc.h = dimensions[1];

        tempSprite.push_back(newSrc);

        x += dimensionXOneSprite;
    }

    sprites = tempSprite;

    if (backAndForth)
    {
        for (int i = tempSprite.size() - 2; i >= 0; i--)
        {
            sprites.push_back(tempSprite[i]);
        }
    }
}

std::vector<SDL_Rect> Animation::getSprites()
{
    return sprites;
}