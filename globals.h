#pragma once
#include <span>
#include <chrono>
#include "elementId.h"
#include "showId.h"

struct Element;

bool attachToMouse(ElementId whosAsking, ShowId id) noexcept;
void clearMouseItem() noexcept;
ShowId mouseItem() noexcept;

void gainMoney(uint16_t diff) noexcept;
void loseMoney(uint16_t diff) noexcept;
void updateRating(float waitedR, float orderMatchR) noexcept;

std::chrono::milliseconds getGameClk() noexcept;
bool isPaused() noexcept;
void pause() noexcept;
void unpause() noexcept;
void togglePause() noexcept;

std::span<Element> getActiveElements() noexcept;
Element& getElement(ElementId id) noexcept;

std::string getText(ShowId id) noexcept;

bool softdrinkUnlocked() noexcept;
void offerSoftdrinks() noexcept;
void dismissSoftdrinks() noexcept;

void showServed(ElementId cus, ShowId ramen, ShowId drink) noexcept;
void hideServed(ElementId cus) noexcept;

void triggerSpecialEvents() noexcept;

void updateNextCustomerTime(ElementId cusId, std::chrono::milliseconds duration) noexcept;