#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "renderer.h"

class ImageTexture final
{
public:
    ImageTexture(Renderer &renderer, const char *path_to_img) : m_texture(renderer.loadTexture(path_to_img))
    {
    }

    ~ImageTexture()
    {
        SDL_DestroyTexture(m_texture);
    }

    void show(Renderer &renderer, const SDL_FRect &rect)
    {
        renderer.renderTexture(m_texture, rect);
    }

private:
    SDL_Texture *m_texture = nullptr;
};