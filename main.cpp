#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "imageTexture.h"

namespace
{
    // Game states
    enum class RamenState
    {
        EMPTY,
        WATER_ADDED,
        WATER_BOILING,
        NOODLES_ADDED,
        COOKING,
        HALF_COOKED,
        COOKED,
        BURNT
    };

    RamenState ramenState = RamenState::EMPTY;
    float boilProgress = 0.0f;
    bool customerActive = false;
    bool served = false;
}

std::string getBasePath()
{
    static std::string basePath = "";
    if (basePath == "")
    {
        auto bPath = SDL_GetBasePath();
        if (bPath)
        {
            basePath = std::string(bPath);
            SDL_free(const_cast<char*>(bPath));
        }
    }
    return basePath;
}

// Timer callback
Uint32 SDLCALL onTimer(void * /*intervalPtr*/, Uint32 interval, Uint32 /*unused*/)
{
    customerActive = true;
    return 0;
}

void drawPotFrame(Renderer &renderer, const SDL_FRect &potDst)
{
    static ImageTexture emptyPotTexture{renderer, (getBasePath() + "assets/pot_empty.png").c_str()};
    static ImageTexture potWithWaterTexture{renderer, (getBasePath() + "assets/pot_with_water.png").c_str()};
    static ImageTexture potWithBoilingWaterTexture{renderer, (getBasePath() + "assets/pot_with_boiling_water.png").c_str()};
    static ImageTexture potWithRamenUncookedTexture{renderer, (getBasePath() + "assets/pot_with_ramen_uncooked.png").c_str()};
    static ImageTexture potWithRamenHalfCookedTexture{renderer, (getBasePath() + "assets/pot_with_ramen_halfcooked.png").c_str()};
    static ImageTexture potWithRamenHalfCookedFlippedTexture{renderer, (getBasePath() + "assets/pot_with_ramen_halfcooked1.png").c_str()};
    static ImageTexture potWithRamenCookedTexture{renderer, (getBasePath() + "assets/pot_with_ramen_cooked.png").c_str()};
    static ImageTexture potWithRamenBurntTexture{renderer, (getBasePath() + "assets/pot_with_ramen_burnt.png").c_str()};

    switch (ramenState)
    {
    case RamenState::EMPTY:
        emptyPotTexture.show(renderer, potDst);
        break;
    case RamenState::WATER_ADDED:
        potWithWaterTexture.show(renderer, potDst);
        break;
    case RamenState::WATER_BOILING:
        potWithBoilingWaterTexture.show(renderer, potDst);
        break;
    case RamenState::NOODLES_ADDED:
        potWithRamenUncookedTexture.show(renderer, potDst);
        break;
    case RamenState::COOKING:
        potWithRamenHalfCookedTexture.show(renderer, potDst);
        break;
    case RamenState::HALF_COOKED:
        potWithRamenHalfCookedFlippedTexture.show(renderer, potDst);
        break;
    case RamenState::COOKED:
        potWithRamenCookedTexture.show(renderer, potDst);
        break;
    case RamenState::BURNT:
        potWithRamenBurntTexture.show(renderer, potDst);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    Uint64 lastTime = 0;
    float deltaTime = 0.0f;

    Renderer renderer{};
    // Load textures
    ImageTexture bgTexture{renderer, (getBasePath() + "assets/bg.png").c_str()};
    ImageTexture burnerTexture{renderer, (getBasePath() + "assets/burner.png").c_str()};
    ImageTexture ramenPkgTexture{renderer, (getBasePath() + "assets/ramen_pkg.png").c_str()};
    ImageTexture sinkTexture = {renderer, (getBasePath() + "assets/sink.png").c_str()};
    ImageTexture binTexture = {renderer, (getBasePath() + "assets/trash_bin_closed.png").c_str()};
    ImageTexture bowlsTexture = {renderer, (getBasePath() + "assets/bowls.png").c_str()};
    ImageTexture customerTexture = {renderer, (getBasePath() + "assets/customer_fox.png").c_str()};
    ImageTexture customerServedTexture = {renderer, (getBasePath() + "assets/customer_fox_satisfied.png").c_str()};

    SDL_AddTimer(2000, onTimer, nullptr);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        Uint64 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        SDL_Point mousePoint;
        const SDL_FRect potFDst = {300, 290, 128, 128};
        const SDL_Rect potDst = {300, 290, 128, 128};
        const SDL_FRect pkgFRect = {670, 490, 100, 100};
        const SDL_Rect pkgRect{670, 490, 100, 100};
        const SDL_FRect sinkFRect = {670, 380, 100, 100};
        const SDL_Rect sinkRect = {670, 380, 100, 100};
        const SDL_FRect binFRect = {670, 270, 100, 100};
        const SDL_Rect binRect = {670, 270, 100, 100};
        const SDL_FRect bowlsFRect = {670, 160, 100, 100};
        const SDL_Rect bowlsRect = {670, 160, 100, 100};

        // Update boiling
        if (ramenState != RamenState::EMPTY && ramenState != RamenState::WATER_BOILING && ramenState != RamenState::BURNT)
        {
            boilProgress += deltaTime * 0.2f;
            if (boilProgress >= 1.0f)
            {
                boilProgress = 1.0f;
            }
        }

        if (ramenState == RamenState::WATER_ADDED && boilProgress == 1)
        {
            ramenState = RamenState::WATER_BOILING;
        }
        else if (ramenState == RamenState::NOODLES_ADDED && boilProgress >= 0.5f)
        {
            ramenState = RamenState::COOKING;
        }
        else if (ramenState == RamenState::COOKING)
        {
            if (boilProgress == 1)
            {
                ramenState = RamenState::BURNT;
                boilProgress = 0;
            }
        }
        else if (ramenState == RamenState::HALF_COOKED && boilProgress >= 1)
        {
            ramenState = RamenState::COOKED;
            boilProgress = 0;
        }
        else if (ramenState == RamenState::COOKED)
        {
            if (boilProgress == 1)
            {
                boilProgress = 0;
                ramenState = RamenState::BURNT;
            }
        }

        while (SDL_PollEvent(&e))
        {
            mousePoint.x = static_cast<int>(e.button.x);
            mousePoint.y = static_cast<int>(e.button.y);

            if (e.type == SDL_EVENT_QUIT)
            {
                quit = true;
                break;
            }
            else
            {
                if (ramenState == RamenState::EMPTY && (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) && SDL_PointInRect(&mousePoint, &sinkRect))
                {
                    ramenState = RamenState::WATER_ADDED;
                }
                else if (ramenState == RamenState::WATER_BOILING && (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) && SDL_PointInRect(&mousePoint, &pkgRect))
                {
                    ramenState = RamenState::NOODLES_ADDED;
                    boilProgress = 0;
                }
                else if (ramenState == RamenState::COOKING)
                {
                    if (boilProgress < 1 && (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) && SDL_PointInRect(&mousePoint, &potDst))
                    {
                        ramenState = RamenState::HALF_COOKED;
                        boilProgress = 0;
                    }
                }
                else if (ramenState == RamenState::COOKED)
                {
                    if (SDL_PointInRect(&mousePoint, &bowlsRect) && (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN))
                    {
                        ramenState = RamenState::EMPTY;
                        served = true;
                        boilProgress = 0;
                    }
                }
            }
        }

        renderer.clear();

        // Draw background
        SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};
        bgTexture.show(renderer, bgDst);

        SDL_FRect burnerDst = {SCREEN_WIDTH * 0.3f, SCREEN_HEIGHT * 0.5f, 320, 300};
        burnerTexture.show(renderer, burnerDst);

        SDL_FRect bar = {350, 460, boilProgress * 100.0f, 12};
        renderer.fillRect(bar, 255, 165, 0, 255);

        drawPotFrame(renderer, potFDst);

        // Draw ramen package, sink
        if (SDL_PointInRect(&mousePoint, &pkgRect))
        {
            ramenPkgTexture.show(renderer, SDL_FRect{665, 485, 110, 110});
        }
        else
        {
            ramenPkgTexture.show(renderer, pkgFRect);
        }

        if (SDL_PointInRect(&mousePoint, &sinkRect))
        {
            sinkTexture.show(renderer, SDL_FRect{665, 375, 110, 110});
        }
        else
        {
            sinkTexture.show(renderer, sinkFRect);
        }

        if (SDL_PointInRect(&mousePoint, &binRect))
        {
            binTexture.show(renderer, SDL_FRect{665, 265, 110, 110});
        }
        else
        {
            binTexture.show(renderer, binFRect);
        }

        if (SDL_PointInRect(&mousePoint, &bowlsRect))
        {
            bowlsTexture.show(renderer, SDL_FRect{665, 155, 110, 110});
        }
        else
        {
            bowlsTexture.show(renderer, bowlsFRect);
        }

        // Draw customer
        if (customerActive)
        {
            SDL_FRect custRect = {50, 100, 200, 200};
            if (!served)
            {
                customerTexture.show(renderer, custRect);
            }
            else
            {
                customerServedTexture.show(renderer, custRect);
            }
        }

        renderer.update();
    }

    return 0;
}