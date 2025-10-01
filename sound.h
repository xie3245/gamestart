#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <chrono>
#include <memory>
#include "soundId.h"

class AudioMixer final {
public:
    AudioMixer() noexcept;
    ~AudioMixer() noexcept;

    void play(SoundId id, int repetition = 0, float gain_ratio = 1.f) const noexcept;

private:
    const bool m_init;
    MIX_Mixer* m_mixer;
};
