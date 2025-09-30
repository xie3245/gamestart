#pragma once
#include <SDL3/SDL.h>
#include "imageTexture.h"
#include "delegate.h"
#include "elementId.h"

struct Element;
using updateFunc = Delegate<void(Element&, const SDL_FPoint&, uint32_t, ImageId)>;

enum class Interaction { none, hover, down, click };

struct Element {
    Element(SDL_Rect rect, ElementId id, ImageId imId, bool hover, bool defaultVisible = true)
        : pos(rect)
        , fpos(to_frect(pos))
        , angle(0.0)
        , imgId(imId)
        , act(Interaction::none)
        , visible(defaultVisible)
        , hoverable(hover)
        , elemId(id) {}

    Element(SDL_FRect rect, ElementId id, ImageId imId, bool hover, bool defaultVisible = true)
        : pos(frect_round(rect))
        , fpos(rect)
        , angle(0.0)
        , imgId(imId)
        , act(Interaction::none)
        , visible(defaultVisible)
        , hoverable(hover)
        , elemId(id) {}

    SDL_Rect pos;
    SDL_FRect fpos;
    float ratio = 1.f;
    double angle;
    ImageId imgId;
    Interaction act;
    bool visible = true;
    bool hoverable;
    ElementId elemId;
};

void updateSideBarFixItem(Element& elem, const SDL_FPoint& mouse, uint32_t type, ImageId sl) noexcept;
void updateCookingItem(Element& elem, const SDL_FPoint& mouse, uint32_t type, ImageId sl) noexcept;
