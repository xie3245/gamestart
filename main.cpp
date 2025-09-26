#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"
#include "imageTexture.h"
#include "element.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    Renderer renderer{};
    AudioMixer mx{};
    using namespace std::chrono_literals;
    SoundTrack bgm{mx, "assets/sounds/bgm.mp3", 5s};
    SoundTrack waterBoiling{mx, "assets/sounds/boiling_water.mp3"};
    bgm.scaleVolume(0.3f);
    bgm.playUntilStop();

    // Load textures
    const ImageTexture& bgTexture       = getImage(ImageId::bg);
    const ImageTexture& counterTexture  = getImage(ImageId::counter_surface);
    const ImageTexture& burnerTexture   = getImage(ImageId::burner);
    const ImageTexture& customerTexture = getImage(ImageId::customer);

    Element all[] = {{pkgRect, ImageId::ramenPkg, updateFunc::fromFunction<updateSideBarFixItem>()},
                     {sinkRect, ImageId::sink, updateFunc::fromFunction<updateSideBarFixItem>()},
                     {binRect, ImageId::bin, updateFunc::fromFunction<updateSideBarFixItem>()},
                     {bowlsRect, ImageId::bowls, updateFunc::fromFunction<updateSideBarFixItem>()},
                     {potToolRect, ImageId::empty_pot, updateFunc::fromFunction<updateSideBarFixItem>()},
                     {pkgRect, ImageId::ramenPkg, updateFunc::fromFunction<updateCookingItem>(), false},
                     {bowlsRect, ImageId::empty_bowl, updateFunc::fromFunction<updateCookingItem>(), false},
                     {potToolRect, ImageId::empty_pot, updateFunc::fromFunction<updateCookingItem>(), false}};

    bool quit = false;
    SDL_Event e;
    RamenCooking pot1{waterBoiling};

    while (!quit) {
        SDL_Point mousePoint;

        while (SDL_PollEvent(&e)) {
            mousePoint.x = static_cast<int>(e.button.x);
            mousePoint.y = static_cast<int>(e.button.y);

            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
                break;
            } else if (isMouse(e)) {
                if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    pot1.handleMouseDown(mousePoint);
                }
                for (Element& elem : all) {
                    elem.update(elem, mousePoint, e.type);
                }
            }
        }

        renderer.clear();

        // Draw background
        bgTexture.show(renderer, bgDst);
        customerTexture.show(renderer, custFRect);
        counterTexture.show(renderer, counterRect);
        burnerTexture.show(renderer, burnerDst);

        pot1.show(renderer);

        // Draw ramen package, sink
        for (const Element& elem : all) {
            if (elem.visible) {
                const ImageTexture& img = getImage(elem.id);
                img.show(renderer, elem.fpos, elem.ratio, elem.angle);
            }
        }

        renderer.update();
    }

    return 0;
}