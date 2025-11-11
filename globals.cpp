#include "globals.h"
#include "ui.h"
#include "element.h"

ShowId itemOnMouse = ShowId::last;

bool attachToMouse(ElementId whosAsking, ShowId id) noexcept {
    switch (whosAsking) {
    case ElementId::sinkSideBar: {
        if (itemOnMouse == ShowId::empty_bowl) {
            itemOnMouse = id;
            return true;
        }
    }
    default: {
        if ((itemOnMouse != ShowId::bowl_with_ramen_plain) && (itemOnMouse != ShowId::pot_water_added)) {
            itemOnMouse = id;
            return true;
        }
    } break;
    }
    return false;
}

void clearMouseItem() noexcept { itemOnMouse = ShowId::last; }
ShowId mouseItem() noexcept { return itemOnMouse; }

static int64_t money = 0;

void gainMoney(uint16_t diff) noexcept { money += diff; }
void loseMoney(uint16_t diff) noexcept { money -= diff; }

std::string getText(ShowId id) noexcept {
    if (id == ShowId::moneyNumberText) {
        return std::to_string(money);
    }
    return "classic";
}

static bool paused = false;
bool isPaused() noexcept { return paused; }
void pause() noexcept { paused = true; }
void unpause() noexcept { paused = false; }
void togglePause() noexcept { paused = !paused; }

static bool overlay = false;
bool isOverlay() noexcept { return overlay; }
void activateOverlay() noexcept { overlay = true; }
void deactivateOverlay() noexcept { overlay = false; }
void toggleOverlay() noexcept { overlay = !overlay; }

static Element nullElemnt{{0.f, 0.f, 0.f, 0.f}, ElementId::undefined, ShowId::last};

