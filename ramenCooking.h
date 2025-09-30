#pragma once

#include <chrono>
#include "imageId.h"
#include <SDL3/SDL.h>
#include "elementId.h"

class SoundTrack;
class ImageTexture;
class Renderer;
class RamenCooking final {
    enum class RamenState {
        IDLE,
        WAIT_POT,
        EMPTY,
        WATER_ADDED,
        WATER_BOILING,
        NOODLES_ADDED,
        COOKING,
        HALF_COOKED,
        COOKED,
        BURNT
    };

public:
    RamenCooking(ElementId id, const SoundTrack& boil) noexcept;

    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend) const noexcept;

private:
    ElementId m_elemId;
    RamenState m_state;
    const SoundTrack& boilingWaterTrack;
};