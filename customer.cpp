#include "customer.h"
#include "cookingStat.h"
#include "imageTexture.h"
#include "sound.h"

void Customers::handleClick(ElementId clicked) noexcept {
    switch (m_state) {
    case CustomerState::undefined:
        if (m_ramen.isCooked(clicked)) {
            m_state = CustomerState::waiting;
        }
        break;
    case CustomerState::waiting:
        if (clicked == ElementId::customer1) {
            m_state = CustomerState::served;
            m_mixer.play(SoundId::slurp);
        } else {
            m_state = CustomerState::undefined;
        }
        break;
    default:
        break;
    }
}

void Customers::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    switch (m_state) {
    case CustomerState::served: {
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
            m_start = tick;
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
    case CustomerState::served:
        if (m_toggle) {
            getImage(ImageId::customer_chew1).show(rend, custFRect);
        } else {
            getImage(ImageId::customer_chew2).show(rend, custFRect);
        }
        break;
    case CustomerState::leaving: {
        getImage(ImageId::customer_served_well).show(rend, custFRect);
    } break;
    default:
        getImage(ImageId::customer).show(rend, custFRect);
        break;
    }
}

void Customers::showServedItems(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::served:
        getImage(ImageId::bowl_with_ramen_plain).show(rend, servingSlotFDst1);
        break;
    default:
        break;
    }
}