#pragma once
#include <SDL3/SDL.h>
#include <algorithm>

bool isMouseButtonMovement(const SDL_Event& e) noexcept;

SDL_FRect enlarge(const SDL_FRect& orig, float ratio = 1.2f) noexcept;

constexpr int SCREEN_WIDTH  = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr SDL_FRect bgDst = {0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT};

constexpr float counterHeight   = SCREEN_HEIGHT * 0.4f;
constexpr SDL_FRect counterRect = {0, counterHeight, SCREEN_WIDTH, 0.12f * SCREEN_HEIGHT};

constexpr float cusSize      = SCREEN_WIDTH * 0.2f;
constexpr SDL_FRect custRect = {SCREEN_WIDTH * 0.1f, counterHeight - 0.8f * cusSize, cusSize, cusSize};

constexpr float columnX            = SCREEN_WIDTH * 0.85f;
constexpr float columnFirstY       = SCREEN_HEIGHT * 0.8f;
constexpr float columnItemSize     = std::min(SCREEN_WIDTH - columnX, std::min(SCREEN_HEIGHT - columnFirstY, 100.f));
constexpr float columnCenterX      = columnX + columnItemSize * 0.5f;
constexpr float columnCenterYFirst = columnFirstY + columnItemSize * 0.5f;

constexpr int columnItemDis       = 10;
constexpr float columnSecondItemY = columnFirstY - columnItemSize - columnItemDis;
constexpr float columnThirdItemY  = columnFirstY - 2 * (columnItemSize + columnItemDis);
constexpr float columnFourthItemY = columnFirstY - 3 * (columnItemSize + columnItemDis);
constexpr float columnFifthItemY  = columnFirstY - 4 * (columnItemSize + columnItemDis);

constexpr SDL_FRect pkgFRect = {columnX, columnFirstY, columnItemSize, columnItemSize};
constexpr SDL_Rect pkgRect{static_cast<int>(columnX), static_cast<int>(columnFirstY), static_cast<int>(columnItemSize),
                           static_cast<int>(columnItemSize)};

constexpr SDL_FRect sinkFRect = {columnX, columnSecondItemY, columnItemSize, columnItemSize};
constexpr SDL_Rect sinkRect   = {static_cast<int>(columnX), static_cast<int>(columnSecondItemY),
                                 static_cast<int>(columnItemSize), static_cast<int>(columnItemSize)};

constexpr SDL_FRect binFRect = {columnX, columnThirdItemY, columnItemSize, columnItemSize};
constexpr SDL_Rect binRect   = {static_cast<int>(columnX), static_cast<int>(columnThirdItemY),
                                static_cast<int>(columnItemSize), static_cast<int>(columnItemSize)};

constexpr SDL_FRect bowlsFRect = {columnX, columnFourthItemY, columnItemSize, columnItemSize};
constexpr SDL_Rect bowlsRect   = {static_cast<int>(columnX), static_cast<int>(columnFourthItemY),
                                  static_cast<int>(columnItemSize), static_cast<int>(columnItemSize)};

constexpr SDL_FRect potToolFRect = {columnX, columnFifthItemY, columnItemSize, columnItemSize};
constexpr SDL_Rect potToolRect   = {static_cast<int>(columnX), static_cast<int>(columnFifthItemY),
                                    static_cast<int>(columnItemSize), static_cast<int>(columnItemSize)};

constexpr float burnerX       = SCREEN_WIDTH * 0.3f;
constexpr float burnerY       = SCREEN_HEIGHT * 0.6f;
constexpr float burnerSize    = 250.f;
constexpr SDL_FRect burnerDst = {burnerX, burnerY, burnerSize, burnerSize};

constexpr SDL_FRect potFDst = {burnerX + burnerSize * 0.12f, burnerY - burnerSize * 0.1f, 128, 128};
constexpr SDL_Rect potDst   = {static_cast<int>(burnerX + burnerSize * 0.12f),
                               static_cast<int>(burnerY - burnerSize * 0.1f), 128, 128};
