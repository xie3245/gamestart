#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>

class Renderer;

class FontTexture final {
public:
    FontTexture() noexcept;

    void show(const Renderer& rend, const std::string& text, const SDL_Color& rgba, float x, float y) noexcept;

    inline int width() const noexcept { return m_texture->w; }
    inline int height() const noexcept { return m_texture->h; }

private:
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> m_surface;
    std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> m_texture;
    std::string m_lastShown;
};