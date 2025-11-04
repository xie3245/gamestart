#pragma once
#include <memory>
#include <SDL3_image/SDL_image.h>
#include "showId.h"

using ImageSurface = std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)>;
using ImageTexture = std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)>;

struct Image final {
    Image() noexcept : surface(nullptr, SDL_DestroySurface), texture(nullptr, SDL_DestroyTexture) {}

    explicit Image(const char* path_to_img) noexcept
        : surface(IMG_Load(path_to_img), SDL_DestroySurface)
        , texture(nullptr, SDL_DestroyTexture) {}

    Image(const ImageTexture&)            = delete;
    Image& operator=(const ImageTexture&) = delete;

    static const Image& getImage(ShowId id) noexcept;
    static const Image& getImage(ShowId id, const std::string& txt) noexcept;

    ImageSurface surface;
    mutable ImageTexture texture;
};