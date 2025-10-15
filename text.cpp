#include "text.h"
#include <iostream>
#include "renderer.h"
#include "imageTexture.h"

struct TTFWrapper final {
    TTFWrapper() noexcept {
        if (!TTF_Init()) {
            std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        } else {
            font.reset(TTF_OpenFont("assets/fonts/TimeburnerBold-peGR.ttf", 24));
        }
    }
    ~TTFWrapper() noexcept { TTF_Quit(); }

    std::unique_ptr<TTF_Font, void (*)(TTF_Font*)> font{nullptr, TTF_CloseFont};
};

static TTFWrapper ttfWrapper{};

FontTexture::FontTexture() noexcept : m_surface(nullptr, SDL_DestroySurface), m_texture(nullptr, SDL_DestroyTexture) {}

void FontTexture::show(const Renderer& rend,
                       const std::string& text,
                       const SDL_Color& rgba,
                       float x,
                       float y) noexcept {
    if ((text == m_lastShown) && m_texture) {
        rend.renderTexture(m_texture.get(), {x, y, static_cast<float>(m_texture->w), static_cast<float>(m_texture->h)});
    } else {
        m_surface.reset(TTF_RenderText_Solid(ttfWrapper.font.get(), text.c_str(), text.size(), rgba));
        m_texture.reset(rend.loadTexture(m_surface.get()));
        rend.renderTexture(m_texture.get(), {x, y, static_cast<float>(m_texture->w), static_cast<float>(m_texture->h)});
    }
    m_lastShown = text;
}
