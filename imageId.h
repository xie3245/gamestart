#pragma once

enum class ImageId {
    bg = 0u,
    sink,
    sink_running_water,
    ramenPkg,
    bowls,
    empty_bowl,
    bowl_with_ramen_plain,
    bin,
    bin_open,
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
    customer14,
    last
};

constexpr ImageId toImgId(int idx) noexcept {
    auto diff = static_cast<int>(ImageId::customer0);
    return static_cast<ImageId>(idx + diff);
}