#pragma once

#include <chrono>
#include <SDL3/SDL.h>
#include "elementId.h"

class AudioMixer;
class Renderer;

enum class RamenState { IDLE, POT_IN_PLACE, WATER_BOILING, NOODLES_ADDED, TO_STIR, HALF_COOKED, COOKED, BURNT };
class CookingPotVisualizer final {
public:
    explicit CookingPotVisualizer(ElementId id) noexcept : m_elemId(id) {}
    void stateChanged(RamenState changedTo) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    ElementId m_elemId;
    RamenState m_state = RamenState::IDLE;
    bool m_toggle      = false;
    std::chrono::milliseconds m_tick;
};

class RamenCooking final {
public:
    explicit RamenCooking(ElementId id) noexcept;
    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    ElementId m_elemId;
    SDL_FRect m_frect;
    RamenState m_state;
    std::chrono::milliseconds m_tick;
    CookingPotVisualizer m_vis;
};
