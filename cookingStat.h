#pragma once
#include "elementId.h"

class CookingStatus final {
public:
    constexpr bool isCooked(ElementId cookingSlot) const noexcept {
        switch (cookingSlot) {
        case ElementId::cookingSlot1:
            return cooked1;
        case ElementId::cookingSlot2:
            return cooked2;
        case ElementId::cookingSlot3:
            return cooked3;
        case ElementId::cookingSlot4:
            return cooked4;
        default:
            return false;
            break;
        }
    }

    constexpr void updateCooked(ElementId cookingSlot, bool cooked) noexcept {
        switch (cookingSlot) {
        case ElementId::cookingSlot1:
            cooked1 = cooked;
            break;
        case ElementId::cookingSlot2:
            cooked2 = cooked;
            break;
        case ElementId::cookingSlot3:
            cooked3 = cooked;
            break;
        case ElementId::cookingSlot4:
            cooked4 = cooked;
            break;
        default:
            break;
        }
    }

private:
    bool cooked1 = false;
    bool cooked2 = false;
    bool cooked3 = false;
    bool cooked4 = false;
};