#pragma once
#include <SDL3/SDL.h>
#include "elementId.h"
#include "sprite.h"
#include "showId.h"
struct Element {
    Element(SDL_FRect rect,
            ElementId id,
            ShowId sId,
            bool hover            = false,
            bool defaultVisible   = false,
            bool defaultClickable = false,
            SrcRatio sc           = SrcRatio{})
        : fpos(rect)
        , src(sc)
        , angle(0.0)
        , showId(sId)
        , visible(defaultVisible)
        , hoverable(hover)
        , clickable(defaultClickable)
        , elemId(id) {}

    SDL_FRect fpos;
    SrcRatio src{};
    float ratio = 1.f;
    double angle;
    ShowId showId;
    bool visible       = false;
    bool hoverable     = false;
    bool clickable     = false;
    bool strikeThrough = false;
    ElementId elemId;
};
