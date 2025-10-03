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
    customer1
};

constexpr bool is_customer(ElementId id) noexcept { return id == ElementId::customer1; }