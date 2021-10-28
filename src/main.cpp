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
#include "Timer.hpp"

constexpr unsigned int LEVEL_WIDTH = 1920;
constexpr unsigned int LEVEL_HEIGHT = 1080;

constexpr unsigned int WINDOW_WIDTH = 1024;
constexpr unsigned int WINDOW_HEIGHT = 768; 
constexpr unsigned int WINDOW_FPS = 60;
const std::string TITLE = "SDL2-Resources";

int main(int argc, char* argv[])
{
    if (!(util::init()))
        std::cout << "(Main) Failed to initialise!" << std::endl;

    RenderWindow window(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

    Text timer("Press Enter to start timer", {255, 128, 64, 255}, "res/gfx/font.ttf", 30, {0, 0, 0, 0}, {50, 50}, window.getRenderer());
    Timer stopclock;
    // timer.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - timer.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - timer.getDstRect()->h / 2});

    Text fpsText("FPS Counter: ", {144, 196, 255, 255}, timer.getFont(), 30, {0, 0, 0, 0}, {50, 150}, window.getRenderer());

    SDL_Rect camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    Animation playerAnimation({0, 0}, {576, 64}, 9, true);
    Entity player("res/gfx/textures.png", {0, 0, 64 , 64}, {0, 0}, window.getRenderer());
    player.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - player.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - player.getDstRect()->h / 2});
    player.setMoveSpeed(5);

    camera.x = (player.getDstRect()->x + player.getDstRect()->w / 2) - WINDOW_WIDTH / 2;
    camera.y = (player.getDstRect()->y + player.getDstRect()->h / 2) - WINDOW_HEIGHT / 2;

    Entity background("res/gfx/level.png", {camera.x, camera.y, camera.w, camera.h}, {0, 0}, window.getRenderer());
    background.setBlendMode(SDL_BLENDMODE_BLEND);

    Entity duck("res/gfx/rubberducky.png", {0, 0, 116, 110}, {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, window.getRenderer());
    duck.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - duck.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - duck.getDstRect()->h / 2});
    // duck.setPos({-50, -50});

    Text collision("Collision: False", {144, 196, 255, 255}, timer.getFont(), 30, {0, 0, 0, 0}, {50, 250}, window.getRenderer());

    Music backgroundMusic("res/gfx/bg.wav");

    std::vector<Entity> entities;
    std::vector<Animation> animations = {playerAnimation};

    SDL_Event event;

    std::stringstream timeText;

    util::CalculateFPS fps;

    // Timer capTimer; 

    std::stringstream FPSText;

    bool quit = false;
    while (!quit)
    {
        // capTimer.start();
        fps.run();

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_0:
                        if (stopclock.isRunning() && stopclock.isPaused())
                            stopclock.reset();
                        
                        else if (!stopclock.isRunning())
                            stopclock.start();
                        
                        break;

                    case SDLK_9:
                        if (stopclock.isPaused())
                            stopclock.resume();
                        else
                            stopclock.pause();
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

        camera.x = (player.getDstRect()->x - player.getDstRect()->w / 2) + player.getDstRect()->w;
        camera.y = (player.getDstRect()->y - player.getDstRect()->h / 2) + player.getDstRect()->h;

        util::keepCamInBounds(camera, LEVEL_WIDTH, LEVEL_HEIGHT);

        background.setSrc({camera.x, camera.y, camera.w, camera.h});

        // player.setPos({camera.x - player.getDstRect()->w / 2, camera.y + player.getDstRect()->h / 2});

        player.activateBorderCollision(WINDOW_WIDTH, WINDOW_HEIGHT);

        // player.setPos({player.getDstRect()->x - camera.x, player.getDstRect()->y - camera.y});

        if (player.collisionWithRect(duck.getDstRect()))
            collision.changeText("Collision: True");
        else 
            collision.changeText("Collision: False");

        FPSText.str("");
        FPSText << "FPS Counter: " << fps.getFps(); 
        fpsText.changeText(FPSText.str());

        timeText.str("");
        timeText << "Seconds since start time: " << (stopclock.getTicks() / 1000.f);

        timer.changeText(timeText.str());

        // timer.setPos({static_cast<int>(WINDOW_WIDTH) / 2 - timer.getDstRect()->w / 2, static_cast<int>(WINDOW_HEIGHT) / 2 - timer.getDstRect()->h / 2});

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

        entities = {background, timer, fpsText, collision, duck, player};

        window.clear();

        window.drawEntities(entities);

        window.update();

        fps.incrementFrames();

        // util::limitFPS(capTimer, WINDOW_FPS);
    }

    util::destroyEntityTex(entities);
    window.close();
    backgroundMusic.close();

    util::close();

    return 0;
}