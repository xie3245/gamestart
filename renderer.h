#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

class Renderer final
{
public:
    Renderer() : m_window(SDL_CreateWindow("Ramen Shop", SCREEN_WIDTH, SCREEN_HEIGHT, 0)), m_renderer(SDL_CreateRenderer(m_window, nullptr))
    {
        if (!m_window || !m_renderer)
        {
            std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
            SDL_Quit();
        }
    }

    ~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    SDL_Texture *loadTexture(const char *path)
    {
        SDL_Texture *tex = IMG_LoadTexture(m_renderer, path);
        if (!tex)
        {
            std::cerr << "IMG_Load failed: " << SDL_GetError() << " (Path: " << path << ")" << std::endl;
        }
        return tex;
    }

    void renderTexture(SDL_Texture *tex, const SDL_FRect &rect)
    {
        SDL_RenderTexture(m_renderer, tex, nullptr, &rect);
    }

    void fillRect(const SDL_FRect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void update()
    {
        SDL_RenderPresent(m_renderer);
    }

    void clear()
    {
        SDL_RenderClear(m_renderer);
    }

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
};