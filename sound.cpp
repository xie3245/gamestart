#include "sound.h"
#include "utils.h"
#include <iostream>

AudioMixer::AudioMixer() noexcept : m_init(MIX_Init()),
                          m_mixer(MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr)) /* ,
                           m_bgm(MIX_LoadAudio(m_mixer, (getBasePath() + "assets/sounds/bgm.mp3").c_str(), false)),
                           m_bgmTrack(MIX_CreateTrack(m_mixer)), m_bgmProps(SDL_CreateProperties()),
                           m_waterBoiling(MIX_LoadAudio(m_mixer, (getBasePath() + "assets/sounds/boiling_water.mp3").c_str(), false)),
                           m_waterBoilingTrack(MIX_CreateTrack(m_mixer)), m_waterBoilingProps(SDL_CreateProperties()) */
{
}

AudioMixer::~AudioMixer() noexcept
{
    MIX_DestroyMixer(m_mixer);
    MIX_Quit();
}

MIX_Audio *AudioMixer::createAudio(const char *path)const noexcept
{
    return MIX_LoadAudio(m_mixer, path, false);
}

MIX_Track *AudioMixer::createTrack() const noexcept
{
    return MIX_CreateTrack(m_mixer);
}

SoundTrack::SoundTrack(const AudioMixer &mixer, const char *path, std::chrono::milliseconds fadeIn, bool infiniteLoop) noexcept : m_audio(mixer.createAudio(path)),
                                                                                                                             m_track(mixer.createTrack()), m_props(SDL_CreateProperties())
{
    if (infiniteLoop)
    {
        SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
    }
/*     else
    {
        SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_LOOPS_NUMBER, 1);
    } */

    SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadeIn.count()); // 5s fade-in

    if (!MIX_SetTrackAudio(m_track, m_audio))
    {
        std::cerr << __func__ << SDL_GetError() << "\n";
    }
}

SoundTrack::~SoundTrack() noexcept
{
    SDL_DestroyProperties(m_props);
    MIX_DestroyTrack(m_track);
    MIX_DestroyAudio(m_audio);
}

void SoundTrack::play() const noexcept
{
    if (!MIX_PlayTrack(m_track, m_props))
    {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void SoundTrack::scaleVolume(float ratio) noexcept
{
    if (!MIX_SetTrackGain(m_track, ratio))
    {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}