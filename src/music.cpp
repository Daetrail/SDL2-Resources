#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#include "Music.hpp"

Music::Music(std::string audioFile)
    : audioFile(audioFile)
{
    this->audio = Mix_LoadMUS(audioFile.c_str());
    if (this->audio == nullptr)
        std::cout << "(Music) Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl; 
}

void Music::close()
{   
    Mix_FreeMusic(this->audio);
    this->audio = nullptr;
}

void Music::play()
{
    Mix_PlayMusic(this->audio, -1);
}

void Music::pause()
{
    Mix_PauseMusic();
}

void Music::resume()
{
    Mix_ResumeMusic();
}

void Music::stop()
{
    Mix_HaltMusic();
}