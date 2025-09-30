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
    /*     switch (m_state) {
        case RamenState::IDLE: {
            if ((elemId == ElementId::potItem)) {
                m_state = RamenState::WAIT_POT;
            }
        } break;
        case RamenState::WAIT_POT: {
            if (elemId == m_elemId) {
            }
        } break;
        case RamenState::EMPTY: {
            if ((elemId == ImageId::pot_water_added)) {
                m_state = RamenState::WATER_ADDED;
                start   = tick;
            }
        } break;
        case RamenState::WATER_ADDED: {
            if ((tick - start) > 2s) {
                m_state = RamenState::WATER_BOILING;
                start   = tick;
            }
        } break;
        case RamenState::WATER_BOILING: {
            if ((elemId == ImageId::ramenPkg)) {
                m_state = RamenState::NOODLES_ADDED;
                start   = tick;
            }
        } break;
        case RamenState::NOODLES_ADDED: {
            if ((tick - start) > 2s) {
                m_state = RamenState::COOKING;
                start   = tick;
            }
        } break;
        case RamenState::COOKING: {
            if ((tick - start) > 2s) {
                m_state = RamenState::HALF_COOKED;
                start   = tick;
            }
        } break;
        case RamenState::HALF_COOKED: {
            if ((tick - start) > 2s) {
                m_state = RamenState::COOKED;
                start   = tick;
            }
        } break;
        case RamenState::COOKED: {
            if ((tick - start) > 5s) {
                m_state = RamenState::BURNT;
            }
            if ((elemId == ImageId::last)) {
                m_state = RamenState::IDLE;
                start   = tick;
            }
        } break;
        case RamenState::BURNT: {
            if ((elemId == ImageId::last)) {
                m_state = RamenState::IDLE;
                start   = tick;
            }
        } break;
        default:
            break;
        } */
}

void RamenCooking::handleTick(std::chrono::milliseconds tick) noexcept { using namespace std::chrono_literals; }

void RamenCooking::show(const Renderer& rend) const noexcept {
    /*     static uint16_t puffCnt = 0;
        switch (m_state) {
        case RamenState::EMPTY:
            getImage(ImageId::empty_pot).show(rend, m_origFRect);
            break;
        case RamenState::WATER_ADDED:
            getImage(ImageId::pot_water_added).show(rend, m_origFRect);
            break;
        case RamenState::WATER_BOILING: {
            if (puffCnt < 60) {
                ++puffCnt;
            } else {
                puffCnt = 0u;
            }
            if (puffCnt > 30u) {
                getImage(ImageId::pot_water_boiling).show(rend, m_origFRect, 1.1f);
            } else {
                getImage(ImageId::pot_water_boiling).show(rend, m_origFRect);
            }
        } break;
        case RamenState::NOODLES_ADDED:
            getImage(ImageId::pot_noodle_added).show(rend, m_origFRect);
            break;
        case RamenState::COOKING:
            getImage(ImageId::pot_noodle_cooking).show(rend, m_origFRect);
            break;
        case RamenState::HALF_COOKED:
            getImage(ImageId::pot_noodle_halfcooked).show(rend, m_origFRect);
            break;
        case RamenState::COOKED:
            getImage(ImageId::pot_noodle_cooked).show(rend, m_origFRect);
            break;
        case RamenState::BURNT:
            getImage(ImageId::pot_burnt).show(rend, m_origFRect);
            break;
        default:
            break;
        } */
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