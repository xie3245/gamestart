#include "ramenCooking.h"
#include "ui.h"
#include "utils.h"
#include "sound.h"

RamenCooking::RamenCooking(Renderer &r, const SoundTrack &boil) noexcept : m_renderer(r), m_state(RamenState::EMPTY),
                                                                           m_thread(Thread<int()>::fromMethod<RamenCooking, &threadLoop>(this, "pot")),
                                                                           m_mtx(),
                                                                           emptyPotTexture(m_renderer, (getBasePath() + "assets/pot_empty.png").c_str()),
                                                                           potWithWaterTexture(m_renderer, (getBasePath() + "assets/pot_with_water.png").c_str()),
                                                                           potWithBoilingWaterTexture(m_renderer, (getBasePath() + "assets/pot_with_boiling_water.png").c_str()),
                                                                           potWithRamenUncookedTexture(m_renderer, (getBasePath() + "assets/pot_with_ramen_uncooked.png").c_str()),
                                                                           potWithRamenHalfCookedTexture(m_renderer, (getBasePath() + "assets/pot_with_ramen_halfcooked.png").c_str()),
                                                                           potWithRamenHalfCookedFlippedTexture(m_renderer, (getBasePath() + "assets/pot_with_ramen_halfcooked1.png").c_str()),
                                                                           potWithRamenCookedTexture(m_renderer, (getBasePath() + "assets/pot_with_ramen_cooked.png").c_str()),
                                                                           potWithRamenBurntTexture(m_renderer, (getBasePath() + "assets/pot_with_ramen_burnt.png").c_str()),
                                                                           boilingWaterTrack(boil)
{
}

RamenCooking::~RamenCooking() noexcept
{
    m_thread.detach();
}

void RamenCooking::show()
{
    static uint16_t puffCnt = 0;
    switch (m_state)
    {
    case RamenState::EMPTY:
        emptyPotTexture.show(m_renderer, potFDst);
        break;
    case RamenState::WATER_ADDED:
        potWithWaterTexture.show(m_renderer, potFDst);
        break;
    case RamenState::WATER_BOILING:
    {
        if (puffCnt < 60)
        {
            ++puffCnt;
        }
        else
        {
            puffCnt = 0u;
        }
        if (puffCnt > 30u)
        {
            potWithBoilingWaterTexture.show(m_renderer, {298, 288, 132, 132});
        }
        else
        {
            potWithBoilingWaterTexture.show(m_renderer, potFDst);
        }
    }
    break;
    case RamenState::NOODLES_ADDED:
        potWithRamenUncookedTexture.show(m_renderer, potFDst);
        break;
    case RamenState::COOKING:
        potWithRamenHalfCookedTexture.show(m_renderer, potFDst);
        break;
    case RamenState::HALF_COOKED:
        potWithRamenHalfCookedFlippedTexture.show(m_renderer, potFDst);
        break;
    case RamenState::COOKED:
        potWithRamenCookedTexture.show(m_renderer, potFDst);
        break;
    case RamenState::BURNT:
        potWithRamenBurntTexture.show(m_renderer, potFDst);
        break;
    default:
        break;
    }
}

void RamenCooking::handleMouseDown(const SDL_Point &downPt)
{
    LockGuard lock{m_mtx};
    switch (m_state)
    {
    case RamenState::EMPTY:
    {
        if (SDL_PointInRect(&downPt, &sinkRect))
        {
            m_state = RamenState::WATER_ADDED;
        }
    }
    break;
    case RamenState::WATER_BOILING:
    {
        if (SDL_PointInRect(&downPt, &pkgRect))
        {
            m_state = RamenState::NOODLES_ADDED;
        }
    }
    break;
    case RamenState::COOKING:
    {
        if (SDL_PointInRect(&downPt, &potDst))
        {
            m_state = RamenState::HALF_COOKED;
        }
    }
    break;
    case RamenState::COOKED:
    {
        if (SDL_PointInRect(&downPt, &bowlsRect))
        {
            m_state = RamenState::EMPTY;
        }
    }
    break;
    case RamenState::BURNT:
    {
        if (SDL_PointInRect(&downPt, &binRect))
        {
            m_state = RamenState::EMPTY;
        }
    }
    break;
    default:
        break;
    }
}

int RamenCooking::threadLoop()
{
    using namespace std::chrono_literals;
    while (true)
    {
        switch (m_state)
        {
        case RamenState::WATER_ADDED:
        {
            this_thread::sleep(2s);
            m_state = RamenState::WATER_BOILING;
            boilingWaterTrack.play();
        }
        break;
        case RamenState::NOODLES_ADDED:
        {
            this_thread::sleep(2s);
            m_state = RamenState::COOKING;
        }
        break;
        case RamenState::COOKING:
        {
            this_thread::sleep(2s);
            LockGuard lock{m_mtx};
            if (m_state == RamenState::COOKING)
            {
                m_state = RamenState::BURNT;
            }
        }
        break;
        case RamenState::HALF_COOKED:
        {
            this_thread::sleep(2s);
            m_state = RamenState::COOKED;
        }
        break;
        case RamenState::COOKED:
        {
            this_thread::sleep(10s);
            LockGuard lock{m_mtx};
            if (m_state == RamenState::COOKED)
            {
                m_state = RamenState::BURNT;
            }
        }
        break;
        default:
            this_thread::sleep(500ms);
            break;
        }
    }
    return 0;
}