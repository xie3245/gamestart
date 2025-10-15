#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "ui.h"

class Renderer final {
public:
    Renderer();

    Renderer(const Renderer&)             = delete;
    Renderer& operator()(const Renderer&) = delete;

    ~Renderer();

    SDL_Texture* loadTexture(const char* path) const;
    SDL_Texture* loadTexture(SDL_Surface* surf) const;

    void renderTexture(SDL_Texture* tex, const SDL_FRect& rect, float ratio = 1.f, double angle = 0.0) const;
    void renderTexture(SDL_Texture* tex,
                       const SDL_FRect& srcRect,
                       const SDL_FRect& dsRrect,
                       float ratio  = 1.f,
                       double angle = 0.0) const;
    void renderLine(float x1, float y1, float x2, float y2) const noexcept;
    void fillRect(const SDL_FRect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    void update() const;

    void clear() const;

    void captureFrame() const noexcept;

private:
    SDL_Window* m_window      = nullptr;
    SDL_Renderer* m_renderer  = nullptr;
    mutable uint64_t frameCnt = 0u;
};