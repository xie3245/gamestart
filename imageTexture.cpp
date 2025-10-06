#include "imageTexture.h"
#include "utils.h"

ImageTexture::ImageTexture(const char* path_to_img) : m_surface(IMG_Load(path_to_img)), m_texture(nullptr) {}

ImageTexture::~ImageTexture() {
    SDL_DestroyTexture(m_texture);
    SDL_DestroySurface(m_surface);
}

void ImageTexture::show(const Renderer& renderer, const SDL_FRect& rect, float ratio, double angle) const {
    if (!m_texture) {
        m_texture = renderer.loadTexture(m_surface);
    }

    if (m_texture) {
        renderer.renderTexture(m_texture, rect, ratio, angle);
    }
}

static ImageTexture defaultTexture{"assets/undefined.png"};
static ImageTexture imageMap[] = {{"assets/bg2areasMoreOp.png"},
                                  {"assets/sink.png"},
                                  {"assets/sink_water_running.png"},
                                  {"assets/ramen_pkg.png"},
                                  {"assets/bowls.png"},
                                  {"assets/empty_bowl.png"},
                                  {"assets/bowl_with_ramen_cooked3.png"},
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
                                  {"assets/cus_hippo1.png"},
                                  {"assets/cus_hippo4.png"},
                                  {"assets/cus_hippo5.png"},
                                  {"assets/cus_hippo7.png"}};

const ImageTexture& getImage(ImageId id) {
    if (static_cast<size_t>(id) < static_cast<size_t>(ImageId::last)) {
        return imageMap[static_cast<size_t>(id)];
    }
    return defaultTexture;
}