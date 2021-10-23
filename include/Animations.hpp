#pragma once

#include "SDL2/SDL.h"

#include <vector>
#include <array>

class Animation
{
public:
    Animation(std::array<int, 2> startPoint, std::array<int, 2> dimensions, int numberOfFrames, bool backAndForth);
    void close();

    std::vector<SDL_Rect> getSprites();    
private:
    std::array<int, 2> startPoint, dimensions;
    int numberOfFrames, dimensionXOneSprite;
    bool backAndForth;

    std::vector<SDL_Rect> sprites; 
};
