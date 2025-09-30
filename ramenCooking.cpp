#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"
#include "imageTexture.h"

RamenCooking::RamenCooking(ElementId id, const SoundTrack& boil) noexcept
    : m_elemId(id)
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

void showBoiling(const Renderer& rend) noexcept {
    static uint16_t puffCnt = 0;
    if (puffCnt < 60) {
        ++puffCnt;
    } else {
        puffCnt = 0u;
    }
    if (puffCnt > 30u) {
        getImage(ImageId::pot_water_boiling).show(rend, potDst1, 1.1f);
    } else {
        getImage(ImageId::pot_water_boiling).show(rend, potDst1);
    }
}

void RamenCooking::show(const Renderer& rend, float x, float y) const noexcept {
    switch (m_state) {
    case RamenState::EMPTY:
        getImage(ImageId::empty_pot).show(rend, {x - potFDst.w * 0.5f, y - potFDst.h * 0.5f, potFDst.w, potFDst.h});
        break;
    case RamenState::WATER_ADDED:
        getImage(ImageId::pot_water_added)
            .show(rend, {x - potFDst.w * 0.5f, y - potFDst.h * 0.5f, potFDst.w, potFDst.h});
        break;
    case RamenState::POT_IN_PLACE:
        getImage(ImageId::pot_water_added).show(rend, potDst1);
        break;
    case RamenState::WATER_BOILING: {
        showBoiling(rend);
    } break;
    case RamenState::NOODLES_CAPTURED: {
        showBoiling(rend);
        getImage(ImageId::ramenPkg).show(rend, {x - pkgFRect.w * 0.5f, y - pkgFRect.h * 0.5f, pkgFRect.w, pkgFRect.h});
    } break;
    case RamenState::NOODLES_ADDED:
        getImage(ImageId::pot_noodle_added).show(rend, potDst1);
        break;
    case RamenState::COOKING:
        getImage(ImageId::pot_noodle_cooking).show(rend, potDst1);
        break;
    case RamenState::HALF_COOKED:
        getImage(ImageId::pot_noodle_halfcooked).show(rend, potDst1);
        break;
    case RamenState::COOKED:
        getImage(ImageId::pot_noodle_cooked).show(rend, potDst1);
        break;
    case RamenState::BURNT:
        getImage(ImageId::pot_burnt).show(rend, potDst1);
        break;
    case RamenState::SERVING:
        getImage(ImageId::pot_noodle_cooked)
            .show(rend, {x - potFDst.w * 0.5f, y - potFDst.h * 0.5f, potFDst.w, potFDst.h});
        break;
    case RamenState::GOING_TO_TRASH:
        getImage(ImageId::pot_burnt).show(rend, {x - potFDst.w * 0.5f, y - potFDst.h * 0.5f, potFDst.w, potFDst.h});
        break;
    default:
        break;
    }
}

/* void RamenCooking::handleMouseDown(const SDL_Point& downPt) {
    LockGuard lock{m_mtx};
    switch (m_state) {
    case RamenState::EMPTY: {
        if (SDL_PointInRect(&downPt, &sinkRect)) {
            m_state = RamenState::WATER_ADDED;
        }
    } break;
    case RamenState::WATER_BOILING: {
        if (SDL_PointInRect(&downPt, &pkgRect)) {
            m_state = RamenState::NOODLES_ADDED;
        }
    } break;
    case RamenState::COOKING: {
        if (SDL_PointInRect(&downPt, &potDst)) {
            m_state = RamenState::HALF_COOKED;
        }
    } break;
    case RamenState::COOKED: {
        if (SDL_PointInRect(&downPt, &bowlsRect)) {
            boilingWaterTrack.stop();
            m_state = RamenState::EMPTY;
        }
    } break;
    case RamenState::BURNT: {
        if (SDL_PointInRect(&downPt, &binRect)) {
            m_state = RamenState::EMPTY;
        }
    } break;
    default:
        break;
    }
}

int RamenCooking::threadLoop() {
    using namespace std::chrono_literals;
    while (true) {
        switch (m_state) {
        case RamenState::WATER_ADDED: {
            this_thread::sleep(2s);
            m_state = RamenState::WATER_BOILING;
            boilingWaterTrack.playUntilStop();
        } break;
        case RamenState::NOODLES_ADDED: {
            this_thread::sleep(2s);
            m_state = RamenState::COOKING;
        } break;
        case RamenState::COOKING: {
            this_thread::sleep(2s);
            LockGuard lock{m_mtx};
            if (m_state == RamenState::COOKING) {
                boilingWaterTrack.stop();
                m_state = RamenState::BURNT;
            }
        } break;
        case RamenState::HALF_COOKED: {
            this_thread::sleep(2s);
            m_state = RamenState::COOKED;
        } break;
        case RamenState::COOKED: {
            this_thread::sleep(10s);
            LockGuard lock{m_mtx};
            if (m_state == RamenState::COOKED) {
                boilingWaterTrack.stop();
                m_state = RamenState::BURNT;
            }
        } break;
        default:
            this_thread::sleep(500ms);
            break;
        }
    }
    return 0;
} */