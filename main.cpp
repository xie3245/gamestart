#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

namespace
{
    // Screen dimensions
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;

    // Game states
    enum class RamenState
    {
        EMPTY,
        BOILING,
        NOODLES_ADDED,
        BROTH_ADDED,
        EGG_ADDED,
        READY
    };

    RamenState ramenState = RamenState::EMPTY;
    float boilProgress = 0.0f;
    bool customerActive = false;
    bool served = false;

    // Button rectangles
    SDL_Rect boilBtn = {100, 300, 60, 30};
    SDL_Rect noodlesBtn = {100, 350, 60, 30};
    SDL_Rect brothBtn = {100, 400, 60, 30};
    SDL_Rect eggBtn = {100, 450, 60, 30};
    SDL_Rect serveBtn = {100, 500, 60, 30};

    Uint64 lastTime = 0;
    float deltaTime = 0.0f;

    // Sprite sheet setup
    const int SHEET_WIDTH = 1536;
    const int SHEET_HEIGHT = 1024;
    const int FRAME_WIDTH = SHEET_WIDTH / 4; // 384
    const int FRAME_HEIGHT = SHEET_HEIGHT;   // 1024

    // Render size and position
    const int POT_RENDER_X = 300;
    const int POT_RENDER_Y = 200;
    const int POT_RENDER_W = 384;
    const int POT_RENDER_H = 256;

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

    class ImageTexture final
    {
    public:
        ImageTexture(Renderer &renderer, const char *path_to_img) : m_texture(renderer.loadTexture(path_to_img))
        {
        }

        ~ImageTexture()
        {
            SDL_DestroyTexture(m_texture);
        }

        void show(Renderer &renderer, const SDL_FRect &rect)
        {
            renderer.renderTexture(m_texture, rect);
        }

    private:
        SDL_Texture *m_texture = nullptr;
    };
}

// Timer callback
Uint32 SDLCALL onTimer(void * /*intervalPtr*/, Uint32 interval, Uint32 /*unused*/)
{
    customerActive = true;
    return 0;
}

