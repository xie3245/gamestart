#pragma once
#include "elementId.h"
#include <chrono>

class CookingStatus;
class Renderer;
class AudioMixer;

class Customers final {
public:
    Customers(const AudioMixer& mx, const CookingStatus& stat) noexcept : m_ramen(stat), m_mixer(mx) {}
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend) const noexcept;
    void showServedItems(const Renderer& rend) const noexcept;

private:
    enum class CustomerState { undefined, waiting, served, leaving } m_state = CustomerState::undefined;
    const CookingStatus& m_ramen;
    std::chrono::milliseconds m_toggleStart;
    std::chrono::milliseconds m_start;
    bool m_toggle = false;
    const AudioMixer& m_mixer;
};