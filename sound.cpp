#include "sound.h"
#include "utils.h"
#include <iostream>

using Audio = std::unique_ptr<MIX_Audio, void (*)(MIX_Audio*)>;

class SoundTrack final {
public:
    SoundTrack(MIX_Track* track, SoundId id, std::chrono::milliseconds fadeIn = std::chrono::milliseconds{0u}) noexcept;
    ~SoundTrack() noexcept;

    void scaleVolume(float ratio) noexcept;
    void setRepetition(int rep) noexcept;
    void play() const noexcept;
    void stop(Uint64 fadeOutFrames = 0u) const noexcept;

private:
    SoundId m_soundId;
    MIX_Track* m_track;
    SDL_PropertiesID m_props;
    float m_gain = 1.f;
    int m_rep    = 0;
};

AudioMixer::AudioMixer() noexcept
    : m_init(MIX_Init())
    , m_mixer(MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr)) {}

AudioMixer::~AudioMixer() noexcept {
    MIX_DestroyMixer(m_mixer);
    if (m_init) {
        MIX_Quit();
    }
}

void AudioMixer::play(SoundId id, int repetition, float gain_ratio) const noexcept {
    using namespace std::chrono_literals;
    static SoundTrack allSoundTracks[] = {
        {MIX_CreateTrack(m_mixer), SoundId::bgm, 5s},       {MIX_CreateTrack(m_mixer), SoundId::water_boiling},
        {MIX_CreateTrack(m_mixer), SoundId::running_water}, {MIX_CreateTrack(m_mixer), SoundId::bin_open},
        {MIX_CreateTrack(m_mixer), SoundId::slurp},         {MIX_CreateTrack(m_mixer), SoundId::burp}};

    SoundTrack& track = allSoundTracks[static_cast<size_t>(id)];
    track.scaleVolume(gain_ratio);
    track.setRepetition(repetition);
    track.play();
}

MIX_Audio* getAudio(SoundId id) noexcept {
    static Audio allAudios[] = {
        {MIX_LoadAudio(nullptr, "assets/sounds/bgm.mp3", false), MIX_DestroyAudio},
        {MIX_LoadAudio(nullptr, "assets/sounds/boiling_water.mp3", false), MIX_DestroyAudio},
        {MIX_LoadAudio(nullptr, "assets/sounds/sink_running_water.wav", false), MIX_DestroyAudio},
        {MIX_LoadAudio(nullptr, "assets/sounds/bin_open_sound.ogg", false), MIX_DestroyAudio},
        {MIX_LoadAudio(nullptr, "assets/sounds/slurp.wav", false), MIX_DestroyAudio},
        {MIX_LoadAudio(nullptr, "assets/sounds/burp.wav", false), MIX_DestroyAudio}};
    return allAudios[static_cast<size_t>(id)].get();
}

SoundTrack::SoundTrack(MIX_Track* track, SoundId id, std::chrono::milliseconds fadeIn) noexcept
    : m_soundId(id)
    , m_track(track)
    , m_props(SDL_CreateProperties()) {
    SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadeIn.count());

    if (!MIX_SetTrackAudio(m_track, getAudio(id))) {
        std::cerr << __func__ << SDL_GetError() << "\n";
    }
}

SoundTrack::~SoundTrack() noexcept {
    SDL_DestroyProperties(m_props);
    MIX_DestroyTrack(m_track);
}

void SoundTrack::play() const noexcept {
    if (!MIX_PlayTrack(m_track, m_props)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void SoundTrack::stop(Uint64 fadeOutFrames) const noexcept {
    if (!MIX_StopTrack(m_track, fadeOutFrames)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void SoundTrack::scaleVolume(float ratio) noexcept {
    if (m_gain != ratio) {
        if (!MIX_SetTrackGain(m_track, ratio)) {
            std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        } else {
            m_gain = ratio;
        }
    }
}

void SoundTrack::setRepetition(int rep) noexcept {
    if (m_rep != rep) {
        if (!SDL_SetNumberProperty(m_props, MIX_PROP_PLAY_LOOPS_NUMBER, rep)) {
            std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        } else {
            m_rep = rep;
        }
    }
}