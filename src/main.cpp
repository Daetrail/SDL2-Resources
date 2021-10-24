#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Util.hpp"
#include "Text.hpp"
#include "Animations.hpp"
#include "Sound.hpp"
#include "Music.hpp"

constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768; 
const std::string TITLE = "SDL2-Resources";

int main(int argc, char* argv[])
{
    if (!(util::init()))
        std::cout << "(Main) Failed to initialise!" << std::endl;

    RenderWindow window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    u_int32_t lastTime = SDL_GetTicks();
    u_int32_t currentFPS;
    u_int32_t frames;

    Entity background("res/gfx/main-bg.png", nullptr, window.getRenderer());
    background.setBlendMode(SDL_BLENDMODE_BLEND);

    Text timer("Press Enter to start timer", {255, 128, 64, 255}, "res/gfx/font.ttf", 30, {0, 0, 0, 0}, {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, window.getRenderer());
    // timer.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - timer.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - timer.getDstRect()->h / 2});
    timer.setPos({50, 50});

    Text fpsText("Fps Counter: ", {144, 196, 255, 255}, timer.getFont(), 30, {0, 0, 0, 0}, {50, 150}, window.getRenderer());

    Animation playerAnimation({0, 0}, {576, 64}, 9, true);
    Entity player("res/gfx/textures.png", {0, 0, 64 , 64}, {0, 0}, window.getRenderer());
    player.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - timer.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - timer.getDstRect()->h / 2 + 200});
    player.setMoveSpeed(5);

    Music backgroundMusic("res/gfx/bg.wav");

    std::vector<Entity> entities;
    std::vector<Animation> animations = {playerAnimation};

    SDL_Event event;

    u_int32_t startTime = 0;

    std::stringstream timeText;

    std::stringstream FPSText;

    bool startedTimer = false;

    bool quit = false;
    while (!quit)
    {
        frames++;
        util::calculateFPS(lastTime, frames, currentFPS, 1.0);

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_0:
                        if (!startedTimer)
                        {
                            startTime = SDL_GetTicks();
                            startedTimer = true;
                        }
                        break;

                    case SDLK_1:
                        backgroundMusic.play();
                        break;

                    case SDLK_2:
                        backgroundMusic.pause();
                        break;

                    case SDLK_3:
                        backgroundMusic.resume();
                        break;

                    case SDLK_4:
                        backgroundMusic.stop();
                        break;

                    default:
                        break;
                }
            }
        }

        FPSText.str("");
        FPSText << "FPS Counter: " << currentFPS; 
        fpsText.changeText(FPSText.str());

        if (startedTimer)
        {
            timeText.str("");
            timeText << "Seconds since start time: " << (SDL_GetTicks() - startTime) / 1000.0;
            timer.changeText(timeText.str());
            // timer.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - timer.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - timer.getDstRect()->h / 2});
        }

        const u_int8_t* currentKeyStates = SDL_GetKeyboardState(nullptr);
        if (currentKeyStates[SDL_SCANCODE_W])
            player.move({0, -1});
        else if (currentKeyStates[SDL_SCANCODE_S])
            player.move({0, 1});
        else if (currentKeyStates[SDL_SCANCODE_A])
            player.move({-1, 0});
        else if (currentKeyStates[SDL_SCANCODE_D])
            player.move({1, 0});

        player.animate(playerAnimation);

        entities = {background, timer, fpsText, player};

        window.clear();

        window.drawEntities(entities);

        window.update();
    }

    util::destroyEntityTex(entities);
    window.close();
    backgroundMusic.close();

    util::close();

    return 0;
}