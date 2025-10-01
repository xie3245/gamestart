#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include "elementId.h"

enum class MoveType { undefined, move, click };

bool isClick(const SDL_Event& e) noexcept;

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

constexpr float cusSize       = SCREEN_WIDTH * 0.2f;
constexpr SDL_FRect custFRect = {SCREEN_WIDTH * 0.1f, counterHeight - 0.8f * cusSize, cusSize, cusSize};

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

constexpr SDL_FRect potFDst1 = {static_cast<int>(burnerX + burnerSize * 0.12f),
                                static_cast<int>(burnerY - burnerSize * 0.08f), 128, 128};

constexpr SDL_FRect potFDst2 = {static_cast<int>(burnerX + burnerSize * 0.47f),
                                static_cast<int>(burnerY - burnerSize * 0.08f), 128, 128};

constexpr SDL_FRect potFDst3 = {static_cast<int>(burnerX + burnerSize * 0.06f),
                                static_cast<int>(burnerY + burnerSize * 0.16f), 128, 128};

constexpr SDL_FRect potFDst4 = {static_cast<int>(burnerX + burnerSize * 0.42f),
                                static_cast<int>(burnerY + burnerSize * 0.16f), 128, 128};

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