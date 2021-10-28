#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Util.hpp"
#include "Entity.hpp"

namespace util
{
    bool init()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cout << "(Util) SDL could not initialise! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }
        
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

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
        {
            std::cout << "SDL_mixer cound not initialise! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return false;
        }
        return true;
    }

    void close()
    {   
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void destroyEntityTex(std::vector<Entity> &entities)
    {
        for (auto entity : entities)
            entity.close();
    }

    CalculateFPS::CalculateFPS()
    {
        this->fpsTimer.start();
    }

    void CalculateFPS::run()
    {
        this->avgFPS = this->countedFrames / (fpsTimer.getTicks() / 1000.f);
        if (this->avgFPS > 2000000) 
            this->avgFPS = 0;
    }

    float CalculateFPS::getFps()
    {
        return this->avgFPS;
    }

    void CalculateFPS::incrementFrames()
    {
        ++this->countedFrames;
    }

    void limitFPS(Timer &capTimer, int fps)
    {
        int ticksPerFrame = 1000 / fps;
        int frameTicks = capTimer.getTicks();
        if (frameTicks < ticksPerFrame)
            SDL_Delay(ticksPerFrame - frameTicks);
    }

    void keepCamInBounds(SDL_Rect &camera, const unsigned int &LEVEL_WIDTH, const unsigned int &LEVEL_HEIGHT)
    {
        if (camera.x < 0)
            camera.x = 0;
        if (camera.y < 0)
            camera.y = 0;
        if( camera.x > static_cast<int>(LEVEL_WIDTH) - camera.w )
            camera.x = static_cast<int>(LEVEL_WIDTH) - camera.w;
        if( camera.y > static_cast<int>(LEVEL_HEIGHT) - camera.h )
            camera.y = static_cast<int>(LEVEL_HEIGHT) - camera.h;
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