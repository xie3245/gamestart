#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <chrono>

class AudioMixer final
{
public:
    AudioMixer() noexcept;
    ~AudioMixer() noexcept;

    MIX_Audio *createAudio(const char *path) const noexcept;
    MIX_Track *createTrack() const noexcept;

private:
    const bool m_init;
    MIX_Mixer *m_mixer;
};

class SoundTrack final
{
public:
    SoundTrack(const AudioMixer& mixer, const char *path, std::chrono::milliseconds fadeIn = std::chrono::milliseconds{0u}) noexcept;
    ~SoundTrack() noexcept;

    void scaleVolume(float ratio) noexcept;
    void playOnce() const noexcept;
    void playUntilStop() const noexcept;
    void stop(Uint64 fadeOutFrames = 0u) const noexcept;

private:
    MIX_Audio *m_audio;
    MIX_Track *m_track;
    SDL_PropertiesID m_props;
};