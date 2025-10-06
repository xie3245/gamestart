#include "customer.h"
#include "cookingStat.h"
#include "imageTexture.h"
#include "sound.h"
#include <random>
#include <cmath>

namespace {
std::random_device rd{};
std::mt19937 rng{rd()};
constexpr double mean = 6.0;
std::normal_distribution distr{mean, 5.0};
}  // namespace

bool Customers::cookedRamenOnTheMouse = false;

Customers::Customers(const AudioMixer& mx, const CookingStatus& stat) noexcept
    : m_ramen(stat)
    , m_start(std::chrono::seconds(std::lround(distr(rng))))
    , m_mixer(mx) {}

void Customers::handleClick(ElementId clicked) noexcept {
    if (!cookedRamenOnTheMouse) {
        cookedRamenOnTheMouse = m_ramen.isCooked(clicked);
    } else {
        cookedRamenOnTheMouse = !is_customer(clicked);
    }

    switch (m_state) {
    case CustomerState::ordered:
        if (cookedRamenOnTheMouse) {
            m_state = CustomerState::waiting;
        }
        break;
    case CustomerState::waiting:
        if (clicked == ElementId::customer1) {
            m_state = CustomerState::eating;
            m_mixer.play(SoundId::slurp);
            cookedRamenOnTheMouse = false;
        } else if (!cookedRamenOnTheMouse) {
            m_state = CustomerState::ordered;
        }
        break;
    default:
        break;
    }
}

void Customers::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    switch (m_state) {
    case CustomerState::undefined: {
        if (m_start < tick) {
            m_state = cookedRamenOnTheMouse ? CustomerState::waiting : CustomerState::ordered;
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
            m_start = tick + std::chrono::seconds(std::lround(distr(rng)));
        }
    } break;
    default:
        m_toggleStart = tick;
        m_start       = tick;
        break;
    }
}

void Customers::show(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        if (m_toggle) {
            getImage(ImageId::customer_chew1).show(rend, custFRect);
        } else {
            getImage(ImageId::customer_chew2).show(rend, custFRect);
        }
        break;
    case CustomerState::leaving: {
        getImage(ImageId::customer_served_well).show(rend, custFRect);
    } break;
    case CustomerState::ordered:
    case CustomerState::waiting: {
        getImage(ImageId::customer).show(rend, custFRect);
    } break;
    default:
        break;
    }
}

void Customers::showServedItems(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        getImage(ImageId::bowl_with_ramen_plain).show(rend, servingSlotFDst1);
        break;
    default:
        break;
    }
}