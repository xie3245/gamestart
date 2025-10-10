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

void ImageTexture::show(const Renderer& renderer, const SrcRations& src, const SDL_FRect& rect) const {
    if (!m_texture) {
        m_texture = renderer.loadTexture(m_surface);
    }

    if (m_texture) {
        renderer.renderTexture(
            m_texture, {m_texture->w * src.r_x, m_texture->h * src.r_y, m_texture->w * src.r_w, m_texture->h * src.r_h},
            rect);
    }
}

static ImageTexture defaultTexture{"assets/undefined.png"};
static ImageTexture imageMap[] = {{"assets/bg2areasMoreOp.png"},
                                  {"assets/sink.png"},
                                  {"assets/sink_water_running.png"},
                                  {"assets/ramen_pkg.png"},
                                  {"assets/bowls.png"},
                                  {"assets/stir_puff.png"},
                                  {"assets/chopsticks1.png"},
                                  {"assets/chopsticks2.png"},
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
                                  {"assets/patiencebar.png"},
                                  {"assets/cus2.png"},
                                  {"assets/cus4.png"},
                                  {"assets/cus6.png"},
                                  {"assets/cus7.png"},
                                  {"assets/cus8.png"},
                                  {"assets/cus9.png"},
                                  {"assets/cus10.png"},
                                  {"assets/cus11.png"},
                                  {"assets/cus13.png"},
                                  {"assets/cus14.png"},
                                  {"assets/cus17.png"},
                                  {"assets/cus18.png"},
                                  {"assets/cus19.png"},
                                  {"assets/cus20.png"},
                                  {"assets/cus21.png"}};

const ImageTexture& getImage(ImageId id) {
    if (static_cast<size_t>(id) < static_cast<size_t>(ImageId::last)) {
        return imageMap[static_cast<size_t>(id)];
    }
    return defaultTexture;
}