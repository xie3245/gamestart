#pragma once

#include <chrono>
#include "imageId.h"
#include <SDL3/SDL.h>
#include "elementId.h"

class AudioMixer;
class ImageTexture;
class Renderer;
class CookingStatus;
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
    RamenCooking(ElementId id, const AudioMixer& mx, CookingStatus& stat) noexcept;

    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend, float x, float y) const noexcept;

private:
    void showPulsingZoom(const Renderer& rend, ImageId id) const noexcept;
    void toggleAmplify(std::chrono::milliseconds tick) noexcept;
    ElementId m_elemId;
    SDL_FRect m_frect;
    RamenState m_state;
    bool m_amplify = false;
    std::chrono::milliseconds m_stateStart;
    std::chrono::milliseconds m_showStateStart;
    const AudioMixer& m_mixer;
    CookingStatus& m_stat;
};