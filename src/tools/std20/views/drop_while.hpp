// nanorange/views/drop_while.hpp
//
// Copyright (c) 2019 Tristan Brindle (tcbrindle at gmail dot com)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NANORANGE_VIEWS_DROP_WHILE_HPP_INCLUDED
#define NANORANGE_VIEWS_DROP_WHILE_HPP_INCLUDED

#include "tools/std20/algorithm/find.hpp"
#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/detail/views/semiregular_box.hpp"
#include "tools/std23/detail/views/nonpropagating_box.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std20/views/interface.hpp"

NANO_BEGIN_NAMESPACE

template <typename R, typename Pred>
struct drop_while_view : view_interface<drop_while_view<R, Pred>> {

    static_assert(view<R>);
    static_assert(input_range<R>);
    static_assert(std::is_object_v<Pred>);
    static_assert(indirect_unary_predicate<const Pred, iterator_t<R>>);

    drop_while_view() = default;

    constexpr drop_while_view(R base, Pred pred)
        : base_(std::move(base)),
          pred_(std::move(pred))
    {}

    constexpr R base() const { return base_; }

    constexpr const Pred& pred() const { return *pred_; }

    constexpr auto begin()
    {
        if (!cached_.has_value()) {

            cached_.emplace( ranges::find_if_not( base_, pred() ) );
        }

        return *cached_;
    }

    constexpr auto end()
    {
        return ranges::end(base_);
    }

private:
    R base_;
    detail::semiregular_box<Pred> pred_;
    std23::ranges::detail::nonpropagating_box<iterator_t<R>> cached_;
};

template <typename R, typename Pred>
drop_while_view(R&& r, Pred pred) -> drop_while_view<all_view<R>, Pred>;

template <typename R, typename Pred>
inline constexpr bool enable_borrowed_range<drop_while_view<R, Pred>> = enable_borrowed_range<R>;

namespace detail {

struct drop_while_view_fn {

    template <typename E, typename F>
    constexpr auto operator()(E&& e, F&& f) const
        -> decltype(drop_while_view{std::forward<E>(e), std::forward<F>(f)})
    {
        return drop_while_view{std::forward<E>(e), std::forward<F>(f)};
    }

    template <typename Pred>
    constexpr auto operator()(Pred&& pred) const
    {
        return detail::rao_proxy{[p = std::forward<Pred>(pred)](auto&& r) mutable
#ifndef NANO_MSVC_LAMBDA_PIPE_WORKAROUND
            -> decltype(drop_while_view{std::forward<decltype(r)>(r), std::declval<Pred&&>()})
#endif
        {
            return drop_while_view{std::forward<decltype(r)>(r), std::move(p)};
        }};
    }

};

} // namespace detail

namespace views {

NANO_INLINE_VAR(ranges::detail::drop_while_view_fn, drop_while)

}

NANO_END_NAMESPACE

#endif
