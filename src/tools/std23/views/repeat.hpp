#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_REPEAT
#define NJOY_TOOLS_STD23_RANGES_VIEWS_REPEAT

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/iterator/unreachable.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std20/views/subrange.hpp"
#include "tools/std20/views/take.hpp"
#include "tools/std20/detail/views/semiregular_box.hpp"
#include "tools/std20/detail/iterator/concepts.hpp"
#include "tools/std20/views/iota.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

template <typename Type, typename = void>
struct repeat_view_iterator_difference {
    using type = std20::detail::iota_diff_t<Type>;
};

template <typename Type>
struct repeat_view_iterator_difference<Type, typename std::enable_if<std20::detail::is_signed_integer_like<Type>>::type> 
{
    using type = Type;
};

template <typename Type>
using repeat_view_iterator_difference_t = typename repeat_view_iterator_difference<Type>::type;

/**
 *  @brief A range factory that generates a sequence of elements by repeatedly
 *         producing the same value. Can be either bounded or unbounded (infinite).
 *
 *  See https://en.cppreference.com/w/cpp/ranges/repeat_view
 */

template < typename Type, typename Bound = std20::unreachable_sentinel_t >
struct repeat_view : public std20::ranges::view_interface< repeat_view< Type, Bound > > {
    // The Type must be a non-const object
    static_assert( std::is_object_v<Type> && std20::same_as< Type, std::remove_cv_t< Type > > );

    // The Bound has to be integer like of unbound
    static_assert( ( std20::detail::is_signed_integer_like< Bound > || 
                 ( std20::detail::is_integer_like< Bound > && std20::weakly_incrementable< Bound > ) ) ||
                 ( std20::same_as< Bound, std20::unreachable_sentinel_t > ) );

private:

    std20::detail::semiregular_box< Type > value_;
    Bound bound_ = Bound();

    struct iterator{
    friend class repeat_view;
    private:
        using IndexT = std::conditional_t<std20::same_as<Bound, std20::unreachable_sentinel_t>, ptrdiff_t, Bound>;
        const Type* ivalue_ = nullptr;
        IndexT current_  = IndexT();

    public:
          
        constexpr explicit iterator(const Type* value, IndexT bound_sentinel = IndexT())
            : ivalue_(value), current_(bound_sentinel) {}

        using iterator_concept  = std20::random_access_iterator_tag;
          using iterator_category = std20::random_access_iterator_tag;
          using value_type        = Type;
          using difference_type   = repeat_view_iterator_difference_t<IndexT>;

          iterator() = default;

          constexpr const Type& operator*() const noexcept { return *ivalue_; }

          constexpr iterator& operator++() {
              ++current_;
              return *this;
          }

          constexpr iterator operator++(int) {
              auto tmp = *this;
              ++*this;
              return tmp;
          }

          constexpr iterator& operator--() {
              --current_;
              return *this;
          }

          constexpr iterator operator--(int) {
              auto tmp = *this;
              --*this;
              return tmp;
          }

          constexpr iterator& operator+=(difference_type n) {
              current_ += n;
              return *this;
          }

          constexpr iterator& operator-=(difference_type n) {
              current_ -= n;
              return *this;
          }

          constexpr const Type& operator[](difference_type n) const noexcept { return *(*this + n); }

          friend constexpr bool operator==(const iterator& left, const iterator& right) {
              return left.current_ == right.current_;
          }

          friend constexpr bool operator!=(const iterator& left, const iterator& right) {
              return !(left.current_ == right.current_);
          }

          friend constexpr auto operator> (const iterator& left, const iterator& right) {
              return left.current_ > right.current_;
          }
          friend constexpr auto operator< (const iterator& left, const iterator& right) {
              return right.current_ > left.current_;
          }

          friend constexpr auto operator>= (const iterator& left, const iterator& right) {
              return left.current_ >= right.current_;
          }
          friend constexpr auto operator<= (const iterator& left, const iterator& right) {
              return left.current_ <= right.current_;
          }


          friend constexpr iterator operator+(iterator i, difference_type n) {
              i += n;
              return i;
          }

          friend constexpr iterator operator+(difference_type n, iterator i) {
              i += n;
              return i;
          }

          friend constexpr iterator operator-(iterator i, difference_type n) {
              i -= n;
              return i;
          }

          friend constexpr difference_type operator-(const iterator& left, const iterator& right) {
              return static_cast<difference_type>(left.current_) - static_cast<difference_type>(right.current_);
          }

          
    };

public:

    repeat_view() = default;

    constexpr explicit repeat_view( const Type& value, Bound bound_sentinel = Bound())
        : value_(std::in_place, value), bound_(bound_sentinel) {
        }

    constexpr explicit repeat_view(Type&& value, Bound bound_sentinel = Bound())
        : value_(std::in_place, std::move(value)), bound_(bound_sentinel) {
    }

    template <class... _TpArgs, class... _BoundArgs, 
          std::enable_if_t<std20::constructible_from<Type, _TpArgs...> && std20::constructible_from<Bound, _BoundArgs...>, bool> = true>
    constexpr explicit repeat_view( std::piecewise_construct_t, std::tuple<_TpArgs...> __value_args, 
                    std::tuple<_BoundArgs...> __bound_args = std::tuple<>{}) 
        : value_(std::in_place, std::make_from_tuple<Type>(std::move(__value_args))),
        bound_(std::make_from_tuple<Bound>(std::move(__bound_args))) {
    }

    constexpr iterator begin() const { return iterator(std::addressof(*value_)); }

    template<typename T=Bound, std::enable_if_t<!std20::same_as<T, std20::unreachable_sentinel_t>, bool> = true> 
    constexpr iterator end() const
    {
        return iterator(std::addressof(*value_), bound_);
    }

    template<typename T=Bound, std::enable_if_t<std20::same_as<T, std20::unreachable_sentinel_t>, bool> = true> 
    constexpr std20::unreachable_sentinel_t end() const noexcept 
    {
        return std20::unreachable_sentinel; 
    }

    template<typename T=Bound, std::enable_if_t<!std20::same_as<T, std20::unreachable_sentinel_t>, bool> = true> 
    constexpr auto size() const
    {
	return std::make_unsigned_t<decltype(bound_)>(bound_);
    }
};

template < typename Type >
repeat_view( Type&&, std20::ranges::range_difference_t< Type > ) -> repeat_view< std20::ranges::all_view< Type > >;

} // namespace ranges
} // namespace std23

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

    template < typename E >
    constexpr auto operator()( E&& e ) const
    -> decltype( repeat_view{ std::forward< E >( e ) } )
    {
        return repeat_view{ std::forward< E >( e ) };
    }

};

}

namespace views {
NANO_INLINE_VAR(ranges::detail::repeat_view_fn, repeat)
}
} // namespace ranges
} // namespace std23

} // namespace tools
} // namespace njoy

#endif
