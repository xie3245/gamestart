#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "ui.h"
#include "showId.h"
#include "sprite.h"

class Image;

class Renderer final {
public:
    Renderer();

    Renderer(const Renderer&)             = delete;
    Renderer& operator()(const Renderer&) = delete;

    ~Renderer();

    void show(ShowId id,
              const SrcRatio& srcRect,
              const SDL_FRect& dsRrect,
              float ratio  = 1.f,
              double angle = 0.0) const noexcept;

    void show(ShowId id, const SDL_FRect& dsRrect) const noexcept;

    void show(ShowId id, const std::string& text, float x, float y, bool strikethrough = false) const noexcept;

    void renderLine(float x1, float y1, float x2, float y2) const noexcept;
    void fillRect(const SDL_FRect& rect, SDL_Color rgba) const noexcept;

    void update() const noexcept;

    void clear() const noexcept;

    void captureFrame() const noexcept;

private:
    SDL_Texture* loadTexture(SDL_Surface* surf) const noexcept;
    void prepareImage(const Image& img) const noexcept;

    void renderTexture(SDL_Texture* tex, const SDL_FRect& rect) const noexcept;
    void renderTexture(SDL_Texture* tex,
                       const SDL_FRect& srcRect,
                       const SDL_FRect& dsRrect,
                       float ratio  = 1.f,
                       double angle = 0.0) const noexcept;

    SDL_Window* m_window      = nullptr;
    SDL_Renderer* m_renderer  = nullptr;
    mutable uint64_t frameCnt = 0u;
};