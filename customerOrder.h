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