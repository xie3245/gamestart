#pragma once
#include "elementId.h"
#include "imageId.h"
#include <chrono>
#include "text.h"

class CookingStatus;
class Renderer;
class AudioMixer;

class Customer final {
public:
    Customer(const AudioMixer& mx, ElementId id) noexcept;
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void handleCycleStart() noexcept;
    void handleCycleEnd() noexcept;
    void show(const Renderer& rend) const noexcept;
    void showItemsBeforeCounter(const Renderer& rend) const noexcept;

private:
    enum class CustomerState {
        undefined,
        ordering,
        ordered,
        waiting,
        eating,
        leavingServed,
        leavingNotServed
    } m_state = CustomerState::undefined;
    std::chrono::milliseconds m_toggleStart;
    std::chrono::milliseconds m_start;
    std::chrono::milliseconds m_tick;
    bool m_toggle = false;
    const AudioMixer& m_mixer;
    ElementId m_id;
    ImageId m_imgId;
    mutable FontTexture m_text;
};