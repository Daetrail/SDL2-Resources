#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Util.hpp"

const unsigned int WINDOW_WIDTH = 1366;
const unsigned int WINDOW_HEIGHT = 768; 
const std::string TITLE = "SDL-Resources";

int main(int argc, char* argv[])
{
    if (!(util::init()))
        std::cout << "(Main) Failed to initialise!" << std::endl;

    RenderWindow window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    Entity background("res/gfx/main-bg.png", window.getRenderer());

    SDL_Event event;

    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
        }

        window.clear();

        window.drawToEntireWindow(background);

        window.update();
    }

    util::destroyEntityTex(background);
    window.close();

    util::close();

    return 0;
}