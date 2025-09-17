#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "renderer.h"

class ImageTexture final {
public:
    ImageTexture(const char* path_to_img);

    ~ImageTexture();

    ImageTexture(ImageTexture&&)      = default;
    ImageTexture(const ImageTexture&) = delete;

    ImageTexture& operator=(ImageTexture&&)      = default;
    ImageTexture& operator=(const ImageTexture&) = delete;

    void show(const Renderer& renderer, const SDL_FRect& rect) const;

private:
    SDL_Surface* m_surface         = nullptr;
    mutable SDL_Texture* m_texture = nullptr;
};

enum class ImageId {
    bg = 0u,
    sink,
    sink_running_water,
    ramenPkg,
    bowls,
    bin,
    bin_open,
    counter_surface,
    burner,
    empty_pot,
    pot_water_added,
    pot_water_boiling,
    pot_noodle_added,
    pot_noodle_cooking,
    pot_noodle_halfcooked,
    pot_noodle_cooked,
    pot_burnt,
    customer,
    last
};

const ImageTexture& getImage(ImageId id);