#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include "elementId.h"

enum class MoveType { undefined, move, click };

bool isClick(const SDL_Event& e) noexcept;
bool isServing() noexcept;
void setServing(bool serve) noexcept;

inline constexpr SDL_FRect to_frect(const SDL_Rect& r) noexcept {
    return SDL_FRect{static_cast<float>(r.x), static_cast<float>(r.y), static_cast<float>(r.w),
                     static_cast<float>(r.h)};
}

inline SDL_Rect frect_round(const SDL_FRect& r) noexcept {
    auto lr = [](float v) { return static_cast<int>(std::lround(v)); };
    return SDL_Rect{lr(r.x), lr(r.y), std::max(0, lr(r.w)), std::max(0, lr(r.h))};
}

bool isMouse(const SDL_Event& e) noexcept;

constexpr int SCREEN_WIDTH  = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};

constexpr float counterHeight   = SCREEN_HEIGHT * 0.4f;
constexpr SDL_FRect counterRect = {0, counterHeight, SCREEN_WIDTH, 0.12f * SCREEN_HEIGHT};

constexpr float cusSize        = SCREEN_WIDTH * 0.2f;
constexpr SDL_FRect cust1FRect = {SCREEN_WIDTH * 0.1f, counterHeight - 0.8f * cusSize, cusSize, cusSize};
constexpr SDL_FRect cust2FRect = {cust1FRect.x + cusSize, counterHeight - 0.8f * cusSize, cusSize, cusSize};
constexpr SDL_FRect cust3FRect = {cust2FRect.x + cusSize, counterHeight - 0.8f * cusSize, cusSize, cusSize};
constexpr SDL_FRect cust4FRect = {cust3FRect.x + cusSize, counterHeight - 0.8f * cusSize, cusSize, cusSize};

constexpr float columnX            = SCREEN_WIDTH * 0.85f;
constexpr float columnFirstY       = SCREEN_HEIGHT * 0.8f;
constexpr float columnItemSize     = std::min(SCREEN_WIDTH - columnX, std::min(SCREEN_HEIGHT - columnFirstY, 100.f));
constexpr float columnCenterX      = columnX + columnItemSize * 0.5f;
constexpr float columnCenterYFirst = columnFirstY + columnItemSize * 0.5f;

constexpr int columnItemDis       = 10;
constexpr float columnSecondItemY = columnFirstY - columnItemSize - columnItemDis;
constexpr float columnThirdItemY  = columnFirstY - 2 * (columnItemSize + columnItemDis);
constexpr float columnFourthItemY = columnFirstY - 3 * (columnItemSize + columnItemDis);
constexpr float columnFifthItemY  = columnFirstY - 4 * (columnItemSize + columnItemDis);

constexpr SDL_FRect pkgFRect = {columnX, columnFirstY, columnItemSize, columnItemSize};

constexpr SDL_FRect sinkFRect = {columnX, columnSecondItemY, columnItemSize, columnItemSize};

constexpr SDL_FRect binFRect = {columnX, columnThirdItemY, columnItemSize, columnItemSize};

constexpr SDL_FRect bowlsFRect = {columnX, columnFourthItemY, columnItemSize, columnItemSize};

constexpr SDL_FRect potToolFRect = {columnX, columnFifthItemY, columnItemSize, columnItemSize};

constexpr float burnerX       = SCREEN_WIDTH * 0.3f;
constexpr float burnerY       = SCREEN_HEIGHT * 0.6f;
constexpr float burnerSize    = 250.f;
constexpr SDL_FRect burnerDst = {burnerX, burnerY, burnerSize, burnerSize};

constexpr SDL_FRect potFDst1 = {burnerX + burnerSize * 0.12f, burnerY - burnerSize * 0.08f, 128, 128};

constexpr SDL_FRect potFDst2 = {burnerX + burnerSize * 0.47f, burnerY - burnerSize * 0.08f, 128, 128};

constexpr SDL_FRect potFDst3 = {burnerX + burnerSize * 0.06f, burnerY + burnerSize * 0.16f, 128, 128};

constexpr SDL_FRect potFDst4 = {burnerX + burnerSize * 0.42f, burnerY + burnerSize * 0.16f, 128, 128};

constexpr SDL_FRect servingSlotFDst1 = {cust1FRect.x + cusSize * 0.3f, cust1FRect.y + cusSize * 0.5f, 80, 80};

constexpr SDL_FRect servingSlotFDst2 = {cust2FRect.x + cusSize * 0.3f, cust2FRect.y + cusSize * 0.5f, 80, 80};

constexpr SDL_FRect servingSlotFDst3 = {cust3FRect.x + cusSize * 0.3f, cust3FRect.y + cusSize * 0.5f, 80, 80};

constexpr SDL_FRect servingSlotFDst4 = {cust4FRect.x + cusSize * 0.3f, cust4FRect.y + cusSize * 0.5f, 80, 80};

constexpr SDL_FRect getCookingSlotFRect(ElementId id) {
    switch (id) {
    case ElementId::cookingSlot1:
        return potFDst1;
    case ElementId::cookingSlot2:
        return potFDst2;
    case ElementId::cookingSlot3:
        return potFDst3;
    case ElementId::cookingSlot4:
        return potFDst4;
    default:
        return {0, 0, 0, 0};
    }
}

constexpr SDL_FRect getCustSlotFRect(ElementId id) {
    switch (id) {
    case ElementId::customer1:
        return cust1FRect;
    case ElementId::customer2:
        return cust2FRect;
    case ElementId::customer3:
        return cust3FRect;
    case ElementId::customerRightMost:
        return cust4FRect;
    default:
        return {0, 0, 0, 0};
    }
}

constexpr SDL_FRect getServingSlotFRect(ElementId id) {
    switch (id) {
    case ElementId::customer1:
        return servingSlotFDst1;
    case ElementId::customer2:
        return servingSlotFDst2;
    case ElementId::customer3:
        return servingSlotFDst3;
    case ElementId::customerRightMost:
        return servingSlotFDst4;
    default:
        return {0, 0, 0, 0};
    }
}