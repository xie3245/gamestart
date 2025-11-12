#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include "elementId.h"

bool isClick(const SDL_Event& e) noexcept;

bool isMouse(const SDL_Event& e) noexcept;

constexpr int SCREEN_WIDTH        = 1920;
constexpr int SCREEN_HEIGHT       = 1080;
constexpr int HALF_WIDTH          = SCREEN_WIDTH / 2;
constexpr int HALF_HEIGHT         = SCREEN_HEIGHT / 2;
constexpr float counterHeight     = SCREEN_HEIGHT * 0.4f;
constexpr float cookingToolSize   = 60.f * SCREEN_HEIGHT / 600.f;
constexpr float appliancesSize    = 50.f + 50.f * SCREEN_HEIGHT / 600.f;
constexpr float columnX           = SCREEN_WIDTH - appliancesSize - 20.f;
constexpr float columnFirstY      = SCREEN_HEIGHT - appliancesSize - 20.f;
constexpr int itemDis             = 10;
constexpr float cookerSize        = 128.f + 10.f * SCREEN_HEIGHT / 600.f;
constexpr float burnerSize        = 300.f;
constexpr float cookerY           = counterHeight + (SCREEN_HEIGHT - counterHeight) * 0.5f;
constexpr float burnerY           = counterHeight + appliancesSize + 3.f * itemDis;
constexpr float potSizeCooking    = cookerSize;
constexpr float potYCooking       = cookerY - potSizeCooking * 0.4f;
constexpr float cusSize           = 160.f;
constexpr float cusDis            = 40.f;
constexpr float postItSize        = 1.4f * cusSize;
constexpr float orderRamenSize    = 60.f;
constexpr float orderItemSize     = 50.f;
constexpr float orderRamenIndentX = postItSize * 0.5f - orderRamenSize * 0.5f;
constexpr float orderRamenIndentY = 60.f;
constexpr float orderLine2IndentX = postItSize * 0.2f;
constexpr float cusHeight         = counterHeight - cusSize + 10.f;
constexpr float cusBegin          = 40.f;
constexpr float patienceBarLength = cusSize * 0.5f;
namespace color {
constexpr SDL_Color black{0, 0, 0, 255};
constexpr SDL_Color gold{245, 131, 39, 255};
}  // namespace color

