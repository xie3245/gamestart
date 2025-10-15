#pragma once

#include <span>
#include <chrono>
#include "elementId.h"
#include "soundId.h"

class AudioMixer;
class Element;

class SideBar final {
public:
    explicit SideBar(const AudioMixer& mx, std::span<Element>&& elems) noexcept
        : m_mixer(mx)
        , m_elemsView(std::move(elems)) {}

    void handleClick(ElementId elemId) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void handleCycleStart() noexcept;
    void handleCycleEnd() noexcept;

private:
    const AudioMixer& m_mixer;
    std::span<Element> m_elemsView;
    bool sinkClicked = false;
    bool binClicked  = false;
    std::chrono::milliseconds sinkStart;
    std::chrono::milliseconds binStart;
};