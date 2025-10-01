#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"
#include "imageTexture.h"

RamenCooking::RamenCooking(ElementId id, const SoundTrack& boil) noexcept
    : m_elemId(id)
    , m_frect(getCookingSlotFRect(id))
    , m_state(RamenState::IDLE)
    , boilingWaterTrack(boil) {}

void RamenCooking::handleClick(ElementId elemId) noexcept {
    switch (m_state) {
    case RamenState::IDLE: {
        if (elemId == ElementId::potSideBar) {
            m_state = RamenState::EMPTY;
        }
    } break;
    case RamenState::EMPTY: {
        if ((elemId == ElementId::sinkSideBar)) {
            m_state = RamenState::WATER_ADDED;
        } else {
            m_state = RamenState::IDLE;
        }
    } break;
    case RamenState::WATER_ADDED: {
        if ((elemId == m_elemId)) {
            m_state = RamenState::POT_IN_PLACE;
        } else {
            m_state = RamenState::IDLE;
        }
    } break;
    case RamenState::WATER_BOILING: {
        if (elemId == ElementId::ramenSideBar) {
            m_state = RamenState::NOODLES_CAPTURED;
        }
    } break;
    case RamenState::NOODLES_CAPTURED: {
        if ((elemId == m_elemId)) {
            m_state = RamenState::NOODLES_ADDED;
        } else {
            m_state = RamenState::WATER_BOILING;
        }
    } break;
    case RamenState::COOKING: {
        if (elemId == m_elemId) {
            m_state = RamenState::HALF_COOKED;
        }
    } break;
    case RamenState::COOKED: {
        if (elemId == m_elemId) {
            m_state = RamenState::SERVING;
        }
    } break;
    case RamenState::BURNT: {
        if (elemId == m_elemId) {
            m_state = RamenState::GOING_TO_TRASH;
        }
    } break;
    case RamenState::SERVING: {
        if (elemId == ElementId::bowlsSideBar) {
            m_state = RamenState::IDLE;
        } else {
            m_state = RamenState::COOKED;
        }
    } break;
    case RamenState::GOING_TO_TRASH: {
        if (elemId == ElementId::binSideBar) {
            m_state = RamenState::IDLE;
        } else {
            m_state = RamenState::BURNT;
        }
    } break;
    default:
        break;
    }
}

void RamenCooking::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    switch (m_state) {
    case RamenState::POT_IN_PLACE: {
        if ((tick - m_start) > 2s) {
            m_state = RamenState::WATER_BOILING;
            boilingWaterTrack.playOnce();
        }
    } break;
    case RamenState::NOODLES_ADDED: {
        if ((tick - m_start) > 5s) {
            m_state = RamenState::COOKING;
            m_start = tick;
        }
    } break;
    case RamenState::COOKING: {
        if ((tick - m_start) > 3s) {
            m_state = RamenState::BURNT;
        }
    } break;
    case RamenState::HALF_COOKED: {
        if ((tick - m_start) > 5s) {
            m_state = RamenState::COOKED;
            m_start = tick;
        }
    } break;
    case RamenState::COOKED: {
        if ((tick - m_start) > 3s) {
            m_state = RamenState::BURNT;
        }
    } break;
    default:
        m_start = tick;
        break;
    }
}

void showBoiling(const Renderer& rend, const SDL_FRect& frect) noexcept {
    static uint16_t puffCnt = 0;
    if (puffCnt < 60) {
        ++puffCnt;
    } else {
        puffCnt = 0u;
    }
    if (puffCnt > 30u) {
        getImage(ImageId::pot_water_boiling).show(rend, frect, 1.1f);
    } else {
        getImage(ImageId::pot_water_boiling).show(rend, frect);
    }
}

void RamenCooking::show(const Renderer& rend, float x, float y) const noexcept {
    switch (m_state) {
    case RamenState::EMPTY:
        getImage(ImageId::empty_pot).show(rend, {x - m_frect.w * 0.5f, y - m_frect.h * 0.5f, m_frect.w, m_frect.h});
        break;
    case RamenState::WATER_ADDED:
        getImage(ImageId::pot_water_added)
            .show(rend, {x - m_frect.w * 0.5f, y - m_frect.h * 0.5f, m_frect.w, m_frect.h});
        break;
    case RamenState::POT_IN_PLACE:
        getImage(ImageId::pot_water_added).show(rend, m_frect);
        break;
    case RamenState::WATER_BOILING: {
        showBoiling(rend, m_frect);
    } break;
    case RamenState::NOODLES_CAPTURED: {
        showBoiling(rend, m_frect);
        getImage(ImageId::ramenPkg).show(rend, {x - pkgFRect.w * 0.5f, y - pkgFRect.h * 0.5f, pkgFRect.w, pkgFRect.h});
    } break;
    case RamenState::NOODLES_ADDED:
        getImage(ImageId::pot_noodle_added).show(rend, m_frect);
        break;
    case RamenState::COOKING:
        getImage(ImageId::pot_noodle_cooking).show(rend, m_frect);
        break;
    case RamenState::HALF_COOKED:
        getImage(ImageId::pot_noodle_halfcooked).show(rend, m_frect);
        break;
    case RamenState::COOKED:
        getImage(ImageId::pot_noodle_cooked).show(rend, m_frect);
        break;
    case RamenState::BURNT:
        getImage(ImageId::pot_burnt).show(rend, m_frect);
        break;
    case RamenState::SERVING:
        getImage(ImageId::pot_noodle_cooked)
            .show(rend, {x - m_frect.w * 0.5f, y - m_frect.h * 0.5f, m_frect.w, m_frect.h});
        break;
    case RamenState::GOING_TO_TRASH:
        getImage(ImageId::pot_burnt).show(rend, {x - m_frect.w * 0.5f, y - m_frect.h * 0.5f, m_frect.w, m_frect.h});
        break;
    default:
        break;
    }
}
