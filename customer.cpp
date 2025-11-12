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
constexpr float customersPerMinute = 2.0f;
std::exponential_distribution<float> intervalDistr{customersPerMinute / 60000.f};
std::discrete_distribution<> cusDistr{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
}  // namespace

using namespace std::chrono_literals;

constexpr std::chrono::duration<float> waitTime = 30s;

Customer::Customer(ElementId id) noexcept
    : m_start(std::chrono::milliseconds(
          std::lround(std::exponential_distribution<float>{customersPerMinute / 60000.f}(rng))))
    , m_id(id)
    , m_vis(m_id, m_order, m_served) {
    updateNextCustomerTime(m_id, m_start);
}

void Customer::handleClick(ElementId clicked) noexcept {
    switch (m_state) {
    case CustomerState::ordered: {
        if (clicked == m_id) {
            if (m_order.has(mouseItem())) {
                m_served.update(mouseItem());
                clearMouseItem();
            }

            if (orderServed()) {
                m_state = CustomerState::eating;
                m_vis.stateChanged(CustomerState::eating);
                playSound(SoundId::slurp);
                float waited = (m_tick - m_start) / (waitTime * 1.f);
                updateRating(waited, orderDiffRatio(m_order, m_served));
                m_start = m_tick;
            }
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
            reset(m_served);
        }
    } break;
    case CustomerState::ordering: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::ordered;
            m_order = spawnOrder();
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
            playSound(SoundId::burp);
            m_start = tick;
        }
    } break;
    case CustomerState::leavingServed: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::undefined;
            m_vis.stateChanged(CustomerState::undefined);
            auto next = std::chrono::milliseconds(std::lround(intervalDistr(rng)));
            m_start   = tick + next;
            updateNextCustomerTime(m_id, next);
            playSound(SoundId::coins_collection);
            gainMoney(5);
        }
    } break;
    case CustomerState::leavingNotServed: {
        m_state = CustomerState::undefined;
        m_vis.stateChanged(CustomerState::undefined);
        updateRating(1.f, orderDiffRatio(m_order, m_served));
        auto next = std::chrono::milliseconds(std::lround(intervalDistr(rng)));
        m_start   = tick + next;
        updateNextCustomerTime(m_id, next);

    } break;
    default:
        m_start = tick;
        break;
    }
    m_tick = tick;
}

bool Customer::orderServed() const noexcept { return m_order == m_served; }

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
        getElement(orderId(m_elemId)).visible      = true;
        getElement(orderRamenId(m_elemId)).visible = true;
        if (isSoftdrink(m_order.drink)) {
            getElement(orderSoftdrinkId(m_elemId)).visible = true;
            getElement(orderSoftdrinkId(m_elemId)).showId  = m_order.drink;
        }
        getElement(pbOut(m_elemId)).visible  = true;
        getElement(pbOut(m_elemId)).src      = getBarOutline(1.f);
        getElement(pbFill(m_elemId)).visible = true;
        getElement(pbFill(m_elemId)).src     = getBarFilling(1.f);
        getElement(pbFill(m_elemId)).fpos.h  = patienceBarLength;
        showServed(m_elemId, m_served.ramen, m_served.drink);
    } break;
    case CustomerState::eating: {
        getElement(m_elemId).clickable       = false;
        getElement(pbOut(m_elemId)).visible  = false;
        getElement(pbFill(m_elemId)).visible = false;
        showServed(m_elemId, m_served.ramen, m_served.drink);
        getElement(m_elemId).src                       = SrcRatio{Sprite2x2::upperRight};
        getElement(orderId(m_elemId)).visible          = false;
        getElement(orderRamenId(m_elemId)).visible     = false;
        getElement(orderSoftdrinkId(m_elemId)).visible = false;
    } break;
    case CustomerState::leavingServed: {
        hideServed(m_elemId);
        getElement(m_elemId).src = SrcRatio{Sprite2x2::lowerRight};
    }
    default:
        getElement(m_elemId).visible   = false;
        getElement(m_elemId).clickable = false;
        hideServed(m_elemId);
        getElement(pbOut(m_elemId)).visible            = false;
        getElement(pbFill(m_elemId)).visible           = false;
        getElement(orderId(m_elemId)).visible          = false;
        getElement(orderRamenId(m_elemId)).visible     = false;
        getElement(orderSoftdrinkId(m_elemId)).visible = false;
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
        showServed(m_elemId, m_served.ramen, m_served.drink);
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

CustomerOrder spawnOrder() noexcept {
    CustomerOrder res{ShowId::bowl_with_ramen_plain, ShowId::lastImg};
    if (softdrinkUnlocked()) {
        std::discrete_distribution<> drinksDistr{1, 1, 1, 1};
        res.drink = static_cast<ShowId>(drinksDistr(rng) + static_cast<int>(ShowId::softdrink_kola));
    }
    return res;
}