#include "money.h"
#include <iostream>
#include "renderer.h"
#include "imageTexture.h"

constexpr float money_x = 55.f;
constexpr float money_y = 20.f;

void Money::show(const Renderer& rend) noexcept {
    getImage(ImageId::coins).show(rend, Sprite2x2::upperLeft, {10, 10, 40, 40});
    m_fontTexture.show(rend, std::to_string(getMoney()), color::gold, money_x, money_y);
}

void showRating(const Renderer& rend) noexcept {
    getImage(ImageId::star).show(rend, {Sprite2x1::left, getRating() * 0.5f}, {400, 10, 40.f * getRating() * 0.5f, 40});

    for (auto i = 0; i < 5; ++i) {
        float x = 400.f + i * 40.f;
        getImage(ImageId::star).show(rend, Sprite2x1::right, {x, 10, 40, 40});
    }
}