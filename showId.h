#pragma once

enum class ShowId {
    bg = 0u,
    operating_area,
    blur,
    sink,
    classicRamen,
    beefRamen,
    seafoodRamen,
    spicyRamen,
    bowls,
    puff,
    chopsticks1,
    chopsticks2,
    empty_bowl,
    bowl_with_ramen_plain,
    bin,
    counter_surface,
    burner,
    empty_pot,
    pot_water_added,
    pot_water_boiling,
    pot_noodle_added,
    pot_noodle_cooking,
    pot_noodle_halfcooked,
    pot_noodle_cooked,
    pot_burnt,
    patiencebar,
    coins,
    star,
    orderPostIt,
    fridge,
    softdrink_kola,
    softdrink_funta,
    softdrink_peppy,
    softdrink_spryte,
    okayBtn,
    newsOpen,
    billPaper,
    customer0,
    customer1,
    customer2,
    customer3,
    customer4,
    customer5,
    customer6,
    customer7,
    customer8,
    customer9,
    customer10,
    customer11,
    customer12,
    customer13,
    customerMax,
    lastImg,
    moneyNumberText,
    ratingNumberText,
    cus1NextText,
    cus2NextText,
    cus3NextText,
    cus4NextText,
    last
};

constexpr ShowId toImgId(int idx) noexcept {
    auto diff = static_cast<int>(ShowId::customer0);
    return static_cast<ShowId>(idx + diff);
}

constexpr bool isCustomer(ShowId id) noexcept { return (id >= ShowId::customer0) && (id <= ShowId::customerMax); }
constexpr bool isSoftdrink(ShowId id) noexcept {
    return (id >= ShowId::softdrink_kola) && (id <= ShowId::softdrink_spryte);
}
constexpr bool isRamenBowl(ShowId id) noexcept { return (id == ShowId::bowl_with_ramen_plain); }