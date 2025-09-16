#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "ui.h"

class Renderer final
{
public:
    Renderer();

    ~Renderer();

    SDL_Texture *loadTexture(const char *path) const;

    void renderTexture(SDL_Texture *tex, const SDL_FRect &rect) const;

    void fillRect(const SDL_FRect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    void update() const;

    void clear() const;

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
};