#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Util.hpp"
#include "Text.hpp"

constexpr unsigned int WINDOW_WIDTH = 1366;
constexpr unsigned int WINDOW_HEIGHT = 768; 
const std::string TITLE = "SDL2-Resources";

int main(int argc, char* argv[])
{
    if (!(util::init()))
        std::cout << "(Main) Failed to initialise!" << std::endl;

    RenderWindow window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    Entity background("res/gfx/main-bg.png", nullptr, window.getRenderer());
    background.setBlendMode(SDL_BLENDMODE_BLEND);

    std::array<int, 2> dst = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    std::array<int, 4> src = {0, 0, 0, 0};

    SDL_Color testColour = {(uint8_t)255, (uint8_t)255, (uint8_t)255, (uint8_t)255};

    // Text test("Hello there!", testColour, "res/gfx/font.ttf", 28, src, dst, window.getRenderer());
    Text test("Hello There!", testColour, "res/gfx/font.ttf", 50, src, dst, window.getRenderer());

    std::array<int, 2> newpos = {WINDOW_WIDTH / 2 - test.getDstRect()->w / 2, WINDOW_HEIGHT / 2 - test.getDstRect()->h / 2};
    test.setPos(newpos);

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

        window.drawEntity(background);
        window.drawEntity(test);

        window.update();
    }

    background.close();
    window.close();

    util::close();

    return 0;
}