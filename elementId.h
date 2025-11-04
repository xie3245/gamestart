#pragma once
enum class ElementId {
    undefined,
    potSideBar,
    sinkSideBar,
    binSideBar,
    ramenSideBar,
    chopsticksSideBar,
    bowlsSideBar,
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
    servedItemCus1,
    servingSlot2,
    servingSlot3,
    servingSlot4,
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
    ordered_itemTxt1_cus1,
    ordered_itemTxt1_cus2,
    ordered_itemTxt1_cus3,
    ordered_itemTxt1_cus4,
    moneyCoin,
    moneyNumber,
    ratingOutline,
    ratingFilling,
    okayButton
};

constexpr bool isCustomer(ElementId id) noexcept {
    return (id >= ElementId::customer1) && (id <= ElementId::customerRightMost);
}

constexpr bool isText(ElementId id) noexcept {
    return (id == ElementId::moneyNumber) ||
           ((id <= ElementId::ordered_itemTxt1_cus4) && (id >= ElementId::ordered_itemTxt1_cus1));
}

inline constexpr ElementId puffId(ElementId cookingSlotId) noexcept {
    int diff = static_cast<int>(ElementId::cookingPuff1) - static_cast<int>(ElementId::cookingSlot1);
    return static_cast<ElementId>(static_cast<int>(cookingSlotId) + diff);
}

inline constexpr ElementId orderId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::order1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}
inline constexpr ElementId orderTextId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::ordered_itemTxt1_cus1) - static_cast<int>(ElementId::customer1);
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

inline constexpr ElementId servedItemId(ElementId cusId) noexcept {
    int diff = static_cast<int>(ElementId::servedItemCus1) - static_cast<int>(ElementId::customer1);
    return static_cast<ElementId>(static_cast<int>(cusId) + diff);
}