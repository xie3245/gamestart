#include "imageAssets.h"
#include "imageTexture.h"

static const ImageTexture defaultTexture{"assets/undefined.png"};
static const ImageTexture imageMap[] = {{"assets/bg2areasMoreOp.png"},
                                        {"assets/sink.png"},
                                        {"assets/sink_water_running.png"},
                                        {"assets/ramen_pkg.png"},
                                        {"assets/bowls.png"},
                                        {"assets/trash_bin_closed.png"},
                                        {"assets/trash_bin_open.png"},
                                        {"assets/counter_surface_lean.png"},
                                        {"assets/burner.png"},
                                        {"assets/pot_empty.png"},
                                        {"assets/pot_with_water.png"},
                                        {"assets/pot_with_boiling_water.png"},
                                        {"assets/pot_with_ramen_uncooked.png"},
                                        {"assets/pot_with_ramen_halfcooked.png"},
                                        {"assets/pot_with_ramen_halfcooked1.png"},
                                        {"assets/pot_with_ramen_cooked.png"},
                                        {"assets/pot_with_ramen_burnt.png"},
                                        {"assets/customer_fox.png"}};

const ImageTexture& getImage(ImageId id) {
    if (static_cast<size_t>(id) < static_cast<size_t>(ImageId::last)) {
        return imageMap[static_cast<size_t>(id)];
    }
    return defaultTexture;
}