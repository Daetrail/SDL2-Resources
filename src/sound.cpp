#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <vector>

#include "Sound.hpp"

Sound::Sound(std::string audioFile)
    : audioFile(audioFile)
{
    this->audio = Mix_LoadWAV(audioFile.c_str());
    if (this->audio == nullptr)
        std::cout << "(Sound) Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl; 
}

void Sound::close()
{
    Mix_FreeChunk(audio);
    audio = nullptr;
}

void Sound::play(int repeats)
{
    Mix_PlayChannel(-1, audio, repeats);
}

