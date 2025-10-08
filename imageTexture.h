#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "renderer.h"
#include "imageId.h"

enum class ImagePart { undefined, upperLeft, upperRight, lowerLeft, lowerRight };
class ImageTexture final {
public:
    ImageTexture(const char* path_to_img);

    ~ImageTexture();

    ImageTexture(ImageTexture&&)      = default;
    ImageTexture(const ImageTexture&) = delete;

    ImageTexture& operator=(ImageTexture&&)      = default;
    ImageTexture& operator=(const ImageTexture&) = delete;

    void show(const Renderer& renderer, const SDL_FRect& rect, float ratio = 1.f, double angle = 0.0) const;
    void show(const Renderer& renderer, const SDL_FRect& rect, ImagePart part) const;

private:
    SDL_Surface* m_surface         = nullptr;
    mutable SDL_Texture* m_texture = nullptr;
};

const ImageTexture& getImage(ImageId id);