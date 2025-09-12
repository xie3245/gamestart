#pragma once

#include <SDL3/SDL_mutex.h>

class Mutex final
{
public:
    Mutex() noexcept;
    ~Mutex() noexcept;

    bool tryLock() noexcept;
    void lock() noexcept;
    void unlock() noexcept;

private:
    SDL_Mutex *m_handle;
};

class LockGuard final
{
public:
    LockGuard(Mutex &mtx) noexcept;
    ~LockGuard() noexcept;

private:
    Mutex &m_mtx;
};