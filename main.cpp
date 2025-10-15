#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ramenCooking.h"
#include "ui.h"
#include "sound.h"
#include "imageTexture.h"
#include "element.h"
#include "customer.h"
#include <algorithm>
#include "money.h"
#include "sidebar.h"

using namespace std::chrono_literals;
Element all[] = {{potToolFRect, ElementId::potSideBar, ImageId::empty_pot, true, true},
                 {pkgFRect, ElementId::ramenSideBar, ImageId::ramenPkg, true, true},
                 {sinkFRect, ElementId::sinkSideBar, ImageId::sink, true, true},
                 {binFRect, ElementId::binSideBar, ImageId::bin, true, true},
                 {bowlsFRect, ElementId::bowlsSideBar, ImageId::bowls, true, true},
                 {chopsticksToolFRect, ElementId::chopsticksSideBar, ImageId::chopsticks2, true, true},
                 {potFDst1, ElementId::cookingSlot1, ImageId::empty_pot},
                 {potFDst2, ElementId::cookingSlot2, ImageId::empty_pot},
                 {potFDst3, ElementId::cookingSlot3, ImageId::empty_pot},
                 {potFDst4, ElementId::cookingSlot4, ImageId::empty_pot},
                 {cust1FRect, ElementId::customer1, ImageId::customer1},
                 {cust2FRect, ElementId::customer2, ImageId::customer1},
                 {cust3FRect, ElementId::customer3, ImageId::customer1},
                 {cust4FRect, ElementId::customerRightMost, ImageId::customer1}};

void handleHover(ElementId clicked, const SDL_FPoint& mousePoint) noexcept {
    static auto hovered = std::end(all);
    auto current_hover  = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
        return e.hoverable && SDL_PointInRectFloat(&mousePoint, &e.fpos);
    });

    if (current_hover != std::end(all) && current_hover->elemId != clicked) {
        current_hover->ratio = 1.2f;
    }

    if (hovered != std::end(all) && hovered != current_hover) {
        hovered->ratio = 1.0f;
    }

    hovered = current_hover;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    Renderer renderer{};
    static AudioMixer mx{};
    mx.play(SoundId::bgm, -1, 0.3f);

    // Load textures
    const ImageTexture& bgTexture      = getImage(ImageId::bg);
    const ImageTexture& counterTexture = getImage(ImageId::counter_surface);
    const ImageTexture& burnerTexture  = getImage(ImageId::burner);
    // const ImageTexture& fridgeTexture  = getImage(ImageId::fridge);

    FontTexture clkTexture{};

    bool quit   = false;
    bool paused = false;

    RamenCooking slots[]{RamenCooking{ElementId::cookingSlot1, mx}, RamenCooking{ElementId::cookingSlot2, mx},
                         RamenCooking{ElementId::cookingSlot3, mx}, RamenCooking{ElementId::cookingSlot4, mx}};

    SideBar sideBar{mx, std::span(all)};

    Customer customers[] = {{mx, ElementId::customer1},
                            {mx, ElementId::customer2},
                            {mx, ElementId::customer3},
                            {mx, ElementId::customerRightMost}};
    Money money{};

    constexpr std::chrono::milliseconds cycleDuration = 2min;
    std::chrono::milliseconds gameClk{0};
    std::chrono::milliseconds prevSysClk{0};
    SDL_Event e;
    // auto captured = 0ms;
    while (!quit) {
        SDL_FPoint mousePoint;
        while (SDL_PollEvent(&e)) {
            // std::cout << "type: " << e.type << "code: " << e.key.key << std::endl;
            mousePoint.x = e.button.x;
            mousePoint.y = e.button.y;

            if (e.type == SDL_EVENT_QUIT || (e.key.key == SDLK_ESCAPE)) {
                quit = true;
                break;
            } else if (e.key.down && (e.key.key == SDLK_SPACE)) {
                paused = !paused;
            } else if (isMouse(e)) {
                // std::cout << e.type << " " << e.button.x << " " << e.button.y << std::endl;
                ElementId selected = ElementId::undefined;
                if (isClick(e)) {
                    auto clicked = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
                        return SDL_PointInRectFloat(&mousePoint, &e.fpos);
                    });

                    selected = clicked == std::end(all) ? ElementId::undefined : clicked->elemId;
                    sideBar.handleClick(selected);
                    for (RamenCooking& r : slots) {
                        r.handleClick(selected);
                    }
                    for (Customer& cus : customers) {
                        cus.handleClick(selected);
                    }
                }
                handleHover(selected, mousePoint);
            }
        }
        auto now = std::chrono::milliseconds(SDL_GetTicks());
        if (!paused) {
            gameClk = std::min(gameClk + (now - prevSysClk), cycleDuration);
        }
        prevSysClk = now;

        for (RamenCooking& r : slots) {
            r.handleTick(gameClk);
        }
        sideBar.handleTick(gameClk);
        for (Customer& cus : customers) {
            cus.handleTick(gameClk);
        }
        renderer.clear();

        // Draw background
        bgTexture.show(renderer, bgDst);

        clkTexture.show(renderer,
                        std::to_string(std::chrono::duration_cast<std::chrono::seconds>(gameClk).count()) + "s",
                        color::black, 800, 10);

        for (Customer& cus : customers) {
            cus.show(renderer);
        }
        // fridgeTexture.show(renderer, Sprite2x1::left, {800, 200, 400, 400});
        counterTexture.show(renderer, counterRect);
        for (Customer& cus : customers) {
            cus.showItemsBeforeCounter(renderer);
        }
        burnerTexture.show(renderer, cookerFDst1);
        burnerTexture.show(renderer, cookerFDst2);
        burnerTexture.show(renderer, cookerFDst3);
        burnerTexture.show(renderer, cookerFDst4);

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
        money.show(renderer);
        showRating(renderer);

        // if (now - captured > 500ms) {
        //     renderer.captureFrame();
        //     captured = now;
        // }
        renderer.update();
        if (gameClk == cycleDuration) {
            gameClk = 0ms;
            for (RamenCooking& r : slots) {
                r.handleCycleEnd();
            }
            for (Customer& cus : customers) {
                cus.handleCycleEnd();
            }
            setServing(false);
        }
    }

    return 0;
}
