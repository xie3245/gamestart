#include "customer.h"
#include "cookingStat.h"
#include "imageTexture.h"

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
        if ((tick - m_start) > 200ms) {
            if (m_toggle) {
                m_toggle = false;
            } else {
                m_toggle = true;
            }
            m_start = tick;
        }
    } break;

    default:
        m_start = tick;
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

    default:
        getImage(ImageId::customer).show(rend, custFRect);
        break;
    }
}