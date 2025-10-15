#pragma once
#include <SDL3/SDL.h>
#include "imageTexture.h"
#include "delegate.h"
#include "elementId.h"

struct Element;
using updateFunc = Delegate<void(Element&, const SDL_FPoint&, uint32_t, ImageId)>;
struct Element {
    Element(SDL_FRect rect, ElementId id, ImageId imId, bool hover = false, bool defaultVisible = false)
        : fpos(rect)
        , angle(0.0)
        , imgId(imId)
        , visible(defaultVisible)
        , hoverable(hover)
        , elemId(id) {}

    SDL_FRect fpos;
    float ratio = 1.f;
    double angle;
    ImageId imgId;
    bool visible = false;
    bool hoverable;
    ElementId elemId;
};
