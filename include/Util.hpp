#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#include "Entity.hpp"
#include "Animations.hpp"

namespace util
{
    bool init();
    void close();
    void destroyEntityTex(std::vector<Entity> entities);

    void calculateFPS(u_int32_t &lastTime, u_int32_t &frames, u_int32_t &currentFPS, float interval);

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