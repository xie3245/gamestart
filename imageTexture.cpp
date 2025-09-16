#include "imageTexture.h"
#include "utils.h"

ImageTexture::ImageTexture(const Renderer &renderer, const char *path_to_img) : m_texture(renderer.loadTexture(path_to_img))
{
}

ImageTexture::~ImageTexture()
{
    SDL_DestroyTexture(m_texture);
}

void ImageTexture::show(const Renderer &renderer, const SDL_FRect &rect) const
{
    renderer.renderTexture(m_texture, rect);
}

const ImageTexture &getImage(ImageId id, const Renderer &rd)
{
    static auto basePath = getBasePath();
    static ImageTexture defaultTexture{rd, (basePath + "assets/undefined.png").c_str()};
    static ImageTexture imageMap[] = {{rd, (basePath + "assets/bg2areasMoreOp.png").c_str()},
                                      {rd, (basePath + "assets/sink.png").c_str()},
                                      {rd, (basePath + "assets/sink_water_running.png").c_str()},
                                      {rd, (basePath + "assets/ramen_pkg.png").c_str()},
                                      {rd, (basePath + "assets/bowls.png").c_str()},
                                      {rd, (basePath + "assets/trash_bin_closed.png").c_str()},
                                      {rd, (basePath + "assets/trash_bin_open.png").c_str()},
                                      {rd, (basePath + "assets/counter_surface_lean.png").c_str()},
                                      {rd, (basePath + "assets/burner.png").c_str()},
                                      {rd, (basePath + "assets/pot_empty.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_water.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_boiling_water.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_ramen_uncooked.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_ramen_halfcooked.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_ramen_halfcooked1.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_ramen_cooked.png").c_str()},
                                      {rd, (basePath + "assets/pot_with_ramen_burnt.png").c_str()},
                                      {rd, (basePath + "assets/customer_fox.png").c_str()}};

    if (!(static_cast<size_t>(id) > static_cast<size_t>(ImageId::last)))
    {
        return imageMap[static_cast<size_t>(id) - 1u];
    }
    return defaultTexture;
}