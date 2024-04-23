// nanorange/algorithm/min.hpp
//
// Copyright (c) 2018 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NANORANGE_ALGORITHM_MIN_HPP_INCLUDED
#define NANORANGE_ALGORITHM_MIN_HPP_INCLUDED

#include "tools/std20/ranges.hpp"

NANO_BEGIN_NAMESPACE

namespace detail {

struct min_fn {
private:
    template <typename Rng, typename Comp, typename Proj>
    static constexpr iter_value_t<iterator_t<Rng>>
    impl(Rng&& rng, Comp& comp, Proj& proj)
    {
        auto first = ranges::begin(rng);
        const auto last = ranges::end(rng);

        // Empty ranges not allowed
        auto result = *first;

        while(++first != last) {
            auto&& val = *first;
            if (ranges::invoke(comp, ranges::invoke(proj, val),
                               ranges::invoke(proj, result))) {
                result = std::forward<decltype(val)>(val);
            }
        }

        return result;
    }

public:
    template <typename T, typename Comp = ranges::less, typename Proj = identity>
    constexpr std::enable_if_t<
        indirect_strict_weak_order<Comp, projected<const T*, Proj>>,
        const T&>
    operator()(const T& a, const T& b, Comp comp = Comp{}, Proj proj = Proj{}) const
    {
        return ranges::invoke(comp, ranges::invoke(proj, b),
                              ranges::invoke(proj, a)) ? b : a;
    }

    template <typename T, typename Comp = ranges::less, typename Proj = identity>
    constexpr std::enable_if_t<
        copyable<T> &&
            indirect_strict_weak_order<Comp, projected<const T*, Proj>>,
        T>
    operator()(std::initializer_list<T> rng, Comp comp = Comp{},
               Proj proj = Proj{}) const
    {
        return min_fn::impl(rng, comp, proj);
    }

    template <typename Rng, typename Comp = ranges::less, typename Proj = identity>
    constexpr std::enable_if_t<
        input_range<Rng> && copyable<iter_value_t<iterator_t<Rng>>> &&
            indirect_strict_weak_order<Comp, projected<iterator_t<Rng>, Proj>>,
        range_value_t<Rng>>
    operator()(Rng&& rng, Comp comp = Comp{}, Proj proj = Proj{}) const
    {
        return min_fn::impl(std::forward<Rng>(rng), comp, proj);
    }
};

}

NANO_INLINE_VAR(detail::min_fn, min)

NANO_END_NAMESPACE

#endif
