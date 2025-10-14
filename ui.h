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
int64_t getMoney() noexcept;
void updateMoney(int64_t diff) noexcept;
float getRating() noexcept;
void updateRating(int rating) noexcept;

inline constexpr SDL_FRect to_frect(const SDL_Rect& r) noexcept {
    return SDL_FRect{static_cast<float>(r.x), static_cast<float>(r.y), static_cast<float>(r.w),
                     static_cast<float>(r.h)};
}

inline SDL_Rect frect_round(const SDL_FRect& r) noexcept {
    auto lr = [](float v) { return static_cast<int>(std::lround(v)); };
    return SDL_Rect{lr(r.x), lr(r.y), std::max(0, lr(r.w)), std::max(0, lr(r.h))};
}

bool isMouse(const SDL_Event& e) noexcept;

constexpr int SCREEN_WIDTH  = 1920;
constexpr int SCREEN_HEIGHT = 1080;

constexpr SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};

constexpr float cusSize         = 160.f;
constexpr float counterHeight   = SCREEN_HEIGHT * 0.4f;
constexpr SDL_FRect counterRect = {0, counterHeight, SCREEN_WIDTH, 72.f};

constexpr float cusHeight           = counterHeight - cusSize + 10.f;
constexpr float cusBegin            = 40.f;
constexpr SDL_FRect cust1FRect      = {cusBegin, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust2FRect      = {cust1FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust3FRect      = {cust2FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust4FRect      = {cust3FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust1OrderFRect = {cust1FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust2OrderFRect = {cust2FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust3OrderFRect = {cust3FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust4OrderFRect = {cust4FRect.x, counterHeight, cusSize, cusSize};

constexpr float columnItemSize = 50.f + 50 * SCREEN_HEIGHT / 600.f;
constexpr float columnX        = SCREEN_WIDTH - columnItemSize - 20.f;
constexpr float columnFirstY   = SCREEN_HEIGHT - columnItemSize - 20.f;

constexpr int columnItemDis       = 10;
constexpr float columnSecondItemY = columnFirstY - columnItemSize - columnItemDis;
constexpr float columnThirdItemY  = columnFirstY - 2 * (columnItemSize + columnItemDis);
constexpr float columnFourthItemY = columnFirstY - 3 * (columnItemSize + columnItemDis);
constexpr float columnFifthItemY  = columnFirstY - 4 * (columnItemSize + columnItemDis);

constexpr SDL_FRect pkgFRect  = {columnX, columnFirstY, columnItemSize, columnItemSize};
constexpr SDL_FRect sinkFRect = {columnX, columnSecondItemY, columnItemSize, columnItemSize};
constexpr SDL_FRect binFRect  = {columnX, columnThirdItemY, columnItemSize, columnItemSize};

constexpr float leftBarBegin            = SCREEN_WIDTH > 800 ? 20.f : 0.f;
constexpr SDL_FRect potToolFRect        = {leftBarBegin, columnThirdItemY, columnItemSize, columnItemSize};
constexpr SDL_FRect chopsticksToolFRect = {leftBarBegin, columnSecondItemY, columnItemSize, columnItemSize};
constexpr SDL_FRect bowlsFRect          = {leftBarBegin, columnFirstY, columnItemSize, columnItemSize};

constexpr float cookerSize = 128.f + 10.f * SCREEN_HEIGHT / 600.f;
constexpr float cookerY = SCREEN_HEIGHT - cookerSize - (columnItemSize - columnItemDis) * (SCREEN_HEIGHT - 600) / 600.f;

constexpr SDL_FRect cookerFDst1 = {SCREEN_WIDTH * 0.5f - 2.f * cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst2 = {cookerFDst1.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst3 = {cookerFDst2.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst4 = {cookerFDst3.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr float potSizeCooking  = cookerSize;
constexpr float potYCooking     = cookerY - potSizeCooking * 0.4f;
constexpr SDL_FRect potFDst1    = {cookerFDst1.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst2    = {cookerFDst2.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst3    = {cookerFDst3.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst4    = {cookerFDst4.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};

constexpr SDL_FRect servingSlotFDst1 = {cust1FRect.x + cusSize * 0.3f, cust1FRect.y + cusSize * 0.7f, 80, 80};

constexpr SDL_FRect servingSlotFDst2 = {cust2FRect.x + cusSize * 0.3f, cust2FRect.y + cusSize * 0.7f, 80, 80};

constexpr SDL_FRect servingSlotFDst3 = {cust3FRect.x + cusSize * 0.3f, cust3FRect.y + cusSize * 0.7f, 80, 80};

constexpr SDL_FRect servingSlotFDst4 = {cust4FRect.x + cusSize * 0.3f, cust4FRect.y + cusSize * 0.7f, 80, 80};

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

constexpr SDL_FRect getOrderSlotFRect(ElementId id) {
    switch (id) {
    case ElementId::customer1:
        return cust1OrderFRect;
    case ElementId::customer2:
        return cust2OrderFRect;
    case ElementId::customer3:
        return cust3OrderFRect;
    case ElementId::customerRightMost:
        return cust4OrderFRect;
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