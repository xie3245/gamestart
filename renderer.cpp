#include <iostream>
#include "renderer.h"

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

SDL_Texture* Renderer::loadTexture(const char* path) const {
    SDL_Texture* tex = IMG_LoadTexture(m_renderer, path);
    if (!tex) {
        std::cerr << "IMG_Load failed: " << SDL_GetError() << " (Path: " << path << ")" << std::endl;
    }
    return tex;
}

SDL_Texture* Renderer::loadTexture(SDL_Surface* surf) const {
    auto tex = SDL_CreateTextureFromSurface(m_renderer, surf);
    if (!tex) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
        return nullptr;
    }
    return tex;
}

void Renderer::renderTexture(SDL_Texture* tex, const SDL_FRect& rect) const {
    if (!SDL_RenderTexture(m_renderer, tex, nullptr, &rect)) {
        std::cerr << __func__ << " failed: " << SDL_GetError() << "\n";
    }
}

void Renderer::fillRect(const SDL_FRect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::update() const { SDL_RenderPresent(m_renderer); }

void Renderer::clear() const { SDL_RenderClear(m_renderer); }