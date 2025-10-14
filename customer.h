#pragma once
#include "elementId.h"
#include "imageId.h"
#include <chrono>

class CookingStatus;
class Renderer;
class AudioMixer;

class Customer final {
public:
    Customer(const AudioMixer& mx, ElementId id) noexcept;
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
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
    std::chrono::duration<float, std::milli> m_toggleStart{0.f};
    std::chrono::duration<float, std::milli> m_start{0.f};
    std::chrono::duration<float, std::milli> m_tick{0.f};
    bool m_toggle = false;
    const AudioMixer& m_mixer;
    ElementId m_id;
    ImageId m_imgId;
};