#include "stats.h"
#include <iostream>
#include "renderer.h"
#include "sprite.h"

static int64_t money = 0;

void gainMoney(uint16_t diff) noexcept { money += diff; }
void loseMoney(uint16_t diff) noexcept { money -= diff; }

void Money::show(const Renderer& rend) noexcept {
    rend.show(ShowId::coins, SrcRatio{Sprite2x2::upperLeft}, moneyFRect);
    rend.show(ShowId::moneyNumberText, std::to_string(money), money_x, money_y);
}

static float averageRating = 0.f;

// exponentially weighted moving average (EWMA) restaurantStars_today = (1-α)·prev + α·todayAverage, α controls
// responsiveness
float getRating() noexcept { return averageRating; }
void updateRating(int rating) noexcept { averageRating = 0.8f * averageRating + 0.2 * rating; }
void showRating(const Renderer& rend) noexcept {
    rend.show(ShowId::star, SrcRatio{Sprite2x1::left, getRating() * 0.5f}, {400, 10, 40.f * getRating() * 0.5f, 40});

    for (auto i = 0; i < 5; ++i) {
        float x = 400.f + i * 40.f;
        rend.show(ShowId::star, SrcRatio{Sprite2x1::right}, {x, 10, 40, 40});
    }
}