#include "mixer.h"
#include "utils.h"
#include <iostream>
Mixer::Mixer() noexcept : m_init(MIX_Init()),
                          m_mixer(MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr)),
                          m_bgm(MIX_LoadAudio(m_mixer, (getBasePath() + "assets/sounds/bgm.mp3").c_str(), false)),
                          m_bgmTrack(MIX_CreateTrack(m_mixer)), m_bgmProps(SDL_CreateProperties())
{
    SDL_SetNumberProperty(m_bgmProps, MIX_PROP_PLAY_LOOPS_NUMBER, -1);                  // infinite loop
    SDL_SetNumberProperty(m_bgmProps, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 5000); // 1s fade-in
}

Mixer::~Mixer() noexcept
{
    SDL_DestroyProperties(m_bgmProps);
    MIX_DestroyTrack(m_bgmTrack);
    MIX_DestroyAudio(m_bgm);
    MIX_DestroyMixer(m_mixer);
    MIX_Quit();
}

void Mixer::playBgm() noexcept
{
    if (!MIX_SetTrackAudio(m_bgmTrack, m_bgm) || !MIX_SetTrackGain(m_bgmTrack, 0.3f) || !MIX_PlayTrack(m_bgmTrack, m_bgmProps))
    {
        std::cerr << "MIX_PlayTrack failed: " << SDL_GetError() << "\n";
    }
}