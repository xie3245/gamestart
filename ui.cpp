#include "ui.h"

bool isMouse(const SDL_Event& e) noexcept {
    return (e.type >= SDL_EVENT_MOUSE_MOTION) && (e.type <= SDL_EVENT_MOUSE_BUTTON_UP);
}

SDL_FRect enlarge(const SDL_FRect& orig, float ratio) noexcept {
    return {orig.x - orig.w * (ratio - 1.f) * 0.5f, orig.y - orig.h * (ratio - 1.f) * 0.5f, orig.w * ratio,
            orig.h * ratio};
}