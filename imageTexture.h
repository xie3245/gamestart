#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "renderer.h"
#include "imageId.h"
#include <memory>

enum class Sprite2x1 { left, right };

enum class Sprite2x2 {
    upperLeft,
    upperRight,
    lowerLeft,
    lowerRight

};

enum class Sprite2x3 { upperLeft, upperRight, middleLeft, middleRight, lowerLeft, lowerRight };

struct SrcRations final {
    float r_x = 0.f;
    float r_y = 0.f;
    float r_w = 1.f;
    float r_h = 1.f;

    constexpr SrcRations(Sprite2x1 part) noexcept : r_x((part == Sprite2x1::right) ? 0.5f : 0.f), r_w(0.5f) {}

    constexpr SrcRations(Sprite2x1 part, float w_ratio) noexcept
        : r_x((part == Sprite2x1::right) ? 0.5f : 0.f)
        , r_w(0.5f * w_ratio) {}

    constexpr SrcRations(Sprite2x2 part) noexcept
        : r_x(((part == Sprite2x2::upperRight) || (part == Sprite2x2::lowerRight)) ? 0.5f : 0.f)
        , r_y(((part == Sprite2x2::lowerLeft) || (part == Sprite2x2::lowerRight)) ? 0.5f : 0.f)
        , r_w(0.5f)
        , r_h(0.5f) {}

    constexpr SrcRations(Sprite2x3 part) noexcept
        : r_x(((part == Sprite2x3::upperRight) || (part == Sprite2x3::middleRight) || (part == Sprite2x3::lowerRight))
                  ? 0.5f
                  : 0.f)
        , r_y(((part == Sprite2x3::upperLeft) || (part == Sprite2x3::upperRight))
                  ? 0.0f
                  : (((part == Sprite2x3::middleLeft) || (part == Sprite2x3::middleRight)) ? (1.f / 3.f) : (2.f / 3.f)))
        , r_w(0.5f)
        , r_h(1.f / 3.f) {}
    constexpr SrcRations(Sprite2x3 part, float w_ratio) noexcept
        : r_x(((part == Sprite2x3::upperRight) || (part == Sprite2x3::middleRight) || (part == Sprite2x3::lowerRight))
                  ? 0.5f
                  : 0.f)
        , r_y(((part == Sprite2x3::upperLeft) || (part == Sprite2x3::upperRight))
                  ? 0.0f
                  : (((part == Sprite2x3::middleLeft) || (part == Sprite2x3::middleRight)) ? (1.f / 3.f) : (2.f / 3.f)))
        , r_w(0.5f)
        , r_h(w_ratio / 3.f) {}
};

class ImageTexture final {
    std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)> m_surface;

public:
    explicit ImageTexture(const char* path_to_img) noexcept;
    ~ImageTexture() noexcept;

    ImageTexture(ImageTexture&&)      = default;
    ImageTexture(const ImageTexture&) = delete;

    ImageTexture& operator=(ImageTexture&&)      = default;
    ImageTexture& operator=(const ImageTexture&) = delete;

    void show(const Renderer& renderer, const SDL_FRect& dist, float ratio = 1.f, double angle = 0.0) const;
    void show(const Renderer& renderer, const SrcRations& src, const SDL_FRect& dist) const;

private:
    mutable SDL_Texture* m_texture = nullptr;
};

const ImageTexture& getImage(ImageId id);