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
    SoundTrack bgm{mx, (getBasePath() + "assets/sounds/bgm.mp3").c_str(), 5s};
    SoundTrack waterBoiling{mx, (getBasePath() + "assets/sounds/boiling_water.mp3").c_str()};
    bgm.scaleVolume(0.3f);
    bgm.playUntilStop();

    // Load textures
    auto  bgTexture = getImage(ImageId::bg, renderer);
    auto  counterTexture = getImage(ImageId::counter_surface, renderer);
    auto  burnerTexture = getImage(ImageId::burner, renderer);
    auto  ramenPkgTexture = getImage(ImageId::ramenPkg, renderer);
    auto  sinkTexture  = getImage(ImageId::sink, renderer);
    auto  binTexture  = getImage(ImageId::bin, renderer);
    auto  bowlsTexture  = getImage(ImageId::bowls, renderer);
    auto  customerTexture  = getImage(ImageId::customer, renderer);
    auto  emptyPotTexture = getImage(ImageId::empty_pot, renderer);

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
        bgTexture.show(renderer, bgDst);
        // Draw customer
        customerTexture.show(renderer, custRect);
        counterTexture.show(renderer, counterRect);
        burnerTexture.show(renderer, burnerDst);

        pot1.show();

        // Draw ramen package, sink
        if (SDL_PointInRect(&mousePoint, &pkgRect))
        {
            ramenPkgTexture.show(renderer, pkgLargeFRect);
        }
        else
        {
            ramenPkgTexture.show(renderer, pkgFRect);
        }

        if (SDL_PointInRect(&mousePoint, &sinkRect))
        {
            sinkTexture.show(renderer, sinkLargeFRect);
        }
        else
        {
            sinkTexture.show(renderer, sinkFRect);
        }

        if (SDL_PointInRect(&mousePoint, &binRect))
        {
            binTexture.show(renderer, binLargeFRect);
        }
        else
        {
            binTexture.show(renderer, binFRect);
        }

        if (SDL_PointInRect(&mousePoint, &bowlsRect))
        {
            bowlsTexture.show(renderer, bowlsLargeFRect);
        }
        else
        {
            bowlsTexture.show(renderer, bowlsFRect);
        }

        if (SDL_PointInRect(&mousePoint, &potToolRect))
        {
            emptyPotTexture.show(renderer, potToolLargeFRect);
        }
        else
        {
            emptyPotTexture.show(renderer, potToolFRect);
        }

        renderer.update();
    }

    return 0;
}