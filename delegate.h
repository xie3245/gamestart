#pragma once

template <class T>
class Delegate {};

template <typename R, typename... Args>
class Delegate<R(Args...)> final {
    using StubType = R (*)(void*, Args&&...);

public:
    template <R (*Func)(Args...)>
    static Delegate fromFunction() {
        return Delegate(nullptr, functionStub<Func>);
    }

    template <class T, R (T::*Method)(Args...)>
    static Delegate fromMethod(T* obj) {
        return Delegate(obj, methodStub<T, Method>);
    }

    template <class T, R (T::*Method)(Args...) const>
    static Delegate fromMethod(const T* obj) {
        return Delegate(obj, constMethodStub<T, Method>);
    }

    R operator()(Args... args) { return m_func(m_obj, std::forward<Args>(args)...); }

private:
    template <R (*Func)(Args...)>
    static R functionStub(void*, Args&&... args) {
        return (*Func)(std::forward<Args>(args)...);
    }

    template <class T, R (T::*Method)(Args...)>
    static R methodStub(void* obj, Args&&... args) {
        return (static_cast<T*>(obj)->*Method)(std::forward<Args>(args)...);
    }

    template <class T, R (T::* const Method)(Args...) const>
    static R constMethodStub(void* obj, Args&&... args) {
        return (static_cast<T*>(obj)->*Method)(std::forward<Args>(args)...);
    }

    Delegate(void* obj, StubType func) : m_obj(obj), m_func(func) {}

    void* m_obj;
    StubType m_func;
};