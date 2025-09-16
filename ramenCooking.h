#pragma once

#include "thread.h"
#include "imageTexture.h"
#include "mutex.h"

class SoundTrack;

class RamenCooking final
{
    enum class RamenState
    {
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
    explicit RamenCooking(Renderer &r, const SoundTrack& boil) noexcept;
    ~RamenCooking() noexcept;

    void show();

    void handleMouseDown(const SDL_Point &downPt);

private:
    int threadLoop();

    Renderer &m_renderer;
    RamenState m_state;
    uint8_t m_progress = 0;
    Thread<int()> m_thread;
    Mutex m_mtx;
    const ImageTexture& emptyPotTexture;
    const ImageTexture& potWithWaterTexture;
    const ImageTexture& potWithBoilingWaterTexture;
    const ImageTexture& potWithRamenUncookedTexture;
    const ImageTexture& potWithRamenHalfCookedTexture;
    const ImageTexture& potWithRamenHalfCookedFlippedTexture;
    const ImageTexture& potWithRamenCookedTexture;
    const ImageTexture& potWithRamenBurntTexture;
    const SoundTrack& boilingWaterTrack;
};