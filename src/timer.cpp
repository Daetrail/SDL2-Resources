#include <SDL2/SDL.h>

#include "Timer.hpp"

Timer::Timer() {}

void Timer::start()
{
    this->running = true;
    this->paused = false;

    this->startTime = SDL_GetTicks();
    this->pauseTime = 0;
}

void Timer::pause()
{
    if (this->running && !this->paused)
    {
        this->paused = true;

        this->pauseTime = SDL_GetTicks() - this->startTime;
    }
}

void Timer::resume()
{
    if (this->running && this->paused)
    {
        this->paused = false;

        this->startTime = SDL_GetTicks() - this->pauseTime;

        this->pauseTime = 0;
    }
}

void Timer::reset()
{
    this->running = false;
    this->paused = false;

    this->startTime = 0;
    this->pauseTime = 0;
}

u_int32_t Timer::getTicks()
{
    u_int32_t time = 0;

    if (this->running)
    {
        if (this->paused)
            time = pauseTime;
        else
            time = SDL_GetTicks() - startTime;
    }

    return time;
}

bool Timer::isRunning()
{
    return this->running;
}

bool Timer::isPaused()
{
    return this->paused;
}