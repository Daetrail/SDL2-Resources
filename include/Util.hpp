#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


#include "Entity.hpp"
#include "Animations.hpp"
#include "Timer.hpp"

namespace util
{
    bool init();
    void close();
    void destroyEntityTex(std::vector<Entity> &entities);
    
    struct CalculateFPS
    {
    public:
        CalculateFPS();

        void run();
        float getFps();
        void incrementFrames();
    private:
        Timer fpsTimer;
        std::stringstream timeText;
        int countedFrames = 0;
        float avgFPS;
    };

    void limitFPS(Timer &capTimer, int fps);

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