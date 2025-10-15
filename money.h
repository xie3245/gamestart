#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
#include "text.h"
class Renderer;

class Money final {
public:
    void show(const Renderer& rend) noexcept;

private:
    FontTexture m_fontTexture{};
};

void showRating(const Renderer& rend) noexcept;