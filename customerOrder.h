#pragma once
#include "showId.h"

struct CustomerOrder {
    ShowId ramen                                 = ShowId::lastImg;
    ShowId drink                                 = ShowId::lastImg;
    auto operator<=>(const CustomerOrder&) const = default;

    bool inline has(ShowId item) const noexcept { return (item == ramen) || (item == drink); }
    void inline update(ShowId item) noexcept {
        if (isSoftdrink(item)) {
            drink = item;
        }

        if (isRamenBowl(item)) {
            ramen = item;
        }
    }
};

inline constexpr void reset(CustomerOrder& order) noexcept { order = CustomerOrder{}; }

CustomerOrder spawnOrder() noexcept;

constexpr float ramenWeight = 10.f;
constexpr float drinkWeight = 5.f;
inline float orderDiffRatio(const CustomerOrder& ordered, const CustomerOrder& served) noexcept {
    if (ordered == served) {
        return 1.f;
    }

    constexpr float total = ramenWeight + drinkWeight;
    float earned =
        ((served.ramen == ordered.ramen) ? ramenWeight : 0.f) + ((served.drink == ordered.drink) ? drinkWeight : 0.f);
    return earned / total;
}