#include <iostream>
#include "renderer.h"
#include "res.h"
#include <string>

void Renderer::show(ShowId id,
                    const SrcRatio& src,
                    const SDL_FRect& dsRrect,
                    float ratio,
                    double angle) const noexcept {
    const Image& img = Image::getImage(id);
    prepareImage(img);
    if (img.texture) {
        renderTexture(
            img.texture.get(),
            {img.texture->w * src.r_x, img.texture->h * src.r_y, img.texture->w * src.r_w, img.texture->h * src.r_h},
            dsRrect, ratio, angle);
    }
}

void Renderer::show(ShowId id, const SDL_FRect& dsRrect) const noexcept {
    const Image& img = Image::getImage(id);
    prepareImage(img);
    if (img.texture) {
        renderTexture(img.texture.get(), dsRrect);
    }
}

void Renderer::show(ShowId id, const std::string& text, float x, float y, bool strikethrough) const noexcept {
    const Image& img = Image::getImage(id, text);
    prepareImage(img);
    if (img.texture) {
        renderTexture(img.texture.get(),
                      {x, y, static_cast<float>(img.texture->w), static_cast<float>(img.texture->h)});
    }

    if (strikethrough) {
        renderLine(x, y + img.texture->h * 0.5f, x + img.texture->w, y + img.texture->h * 0.5f);
    }
}

Renderer::Renderer()
    : m_window(SDL_CreateWindow("Ramen Shop", SCREEN_WIDTH, SCREEN_HEIGHT, 0))
    , m_renderer(SDL_CreateRenderer(m_window, nullptr)) {
    if (!m_window || !m_renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    SDL_SetRenderVSync(m_renderer, 1);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

SDL_Texture* Renderer::loadTexture(SDL_Surface* surf) const noexcept {
    auto tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    if (!tex) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        return nullptr;
    }
    return tex;
}

void Renderer::prepareImage(const Image& img) const noexcept {
    if (!img.surface) {
        return;
    }
    if (!img.texture) {
        img.texture.reset(loadTexture(img.surface.get()));
    }
}

void Renderer::renderLine(float x1, float y1, float x2, float y2) const noexcept {
    if (!SDL_RenderLine(m_renderer, x1, y1, x2, y2)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void Renderer::captureFrame() const noexcept {
    SDL_Surface* surface = SDL_RenderReadPixels(m_renderer, nullptr);
    char filename[64];
    std::sprintf(filename, "captures/frame%04d.bmp", frameCnt);
    SDL_SaveBMP(surface, filename);

    SDL_DestroySurface(surface);
}

static SDL_FRect enlarge(const SDL_FRect& orig, float ratio) noexcept {
    return {orig.x - orig.w * (ratio - 1.f) * 0.5f, orig.y - orig.h * (ratio - 1.f) * 0.5f, orig.w * ratio,
            orig.h * ratio};
}

void Renderer::renderTexture(SDL_Texture* tex,
                             const SDL_FRect& srcRect,
                             const SDL_FRect& dstRect,
                             float ratio,
                             double angle) const noexcept {
    auto rec = enlarge(dstRect, ratio);
    if (!SDL_RenderTextureRotated(m_renderer, tex, &srcRect, &rec, angle, nullptr, SDL_FLIP_NONE)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void Renderer::renderTexture(SDL_Texture* tex, const SDL_FRect& dstRect) const noexcept {
    if (!SDL_RenderTexture(m_renderer, tex, nullptr, &dstRect)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void Renderer::fillRect(const SDL_FRect& rect, SDL_Color rgba) const noexcept {
    SDL_SetRenderDrawColor(m_renderer, rgba.r, rgba.g, rgba.b, rgba.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::update() const noexcept {
    SDL_RenderPresent(m_renderer);
    ++frameCnt;
}

void Renderer::clear() const noexcept { SDL_RenderClear(m_renderer); }