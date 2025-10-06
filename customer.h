#pragma once
#include "elementId.h"
#include <chrono>

class CookingStatus;
class Renderer;
class AudioMixer;

class Customers final {
public:
    Customers(const AudioMixer& mx, const CookingStatus& stat) noexcept;
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend) const noexcept;
    void showServedItems(const Renderer& rend) const noexcept;

private:
    enum class CustomerState { undefined, ordered, waiting, eating, leaving } m_state = CustomerState::undefined;
    const CookingStatus& m_ramen;
    static bool cookedRamenOnTheMouse;
    std::chrono::milliseconds m_toggleStart;
    std::chrono::milliseconds m_start;
    bool m_toggle = false;
    const AudioMixer& m_mixer;
};