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
        EMPTY,
        WATER_ADDED,
        POT_IN_PLACE,
        WATER_BOILING,
        NOODLES_CAPTURED,
        NOODLES_ADDED,
        COOKING,
        HALF_COOKED,
        COOKED,
        BURNT,
        SERVING,
        GOING_TO_TRASH
    };

public:
    RamenCooking(ElementId id, const SoundTrack& boil) noexcept;

    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend, float x, float y) const noexcept;

private:
    ElementId m_elemId;
    SDL_FRect m_frect;
    RamenState m_state;
    std::chrono::milliseconds m_start;
    const SoundTrack& boilingWaterTrack;
};