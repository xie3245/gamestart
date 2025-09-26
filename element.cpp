#include "element.h"

void updateSideBarFixItem(Element& elem, const SDL_Point& mouse, uint32_t type) noexcept {
    switch (elem.act) {
    case Interaction::undefined: {
        if (SDL_PointInRect(&mouse, &elem.pos)) {
            elem.act   = Interaction::hover;
            elem.ratio = 1.2f;
        }
    } break;
    case Interaction::hover: {
        if (!SDL_PointInRect(&mouse, &elem.pos)) {
            elem.ratio = 1.f;
            elem.act   = Interaction::undefined;
        }
    } break;
    default:
        break;
    }
}

void updateCookingItem(Element& elem, const SDL_Point& mouse, uint32_t type) noexcept {
    switch (elem.act) {
    case Interaction::undefined: {
        if (SDL_PointInRect(&mouse, &elem.pos)) {
            if (type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                elem.act = Interaction::down;
            }
        }
    } break;
    case Interaction::down: {
        if (SDL_PointInRect(&mouse, &elem.pos)) {
            if (type == SDL_EVENT_MOUSE_BUTTON_UP) {
                elem.act     = Interaction::click;
                elem.visible = true;
                elem.fpos    = SDL_FRect{mouse.x - elem.pos.w * 0.5f, mouse.y - elem.pos.h * 0.5f,
                                      static_cast<float>(elem.pos.w), static_cast<float>(elem.pos.h)};
            } else {
                elem.act = Interaction::undefined;
            }
        }
    } break;
    case Interaction::click: {
        if ((type == SDL_EVENT_MOUSE_BUTTON_DOWN)) {
            elem.visible = false;
            elem.fpos    = to_frect(elem.pos);
            elem.act     = Interaction::undefined;
        } else {
            elem.fpos = SDL_FRect{mouse.x - elem.pos.w * 0.5f, mouse.y - elem.pos.h * 0.5f,
                                  static_cast<float>(elem.pos.w), static_cast<float>(elem.pos.h)};
        }
    } break;
    default:
        break;
    }
}
