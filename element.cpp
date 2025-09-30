#include "element.h"

void updateSideBarFixItem(Element& elem, const SDL_FPoint& mouse, uint32_t type, ImageId sl) noexcept {
    switch (elem.act) {
    case Interaction::none: {
        if (SDL_PointInRectFloat(&mouse, &elem.fpos)) {
            elem.act   = Interaction::hover;
            elem.ratio = 1.2f;
        }
    } break;
    case Interaction::hover: {
        if (!SDL_PointInRectFloat(&mouse, &elem.fpos)) {
            elem.ratio = 1.f;
            elem.act   = Interaction::none;
        }
    } break;
    default:
        break;
    }
}

void updateCookingItem(Element& elem, const SDL_FPoint& mouse, uint32_t type, ImageId sl) noexcept {
    switch (elem.act) {
    case Interaction::none: {
        if (SDL_PointInRectFloat(&mouse, &elem.fpos)) {
            if (type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                elem.act = Interaction::down;
            }
        }
    } break;
    case Interaction::down: {
        if (SDL_PointInRectFloat(&mouse, &elem.fpos)) {
            if (type == SDL_EVENT_MOUSE_BUTTON_UP) {
                elem.act     = Interaction::click;
                elem.visible = true;
                elem.fpos    = SDL_FRect{mouse.x - elem.pos.w * 0.5f, mouse.y - elem.pos.h * 0.5f,
                                      static_cast<float>(elem.pos.w), static_cast<float>(elem.pos.h)};
            }
        } else {
            elem.act = Interaction::none;
        }
    } break;
    case Interaction::click: {
        if ((type == SDL_EVENT_MOUSE_BUTTON_DOWN)) {
            elem.visible = false;
            elem.fpos    = to_frect(elem.pos);
            elem.act     = Interaction::none;
        } else {
            elem.fpos = SDL_FRect{mouse.x - elem.pos.w * 0.5f, mouse.y - elem.pos.h * 0.5f,
                                  static_cast<float>(elem.pos.w), static_cast<float>(elem.pos.h)};
        }
    } break;
    default:
        break;
    }
}
