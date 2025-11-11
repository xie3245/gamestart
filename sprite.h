#pragma once

enum class Sprite2x1 { left, right };
enum class Sprite1x2 { upper, lower };
enum class Sprite4x1 { first = 0u, second, third, last };

enum class Sprite2x2 {
    upperLeft,
    upperRight,
    lowerLeft,
    lowerRight

};

enum class Sprite2x3 { upperLeft, upperRight, middleLeft, middleRight, lowerLeft, lowerRight };

struct SrcRatio final {
    float r_x           = 0.f;
    float r_y           = 0.f;
    float r_w           = 1.f;
    float r_h           = 1.f;
    SrcRatio() noexcept = default;
    SrcRatio(float x, float y, float w, float h) noexcept : r_x(x), r_y(y), r_w(w), r_h(h) {};
    explicit constexpr SrcRatio(Sprite2x1 part) noexcept : r_x((part == Sprite2x1::right) ? 0.5f : 0.f), r_w(0.5f) {}
    explicit constexpr SrcRatio(Sprite1x2 part) noexcept : r_y((part == Sprite1x2::lower) ? 0.5f : 0.f), r_h(0.5f) {}
    explicit constexpr SrcRatio(Sprite2x1 part, float w_ratio) noexcept
        : r_x((part == Sprite2x1::right) ? 0.5f : 0.f)
        , r_w(0.5f * w_ratio) {}

    explicit constexpr SrcRatio(Sprite2x2 part) noexcept
        : r_x(((part == Sprite2x2::upperRight) || (part == Sprite2x2::lowerRight)) ? 0.5f : 0.f)
        , r_y(((part == Sprite2x2::lowerLeft) || (part == Sprite2x2::lowerRight)) ? 0.5f : 0.f)
        , r_w(0.5f)
        , r_h(0.5f) {}

    explicit constexpr SrcRatio(Sprite2x3 part) noexcept
        : r_x(((part == Sprite2x3::upperRight) || (part == Sprite2x3::middleRight) || (part == Sprite2x3::lowerRight))
                  ? 0.5f
                  : 0.f)
        , r_y(((part == Sprite2x3::upperLeft) || (part == Sprite2x3::upperRight))
                  ? 0.0f
                  : (((part == Sprite2x3::middleLeft) || (part == Sprite2x3::middleRight)) ? (1.f / 3.f) : (2.f / 3.f)))
        , r_w(0.5f)
        , r_h(1.f / 3.f) {}
    constexpr SrcRatio(Sprite2x3 part, float h_ratio) noexcept
        : r_x(((part == Sprite2x3::upperRight) || (part == Sprite2x3::middleRight) || (part == Sprite2x3::lowerRight))
                  ? 0.5f
                  : 0.f)
        , r_y(((part == Sprite2x3::upperLeft) || (part == Sprite2x3::upperRight))
                  ? 0.0f
                  : (((part == Sprite2x3::middleLeft) || (part == Sprite2x3::middleRight)) ? (1.f / 3.f) : (2.f / 3.f)))
        , r_w(0.5f)
        , r_h(h_ratio / 3.f) {}
    explicit constexpr SrcRatio(Sprite4x1 part) noexcept
        : r_x(static_cast<float>(part) / (static_cast<float>(Sprite4x1::last) + 1.f))
        , r_w(0.25f) {}
};