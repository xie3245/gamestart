#include "customer.h"
#include "imageTexture.h"
#include "sound.h"
#include <random>
#include <cmath>

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
    : m_start(std::chrono::milliseconds(std::lround(intervalDistr(rng))))
    , m_mixer(mx)
    , m_id(id)
    , m_imgId(toImgId(cusDistr(rng))) {}

void Customer::handleClick(ElementId clicked) noexcept {
    switch (m_state) {
    case CustomerState::ordered:
        if (isServing()) {
            m_state = CustomerState::waiting;
        }
        break;
    case CustomerState::waiting:
        if (clicked == m_id) {
            m_state = CustomerState::eating;
            m_mixer.play(SoundId::slurp);
            setServing(false);
            m_toggleStart = m_tick;
            m_start       = m_tick;
        } else if (!isServing()) {
            m_state = CustomerState::ordered;
        }
        break;
    default:
        break;
    }
}

void Customer::handleTick(std::chrono::milliseconds tick) noexcept {
    switch (m_state) {
    case CustomerState::undefined: {
        if (m_start < tick) {
            m_state = isServing() ? CustomerState::waiting : CustomerState::ordered;
            m_start = tick;
        }
    } break;
    case CustomerState::ordered: {
        if ((tick - m_start) > waitTime) {
            m_state = CustomerState::leavingNotServed;
            break;
        }

        if (isServing()) {
            m_state = CustomerState::waiting;
        }
    } break;
    case CustomerState::waiting: {
        if ((tick - m_start) > waitTime) {
            m_state = CustomerState::leavingNotServed;
        }
    } break;
    case CustomerState::eating: {
        if ((tick - m_toggleStart) > 300ms) {
            m_toggle      = !m_toggle;
            m_toggleStart = tick;
        }
        if (tick - m_start > 5s) {
            m_state = CustomerState::leavingServed;
            m_mixer.play(SoundId::burp);
            m_start = tick;
        }
    } break;
    case CustomerState::leavingServed: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::undefined;
            m_start = tick + std::chrono::milliseconds(std::lround(intervalDistr(rng)));
            m_imgId = toImgId(cusDistr(rng));
            m_mixer.play(SoundId::coins_collection);
            updateMoney(10);
        }
    } break;
    case CustomerState::leavingNotServed: {
        m_state = CustomerState::undefined;
        m_start = tick + std::chrono::milliseconds(std::lround(intervalDistr(rng)));
        m_imgId = toImgId(cusDistr(rng));

    } break;
    default:
        m_toggleStart = tick;
        m_start       = tick;
        break;
    }
    m_tick = tick;
}

SrcRations getBarOutline(float patience) noexcept {
    if (patience > 0.6f) {
        return {Sprite3x2::upperLeft};
    } else if (patience > 0.2f) {
        return {Sprite3x2::upperMiddle};
    }
    return {Sprite3x2::upperRight};
}

SrcRations getBarFilling(float patience) noexcept {
    if (patience > 0.6f) {
        return {Sprite3x2::lowerLeft, patience};
    } else if (patience > 0.2f) {
        return {Sprite3x2::lowerMiddle, patience};
    }
    return {Sprite3x2::lowerRight, patience};
}

void Customer::show(const Renderer& rend) const noexcept {
    auto cusFRect = getCustSlotFRect(m_id);
    switch (m_state) {
    case CustomerState::eating:
        if (m_toggle) {
            getImage(m_imgId).show(rend, Sprite2x2::upperRight, cusFRect);
        } else {
            getImage(m_imgId).show(rend, Sprite2x2::lowerLeft, cusFRect);
        }
        break;
    case CustomerState::leavingServed: {
        getImage(m_imgId).show(rend, Sprite2x2::lowerRight, cusFRect);
    } break;
    case CustomerState::ordered:
    case CustomerState::waiting: {
        getImage(m_imgId).show(rend, Sprite2x2::upperLeft, cusFRect);
        float elapsed_ratio  = (m_tick - m_start) / waitTime;
        float patience_ratio = 1.f - elapsed_ratio;
        getImage(ImageId::patiencebar)
            .show(rend, getBarOutline(patience_ratio),
                  {cusFRect.x + cusFRect.w * 0.25f, counterHeight - cusSize, cusFRect.w * 0.5f, 10});
        getImage(ImageId::patiencebar)
            .show(rend, getBarFilling(patience_ratio),
                  {cusFRect.x + cusFRect.w * 0.25f, counterHeight - cusSize, cusFRect.w * 0.5f * patience_ratio, 10});
    } break;
    default:
        break;
    }
}

void Customer::showServedItems(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        getImage(ImageId::bowl_with_ramen_plain).show(rend, getServingSlotFRect(m_id));
        break;
    default:
        break;
    }
}