#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

class Renderer final
{
public:
    Renderer();

    ~Renderer();

    SDL_Texture *loadTexture(const char *path);

    void renderTexture(SDL_Texture *tex, const SDL_FRect &rect);

    void fillRect(const SDL_FRect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    void update();

    void clear();

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
};