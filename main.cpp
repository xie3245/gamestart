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
#include "customer.h"
#include <algorithm>

Element all[] = {{potToolFRect, ElementId::potSideBar, ImageId::empty_pot, true, true},
                 {pkgFRect, ElementId::ramenSideBar, ImageId::ramenPkg, true, true},
                 {sinkFRect, ElementId::sinkSideBar, ImageId::sink, true, true},
                 {binFRect, ElementId::binSideBar, ImageId::bin, true, true},
                 {bowlsFRect, ElementId::bowlsSideBar, ImageId::bowls, true, true},
                 {potFDst1, ElementId::cookingSlot1, ImageId::empty_pot},
                 {potFDst2, ElementId::cookingSlot2, ImageId::empty_pot},
                 {potFDst3, ElementId::cookingSlot3, ImageId::empty_pot},
                 {potFDst4, ElementId::cookingSlot4, ImageId::empty_pot},
                 {cust1FRect, ElementId::customer1, ImageId::customer1},
                 {cust2FRect, ElementId::customer2, ImageId::customer1},
                 {cust3FRect, ElementId::customer3, ImageId::customer1},
                 {cust4FRect, ElementId::customerRightMost, ImageId::customer1}};

class SideBar final {
public:
    explicit SideBar(const AudioMixer& mx) noexcept : m_mixer(mx) {}
    void handleClick(ElementId elemId) noexcept {
        if (!sinkClicked && elemId == ElementId::sinkSideBar) {
            auto sink = std::find_if(std::begin(all), std::end(all),
                                     [](const Element& e) { return e.elemId == ElementId::sinkSideBar; });
            if (sink != std::end(all)) {
                sink->imgId = ImageId::sink_running_water;
                sink->ratio = 1.5f;
            }
            sinkClicked = true;
            m_mixer.play(SoundId::running_water);
        }

        if (!binClicked && elemId == ElementId::binSideBar) {
            auto bin = std::find_if(std::begin(all), std::end(all),
                                    [](const Element& e) { return e.elemId == ElementId::binSideBar; });
            if (bin != std::end(all)) {
                bin->imgId = ImageId::bin_open;
                bin->ratio = 1.5f;
            }
            binClicked = true;
            m_mixer.play(SoundId::bin_open);
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
                    itr->ratio = 1.f;
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
                    itr->ratio = 1.f;
                }
                binClicked = false;
            }
        } else {
            binStart = tick;
        }
    }

private:
    const AudioMixer& m_mixer;
    bool sinkClicked = false;
    bool binClicked  = false;
    std::chrono::milliseconds sinkStart;
    std::chrono::milliseconds binStart;
};

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
    const ImageTexture& bgTexture       = getImage(ImageId::bg);
    const ImageTexture& counterTexture  = getImage(ImageId::counter_surface);
    const ImageTexture& burnerTexture   = getImage(ImageId::burner);
    const ImageTexture& customerTexture = getImage(ImageId::customer1);

    bool quit = false;

    RamenCooking slots[]{RamenCooking{ElementId::cookingSlot1, mx}, RamenCooking{ElementId::cookingSlot2, mx},
                         RamenCooking{ElementId::cookingSlot3, mx}, RamenCooking{ElementId::cookingSlot4, mx}};
    SideBar sideBar{mx};
    Customer customers[] = {{mx, ElementId::customer1},
                            {mx, ElementId::customer2},
                            {mx, ElementId::customer3},
                            {mx, ElementId::customerRightMost}};
    SDL_Event e;
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
        for (RamenCooking& r : slots) {
            r.handleTick(now);
        }
        sideBar.handleTick(now);
        for (Customer& cus : customers) {
            cus.handleTick(now);
        }
        renderer.clear();

        // Draw background
        bgTexture.show(renderer, bgDst);
        for (Customer& cus : customers) {
            cus.show(renderer);
        }

        counterTexture.show(renderer, counterRect);
        for (Customer& cus : customers) {
            cus.showServedItems(renderer);
        }
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