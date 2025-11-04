#include "customer.h"
#include "element.h"
#include "sound.h"
#include <random>
#include <cmath>
#include "globals.h"
#include "ui.h"
#include "renderer.h"

namespace {
std::random_device rd{};
std::mt19937 rng{rd()};
constexpr float customersPerMinute = 1.0f;
std::exponential_distribution<float> intervalDistr{customersPerMinute / 60000.f};
std::discrete_distribution<> cusDistr{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
}  // namespace

using namespace std::chrono_literals;

constexpr std::chrono::duration<float> waitTime = 30s;

Customer::Customer(const AudioMixer& mx, ElementId id) noexcept
    : m_start(std::chrono::milliseconds(
          std::lround(std::exponential_distribution<float>{customersPerMinute / 60000.f}(rng))))
    , m_mixer(mx)
    , m_id(id)
    , m_vis(m_id) {}

void Customer::handleClick(ElementId clicked) noexcept {
    switch (m_state) {
    case CustomerState::ordered: {
        if (clicked == m_id && (mouseItem() == ShowId::bowl_with_ramen_plain)) {
            m_state = CustomerState::eating;
            m_vis.stateChanged(CustomerState::eating);
            m_mixer.play(SoundId::slurp);
            clearMouseItem();
            auto rating = ((m_tick - m_start) > (0.5f * waitTime)) ? 1 : 2;
            updateRating(rating);
            m_start = m_tick;
        }
    } break;
    default:
        break;
    }
}

void Customer::handleTick(std::chrono::milliseconds tick) noexcept {
    m_vis.handleTick(tick);
    switch (m_state) {
    case CustomerState::undefined: {
        if (m_start < tick) {
            m_state = CustomerState::ordering;
            m_vis.stateChanged(CustomerState::ordering);
            m_start = tick;
        }
    } break;
    case CustomerState::ordering: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::ordered;
            m_vis.stateChanged(CustomerState::ordered);
            m_start = tick;
        }
    } break;
    case CustomerState::ordered: {
        if ((tick - m_start) > waitTime) {
            m_state = CustomerState::leavingNotServed;
            m_vis.stateChanged(CustomerState::leavingNotServed);
        }
    } break;
    case CustomerState::eating: {
        if (tick - m_start > 5s) {
            m_state = CustomerState::leavingServed;
            m_vis.stateChanged(CustomerState::leavingServed);
            m_mixer.play(SoundId::burp);
            m_start = tick;
        }
    } break;
    case CustomerState::leavingServed: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::undefined;
            m_vis.stateChanged(CustomerState::undefined);
            m_start = tick + std::chrono::milliseconds(std::lround(intervalDistr(rng)));
            m_mixer.play(SoundId::coins_collection);
            gainMoney(5);
        }
    } break;
    case CustomerState::leavingNotServed: {
        m_state = CustomerState::undefined;
        m_vis.stateChanged(CustomerState::undefined);
        updateRating(0);
        m_start = tick + std::chrono::milliseconds(std::lround(intervalDistr(rng)));

    } break;
    default:
        m_start = tick;
        break;
    }
    m_tick = tick;
}

SrcRatio getBarOutline(float patience) noexcept {
    if (patience > 0.6f) {
        return SrcRatio{Sprite2x3::upperRight};
    } else if (patience > 0.2f) {
        return SrcRatio{Sprite2x3::middleRight};
    }
    return SrcRatio{Sprite2x3::lowerRight};
}

SrcRatio getBarFilling(float patience) noexcept {
    if (patience > 0.6f) {
        return SrcRatio{Sprite2x3::upperLeft, patience};
    } else if (patience > 0.2f) {
        return SrcRatio{Sprite2x3::middleLeft, patience};
    }
    return SrcRatio{Sprite2x3::lowerLeft, patience};
}

void CustomerVisualizer::stateChanged(CustomerState changedTo) noexcept {
    switch (changedTo) {
    case CustomerState::ordering: {
        Element& elem  = getElement(m_elemId);
        elem.visible   = true;
        elem.clickable = true;
        elem.showId    = toImgId(cusDistr(rng));
        elem.src       = SrcRatio{Sprite2x2::upperLeft};
    } break;
    case CustomerState::ordered: {
        getElement(orderId(m_elemId)).visible     = true;
        getElement(orderTextId(m_elemId)).visible = true;
        getElement(pbOut(m_elemId)).visible       = true;
        getElement(pbOut(m_elemId)).src           = getBarOutline(1.f);
        getElement(pbFill(m_elemId)).visible      = true;
        getElement(pbFill(m_elemId)).src          = getBarFilling(1.f);
        getElement(pbFill(m_elemId)).fpos.h       = patienceBarLength;

    } break;
    case CustomerState::eating: {
        getElement(m_elemId).clickable                  = false;
        getElement(pbOut(m_elemId)).visible             = false;
        getElement(pbFill(m_elemId)).visible            = false;
        getElement(servedItemId(m_elemId)).visible      = true;
        getElement(orderTextId(m_elemId)).strikeThrough = true;
        getElement(m_elemId).src                        = SrcRatio{Sprite2x2::upperRight};
    } break;
    case CustomerState::leavingServed: {
        getElement(m_elemId).src                        = SrcRatio{Sprite2x2::lowerRight};
        getElement(servedItemId(m_elemId)).visible      = false;
        getElement(orderId(m_elemId)).visible           = false;
        getElement(orderTextId(m_elemId)).visible       = false;
        getElement(orderTextId(m_elemId)).strikeThrough = false;
    }
    default:
        getElement(m_elemId).visible                    = false;
        getElement(m_elemId).clickable                  = false;
        getElement(orderId(m_elemId)).visible           = false;
        getElement(servedItemId(m_elemId)).visible      = false;
        getElement(pbOut(m_elemId)).visible             = false;
        getElement(pbFill(m_elemId)).visible            = false;
        getElement(orderTextId(m_elemId)).visible       = false;
        getElement(orderTextId(m_elemId)).strikeThrough = false;
        break;
    }
    m_state = changedTo;
}

void CustomerVisualizer::handleTick(std::chrono::milliseconds tick) noexcept {
    if (m_state == CustomerState::ordered) {
        float elapsed_ratio                 = std::chrono::duration<float, std::milli>(tick - m_tick) / waitTime;
        float patience_ratio                = 1.f - elapsed_ratio;
        getElement(pbOut(m_elemId)).src     = getBarOutline(patience_ratio);
        getElement(pbFill(m_elemId)).src    = getBarFilling(patience_ratio);
        getElement(pbFill(m_elemId)).fpos.h = patienceBarLength * patience_ratio;
    } else if (m_state == CustomerState::eating) {
        if ((tick - m_tick) > 300ms) {
            if (m_toggle) {
                getElement(m_elemId).src = SrcRatio{Sprite2x2::lowerLeft};
            } else {
                getElement(m_elemId).src = SrcRatio{Sprite2x2::upperRight};
            }
            m_toggle = !m_toggle;
            m_tick   = tick;
        }
    } else {
        m_tick = tick;
    }
}