constexpr SDL_FRect bgDst           = {0.f, 0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
constexpr SDL_FRect fridgeDst       = {SCREEN_WIDTH * 0.7f, SCREEN_HEIGHT * 0.1f, 300.f, 400.f};
constexpr float drinksy             = fridgeDst.y - 20.f;
constexpr float drinksw             = fridgeDst.w * 0.2f;
constexpr float drinksh             = fridgeDst.w * 0.4f;
constexpr SDL_FRect softdrink1FDst  = {fridgeDst.x - drinksw * 4.1f, drinksy, drinksw, drinksh};
constexpr SDL_FRect softdrink2FDst  = {softdrink1FDst.x + softdrink1FDst.w, drinksy, drinksw, drinksh};
constexpr SDL_FRect softdrink3FDst  = {softdrink2FDst.x + softdrink2FDst.w, drinksy, drinksw, drinksh};
constexpr SDL_FRect softdrink4FDst  = {softdrink3FDst.x + softdrink3FDst.w, drinksy, drinksw, drinksh};
constexpr SDL_FRect opArea          = {0.f, counterHeight + 20.f, SCREEN_WIDTH, SCREEN_WIDTH - counterHeight - 20.f};
constexpr SDL_FRect counterRect     = {0.f, counterHeight, SCREEN_WIDTH, 72.f};
constexpr SDL_FRect moneyFRect      = {10.f, 10.f, 40.f, 40.f};
constexpr SDL_FRect cust1FRect      = {cusBegin, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust2FRect      = {cust1FRect.x + cusSize + cusDis, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust3FRect      = {cust2FRect.x + cusSize + cusDis, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust4FRect      = {cust3FRect.x + cusSize + cusDis, cusHeight, cusSize, cusSize};
constexpr SDL_FRect cust1OrderFRect = {cust1FRect.x - 0.2f * cusSize, counterHeight, postItSize, postItSize};
constexpr SDL_FRect cust2OrderFRect = {cust2FRect.x - 0.2f * cusSize, counterHeight, postItSize, postItSize};
constexpr SDL_FRect cust3OrderFRect = {cust3FRect.x - 0.2f * cusSize, counterHeight, postItSize, postItSize};
constexpr SDL_FRect cust4OrderFRect = {cust4FRect.x - 0.2f * cusSize, counterHeight, postItSize, postItSize};
constexpr SDL_FRect cust1PatienceBarFRect = {cust1FRect.x + 10.f, cust1FRect.y, 10.f, patienceBarLength};
constexpr SDL_FRect cust2PatienceBarFRect = {cust2FRect.x + 10.f, cust2FRect.y, 10.f, patienceBarLength};
constexpr SDL_FRect cust3PatienceBarFRect = {cust3FRect.x + 10.f, cust3FRect.y, 10.f, patienceBarLength};
constexpr SDL_FRect cust4PatienceBarFRect = {cust4FRect.x + 10.f, cust4FRect.y, 10.f, patienceBarLength};

constexpr SDL_FRect burnerFDst = {HALF_WIDTH - burnerSize, burnerY, burnerSize, burnerSize};

constexpr SDL_FRect cookerFDst1 = {HALF_WIDTH - 2.f * cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst2 = {cookerFDst1.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst3 = {cookerFDst2.x + cookerSize, cookerY, cookerSize, cookerSize};
constexpr SDL_FRect cookerFDst4 = {cookerFDst3.x + cookerSize, cookerY, cookerSize, cookerSize};

constexpr float ratingBarLength = 200.f;
constexpr float ratingBarWidth  = 40.f;
constexpr float ratingBarX      = 400.f;
constexpr float ratingBarY      = 10.f;
constexpr SDL_FRect sinkFRect   = {HALF_WIDTH, counterHeight + counterRect.h, appliancesSize, appliancesSize};
constexpr SDL_FRect binFRect    = {HALF_WIDTH + itemDis + appliancesSize, counterHeight + counterRect.h, appliancesSize,
                                   appliancesSize};

constexpr float cookingToolX            = HALF_WIDTH * 0.5f;
constexpr float cookingToolY            = cookerY + cookerSize + itemDis;
constexpr SDL_FRect potToolFRect        = {cookingToolX, cookingToolY, cookingToolSize, cookingToolSize};
constexpr SDL_FRect chopsticksToolFRect = {potToolFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                           cookingToolSize};
constexpr SDL_FRect bowlsFRect = {chopsticksToolFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                  cookingToolSize};
constexpr SDL_FRect classicRamenFRect = {bowlsFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                         cookingToolSize};
constexpr SDL_FRect beefRamenFRect    = {classicRamenFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                         cookingToolSize};
constexpr SDL_FRect seafoodRamenFRect = {beefRamenFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                         cookingToolSize};
constexpr SDL_FRect spicyRamenFRect   = {seafoodRamenFRect.x + cookingToolSize + itemDis, cookingToolY, cookingToolSize,
                                         cookingToolSize};
constexpr SDL_FRect potFDst1          = {burnerFDst.x + burnerFDst.w * 0.13f, burnerFDst.y - 20.f, potSizeCooking,
                                         potSizeCooking};
constexpr SDL_FRect potFDst2          = {potFDst1.x + burnerFDst.w * 0.35f, potFDst1.y, potSizeCooking, potSizeCooking};
constexpr SDL_FRect potFDst3 = {potFDst1.x - burnerFDst.w * 0.07f, potFDst1.y + potFDst1.h * 0.5f, potSizeCooking,
                                potSizeCooking};
constexpr SDL_FRect potFDst4 = {potFDst3.x + burnerFDst.w * 0.36f, potFDst3.y, potSizeCooking, potSizeCooking};

constexpr float puffSize             = 80.f;
constexpr float potZoomDiff          = 0.1f;
constexpr SDL_FRect puffFDst1        = {potFDst1.x, potFDst1.y - 30.f, puffSize, puffSize};
constexpr SDL_FRect puffFDst2        = {potFDst2.x, potFDst2.y - 30.f, puffSize, puffSize};
constexpr SDL_FRect puffFDst3        = {potFDst3.x, potFDst3.y - 30.f, puffSize, puffSize};
constexpr SDL_FRect puffFDst4        = {potFDst4.x, potFDst4.y - 30.f, puffSize, puffSize};
constexpr SDL_FRect puffZoomedFDst1  = {potFDst1.x - potZoomDiff * 0.05f * potSizeCooking,
                                        potFDst1.y - 30.f - potZoomDiff * 0.05f * potSizeCooking, puffSize, puffSize};
constexpr SDL_FRect puffZoomedFDst2  = {potFDst2.x - potZoomDiff * 0.05f * potSizeCooking,
                                        potFDst2.y - 30.f - potZoomDiff * 0.05f * potSizeCooking, puffSize, puffSize};
constexpr SDL_FRect puffZoomedFDst3  = {potFDst3.x - potZoomDiff * 0.05f * potSizeCooking,
                                        potFDst3.y - 30.f - potZoomDiff * 0.05f * potSizeCooking, puffSize, puffSize};
constexpr SDL_FRect puffZoomedFDst4  = {potFDst4.x - potZoomDiff * 0.05f * potSizeCooking,
                                        potFDst4.y - 30.f - potZoomDiff * 0.05f * potSizeCooking, puffSize, puffSize};
constexpr float servedRamenSize      = 80.f;
constexpr float servedDrinkSize      = 80.f;
constexpr SDL_FRect servedRamenFDst1 = {cust1FRect.x + cusSize * 0.3f, cust1FRect.y + cusSize * 0.7f, servedRamenSize,
                                        servedRamenSize};
constexpr SDL_FRect servedRamenFDst2 = {cust2FRect.x + cusSize * 0.3f, cust2FRect.y + cusSize * 0.7f, servedRamenSize,
                                        servedRamenSize};
constexpr SDL_FRect servedRamenFDst3 = {cust3FRect.x + cusSize * 0.3f, cust3FRect.y + cusSize * 0.7f, servedRamenSize,
                                        servedRamenSize};
constexpr SDL_FRect servedRamenFDst4 = {cust4FRect.x + cusSize * 0.3f, cust4FRect.y + cusSize * 0.7f, servedRamenSize,
                                        servedRamenSize};
constexpr SDL_FRect servedDrinkFDst1 = {servedRamenFDst1.x + 0.7f * servedRamenFDst1.w, cust1FRect.y + cusSize * 0.7f,
                                        servedDrinkSize, servedDrinkSize};
constexpr SDL_FRect servedDrinkFDst2 = {servedRamenFDst2.x + 0.7f * servedRamenFDst2.w, cust2FRect.y + cusSize * 0.7f,
                                        servedDrinkSize, servedDrinkSize};
constexpr SDL_FRect servedDrinkFDst3 = {servedRamenFDst3.x + 0.7f * servedRamenFDst3.w, cust3FRect.y + cusSize * 0.7f,
                                        servedDrinkSize, servedDrinkSize};
constexpr SDL_FRect servedDrinkFDst4 = {servedRamenFDst4.x + 0.7f * servedRamenFDst4.w, cust4FRect.y + cusSize * 0.7f,
                                        servedDrinkSize, servedDrinkSize};

constexpr float money_x = 55.f;
constexpr float money_y = 20.f;

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

constexpr SDL_FRect getRamenServingSlotFRect(ElementId id) {
    switch (id) {
    case ElementId::customer1:
        return servedRamenFDst1;
    case ElementId::customer2:
        return servedRamenFDst2;
    case ElementId::customer3:
        return servedRamenFDst3;
    case ElementId::customerRightMost:
        return servedRamenFDst4;
    default:
        return {0, 0, 0, 0};
    }
}

constexpr SDL_FRect getPatienceBarFRect(ElementId id) {
    switch (id) {
    case ElementId::customer1:
        return cust1PatienceBarFRect;
    case ElementId::customer2:
        return cust2PatienceBarFRect;
    case ElementId::customer3:
        return cust3PatienceBarFRect;
    case ElementId::customerRightMost:
        return cust4PatienceBarFRect;
    default:
        return {0, 0, 0, 0};
    }
}

constexpr SDL_FRect getPuffFRect(ElementId id, bool zooming) noexcept {
    switch (id) {
    case ElementId::cookingSlot1:
        return zooming ? puffZoomedFDst1 : puffFDst1;
    case ElementId::cookingSlot2:
        return zooming ? puffZoomedFDst2 : puffFDst2;
    case ElementId::cookingSlot3:
        return zooming ? puffZoomedFDst3 : puffFDst3;
    case ElementId::cookingSlot4:
        return zooming ? puffZoomedFDst4 : puffFDst4;
    default:
        return {0, 0, 0, 0};
    }
}

/* inline constexpr SDL_FRect to_frect(const SDL_Rect& r) noexcept {
    return SDL_FRect{static_cast<float>(r.x), static_cast<float>(r.y), static_cast<float>(r.w),
                     static_cast<float>(r.h)};
}

inline constexpr SDL_Rect frect_round(const SDL_FRect& r) noexcept {
    auto lr = [](float v) { return static_cast<int>(std::lround(v)); };
    return SDL_Rect{lr(r.x), lr(r.y), std::max(0, lr(r.w)), std::max(0, lr(r.h))};
} */