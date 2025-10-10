#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

class Renderer;

class Money final {
public:
    Money() noexcept;

    void show(const Renderer& rend) noexcept;

private:
    std::unique_ptr<TTF_Font, void (*)(TTF_Font*)> m_font;
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> m_surface;
    std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> m_texture;
    int64_t m_lastShown = 0u;
};
