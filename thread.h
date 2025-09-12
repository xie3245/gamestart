#pragma once
#include <SDL3/SDL_thread.h>
#include <chrono>
#include <utility>
#include <SDL3/SDL_timer.h>

namespace this_thread
{
    void sleep(std::chrono::milliseconds duration) noexcept;
}

template <typename Func>
class Thread;

template <typename R, typename... Args>
class Thread<R(Args...)> final
{
    using StubType = R (*)(void *, Args &&...);

public:
    template <R (*Func)(Args...)>
    static Thread fromFunction(const char *name)
    {
        return {nullptr, functionStub<Func>, name};
    }

    template <class T, R (T::*Method)(Args...)>
    static Thread fromMethod(T *obj, const char *name)
    {
        return Thread(obj, methodStub<T, Method>, name);
    }

    void detach() noexcept
    {
        SDL_DetachThread(m_handle);
    }
    
private:
    template <R (*Func)(Args...)>
    static R functionStub(void *, Args &&...args)
    {
        return (*Func)(std::forward<Args>(args)...);
    }

    template <class T, R (T::*Method)(Args...)>
    static R methodStub(void *obj, Args &&...args)
    {
        return (static_cast<T *>(obj)->*Method)(std::forward<Args>(args)...);
    }

    Thread(void *obj, StubType func, const char *name) : m_object(obj), m_func(func), m_handle(SDL_CreateThread(m_func, name, m_object))
    {
    }

    void *m_object;
    StubType m_func;
    SDL_Thread *m_handle;
};