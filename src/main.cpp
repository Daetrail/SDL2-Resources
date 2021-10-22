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

    Text test("Hello World!", {255, 255, 255, 255}, "res/gfx/font.ttf", 50, {0, 0, 0, 0}, {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, window.getRenderer());
    test.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - test.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - test.getDstRect()->h / 2});

    std::vector<Entity> entities;

    SDL_Event event;

    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_w:
                        test.changeText("Hi World!");
                        test.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - test.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - test.getDstRect()->h / 2});
                        break;
                    case SDLK_s:
                        test.changeText("Hello World!");
                        test.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - test.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - test.getDstRect()->h / 2});
                        break;
                    default:
                        break;
                }
            }
        }

        entities = {background, test};

        window.clear();

        window.drawEntities(entities);

        window.update();
    }

    background.close();
    window.close();

    util::close();

    return 0;
}