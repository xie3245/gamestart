#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "ramenCooking.h"
#include "ui.h"
#include "sound.h"
#include "element.h"
#include "customer.h"
#include <algorithm>
#include "sidebar.h"
#include "globals.h"
#include "renderer.h"

using namespace std::chrono_literals;
static std::chrono::milliseconds gameClk = 0ms;

std::chrono::milliseconds getGameClk() noexcept { return gameClk; }

void handleHover(std::span<Element> all, ElementId clicked, const SDL_FPoint& mousePoint) noexcept {
    static auto hovered = std::end(all);
    auto current_hover  = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
        return e.visible && e.hoverable && SDL_PointInRectFloat(&mousePoint, &e.fpos);
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
    playSound(SoundId::bgm, -1, 0.3f);

    auto all = getActiveElements();

    bool quit = false;
    RamenCooking slots[]{RamenCooking{ElementId::cookingSlot1}, RamenCooking{ElementId::cookingSlot2},
                         RamenCooking{ElementId::cookingSlot3}, RamenCooking{ElementId::cookingSlot4}};

    SideBar sideBar{};

    Customer customers[] = {Customer{ElementId::customer1}, Customer{ElementId::customer2},
                            Customer{ElementId::customer3}, Customer{ElementId::customerRightMost}};

    constexpr std::chrono::milliseconds cycleDuration = 10min;
    std::chrono::milliseconds prevSysClk{0};
    SDL_Event e;
    auto captured = 0ms;
    while (!quit) {
        all = getActiveElements();
        SDL_FPoint mousePoint;
        while (SDL_PollEvent(&e)) {
            // std::cout << "type: " << e.type << "code: " << e.key.key << std::endl;
            mousePoint.x = e.button.x;
            mousePoint.y = e.button.y;

            if (e.type == SDL_EVENT_QUIT || (e.key.key == SDLK_ESCAPE)) {
                quit = true;
                break;
            } else if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_SPACE) {
                    togglePause();
                }
            } else if (isMouse(e)) {
                // std::cout << e.type << " " << e.button.x << " " << e.button.y << std::endl;

                ElementId selected = ElementId::undefined;
                if (isClick(e)) {
                    auto clicked = std::find_if(std::begin(all), std::end(all), [&](const Element& e) {
                        return e.clickable && SDL_PointInRectFloat(&mousePoint, &e.fpos);
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
                handleHover(all, selected, mousePoint);
            }
        }

        auto now = std::chrono::milliseconds(SDL_GetTicks());

        if (!isPaused()) {
            gameClk = std::min(gameClk + (now - prevSysClk), cycleDuration);
            for (RamenCooking& r : slots) {
                r.handleTick(gameClk);
            }
            sideBar.handleTick(gameClk);
            for (Customer& cus : customers) {
                cus.handleTick(gameClk);
            }
        }

        prevSysClk = now;

        /*if (gameClk >= cycleDuration) {
            gameClk = 0ms;
                         for (RamenCooking& r : slots) {
                            r.handleCycleEnd();
                        }
                        for (Customer& cus : customers) {
                            cus.handleCycleEnd();
                        }
            clearMouseItem();
        }*/

        renderer.clear();

        // Draw ramen package, sink
        for (const Element& elem : all) {
            if (elem.visible) {
                if (isText(elem.elemId)) {
                    renderer.show(elem.showId, getText(elem.showId), elem.fpos.x, elem.fpos.y);
                } else {
                    renderer.show(elem.showId, elem.src, elem.fpos, elem.ratio, elem.angle);
                }
            }
        }

        if (mouseItem() != ShowId::last) {
            renderer.show(mouseItem(), {mousePoint.x - potSizeCooking * 0.5f, mousePoint.y - potSizeCooking * 0.5f,
                                        potSizeCooking, potSizeCooking});
        }

        if (now - captured > 500ms) {
            renderer.captureFrame();
            captured = now;
        }
        renderer.update();
        triggerSpecialEvents();
    }

    return 0;
}
