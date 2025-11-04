#pragma once

#include <span>
#include <chrono>
#include "elementId.h"
#include "soundId.h"

class AudioMixer;
class Element;

class SideBar final {
public:
    explicit SideBar(const AudioMixer& mx) noexcept : m_mixer(mx) {}

    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;

private:
    const AudioMixer& m_mixer;
    bool sinkClicked = false;
    bool binClicked  = false;
    std::chrono::milliseconds m_tick;
};