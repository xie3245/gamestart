#include "ui.h"
#include <cmath>

bool isMouse(const SDL_Event& e) noexcept {
    return (e.type >= SDL_EVENT_MOUSE_MOTION) && (e.type <= SDL_EVENT_MOUSE_BUTTON_UP);
}

bool isClick(const SDL_Event& e) noexcept {
    if (!isMouse(e)) {
        return false;
    }
    static MoveType prev_type = MoveType::undefined;
    static float press_x      = 0.f;
    static float press_y      = 0.f;
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        press_x = e.button.x;
        press_y = e.button.y;
    }

    if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && std::abs(press_x - e.button.x) < 10.f &&
        std::abs(press_y - e.button.y) < 10.f) {
        return true;
    }

    return false;
}

static bool serving = false;
bool isServing() noexcept { return serving; }
void setServing(bool serve) noexcept { serving = serve; }

static int64_t money = 0;

int64_t getMoney() noexcept { return money; }
void updateMoney(int64_t diff) noexcept { money += diff; }

static float averageRating    = 5.f;
static uint64_t customerCount = 0;

float getRating() noexcept { return averageRating / 10.f; }
void updateRating(int rating) noexcept {
    ++customerCount;
    averageRating = (averageRating + rating) / customerCount;
}