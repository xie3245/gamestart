#include "mutex.h"

Mutex::Mutex() noexcept : m_handle(SDL_CreateMutex()) {}

bool Mutex::tryLock() noexcept { return SDL_TryLockMutex(m_handle); }

void Mutex::lock() noexcept { SDL_LockMutex(m_handle); }

void Mutex::unlock() noexcept { SDL_UnlockMutex(m_handle); }

Mutex::~Mutex() noexcept { SDL_RELEASE(m_handle); }

LockGuard::LockGuard(Mutex& mtx) noexcept : m_mtx(mtx) { mtx.lock(); }

LockGuard::~LockGuard() noexcept { m_mtx.unlock(); }