#pragma once
#include <SDL3/SDL.h>
#include "imageTexture.h"
#include "delegate.h"
#include "elementId.h"

struct Element;
using updateFunc = Delegate<void(Element&, const SDL_FPoint&, uint32_t, ImageId)>;

enum class Interaction { none, hover, down, click };

struct Element {
    Element(SDL_FRect rect, ElementId id, ImageId imId, bool hover, bool defaultVisible = true)
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
    bool visible = true;
    bool hoverable;
    ElementId elemId;
};
