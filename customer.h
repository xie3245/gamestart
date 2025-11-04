#pragma once
#include "elementId.h"
#include <chrono>

class Renderer;
class AudioMixer;

enum class CustomerState { undefined, ordering, ordered, eating, leavingServed, leavingNotServed };

class CustomerVisualizer final {
public:
    explicit CustomerVisualizer(ElementId id) noexcept : m_elemId(id) {}
    void stateChanged(CustomerState changedTo) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    ElementId m_elemId;
    CustomerState m_state = CustomerState::undefined;
    bool m_toggle         = false;
    std::chrono::milliseconds m_tick;
};

class Customer final {
public:
    Customer(const AudioMixer& mx, ElementId id) noexcept;
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    CustomerState m_state = CustomerState::undefined;
    std::chrono::milliseconds m_start;
    std::chrono::milliseconds m_tick;
    const AudioMixer& m_mixer;
    ElementId m_id;
    CustomerVisualizer m_vis;
};