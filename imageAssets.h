#pragma once

class ImageTexture;

enum class ImageId {
    bg = 0u,
    sink,
    sink_running_water,
    ramenPkg,
    bowls,
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
    customer,
    last
};

const ImageTexture& getImage(ImageId id);