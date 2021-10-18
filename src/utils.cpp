#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "Util.hpp"
#include "Entity.hpp"

namespace util
{
    bool util()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            std::cout << "(Util) SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
                std::cout << "(Util) SDL_image PNG could not initialise! SDL_image Error: " << SDL_GetError() << std::endl;  
        }
    }

    void destroyEntityTex(std::vector<Entity> entities)
    {
        for (auto entity : entities)
            entity.~Entity();
    }

    template <class T>
    Vector2<T>::Vector2(T x, T y) :x(x), y(y) {}

    template <class T>
    Vector2<T> Vector2<T>::operator+ (Vector2<T> vector)
    {
        return Vector2(x + vector.x, y + vector.y)
    }

    template <class T>
    Vector2<T> Vector2<T>::operator- (Vector2<T> vector)
    {
        return Vector2(x - vector.x, y - vector.y)
    }   

    template <class T>
    Vector2<T> Vector2<T>::operator* (Vector2<T> vector)
    {
        return Vector2(x * vector.x, y * vector.y)
    } 

    template <class T>
    Vector2<T> Vector2<T>::operator/ (Vector2<T> vector)
    {
        return Vector2<T>(x / vector.x, y / vector.y)
    } 
}