static Element gamePlayElems[] = {
    {bgDst, ElementId::undefined, ShowId::bg, false, true},
    {fridgeDst, ElementId::fridge, ShowId::fridge, false, true, true, SrcRatio{Sprite1x2::upper}},
    {cust1FRect, ElementId::customer1, ShowId::customer1},
    {cust2FRect, ElementId::customer2, ShowId::customer1},
    {cust3FRect, ElementId::customer3, ShowId::customer1},
    {cust4FRect, ElementId::customerRightMost, ShowId::customer1},
    {softdrink1FDst, ElementId::softdrink1, ShowId::softdrink_kola, false, false, false,
     SrcRatio{0.25f, 0.f, 0.5f, 1.f}},
    {softdrink2FDst, ElementId::softdrink2, ShowId::softdrink_funta, false, false, false,
     SrcRatio{0.25f, 0.f, 0.5f, 1.f}},
    {softdrink3FDst, ElementId::softdrink3, ShowId::softdrink_peppy, false, false, false,
     SrcRatio{0.25f, 0.f, 0.5f, 1.f}},
    {softdrink4FDst, ElementId::softdrink4, ShowId::softdrink_spryte, false, false, false,
     SrcRatio{0.25f, 0.f, 0.5f, 1.f}},
    {cust1PatienceBarFRect, ElementId::patienceBarOutline1, ShowId::patiencebar},
    {cust2PatienceBarFRect, ElementId::patienceBarOutline2, ShowId::patiencebar},
    {cust3PatienceBarFRect, ElementId::patienceBarOutline3, ShowId::patiencebar},
    {cust4PatienceBarFRect, ElementId::patienceBarOutline4, ShowId::patiencebar},
    {cust1PatienceBarFRect, ElementId::patienceBarFilling1, ShowId::patiencebar},
    {cust2PatienceBarFRect, ElementId::patienceBarFilling2, ShowId::patiencebar},
    {cust3PatienceBarFRect, ElementId::patienceBarFilling3, ShowId::patiencebar},
    {cust4PatienceBarFRect, ElementId::patienceBarFilling4, ShowId::patiencebar},
    {opArea, ElementId::undefined, ShowId::operating_area, false, true},
    {counterRect, ElementId::undefined, ShowId::counter_surface, false, true},
    {servedRamenFDst1, ElementId::servedRamenCus1, ShowId::bowl_with_ramen_plain},
    {servedRamenFDst2, ElementId::servedRamenCus2, ShowId::bowl_with_ramen_plain},
    {servedRamenFDst3, ElementId::servedRamenCus3, ShowId::bowl_with_ramen_plain},
    {servedRamenFDst4, ElementId::servedRamenCus4, ShowId::bowl_with_ramen_plain},
    {servedDrinkFDst1, ElementId::servedDrinkCus1, ShowId::softdrink_kola},
    {servedDrinkFDst2, ElementId::servedDrinkCus2, ShowId::softdrink_kola},
    {servedDrinkFDst3, ElementId::servedDrinkCus3, ShowId::softdrink_kola},
    {servedDrinkFDst4, ElementId::servedDrinkCus4, ShowId::softdrink_kola},
    {cust1OrderFRect, ElementId::order1, ShowId::orderPostIt},
    {cust2OrderFRect, ElementId::order2, ShowId::orderPostIt},
    {cust3OrderFRect, ElementId::order3, ShowId::orderPostIt},
    {cust4OrderFRect, ElementId::order4, ShowId::orderPostIt},
    {potToolFRect, ElementId::potSideBar, ShowId::empty_pot, true, true, true},
    {classicRamenFRect, ElementId::classicRamenSideBar, ShowId::classicRamen, true, true, true},
    {beefRamenFRect, ElementId::beefRamenSideBar, ShowId::beefRamen},
    {spicyRamenFRect, ElementId::spicyRamenSideBar, ShowId::spicyRamen},
    {seafoodRamenFRect, ElementId::seafoodRamenSideBar, ShowId::seafoodRamen},
    {sinkFRect, ElementId::sinkSideBar, ShowId::sink, true, true, true, SrcRatio{Sprite1x2::upper}},
    {binFRect, ElementId::binSideBar, ShowId::bin, true, true, true, SrcRatio{Sprite1x2::upper}},
    {bowlsFRect, ElementId::bowlsSideBar, ShowId::bowls, true, true, true},
    {chopsticksToolFRect, ElementId::chopsticksSideBar, ShowId::chopsticks2, true, true, true},
    {burnerFDst, ElementId::undefined, ShowId::burner, false, true}, /*
     {cookerFDst2, ElementId::undefined, ShowId::burner, false, true},
     {cookerFDst3, ElementId::undefined, ShowId::burner, false, true},
     {cookerFDst4, ElementId::undefined, ShowId::burner, false, true}, */
    {potFDst1, ElementId::cookingSlot1, ShowId::empty_pot, false, false, true},
    {potFDst2, ElementId::cookingSlot2, ShowId::empty_pot, false, false, true},
    {potFDst3, ElementId::cookingSlot3, ShowId::empty_pot, false, false, true},
    {potFDst4, ElementId::cookingSlot4, ShowId::empty_pot, false, false, true},
    {puffFDst1, ElementId::cookingPuff1, ShowId::puff},
    {puffFDst2, ElementId::cookingPuff2, ShowId::puff},
    {puffFDst3, ElementId::cookingPuff3, ShowId::puff},
    {puffFDst4, ElementId::cookingPuff4, ShowId::puff},
    {{cust1OrderFRect.x + orderRamenIndentX, cust1OrderFRect.y + orderRamenIndentY, orderRamenSize, orderRamenSize},
     ElementId::ordered_ramen_cus1,
     ShowId::classicRamen},
    {{cust2OrderFRect.x + orderRamenIndentX, cust2OrderFRect.y + orderRamenIndentY, orderRamenSize, orderRamenSize},
     ElementId::ordered_ramen_cus2,
     ShowId::classicRamen},
    {{cust3OrderFRect.x + orderRamenIndentX, cust3OrderFRect.y + orderRamenIndentY, orderRamenSize, orderRamenSize},
     ElementId::ordered_ramen_cus3,
     ShowId::classicRamen},
    {{cust4OrderFRect.x + orderRamenIndentX, cust4OrderFRect.y + orderRamenIndentY, orderRamenSize, orderRamenSize},
     ElementId::ordered_ramen_cus4,
     ShowId::classicRamen},
    {{cust1OrderFRect.x + orderLine2IndentX, cust1OrderFRect.y + 2.f * orderRamenIndentY, orderItemSize, orderItemSize},
     ElementId::ordered_drink_cus1,
     ShowId::softdrink_kola},
    {{cust2OrderFRect.x + orderLine2IndentX, cust2OrderFRect.y + 2.f * orderRamenIndentY, orderItemSize, orderItemSize},
     ElementId::ordered_drink_cus2,
     ShowId::softdrink_kola},
    {{cust3OrderFRect.x + orderLine2IndentX, cust3OrderFRect.y + 2.f * orderRamenIndentY, orderItemSize, orderItemSize},
     ElementId::ordered_drink_cus3,
     ShowId::softdrink_kola},
    {{cust4OrderFRect.x + orderLine2IndentX, cust4OrderFRect.y + 2.f * orderRamenIndentY, orderItemSize, orderItemSize},
     ElementId::ordered_drink_cus4,
     ShowId::softdrink_kola},
    {moneyFRect, ElementId::moneyCoin, ShowId::coins, false, true, false, SrcRatio{Sprite2x2::upperLeft}},
    {{money_x, money_y, 0.f, 0.f}, ElementId::moneyNumber, ShowId::moneyNumberText, false, true},
    {{400.f, 10.f, 200.f, 40.f},
     ElementId::ratingOutline,
     ShowId::star,
     false,
     true,
     false,
     SrcRatio{Sprite2x1::right}},
    {{400.f, 10.f, 200.f, 40.f},
     ElementId::ratingFilling,
     ShowId::star,
     false,
     true,
     false,
     SrcRatio{Sprite2x1::left, 0.f}}};

