#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

class Music
{
public:
    Music(std::string audioFile);
    void close();

    void play();
    void pause();
    void resume();
    void stop();
private:
    std::string audioFile;
    Mix_Music* audio = nullptr;
};