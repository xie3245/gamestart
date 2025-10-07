#include "customer.h"
#include "imageTexture.h"
#include "sound.h"
#include <random>
#include <cmath>

namespace {
std::random_device rd{};
std::mt19937 rng{rd()};
constexpr float customersPerMinute = 1.0f;
std::exponential_distribution<float> distr{customersPerMinute / 60000.f};
}  // namespace

Customer::Customer(const AudioMixer& mx, ElementId id) noexcept
    : m_start(std::chrono::milliseconds(std::lround(distr(rng))))
    , m_mixer(mx)
    , m_id(id) {}

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
        } else if (!isServing()) {
            m_state = CustomerState::ordered;
        }
        break;
    default:
        break;
    }
}

void Customer::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    switch (m_state) {
    case CustomerState::undefined: {
        if (m_start < tick) {
            m_state = isServing() ? CustomerState::waiting : CustomerState::ordered;
            m_start = tick;
        }
    } break;
    case CustomerState::eating: {
        if ((tick - m_toggleStart) > 300ms) {
            m_toggle      = !m_toggle;
            m_toggleStart = tick;
        }
        if (tick - m_start > 5s) {
            m_state = CustomerState::leaving;
            m_mixer.play(SoundId::burp);
            m_start = tick;
        }
    } break;
    case CustomerState::leaving: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::undefined;
            m_start = tick + std::chrono::milliseconds(std::lround(distr(rng)));
        }
    } break;
    default:
        m_toggleStart = tick;
        m_start       = tick;
        break;
    }
}

void Customer::show(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        if (m_toggle) {
            getImage(ImageId::customer_chew1).show(rend, getCustSlotFRect(m_id));
        } else {
            getImage(ImageId::customer_chew2).show(rend, getCustSlotFRect(m_id));
        }
        break;
    case CustomerState::leaving: {
        getImage(ImageId::customer_served_well).show(rend, getCustSlotFRect(m_id));
    } break;
    case CustomerState::ordered:
    case CustomerState::waiting: {
        getImage(ImageId::customer).show(rend, getCustSlotFRect(m_id));
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