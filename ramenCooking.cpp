#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"
#include "imageTexture.h"

RamenCooking::RamenCooking(ElementId id, const AudioMixer& mx) noexcept
    : m_elemId(id)
    , m_frect(getCookingSlotFRect(id))
    , m_state(RamenState::IDLE)
    , m_mixer(mx) {}

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
            m_state   = RamenState::NOODLES_ADDED;
            m_amplify = false;
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
        if ((tick - m_stateStart) > 2s) {
            m_state          = RamenState::WATER_BOILING;
            m_showStateStart = tick;
            m_mixer.play(SoundId::water_boiling, 1);
            m_stateStart = tick;
        }
    } break;
    case RamenState::WATER_BOILING: {
        if ((tick - m_showStateStart) > 500ms) {
            if (m_amplify) {
                m_amplify = false;
            } else {
                m_amplify = true;
            }
            m_showStateStart = tick;
        }
        m_stateStart = tick;
    } break;
    case RamenState::NOODLES_ADDED: {
        if ((tick - m_stateStart) > 5s) {
            m_state      = RamenState::COOKING;
            m_stateStart = tick;
        }
    } break;
    case RamenState::COOKING: {
        if ((tick - m_stateStart) > 3s) {
            m_state = RamenState::BURNT;
        }
    } break;
    case RamenState::HALF_COOKED: {
        if ((tick - m_stateStart) > 5s) {
            m_state      = RamenState::COOKED;
            m_stateStart = tick;
        }
    } break;
    case RamenState::COOKED: {
        if ((tick - m_stateStart) > 3s) {
            m_state = RamenState::BURNT;
        }
    } break;
    default:
        m_stateStart = tick;
        break;
    }
}

void RamenCooking::showPulsingZoom(const Renderer& rend, ImageId id) const noexcept {
    if (m_amplify) {
        getImage(id).show(rend, m_frect, 1.1f);
    } else {
        getImage(id).show(rend, m_frect);
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
        showPulsingZoom(rend, ImageId::pot_water_boiling);
    } break;
    case RamenState::NOODLES_CAPTURED: {
        showPulsingZoom(rend, ImageId::pot_water_boiling);
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
