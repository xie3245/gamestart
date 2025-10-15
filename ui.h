#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include "elementId.h"

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

constexpr int SCREEN_WIDTH       = 1920;
constexpr int SCREEN_HEIGHT      = 1080;
constexpr int HALF_WIDTH         = SCREEN_WIDTH / 2;
constexpr int HALF_HEIGHT        = SCREEN_HEIGHT / 2;
constexpr float counterHeight    = SCREEN_HEIGHT * 0.4f;
constexpr float cookingToolSize  = 50.f * SCREEN_HEIGHT / 600.f;
constexpr float appliancesSize   = 50.f + 50.f * SCREEN_HEIGHT / 600.f;
constexpr float columnX          = SCREEN_WIDTH - appliancesSize - 20.f;
constexpr float columnFirstY     = SCREEN_HEIGHT - appliancesSize - 20.f;
constexpr int itemDis            = 10;
constexpr float cookerSize       = 128.f + 10.f * SCREEN_HEIGHT / 600.f;
constexpr float cookerY          = counterHeight + (SCREEN_HEIGHT - counterHeight) * 0.5f;
constexpr float potSizeCooking   = cookerSize;
constexpr float potYCooking      = cookerY - potSizeCooking * 0.4f;
constexpr float orderTextIndentX = 40.f;
constexpr float orderTextIndentY = 50.f;
constexpr float cusSize          = 160.f;
constexpr float cusHeight        = counterHeight - cusSize + 10.f;
constexpr float cusBegin         = 40.f;
constexpr float leftBarBegin     = SCREEN_WIDTH > 800 ? 20.f : 0.f;
namespace color {
constexpr SDL_Color black{0, 0, 0, 255};
constexpr SDL_Color gold{245, 131, 39, 255};
}  // namespace color

constexpr SDL_FRect bgDst           = {0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
constexpr SDL_FRect counterRect     = {0.f, counterHeight, SCREEN_WIDTH, 72.f};
constexpr SDL_FRect moneyFRect      = {10.f, 10.f, 40.f, 40.f};
constexpr SDL_FRect cust1FRect      = {cusBegin, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust2FRect      = {cust1FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust3FRect      = {cust2FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust4FRect      = {cust3FRect.x + cusSize, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust1OrderFRect = {cust1FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust2OrderFRect = {cust2FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust3OrderFRect = {cust3FRect.x, counterHeight, cusSize, cusSize};
constexpr SDL_FRect cust4OrderFRect = {cust4FRect.x, counterHeight, cusSize, cusSize};

constexpr SDL_FRect cookerFDst1 = {HALF_WIDTH - 2.f * cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst2 = {cookerFDst1.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst3 = {cookerFDst2.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst4 = {cookerFDst3.x + cookerSize, cookerY, cookerSize, cookerSize};

constexpr float columnSecondItemY = columnFirstY - appliancesSize - itemDis;
constexpr float columnThirdItemY  = columnFirstY - 2.f * (appliancesSize + itemDis);
constexpr float columnFourthItemY = columnFirstY - 3.f * (appliancesSize + itemDis);
constexpr float columnFifthItemY  = columnFirstY - 4.f * (appliancesSize + itemDis);
;

constexpr SDL_FRect sinkFRect = {HALF_WIDTH, counterHeight + counterRect.h, appliancesSize, appliancesSize};
constexpr SDL_FRect binFRect  = {HALF_WIDTH + itemDis + appliancesSize, counterHeight + counterRect.h, appliancesSize,
                                 appliancesSize};

constexpr float cookingToolX            = HALF_WIDTH * 0.5f;
constexpr float cookingToolY            = cookerY + cookerSize + itemDis;
constexpr SDL_FRect pkgFRect            = {cookingToolX, cookingToolY, cookingToolSize, cookingToolSize};
constexpr SDL_FRect potToolFRect        = {pkgFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                           cookingToolSize};
constexpr SDL_FRect chopsticksToolFRect = {potToolFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                           cookingToolSize};
constexpr SDL_FRect bowlsFRect = {chopsticksToolFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                  cookingToolSize};

constexpr SDL_FRect potFDst1 = {cookerFDst1.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst2 = {cookerFDst2.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst3 = {cookerFDst3.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst4 = {cookerFDst4.x + 10.f, potYCooking, potSizeCooking, potSizeCooking};

constexpr SDL_FRect servingSlotFDst1 = {cust1FRect.x + cusSize * 0.3f, cust1FRect.y + cusSize * 0.7f, 80.f, 80.f};

constexpr SDL_FRect servingSlotFDst2 = {cust2FRect.x + cusSize * 0.3f, cust2FRect.y + cusSize * 0.7f, 80.f, 80.f};

constexpr SDL_FRect servingSlotFDst3 = {cust3FRect.x + cusSize * 0.3f, cust3FRect.y + cusSize * 0.7f, 80.f, 80.f};

constexpr SDL_FRect servingSlotFDst4 = {cust4FRect.x + cusSize * 0.3f, cust4FRect.y + cusSize * 0.7f, 80.f, 80.f};

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