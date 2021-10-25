#pragma once

#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();

    void start();
    void pause();
    void resume();
    void reset();

    u_int32_t getTicks();

    bool isRunning();
    bool isPaused();
private:
    u_int32_t startTime = 0;
    u_int32_t pauseTime = 0;

    bool running = false;
    bool paused = true;
};