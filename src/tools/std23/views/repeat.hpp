#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_REPEAT
#define NJOY_TOOLS_STD23_RANGES_VIEWS_REPEAT

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/iterator/unreachable.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std20/views/subrange.hpp"
#include "tools/std20/views/take.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

/**
 *  @brief A range factory that generates a sequence of elements by repeatedly
 *         producing the same value. Can be either bounded or unbounded (infinite).
 *
 *  See https://en.cppreference.com/w/cpp/ranges/repeat_view
 */
template < typename Type, typename Bound = std20::unreachable_sentinel_t >
struct repeat_view : std20::ranges::view_interface< repeat_view< T, Bound > > {

  static_assert( std20::same_as< Type, std::remove_cv_t< Type > > );
  static_assert( ( std::is_signed_integer< Type > ||
                   ( std::is_integer< Type > && std20::weakly_incrementable< Type > ) ) ||
                 ( std20::same_as< Bound, std20::unreachable_sentinel_t > ) );

private:

  movable_box< Type > value_;
  Bound bound_ = Bound();

  struct iterator;

public:

  repeat_view() = default;

  repeat_view( const Type&, )

  repeat_view( Type&&, )
};

template < typename R >
repeat_view( R&&, std20::ranges::range_difference_t< R > ) -> repeat_view< std20::ranges::all_view< R > >;

} // namespace ranges
} // namespace std23

namespace std20 {
inline namespace ranges {

template <typename R>
inline constexpr bool enable_borrowed_range<std23::ranges::repeat_view<R>> = forward_range<R> && enable_borrowed_range<R>;

} // namespace ranges
} // namespace std20

namespace std23 {
inline namespace ranges {

namespace detail {

struct repeat_view_fn {

    template < typename E, typename F >
    constexpr auto operator()( E&& e, F&& f ) const
    -> decltype( repeat_view{ std::forward< E >( e ), std::forward< F >( f ) } )
    {
        return repeat_view{ std::forward< E >( e ), std::forward< F >( f ) };
    }

    template < typename C >
    constexpr auto operator()( C c ) const
    {
        return std20::ranges::detail::rao_proxy{ [c = std::move(c)] ( auto&& r ) mutable
#ifndef NANO_MSVC_LAMBDA_PIPE_WORKAROUND
            -> decltype( repeat_view{ std::forward< decltype( r ) >( r ), std::declval< C&& >() } )
#endif
        {
            return repeat_view{ std::forward< decltype( r ) >( r ), std::move( c ) };
        }};
    }

};

}

namespace views {

NANO_INLINE_VAR(ranges::detail::repeat_view_fn, chunk)

}

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
