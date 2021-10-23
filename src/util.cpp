#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#include "Util.hpp"
#include "Entity.hpp"

namespace util
{
    bool init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "(Util) SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "(Util) SDL_image PNG could not initialise! SDL_image Error: " << SDL_GetError() << std::endl;  
                return false;
            }

            if (TTF_Init() == -1)
            {
                std::cout << "(Util) SDL_ttf could not initialise! SDL_ttf Error: " << TTF_GetError() << std::endl;
                return false;
            }
        }
        return true;
    }

    void close()
    {   
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void destroyEntityTex(std::vector<Entity> entities)
    {
        for (auto entity : entities)
            entity.close();
    }

    void calculateFPS(u_int32_t &lastTime, u_int32_t &frames, u_int32_t &currentFPS, const float interval)
    {
        if (lastTime < SDL_GetTicks() - interval * 1000)
        {
            lastTime = SDL_GetTicks();
            currentFPS = frames;
            frames = 0;
        }
    }

    template <class T>
    Vector2<T>::Vector2(T x, T y) :x(x), y(y) {}

    template <class T>
    Vector2<T> Vector2<T>::operator+ (Vector2<T> vector)
    {
        return Vector2(x + vector.x, y + vector.y);
    }

    template <class T>
    Vector2<T> Vector2<T>::operator- (Vector2<T> vector)
    {
        return Vector2(x - vector.x, y - vector.y);
    }   

    template <class T>
    Vector2<T> Vector2<T>::operator* (Vector2<T> vector)
    {
        return Vector2(x * vector.x, y * vector.y);
    } 

    template <class T>
    Vector2<T> Vector2<T>::operator/ (Vector2<T> vector)
    {
        return Vector2<T>(x / vector.x, y / vector.y);
    } 
}