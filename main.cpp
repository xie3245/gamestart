#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    Uint64 lastTime = 0;
    float deltaTime = 0.0f;

    Renderer renderer{};
    AudioMixer mx{};
    using namespace std::chrono_literals;
    SoundTrack bgm{mx, (getBasePath() + "assets/sounds/bgm.mp3").c_str(), 5s, true};
    SoundTrack waterBoiling{mx, (getBasePath() + "assets/sounds/boiling_water.mp3").c_str()};
    bgm.scaleVolume(0.3f);
    bgm.play();
    //waterBoiling.scaleVolume(1.f);
    
    // Load textures
    ImageTexture bgTexture{renderer, (getBasePath() + "assets/bg.png").c_str()};
    ImageTexture burnerTexture{renderer, (getBasePath() + "assets/burner.png").c_str()};
    ImageTexture ramenPkgTexture{renderer, (getBasePath() + "assets/ramen_pkg.png").c_str()};
    ImageTexture sinkTexture = {renderer, (getBasePath() + "assets/sink.png").c_str()};
    ImageTexture binTexture = {renderer, (getBasePath() + "assets/trash_bin_closed.png").c_str()};
    ImageTexture bowlsTexture = {renderer, (getBasePath() + "assets/bowls.png").c_str()};
    ImageTexture customerTexture = {renderer, (getBasePath() + "assets/customer_fox.png").c_str()};
    ImageTexture customerServedTexture = {renderer, (getBasePath() + "assets/customer_fox_satisfied.png").c_str()};

    bool quit = false;
    SDL_Event e;
    RamenCooking pot1{renderer, waterBoiling};

    while (!quit)
    {
        SDL_Point mousePoint;

        while (SDL_PollEvent(&e))
        {
            mousePoint.x = static_cast<int>(e.button.x);
            mousePoint.y = static_cast<int>(e.button.y);

            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            else
            {
                if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
                {
                    pot1.handleMouseDown(mousePoint);
                }
            }
        }

        renderer.clear();

        // Draw background
        SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
        bgTexture.show(renderer, bgDst);

        SDL_FRect burnerDst = {SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.5f, 320, 300};
        burnerTexture.show(renderer, burnerDst);

        pot1.show();

        // Draw ramen package, sink
        if (SDL_PointInRect(&mousePoint, &pkgRect))
        {
            ramenPkgTexture.show(renderer, SDL_FRect{665, 485, 110, 110});
        }
        else
        {
            ramenPkgTexture.show(renderer, pkgFRect);
        }

        if (SDL_PointInRect(&mousePoint, &sinkRect))
        {
            sinkTexture.show(renderer, SDL_FRect{665, 375, 110, 110});
        }
        else
        {
            sinkTexture.show(renderer, sinkFRect);
        }

        if (SDL_PointInRect(&mousePoint, &binRect))
        {
            binTexture.show(renderer, SDL_FRect{665, 265, 110, 110});
        }
        else
        {
            binTexture.show(renderer, binFRect);
        }

        if (SDL_PointInRect(&mousePoint, &bowlsRect))
        {
            bowlsTexture.show(renderer, SDL_FRect{665, 155, 110, 110});
        }
        else
        {
            bowlsTexture.show(renderer, bowlsFRect);
        }

        // Draw customer

        SDL_FRect custRect = {50, 100, 200, 200};

        customerTexture.show(renderer, custRect);

        renderer.update();
    }

    return 0;
}