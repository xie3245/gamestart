#pragma once
#include <SDL3/SDL.h>
#include "imageTexture.h"
#include "delegate.h"
#include <algorithm>
#include <cmath>
#include <limits>

inline constexpr SDL_FRect to_frect(const SDL_Rect& r) noexcept {
    return SDL_FRect{static_cast<float>(r.x), static_cast<float>(r.y), static_cast<float>(r.w),
                     static_cast<float>(r.h)};
}

inline SDL_Rect frect_round(const SDL_FRect& r) noexcept {
    auto lr = [](float v) { return static_cast<int>(std::lround(v)); };
    return SDL_Rect{lr(r.x), lr(r.y), std::max(0, lr(r.w)), std::max(0, lr(r.h))};
}

struct Element;
using updateFunc = Delegate<void(Element& elem, const SDL_Point& mouse, uint32_t type)>;

enum class Interaction { undefined, hover, down, click };

struct Element {
    Element(SDL_Rect rect, ImageId imId, updateFunc&& func, bool defaultVisible = true)
        : pos(rect)
        , fpos(to_frect(pos))
        , angle(0.0)
        , id(imId)
        , act(Interaction::undefined)
        , visible(defaultVisible)
        , update(std::move(func)) {}

    Element(SDL_FRect rect, ImageId imId, updateFunc&& func, bool defaultVisible = true)
        : pos(frect_round(rect))
        , fpos(rect)
        , angle(0.0)
        , id(imId)
        , act(Interaction::undefined)
        , visible(defaultVisible)
        , update(std::move(func)) {}

    SDL_Rect pos;
    SDL_FRect fpos;
    float ratio = 1.f;
    double angle;
    ImageId id;
    Interaction act;
    bool visible = true;
    updateFunc update;
};

void updateSideBarFixItem(Element& elem, const SDL_Point& mouse, uint32_t type) noexcept;
void updateCookingItem(Element& elem, const SDL_Point& mouse, uint32_t type) noexcept;
