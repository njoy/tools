// nanorange/views/counted.hpp
//
// Copyright (c) 2018 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NANORANGE_VIEWS_COUNTED_HPP_INCLUDED
#define NANORANGE_VIEWS_COUNTED_HPP_INCLUDED

#include "tools/std20/iterator/counted_iterator.hpp"
#include "tools/std20/views/subrange.hpp"

NANO_BEGIN_NAMESPACE

namespace views {

namespace detail {

struct counted_fn {
private:
    template <typename I>
    static constexpr auto impl(I i, iter_difference_t<I> n, ranges::detail::priority_tag<1>)
        noexcept(noexcept(ranges::subrange{i, i + n}))
        -> std::enable_if_t<random_access_iterator<I>, decltype(ranges::subrange{i, i + n})>
    {
        return ranges::subrange{i, i + n};
    }

    template <typename I>
    static constexpr auto impl(I i, iter_difference_t<I> n, ranges::detail::priority_tag<0>)
        noexcept(noexcept(ranges::subrange{
                ranges::make_counted_iterator(std::move(i), n),
                default_sentinel}))
        -> decltype(ranges::subrange{
            ranges::make_counted_iterator(std::move(i), n), default_sentinel})
    {
        return ranges::subrange{ranges::make_counted_iterator(std::move(i), n),
                                   default_sentinel};
    }

public:
    template <typename E, typename F, typename T = std::decay_t<E>>
    constexpr auto operator()(E&& e, F&& f) const
        noexcept(noexcept(impl(std::forward<E>(e),
                               static_cast<iter_difference_t<T>>(std::forward<F>(f)),
                               ranges::detail::priority_tag<1>{})))
        -> std::enable_if_t<
            input_or_output_iterator<T> &&
            convertible_to<F, iter_difference_t<T>>,
            decltype(impl(std::forward<E>(e),
                          static_cast<iter_difference_t<T>>(std::forward<F>(f)),
                          ranges::detail::priority_tag<1>{}))>
    {
        return impl(std::forward<E>(e),
                    static_cast<iter_difference_t<T>>(std::forward<F>(f)),
                    ranges::detail::priority_tag<1>{});
    }
};

} // namespace detail

NANO_INLINE_VAR(detail::counted_fn, counted)

} // namespace views

NANO_END_NAMESPACE

#endif
