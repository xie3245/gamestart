#include "res.h"
#include "ui.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

struct FontTexture final {
    explicit FontTexture(const SDL_Color& cl) noexcept : rgba(cl) {}
    FontTexture() noexcept = default;

    std::string txt;
    SDL_Color rgba = color::black;
    Image img;
};

static const Image defaultImage{"assets/undefined.png"};

struct TTFWrapper final {
    TTFWrapper() noexcept {
        if (!TTF_Init()) {
            std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        } else {
            font.reset(TTF_OpenFont("assets/fonts/TimeburnerBold-peGR.ttf", 24));
        }
    }
    ~TTFWrapper() noexcept { TTF_Quit(); }

    const Image& get(size_t id, const std::string& txt) noexcept {
        if (id >= std::size(txts)) {
            return defaultImage;
        }

        FontTexture& tex = txts[static_cast<size_t>(id)];
        if (txt != tex.txt) {
            tex.img.surface.reset(TTF_RenderText_Solid(font.get(), txt.c_str(), txt.size(), tex.rgba));
            tex.img.texture = nullptr;
            tex.txt         = txt;
        }
        return tex.img;
    }

    std::unique_ptr<TTF_Font, void (*)(TTF_Font*)> font{nullptr, TTF_CloseFont};
    FontTexture txts[static_cast<size_t>(ShowId::last)]{FontTexture{color::gold}, FontTexture{}};
};

static TTFWrapper ttfWrapper{};

static constexpr auto bgPath = SCREEN_WIDTH == 800 ? "assets/bg800.png" : "assets/bg1920.png";
static constexpr auto opPath =
    (SCREEN_WIDTH == 800) ? "assets/bg800_operating_area.png" : "assets/bg1920_operating_area.png";
static const Image images[] = {Image{bgPath},
                               Image{opPath},
                               Image{"assets/baby_powder_white_overlay_1960x1080.png"},
                               Image{"assets/sink.png"},
                               Image{"assets/sink_water_running.png"},
                               Image{"assets/ramen_pkg.png"},
                               Image{"assets/bowls.png"},
                               Image{"assets/stir_puff.png"},
                               Image{"assets/chopsticks1.png"},
                               Image{"assets/chopsticks2.png"},
                               Image{"assets/empty_bowl.png"},
                               Image{"assets/bowl_with_ramen_cooked3.png"},
                               Image{"assets/trash_bin_closed.png"},
                               Image{"assets/trash_bin_open.png"},
                               Image{"assets/counter_surface_lean.png"},
                               Image{"assets/cooker2.png"},
                               Image{"assets/pot_empty.png"},
                               Image{"assets/pot_with_water.png"},
                               Image{"assets/pot_with_boiling_water.png"},
                               Image{"assets/pot_with_ramen_uncooked.png"},
                               Image{"assets/pot_with_ramen_halfcooked.png"},
                               Image{"assets/pot_with_ramen_halfcooked1.png"},
                               Image{"assets/pot_with_ramen_cooked.png"},
                               Image{"assets/pot_with_ramen_burnt.png"},
                               Image{"assets/patiencebar.png"},
                               Image{"assets/coins2.png"},
                               Image{"assets/stars.png"},
                               Image{"assets/postit.png"},
                               Image{"assets/fridge.png"},
                               Image{"assets/btn_start.png"},
                               Image{"assets/newspaper_openning2.png"},
                               Image{"assets/ramen_game_bill_paper.png"},
                               Image{"assets/cus2.png"},
                               Image{"assets/cus4.png"},
                               Image{"assets/cus6.png"},
                               Image{"assets/cus7.png"},
                               Image{"assets/cus8.png"},
                               Image{"assets/cus9.png"},
                               Image{"assets/cus10.png"},
                               Image{"assets/cus11.png"},
                               Image{"assets/cus13.png"},
                               Image{"assets/cus14.png"},
                               Image{"assets/cus17.png"},
                               Image{"assets/cus18.png"},
                               Image{"assets/cus19.png"},
                               Image{"assets/cus20.png"},
                               Image{"assets/cus21.png"}};

static_assert(static_cast<size_t>(ShowId::lastImg) == std::size(images));

const Image& Image::getImage(ShowId id) noexcept {
    if (static_cast<size_t>(id) >= static_cast<size_t>(ShowId::lastImg)) {
        return defaultImage;
    }

    return images[static_cast<size_t>(id)];
}

const Image& Image::getImage(ShowId id, const std::string& txt) noexcept {
    size_t txtId = static_cast<size_t>(id) - static_cast<size_t>(ShowId::lastImg) - 1u;
    return ttfWrapper.get(txtId, txt);
}