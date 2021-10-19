#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.hpp"

namespace util
{
    bool init();
    void close();
    void destroyEntityTex(Entity entity);
    void destroyEntityTex(std::vector<Entity> entities);

    template <class T>
    class Vector2
    {
    public:
        T x, y;
        Vector2(T x, T y);

        Vector2<T> operator+ (Vector2<T> vector);
        Vector2<T> operator- (Vector2<T> vector);
        Vector2<T> operator* (Vector2<T> vector);
        Vector2<T> operator/ (Vector2<T> vector);
    };
}