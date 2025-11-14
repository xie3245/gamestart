#include "ramenCooking.h"
#include "ui.h"
#include "globals.h"
#include "sound.h"
#include "element.h"

using namespace std::chrono_literals;

RamenCooking::RamenCooking(ElementId id) noexcept
    : m_elemId(id)
    , m_frect(getCookingSlotFRect(id))
    , m_state(RamenState::IDLE)
    , m_vis(m_elemId) {}

void RamenCooking::handleClick(ElementId elemId) noexcept {
    switch (m_state) {
    case RamenState::IDLE: {
        if ((elemId == m_elemId) && mouseItem() == ShowId::pot_water_added) {
            m_state = RamenState::POT_IN_PLACE;
            m_vis.stateChanged(RamenState::POT_IN_PLACE);
            clearMouseItem();
        }
    } break;
    case RamenState::WATER_BOILING: {
        if ((elemId == m_elemId) && mouseItem() == ShowId::classicRamen) {
            m_state = RamenState::NOODLES_ADDED;
            m_vis.stateChanged(RamenState::NOODLES_ADDED);
            clearMouseItem();
        }
    } break;
    case RamenState::TO_STIR: {
        if ((elemId == m_elemId) && (mouseItem() == ShowId::chopsticks1)) {
            m_state = RamenState::HALF_COOKED;
            m_vis.stateChanged(RamenState::HALF_COOKED);
            clearMouseItem();
            m_tick = getGameClk();
        }
    } break;
    case RamenState::BURNT: {
        if (elemId == m_elemId) {
            if (attachToMouse(m_elemId, ShowId::pot_burnt)) {
                m_state = RamenState::IDLE;
                m_vis.stateChanged(RamenState::IDLE);
            }
        }
    } break;
    case RamenState::COOKED: {
        if ((elemId == m_elemId) && (mouseItem() == ShowId::empty_bowl)) {
            m_state = RamenState::IDLE;
            m_vis.stateChanged(RamenState::IDLE);
            attachToMouse(m_elemId, ShowId::bowl_with_ramen_plain);
        }
    } break;
    default:
        break;
    }
}

void RamenCooking::handleTick(std::chrono::milliseconds tick) noexcept {
    m_vis.handleTick(tick);
    switch (m_state) {
    case RamenState::POT_IN_PLACE: {
        if ((tick - m_tick) > 2s) {
            m_state = RamenState::WATER_BOILING;
            m_vis.stateChanged(RamenState::WATER_BOILING);
            playSound(SoundId::water_boiling);
            m_tick = tick;
        }
    } break;
    case RamenState::NOODLES_ADDED: {
        if ((tick - m_tick) > 3s) {
            m_state = RamenState::TO_STIR;
            m_vis.stateChanged(RamenState::TO_STIR);
            m_tick = tick;
        }
    } break;
    case RamenState::TO_STIR: {
        if ((tick - m_tick) > 5s) {
            m_state = RamenState::BURNT;
            m_vis.stateChanged(RamenState::BURNT);
        }
    } break;
    case RamenState::HALF_COOKED: {
        if ((tick - m_tick) > 3s) {
            m_state = RamenState::COOKED;
            m_vis.stateChanged(RamenState::COOKED);
            m_tick = tick;
        }
    } break;
    case RamenState::COOKED: {
        if ((tick - m_tick) > 5s) {
            m_state = RamenState::BURNT;
            m_vis.stateChanged(RamenState::BURNT);
        }
    } break;
    default:
        m_tick = tick;
        break;
    }
}

void CookingPotVisualizer::stateChanged(RamenState changedTo) noexcept {
    Element& elem = getElement(m_elemId);
    switch (changedTo) {
    case RamenState::POT_IN_PLACE: {
        elem.visible = true;
        elem.showId  = ShowId::pot_water_added;
    } break;
    case RamenState::WATER_BOILING: {
        elem.showId = ShowId::pot_water_boiling;
    } break;
    case RamenState::NOODLES_ADDED:
        elem.showId = ShowId::pot_noodle_added;
        break;
    case RamenState::TO_STIR:
        elem.showId                          = ShowId::pot_noodle_cooking;
        getElement(puffId(m_elemId)).visible = true;

        break;
    case RamenState::HALF_COOKED:
        elem.showId                          = ShowId::pot_noodle_halfcooked;
        getElement(puffId(m_elemId)).visible = false;
        break;
    case RamenState::COOKED:
        elem.showId = ShowId::pot_noodle_cooked;
        break;
    case RamenState::BURNT:
        elem.showId                          = ShowId::pot_burnt;
        getElement(puffId(m_elemId)).visible = false;
        break;
    default:
        elem.visible                         = false;
        getElement(puffId(m_elemId)).visible = false;
        break;
    }
    m_state = changedTo;
}

void CookingPotVisualizer::handleTick(std::chrono::milliseconds tick) noexcept {
    switch (m_state) {
    case RamenState::WATER_BOILING:
    case RamenState::TO_STIR:
    case RamenState::COOKED: {
        if (tick - m_tick > 500ms) {
            Element& elem = getElement(m_elemId);
            if (m_toggle) {
                elem.ratio = (1.f + potZoomDiff);
                m_toggle   = false;
            } else {
                elem.ratio = 1.f;
                m_toggle   = true;
            }
            m_tick = tick;
        }
    } break;
    default:
        m_tick = tick;
        break;
    }

    if (m_state == RamenState::TO_STIR) {
        getElement(puffId(m_elemId)).fpos = getPuffFRect(m_elemId, m_toggle);
    }
}
