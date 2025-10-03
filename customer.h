#pragma once
#include "elementId.h"
#include <chrono>

class CookingStatus;
class Renderer;

class Customers final {
public:
    explicit Customers(const CookingStatus& stat) noexcept : m_ramen(stat) {}
    void handleClick(ElementId clicked) noexcept;
    void handleTick(std::chrono::milliseconds tick) noexcept;
    void show(const Renderer& rend) const noexcept;

private:
    enum class CustomerState { undefined, waiting, served } m_state = CustomerState::undefined;
    const CookingStatus& m_ramen;
    std::chrono::milliseconds m_start;
    bool m_toggle = false;
};