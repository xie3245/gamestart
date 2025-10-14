#include "imageTexture.h"
#include "utils.h"

ImageTexture::ImageTexture(const char* path_to_img) noexcept
    : m_surface(IMG_Load(path_to_img), SDL_DestroySurface)
    , m_texture(nullptr) {}

ImageTexture::~ImageTexture() noexcept { SDL_DestroyTexture(m_texture); }

void ImageTexture::show(const Renderer& renderer, const SDL_FRect& rect, float ratio, double angle) const {
    if (!m_texture) {
        m_texture = renderer.loadTexture(m_surface.get());
    }

    if (m_texture) {
        renderer.renderTexture(m_texture, rect, ratio, angle);
    }
}

void ImageTexture::show(const Renderer& renderer, const SrcRations& src, const SDL_FRect& rect) const {
    if (!m_texture) {
        m_texture = renderer.loadTexture(m_surface.get());
    }

    if (m_texture) {
        renderer.renderTexture(
            m_texture, {m_texture->w * src.r_x, m_texture->h * src.r_y, m_texture->w * src.r_w, m_texture->h * src.r_h},
            rect);
    }
}

static constexpr auto bgPath = SCREEN_WIDTH == 800 ? "assets/bg800.png" : "assets/bg1920.png";
static const ImageTexture defaultTexture{"assets/undefined.png"};
static const ImageTexture imageMap[] = {ImageTexture{bgPath},
                                        ImageTexture{"assets/sink.png"},
                                        ImageTexture{"assets/sink_water_running.png"},
                                        ImageTexture{"assets/ramen_pkg.png"},
                                        ImageTexture{"assets/bowls.png"},
                                        ImageTexture{"assets/stir_puff.png"},
                                        ImageTexture{"assets/chopsticks1.png"},
                                        ImageTexture{"assets/chopsticks2.png"},
                                        ImageTexture{"assets/empty_bowl.png"},
                                        ImageTexture{"assets/bowl_with_ramen_cooked3.png"},
                                        ImageTexture{"assets/trash_bin_closed.png"},
                                        ImageTexture{"assets/trash_bin_open.png"},
                                        ImageTexture{"assets/counter_surface_lean.png"},
                                        ImageTexture{"assets/cooker2.png"},
                                        ImageTexture{"assets/pot_empty.png"},
                                        ImageTexture{"assets/pot_with_water.png"},
                                        ImageTexture{"assets/pot_with_boiling_water.png"},
                                        ImageTexture{"assets/pot_with_ramen_uncooked.png"},
                                        ImageTexture{"assets/pot_with_ramen_halfcooked.png"},
                                        ImageTexture{"assets/pot_with_ramen_halfcooked1.png"},
                                        ImageTexture{"assets/pot_with_ramen_cooked.png"},
                                        ImageTexture{"assets/pot_with_ramen_burnt.png"},
                                        ImageTexture{"assets/patiencebar.png"},
                                        ImageTexture{"assets/coins2.png"},
                                        ImageTexture{"assets/stars.png"},
                                        ImageTexture{"assets/postit.png"},
                                        ImageTexture{"assets/cus2.png"},
                                        ImageTexture{"assets/cus4.png"},
                                        ImageTexture{"assets/cus6.png"},
                                        ImageTexture{"assets/cus7.png"},
                                        ImageTexture{"assets/cus8.png"},
                                        ImageTexture{"assets/cus9.png"},
                                        ImageTexture{"assets/cus10.png"},
                                        ImageTexture{"assets/cus11.png"},
                                        ImageTexture{"assets/cus13.png"},
                                        ImageTexture{"assets/cus14.png"},
                                        ImageTexture{"assets/cus17.png"},
                                        ImageTexture{"assets/cus18.png"},
                                        ImageTexture{"assets/cus19.png"},
                                        ImageTexture{"assets/cus20.png"},
                                        ImageTexture{"assets/cus21.png"}};

const ImageTexture& getImage(ImageId id) {
    if (static_cast<size_t>(id) < static_cast<size_t>(ImageId::last)) {
        return imageMap[static_cast<size_t>(id)];
    }
    return defaultTexture;
}