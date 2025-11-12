#pragma once
#include "elementId.h"
#include <chrono>
#include "customerOrder.h"

class Renderer;
class AudioMixer;

enum class CustomerState { undefined, ordering, ordered, eating, leavingServed, leavingNotServed };

class CustomerVisualizer final {
public:
    explicit CustomerVisualizer(ElementId id, const CustomerOrder& order, const CustomerOrder& served) noexcept
        : m_elemId(id)
        , m_order(order)
        , m_served(served) {}
    void stateChanged(CustomerState changedTo) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    ElementId m_elemId;
    CustomerState m_state = CustomerState::undefined;
    bool m_toggle         = false;
    std::chrono::milliseconds m_tick;
    const CustomerOrder& m_order;
    const CustomerOrder& m_served;
};

class Customer final {
public:
    explicit Customer(ElementId id) noexcept;
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    CustomerState m_state = CustomerState::undefined;
    std::chrono::milliseconds m_start;
    std::chrono::milliseconds m_tick;
    ElementId m_id;
    CustomerVisualizer m_vis;
    CustomerOrder m_order;
    CustomerOrder m_served;
    bool orderServed() const noexcept;
};