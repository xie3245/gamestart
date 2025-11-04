#pragma once
#include <span>
#include <chrono>
#include "elementId.h"
#include "showId.h"

class Element;

bool attachToMouse(ElementId whosAsking, ShowId id) noexcept;
void clearMouseItem() noexcept;
ShowId mouseItem() noexcept;

void gainMoney(uint16_t diff) noexcept;
void loseMoney(uint16_t diff) noexcept;
void updateRating(int rating) noexcept;

std::chrono::milliseconds getGameClk() noexcept;
bool isPaused() noexcept;
void pause() noexcept;
void unpause() noexcept;
void togglePause() noexcept;

bool isOverlay() noexcept;
void activateOverlay() noexcept;
void deactivateOverlay() noexcept;
void toggleOverlay() noexcept;
void tickOverlay(std::chrono::milliseconds tick) noexcept;

std::span<Element> getActiveElements() noexcept;
Element& getElement(ElementId id) noexcept;

std::string getText(ShowId id) noexcept;

void cycleStarts() noexcept;
void cycleEnds() noexcept;