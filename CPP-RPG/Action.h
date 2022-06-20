#pragma once
#include "Global.h"

template<class Sig>
struct Action {
    template<typename Functor>
    void operator+=(Functor&& f)
    {
        _funcs.emplace_back(std::forward<Functor>(f));
    }
    template<class... Args>
    void operator()(Args&&... args) const {
        for (auto& f : _funcs)
            f(args...);
    }
private:
    std::vector<std::function<Sig>> _funcs;
};
