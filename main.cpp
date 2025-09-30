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
#include <algorithm>

Element all[] = {{potToolRect, ElementId::potSideBar, ImageId::empty_pot, true},
                 {pkgRect, ElementId::ramenSideBar, ImageId::ramenPkg, true},
                 {sinkRect, ElementId::sinkSideBar, ImageId::sink, true},
                 {binRect, ElementId::binSideBar, ImageId::bin, true},
                 {bowlsRect, ElementId::bowlsSideBar, ImageId::bowls, true},
                 {bowlsRect, ElementId::bowlsItem, ImageId::empty_bowl, false, false},
                 {potDst1, ElementId::cookingSlot1, ImageId::empty_pot, false, false},
                 {potDst2, ElementId::cookingSlot2, ImageId::empty_pot, false, false},
                 {potDst3, ElementId::cookingSlot3, ImageId::empty_pot, false, false},
                 {potDst4, ElementId::cookingSlot4, ImageId::empty_pot, false, false}};

class SideBar final {
public:
    void handleClick(ElementId elemId) noexcept {
        if (!sinkClicked && elemId == ElementId::sinkSideBar) {
            auto sink = std::find_if(std::begin(all), std::end(all),
                                     [](const Element& e) { return e.elemId == ElementId::sinkSideBar; });
            if (sink != std::end(all)) {
                sink->imgId = ImageId::sink_running_water;
            }
            sinkClicked = true;
        }

        if (!binClicked && elemId == ElementId::binSideBar) {
            auto sink = std::find_if(std::begin(all), std::end(all),
                                     [](const Element& e) { return e.elemId == ElementId::binSideBar; });
            if (sink != std::end(all)) {
                sink->imgId = ImageId::bin_open;
            }
            binClicked = true;
        }
    }

    void handleTick(std::chrono::milliseconds tick) {
        using namespace std::chrono_literals;
        if (sinkClicked) {
            if ((tick - sinkStart) > 500ms) {
                auto itr = std::find_if(std::begin(all), std::end(all),
                                        [](const Element& e) { return e.elemId == ElementId::sinkSideBar; });
                if (itr != std::end(all)) {
                    itr->imgId = ImageId::sink;
                }
                sinkClicked = false;
            }
        } else {
            sinkStart = tick;
        }

        if (binClicked) {
            if ((tick - binStart) > 500ms) {
                auto itr = std::find_if(std::begin(all), std::end(all),
                                        [](const Element& e) { return e.elemId == ElementId::binSideBar; });
                if (itr != std::end(all)) {
                    itr->imgId = ImageId::bin;
                }
                binClicked = false;
            }
        } else {
            binStart = tick;
        }
    }

private:
    bool sinkClicked = false;
    bool binClicked  = false;
    std::chrono::milliseconds sinkStart;
    std::chrono::milliseconds binStart;
};

void notifyCaptured(ElementId elemId) noexcept {}

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

    bool quit = false;
    SDL_Event e;
    RamenCooking slots[]{
        RamenCooking{ElementId::cookingSlot1, waterBoiling}, RamenCooking{ElementId::cookingSlot2, waterBoiling},
        RamenCooking{ElementId::cookingSlot3, waterBoiling}, RamenCooking{ElementId::cookingSlot4, waterBoiling}};
    SideBar sideBar{};
    auto hovered = std::end(all);

    while (!quit) {
        SDL_FPoint mousePoint;
        while (SDL_PollEvent(&e)) {
            mousePoint.x = e.button.x;
            mousePoint.y = e.button.y;

            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
                break;
            } else if (isMouse(e)) {
                // std::cout << e.type << " " << e.button.x << " " << e.button.y << std::endl;
                auto current_hover = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
                    return e.hoverable && SDL_PointInRectFloat(&mousePoint, &e.fpos);
                });

                if (current_hover != std::end(all)) {
                    current_hover->ratio = 1.2f;
                }

                if (hovered != std::end(all) && hovered != current_hover) {
                    hovered->ratio = 1.0f;
                }

                hovered = current_hover;

                if (isClick(e)) {
                    auto clicked       = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
                        return SDL_PointInRectFloat(&mousePoint, &e.fpos);
                    });
                    ElementId selected = clicked == std::end(all) ? ElementId::undefined : clicked->elemId;

                    sideBar.handleClick(selected);
                    // notifyCaptured(selected);
                    for (RamenCooking& r : slots) {
                        r.handleClick(selected);
                    }
                }
            }
        }
        auto now = std::chrono::milliseconds(SDL_GetTicks());
        for (RamenCooking& r : slots) {
            r.handleTick(now);
        }
        sideBar.handleTick(now);
        renderer.clear();

        // Draw background
        bgTexture.show(renderer, bgDst);
        customerTexture.show(renderer, custFRect);
        counterTexture.show(renderer, counterRect);
        burnerTexture.show(renderer, burnerDst);

        // Draw ramen package, sink
        for (const Element& elem : all) {
            if (elem.visible) {
                const ImageTexture& img = getImage(elem.imgId);
                img.show(renderer, elem.fpos, elem.ratio, elem.angle);
            }
        }
        // cooking slots
        for (const RamenCooking& r : slots) {
            r.show(renderer, mousePoint.x, mousePoint.y);
        }
        renderer.update();
    }

    return 0;
}