void drawPotFrame(Renderer &renderer, int frameIndex)
{
    ImageTexture emptyPotTexture{renderer, "assets/pot1.png"};
    ImageTexture potWithWaterTexture{renderer, "assets/pot_with_water.png"};
    ImageTexture potWithRamenUncookedTexture{renderer, "assets/pot_with_ramen_uncooked.png"};
    ImageTexture potWithRamenHalfCookedTexture{renderer, "assets/pot_with_ramen_halfcooked1.png"};
    ImageTexture potWithRamenCookedTexture{renderer, "assets/pot_with_ramen_cooked1.png"};
    SDL_FRect potDst = {300, 290, 128, 128};

    if (frameIndex == 0)
    {
        emptyPotTexture.show(renderer, potDst);
    }

    if (frameIndex == 1)
    {
        potWithWaterTexture.show(renderer, potDst);
    }

    if (frameIndex == 2)
    {
        potWithRamenUncookedTexture.show(renderer, potDst);
    }

    if (frameIndex == 3)
    {
        potWithRamenHalfCookedTexture.show(renderer, potDst);
    }

    if (frameIndex == 4)
    {
        potWithRamenCookedTexture.show(renderer, potDst);
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    Renderer renderer{};
    // Load textures
    ImageTexture bgTexture{renderer, "assets/bg.png"};
    ImageTexture burnerTexture{renderer, "assets/burner.png"};
    ImageTexture ramenPkgTexture{renderer, "assets/ramen_pkg.png"};
    ImageTexture sinkTexture = {renderer, "assets/sink.png"};
    ImageTexture binTexture = {renderer, "assets/trash_bin_closed.png"};
    ImageTexture bowlsTexture = {renderer, "assets/bowls.png"};
    ImageTexture customerTexture = {renderer, "assets/customer.png"};

    SDL_AddTimer(2000, onTimer, nullptr);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        Uint64 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                SDL_Point mousePoint = {
                    static_cast<int>(e.button.x),
                    static_cast<int>(e.button.y)};

                if (ramenState == RamenState::EMPTY && SDL_PointInRect(&mousePoint, &boilBtn))
                {
                    ramenState = RamenState::BOILING;
                }
                else if (ramenState == RamenState::BOILING && SDL_PointInRect(&mousePoint, &noodlesBtn) && boilProgress >= 1.0f)
                {
                    ramenState = RamenState::NOODLES_ADDED;
                }
                else if (ramenState == RamenState::NOODLES_ADDED && SDL_PointInRect(&mousePoint, &brothBtn))
                {
                    ramenState = RamenState::BROTH_ADDED;
                }
                else if (ramenState == RamenState::BROTH_ADDED && SDL_PointInRect(&mousePoint, &eggBtn))
                {
                    ramenState = RamenState::EGG_ADDED;
                }
                else if (ramenState == RamenState::EGG_ADDED && SDL_PointInRect(&mousePoint, &serveBtn))
                {
                    ramenState = RamenState::READY;
                    served = true;
                }
            }
        }

        // Update boiling
        if (ramenState == RamenState::BOILING)
        {
            boilProgress += deltaTime * 0.5f;
            if (boilProgress >= 1.0f)
            {
                boilProgress = 1.0f;
            }
        }

        renderer.clear();

        // Draw background
        SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
        bgTexture.show(renderer, bgDst);

        SDL_FRect burnerDst = {SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.5f, 320, 300};
        burnerTexture.show(renderer, burnerDst);

        // Draw pot frame
        int frame = 0;
        if (ramenState == RamenState::EMPTY)
        {
            frame = 0;
        }
        else if (ramenState == RamenState::BOILING)
        {
            frame = (boilProgress < 0.5f) ? 1 : 2;
        }
        else if (ramenState == RamenState::NOODLES_ADDED)
        {
            frame = 3;
        }
        else
        {
            frame = 4;
        }

        drawPotFrame(renderer, frame);

        // Draw ramen package, sink
        SDL_FRect pkgRect = {650, 450, 128, 128};
        ramenPkgTexture.show(renderer, pkgRect);
        SDL_FRect sinkRect = {650, 300, 128, 128};
        sinkTexture.show(renderer, sinkRect);
        SDL_FRect binRect = {650, 150, 128, 128};
        binTexture.show(renderer, binRect);
        SDL_FRect bowlsRect = {650, 10, 128, 128};
        bowlsTexture.show(renderer, bowlsRect);

        // Draw customer
        if (customerActive)
        {
            SDL_FRect custRect = {50, 100, 200, 200};
            customerTexture.show(renderer, custRect);
        }

        // Boiling progress bar
        if (ramenState == RamenState::BOILING)
        {
            SDL_FRect bar = {350, 460, boilProgress * 100.0f, 12};
            renderer.fillRect(bar, 255, 165, 0, 255);
        }

        // Draw buttons
        auto drawButton = [&](const SDL_Rect &rect, bool enabled)
        {
            SDL_FRect frect = {(float)rect.x, (float)rect.y, (float)rect.w, (float)rect.h};
            Uint8 r = enabled ? 100 : 80;
            Uint8 g = enabled ? 150 : 80;
            Uint8 b = enabled ? 255 : 80;
            renderer.fillRect(frect, r, g, b, 255);
        };

        drawButton(boilBtn, ramenState == RamenState::EMPTY);
        drawButton(noodlesBtn, ramenState == RamenState::BOILING && boilProgress >= 1.0f);
        drawButton(brothBtn, ramenState == RamenState::NOODLES_ADDED);
        drawButton(eggBtn, ramenState == RamenState::BROTH_ADDED);
        drawButton(serveBtn, ramenState == RamenState::EGG_ADDED);

        // Served flash
        if (served)
        {
            SDL_FRect overlay = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
            renderer.fillRect(overlay, 255, 255, 0, 100);
        }

        renderer.update();
    }

    return 0;
}