#pragma once
enum class ElementId {
    undefined,
    potSideBar,
    sinkSideBar,
    binSideBar,
    classicRamenSideBar,
    beefRamenSideBar,
    spicyRamenSideBar,
    seafoodRamenSideBar,
    chopsticksSideBar,
    bowlsSideBar,
    fridge,
    softdrink1,
    softdrink2,
    softdrink3,
    softdrink4,
    bowlsItem,
    potItem,
    ramenItem,
    cookingSlot1,
    cookingSlot2,
    cookingSlot3,
    cookingSlot4,
    cookingPuff1,
    cookingPuff2,
    cookingPuff3,
    cookingPuff4,
    customer1,
    customer2,
    customer3,
    customerRightMost,
    servedRamenCus1,
    servedRamenCus2,
    servedRamenCus3,
    servedRamenCus4,
    servedDrinkCus1,
    servedDrinkCus2,
    servedDrinkCus3,
    servedDrinkCus4,
    order1,
    order2,
    order3,
    order4,
    patienceBarOutline1,
    patienceBarOutline2,
    patienceBarOutline3,
    patienceBarOutline4,
    patienceBarFilling1,
    patienceBarFilling2,
    patienceBarFilling3,
    patienceBarFilling4,
    ordered_ramen_cus1,
    ordered_ramen_cus2,
    ordered_ramen_cus3,
    ordered_ramen_cus4,
    ordered_drink_cus1,
    ordered_drink_cus2,
    ordered_drink_cus3,
    ordered_drink_cus4,
    moneyCoin,
    moneyNumber,
    ratingOutline,
    ratingFilling,
    okayButton
};

constexpr bool isCustomer(ElementId id) noexcept {
    return (id >= ElementId::customer1) && (id <= ElementId::customerRightMost);
}

constexpr bool isText(ElementId id) noexcept { return (id == ElementId::moneyNumber); }

inline constexpr ElementId puffId(ElementId cookingSlotId) noexcept {
    int diff = static_cast<int>(ElementId::cookingPuff1) - static_cast<int>(ElementId::cookingSlot1);
    return static_cast<ElementId>(static_cast<int>(cookingSlotId) + diff);
}

inline constexpr ElementId orderId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::order1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}
inline constexpr ElementId orderRamenId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::ordered_ramen_cus1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}
inline constexpr ElementId orderSoftdrinkId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::ordered_drink_cus1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}

inline constexpr ElementId pbOut(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::patienceBarOutline1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}

inline constexpr ElementId pbFill(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::patienceBarFilling1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}

inline constexpr ElementId servedRamenId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::servedRamenCus1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}

inline constexpr ElementId servedDrinkId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::servedDrinkCus1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}

inline constexpr isSoftdrinkOption(ElementId id) noexcept {
    return (id >= ElementId::softdrink1) && (id <= ElementId::softdrink4);
}