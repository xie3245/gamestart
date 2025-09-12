#pragma once

#include <SDL3_mixer/SDL_mixer.h>

class Mixer final
{
public:
    Mixer() noexcept;
    ~Mixer() noexcept;

    void playBgm() noexcept;

private:
    const bool m_init;
    MIX_Mixer *m_mixer;
    MIX_Audio *m_bgm;
    MIX_Track *m_bgmTrack;
    SDL_PropertiesID m_bgmProps;
};