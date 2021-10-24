#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>

class Sound
{
public:
    Sound(std::string audioFile);
    void close();

    void play(int repeats);
private:
    std::string audioFile;
    Mix_Chunk* audio = nullptr;
};