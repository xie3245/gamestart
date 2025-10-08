#include "customer.h"
#include "imageTexture.h"
#include "sound.h"
#include <random>
#include <cmath>

namespace {
std::random_device rd{};
std::mt19937 rng{rd()};
constexpr float customersPerMinute = 1.0f;
std::exponential_distribution<float> intervalDistr{customersPerMinute / 60000.f};
std::discrete_distribution<> cusDistr{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

void DrawPatienceBar(SDL_Renderer* r, SDL_FRect dst, float value) {
    // clamp
    if (value < 0.f) value = 0.f;
    if (value > 1.f) value = 1.f;

    // colors
    SDL_Color bg       = {30, 30, 34, 255};
    SDL_Color leftCol  = {60, 210, 110, 255};
    SDL_Color rightCol = {210, 70, 60, 255};
    SDL_Color outline  = {8, 8, 10, 255};

    // background
    SDL_SetRenderDrawColor(r, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderFillRect(r, &dst);

    // fill width
    float w = dst.w * value;
    if (w > 0.f) {
        SDL_FRect fill = {dst.x, dst.y, w, dst.h};

        SDL_Vertex verts[4] = {
            {{fill.x, fill.y}, {leftCol.r / 255.f, leftCol.g / 255.f, leftCol.b / 255.f, leftCol.a / 255.f}, {0, 0}},
            {{fill.x + fill.w, fill.y},
             {rightCol.r / 255.f, rightCol.g / 255.f, rightCol.b / 255.f, rightCol.a / 255.f},
             {0, 0}},
            {{fill.x + fill.w, fill.y + fill.h},
             {rightCol.r / 255.f, rightCol.g / 255.f, rightCol.b / 255.f, rightCol.a / 255.f},
             {0, 0}},
            {{fill.x, fill.y + fill.h},
             {leftCol.r / 255.f, leftCol.g / 255.f, leftCol.b / 255.f, leftCol.a / 255.f},
             {0, 0}},
        };
        int idx[6] = {0, 1, 2, 0, 2, 3};
        SDL_RenderGeometry(r, nullptr, verts, 4, idx, 6);
    }

    // outline (1px)
    SDL_SetRenderDrawColor(r, outline.r, outline.g, outline.b, outline.a);
    SDL_FRect top    = {dst.x, dst.y, dst.w, 1.f};
    SDL_FRect bottom = {dst.x, dst.y + dst.h - 1.f, dst.w, 1.f};
    SDL_FRect leftR  = {dst.x, dst.y, 1.f, dst.h};
    SDL_FRect rightR = {dst.x + dst.w - 1.f, dst.y, 1.f, dst.h};
    SDL_RenderFillRect(r, &top);
    SDL_RenderFillRect(r, &bottom);
    SDL_RenderFillRect(r, &leftR);
    SDL_RenderFillRect(r, &rightR);
}

}  // namespace

Customer::Customer(const AudioMixer& mx, ElementId id) noexcept
    : m_start(std::chrono::milliseconds(std::lround(intervalDistr(rng))))
    , m_mixer(mx)
    , m_id(id)
    , m_imgId(toImgId(cusDistr(rng))) {}

void Customer::handleClick(ElementId clicked) noexcept {
    switch (m_state) {
    case CustomerState::ordered:
        if (isServing()) {
            m_state = CustomerState::waiting;
        }
        break;
    case CustomerState::waiting:
        if (clicked == m_id) {
            m_state = CustomerState::eating;
            m_mixer.play(SoundId::slurp);
            setServing(false);
        } else if (!isServing()) {
            m_state = CustomerState::ordered;
        }
        break;
    default:
        break;
    }
}

void Customer::handleTick(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    switch (m_state) {
    case CustomerState::undefined: {
        if (m_start < tick) {
            m_state = isServing() ? CustomerState::waiting : CustomerState::ordered;
            m_start = tick;
        }
    } break;
    case CustomerState::eating: {
        if ((tick - m_toggleStart) > 300ms) {
            m_toggle      = !m_toggle;
            m_toggleStart = tick;
        }
        if (tick - m_start > 5s) {
            m_state = CustomerState::leaving;
            m_mixer.play(SoundId::burp);
            m_start = tick;
        }
    } break;
    case CustomerState::leaving: {
        if (tick - m_start > 1s) {
            m_state = CustomerState::undefined;
            m_start = tick + std::chrono::milliseconds(std::lround(intervalDistr(rng)));
            m_imgId = toImgId(cusDistr(rng));
        }
    } break;
    default:
        m_toggleStart = tick;
        m_start       = tick;
        break;
    }
}

void Customer::show(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        if (m_toggle) {
            getImage(m_imgId).show(rend, getCustSlotFRect(m_id), ImagePart::upperRight);
        } else {
            getImage(m_imgId).show(rend, getCustSlotFRect(m_id), ImagePart::lowerLeft);
        }
        break;
    case CustomerState::leaving: {
        getImage(m_imgId).show(rend, getCustSlotFRect(m_id), ImagePart::lowerRight);
    } break;
    case CustomerState::ordered:
    case CustomerState::waiting: {
        getImage(m_imgId).show(rend, getCustSlotFRect(m_id), ImagePart::upperLeft);
    } break;
    default:
        break;
    }
}

void Customer::showServedItems(const Renderer& rend) const noexcept {
    switch (m_state) {
    case CustomerState::eating:
        getImage(ImageId::bowl_with_ramen_plain).show(rend, getServingSlotFRect(m_id), ImagePart::undefined);
        break;
    default:
        break;
    }
}