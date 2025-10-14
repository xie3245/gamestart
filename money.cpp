#include "money.h"
#include <iostream>
#include "renderer.h"
#include "imageTexture.h"

class TTFWrapper final {
public:
    TTFWrapper() noexcept {
        if (!TTF_Init()) {
            std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        }
    }
    ~TTFWrapper() noexcept { TTF_Quit(); }
};

static TTFWrapper ttfWrapper{};

constexpr float money_x = 55.f;
constexpr float money_y = 20.f;

Money::Money() noexcept
    : m_font(TTF_OpenFont("assets/fonts/TimeburnerBold-peGR.ttf", 24), TTF_CloseFont)
    , m_surface(nullptr, SDL_DestroySurface)
    , m_texture(nullptr, SDL_DestroyTexture) {}

void Money::show(const Renderer& rend) noexcept {
    getImage(ImageId::coins).show(rend, Sprite2x2::upperLeft, {10, 10, 40, 40});
    auto curr = getMoney();
    if ((curr == m_lastShown) && m_texture) {
        rend.renderTexture(m_texture.get(), {money_x, money_y, static_cast<float>(m_texture.get()->w),
                                             static_cast<float>(m_texture.get()->h)});
    } else {
        auto text = std::to_string(curr);
        m_surface.reset(TTF_RenderText_Solid(m_font.get(), text.c_str(), text.size(), {245, 131, 39, 255}));
        m_texture.reset(rend.loadTexture(m_surface.get()));
        rend.renderTexture(m_texture.get(), {money_x, money_y, static_cast<float>(m_texture.get()->w),
                                             static_cast<float>(m_texture.get()->h)});
    }
    m_lastShown = curr;
}

void showRating(const Renderer& rend) noexcept {
    getImage(ImageId::star).show(rend, {Sprite2x1::left, getRating()}, {400, 10, 40 * getRating(), 40});

    for (float x = 400.f; x < (400.f + 5 * 40.f); x += 40.f)
        getImage(ImageId::star).show(rend, Sprite2x1::right, {x, 10, 40, 40});
}