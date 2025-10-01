#include "ui.h"
#include <cmath>

bool isMouse(const SDL_Event& e) noexcept {
    return (e.type >= SDL_EVENT_MOUSE_MOTION) && (e.type <= SDL_EVENT_MOUSE_BUTTON_UP);
}

bool isClick(const SDL_Event& e) noexcept {
    if (!isMouse(e)) {
        return false;
    }
    static MoveType prev_type = MoveType::undefined;
    static float press_x      = 0.f;
    static float press_y      = 0.f;
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        press_x = e.button.x;
        press_y = e.button.y;
    }

    if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && std::abs(press_x - e.button.x) < 10.f &&
        std::abs(press_y - e.button.y) < 10.f) {
        return true;
    }

    return false;
}