static Element overlayElems[] = {
    {{1500.f, 900.f, 160.f, 130.f}, ElementId::okayButton, ShowId::okayBtn, true, false},
    {{SCREEN_WIDTH * 0.5f - SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.5f, SCREEN_HEIGHT * 0.5f},
     ElementId::undefined,
     ShowId::newsOpen},
    {{SCREEN_WIDTH * 0.5f - SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.5f, SCREEN_HEIGHT * 0.5f},
     ElementId::undefined,
     ShowId::billPaper}};

std::span<Element> getActiveElements() noexcept {
    if (overlay) {
        return overlayElems;
    }
    return gamePlayElems;
}

Element& getElement(ElementId id) noexcept {
    auto elem = std::find_if(std::begin(gamePlayElems), std::end(gamePlayElems),
                             [&](const Element& e) { return e.elemId == id; });
    if (elem == std::end(gamePlayElems)) {
        return nullElemnt;
    }
    return *elem;
}

static uint8_t maxRating   = 20u;
static float averageRating = 0.f;

void levelUpMaxRating() noexcept {
    if (maxRating < 100u) {
        maxRating += 20u;
    }
}
// exponentially weighted moving average (EWMA) restaurantStars_today = (1-α)·prev + α·todayAverage, α controls
// responsiveness
void updateRating(int rating) noexcept {
    averageRating = 0.8f * averageRating + 0.2 * rating;
    Element& elem = getElement(ElementId::ratingFilling);
    elem.src      = SrcRatio{Sprite2x1::left, averageRating * 0.5f};
    elem.fpos.w   = 200.f * averageRating * 0.5f;
}

void activateNewsOpeningEvent() noexcept {
    static bool called = false;
    if (!called) {
        called                   = true;
        overlayElems[1u].visible = true;
    } else {
        overlayElems[2u].visible = true;
    }
}

void newsOpeningEvent(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    static auto start = tick;
    if (overlayElems[1u].visible) {
        if ((tick - start) <= 1s) {
            overlayElems[1u].ratio = std::chrono::duration<float, std::milli>(tick - start) / 1s;
            overlayElems[1u].angle = 360.f * std::chrono::duration<float, std::milli>(tick - start) / 1s;
        } else if ((tick - start) > 4s) {
            overlayElems[1u].visible = false;
            overlayElems[2u].visible = true;
        }
        return;
    }
    start = tick;
}

void billPaperEvent(std::chrono::milliseconds tick) noexcept {
    using namespace std::chrono_literals;
    static auto start = tick;
    if (overlayElems[2u].visible) {
        if ((tick - start) <= 1s) {
            overlayElems[2u].ratio = std::chrono::duration<float, std::milli>(tick - start) / 1s;
            overlayElems[2u].angle = 360.f * std::chrono::duration<float, std::milli>(tick - start) / 1s;
        } else if ((tick - start) > 4s) {
            overlayElems[0u].visible = true;
        }
        return;
    }

    start = tick;
}

void tickOverlay(std::chrono::milliseconds tick) noexcept {
    newsOpeningEvent(tick);
    billPaperEvent(tick);
}

void cycleStarts() noexcept {
    deactivateOverlay();
    unpause();
    overlayElems[0u].visible = false;
    overlayElems[2u].visible = false;
}
void cycleEnds() noexcept {
    activateOverlay();
    pause();
    activateNewsOpeningEvent();
}

void offerSoftdrinks() noexcept {
    std::for_each(std::begin(gamePlayElems), std::end(gamePlayElems), [](Element& el) {
        if (isSoftdrinkOption(el.elemId)) {
            el.visible   = true;
            el.clickable = true;
        }
    });
}

void dismissSoftdrinks() noexcept {
    std::for_each(std::begin(gamePlayElems), std::end(gamePlayElems), [](Element& el) {
        if (isSoftdrinkOption(el.elemId)) {
            el.visible   = false;
            el.clickable = false;
        }
    });
}

void showServed(ElementId cus, ShowId ramen, ShowId drink) noexcept {
    if (ramen != ShowId::lastImg) {
        getElement(servedRamenId(cus)).visible = true;
        getElement(servedRamenId(cus)).showId  = ramen;
    }
    if (drink != ShowId::lastImg) {
        getElement(servedDrinkId(cus)).visible = true;
        getElement(servedDrinkId(cus)).showId  = drink;
    }
}
void hideServed(ElementId cus) noexcept {
    getElement(servedDrinkId(cus)).visible = false;
    getElement(servedRamenId(cus)).visible = false;
}