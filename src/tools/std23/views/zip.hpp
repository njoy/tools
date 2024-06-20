#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_ZIP
#define NJOY_TOOLS_STD23_RANGES_VIEWS_ZIP

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

template < typename... Rs >
inline constexpr bool zip_is_common =
    ( sizeof...( Rs ) == 1 && ( std20::ranges::common_range< Rs > && ...)) ||
    ( ! ( std20::ranges::bidirectional_range< Rs > && ...) && ( std20::ranges::common_range< Rs > && ...) ) ||
    ( ( std20::ranges::random_access_range< Rs > && ...) && ( std20::ranges::sized_range< Rs > && ... ) );

template < typename T, typename U >
auto tuple_or_pair_test() -> std::pair< T, U >;

template < typename... T >
auto tuple_or_pair_test() -> std::enable_if_t< ( sizeof...( T ) != 2 ), std::tuple< T... > >;

template < typename... T >
using tuple_or_pair = decltype( tuple_or_pair_test< T...>() );

template < typename Function, typename Tuple >
constexpr auto tuple_transform( Function&& f, Tuple&& tuple ) {

  return std::apply(
           [&] ( auto&&... elements ) {

             return tuple_or_pair<
                      std::invoke_result_t< Function&, decltype(elements) >... >( std::invoke( f, std::forward< decltype(elements) >( elements ) )... );
           },
           std::forward< Tuple >( tuple ) );
}

template < typename Function, typename Tuple >
constexpr void tuple_for_each( Function&& f, Tuple&& tuple ) {

  std::apply(
      [&] ( auto&&... elements ) {

        (static_cast<void>(std::invoke( f, std::forward< decltype(elements) >(elements))), ...);
      },
      std::forward< Tuple >(tuple));
}

template < typename Function, typename LeftTuple, typename RightTuple, std::size_t... Indices >
constexpr tuple_or_pair< std20::invoke_result_t< Function&,
                                                 typename std::tuple_element< Indices, std20::remove_cvref_t< LeftTuple > >::type,
                                                 typename std::tuple_element< Indices, std20::remove_cvref_t< RightTuple > >::type >... >
tuple_zip_transform( Function&& f, LeftTuple&& left, RightTuple&& right, std::index_sequence< Indices... > ) {

  return { std::invoke( f,
                        std::get< Indices >( std::forward<LeftTuple>(left)),
                        std::get< Indices >( std::forward<RightTuple>(right)))...};
}

template < typename Function, typename LeftTuple, typename RightTuple >
constexpr auto tuple_zip_transform( Function&& f, LeftTuple&& left, RightTuple&& right) {
  return tuple_zip_transform(
             f,
             std::forward< LeftTuple >( left ),
             std::forward< RightTuple >( right ),
             std::make_index_sequence< std::tuple_size< std20::remove_cvref_t< LeftTuple > >::value>() );
}

template < bool Const, typename T >
using maybe_const = std20::ranges::detail::conditional_t< Const, const T, T >;

template < bool Const, typename... Rs >
inline constexpr bool zip_all_forward = (

  std20::ranges::forward_range< maybe_const< Const, Rs > > && ...
);

template < bool Const, typename... Rs >
inline constexpr bool zip_all_bidirectional = (

  std20::ranges::bidirectional_range< std20::ranges::detail::conditional_t< Const, const Rs, Rs > > && ...
);

template < bool Const, typename... Rs >
inline constexpr bool zip_all_random_access = (

  std20::ranges::random_access_range< std20::ranges::detail::conditional_t< Const, const Rs, Rs > > && ...
);

template < typename LeftTuple, typename RightTuple >
constexpr bool tuple_any_equals( const LeftTuple& left, const RightTuple& right ) {

  const auto equals = tuple_zip_transform( std::equal_to<>(), left, right );
  return std::apply( [] ( auto... bools )
                        { return ( bools || ... ); },
                     equals );
}

template < bool Const, typename... Rs >
inline constexpr bool zip_all_simple = (

  std20::ranges::detail::simple_view< maybe_const< Const, Rs > > && ...
);

template < bool Const, typename... Rs >
inline constexpr bool zip_all_range = (

  std20::ranges::range< maybe_const< Const, Rs > > && ...
);

template < bool Const, typename... Rs >
inline constexpr bool zip_all_sized = (

  std20::ranges::sized_range< maybe_const< Const, Rs > > && ...
);

// abs in cstdlib is not constexpr
template < typename T >
constexpr T abs( T t ) { return t < 0 ? -t : t; }

struct zip_view_iterator_access {

  template < typename Iter >
  static constexpr decltype(auto) get_underlying( Iter& iter ) noexcept {

    return iter.current_;
  }
};
/**
 *  @brief A range adaptor that takes one or more views, and produces a view
 *         whose element is a tuple-like value consisting of the corresponding
 *         elements of all views
 *
 *  See https://en.cppreference.com/w/cpp/ranges/zip_view
 */
template < typename... Rs >
struct zip_view : std20::ranges::view_interface< zip_view< Rs... > > {

  static_assert( ( std20::ranges::view< Rs > && ... ) );
  static_assert( sizeof...( Rs ) > 0 );

private:

  std::tuple< Rs... > views_;

  template < bool Const >
  struct sentinel;

  template < bool Const >
  struct iterator{

  private:

    using Iterators = tuple_or_pair< std20::ranges::iterator_t< maybe_const< Const, Rs > >... >;
    Iterators current_;

    constexpr explicit iterator( Iterators current ) : current_( std::move( current ) ) {}

    template < bool >
    friend class zip_view< Rs...>::sentinel;

    friend class zip_view< Rs... >;

    friend zip_view_iterator_access;

  public:

    using value_type        = tuple_or_pair< std20::ranges::range_value_t< maybe_const< Const, Rs > >... >;
    using difference_type   = std::common_type_t< std20::ranges::range_difference_t< maybe_const< Const, Rs > >... >;
    using iterator_category = std::conditional_t<
                                  zip_all_random_access< Const, Rs... >,
                                  std20::random_access_iterator_tag,
                                  std::conditional_t<
                                      zip_all_bidirectional< Const, Rs... >,
                                      std20::bidirectional_iterator_tag,
                                      std::conditional_t<
                                          zip_all_forward< Const, Rs... >,
                                          std20::forward_iterator_tag,
                                          std20::input_iterator_tag > > >;

    iterator() = default;

    template < bool C = Const,
               typename = std::enable_if_t<
                 C &&
                 ( std20::convertible_to<
                       std20::ranges::iterator_t< Rs >,
                       std20::ranges::iterator_t< maybe_const< C, Rs > > > && ... ) > >
    constexpr iterator( iterator< ! Const > iter ) : current_( std::move( iter.current_ ) ) {}

    constexpr decltype(auto) operator*() const {

      return tuple_transform( [] ( auto& iter ) -> decltype(auto)
                                 { return *iter; },
                              this->current_ );
    }

    constexpr iterator& operator++() {

      tuple_for_each( []( auto& iter ) { ++iter; }, this->current_ );
      return *this;
    }

    template < bool C = Const >
    constexpr auto operator++(int)
    -> std::enable_if_t< zip_all_forward< C, Rs... >, iterator > {

      auto temp = *this;
      ++*this;
      return temp;
    }

    template < bool C = Const >
    constexpr auto operator--()
    -> std::enable_if_t< zip_all_bidirectional< C, Rs... >, iterator& > {

      tuple_for_each( [] ( auto& iter ) { --iter; }, this->current_);
      return *this;
    }

    template < bool C = Const >
    constexpr auto operator--(int)
    -> std::enable_if_t< zip_all_bidirectional< C, Rs... >, iterator > {

      auto temp = *this;
      --*this;
      return temp;
    }

    template < bool C = Const >
    constexpr auto operator+=( difference_type n )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, iterator& > {

      tuple_for_each( [&] ( auto& iter )
                          { iter += std20::ranges::iter_difference_t< std::decay_t< decltype( iter ) > >( n ); },
                      this->current_ );
      return *this;
    }

    template < bool C = Const >
    constexpr auto operator-=( difference_type n )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, iterator& > {

      return *this += -n;
    }

    template < bool C = Const, typename = std::enable_if_t< zip_all_random_access< C, Rs... > > >
    constexpr decltype(auto) operator[]( difference_type n ) const {

      return tuple_transform( [&] ( auto& iter ) -> decltype(auto)
                                  { return iter[ std20::ranges::iter_difference_t< std::decay_t< decltype( iter ) > >( n ) ]; },
                              this->current_ );
    }

    template < bool C = Const >
    friend constexpr auto operator==( const iterator& left, const iterator& right )
    -> std::enable_if_t< ( std20::equality_comparable< std20::ranges::iterator_t< maybe_const< C, Rs > > > && ... ), bool > {

      if constexpr ( zip_all_bidirectional< Const, Rs... > ) {

        return left.current_ == right.current_;
      }
      else {

        return tuple_any_equals( left.current_, right.current_ );
      }
    }

    template < bool C = Const >
    friend constexpr auto operator!=( const iterator& left, const iterator& right )
    -> std::enable_if_t< ( std20::equality_comparable< std20::ranges::iterator_t< maybe_const< C, Rs > > > && ... ), bool > {

      return ! ( left == right );
    }

    template < bool C = Const >
    friend constexpr auto operator<( const iterator& left, const iterator& right )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, bool > {

      return left.current_ < right.current_;
    }

    template < bool C = Const >
    friend constexpr auto operator>( const iterator& left, const iterator& right )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, bool > {

      return left < right;
    }

    template < bool C = Const >
    friend constexpr auto operator<=( const iterator& left, const iterator& right )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, bool > {

      return ! ( right < left );
    }

    template < bool C = Const >
    friend constexpr auto operator>=( const iterator& left, const iterator& right )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, bool > {

      return ! ( left < right );
    }

    template < bool C = Const >
    friend constexpr auto operator+( const iterator& left, const difference_type n )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, iterator > {

      return iterator{ left } += n;
    }

    template < bool C = Const >
    friend constexpr auto operator+( const difference_type n, const iterator& right )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, iterator > {

      return right + n;
    }

    template < bool C = Const >
    friend constexpr auto operator-( const iterator& left, const difference_type n )
    -> std::enable_if_t< zip_all_random_access< C, Rs... >, iterator > {

      return iterator{ left } -= n;
    }

    template < bool C = Const >
    friend constexpr auto operator-( const iterator& left, const iterator& right )
    -> std::enable_if_t< ( std20::ranges::sized_sentinel_for< std20::ranges::iterator_t< maybe_const< C, Rs > >,
                                                              std20::ranges::iterator_t< maybe_const< C, Rs > > > && ...),
                         difference_type > {

      const auto diffs = tuple_zip_transform( std::minus<>(), left.current_, right.current_ );
      return std::apply(
                 [] ( auto... differences ) {

                   return std20::ranges::min( { difference_type( differences )... },
                                              [] ( auto a, auto b ) { return ranges::abs( a ) < ranges::abs( b ); } );
                 },
                 diffs );
    }

    friend constexpr auto iter_move( const iterator& iter ) {

      return tuple_transform( std20::ranges::iter_move, iter.current_);
    }

    template < bool C = Const, typename = std::enable_if_t< ( std20::indirectly_swappable< std20::ranges::iterator_t< maybe_const< C, Rs > > > && ...) > >
    friend constexpr void iter_swap( const iterator& left, const iterator& right ) {

      tuple_zip_for_each( std20::ranges::iter_swap, left.current_, right.current_ );
    }
  };

  template < bool Const >
  struct sentinel {

  private:

    using Sentinels = tuple_or_pair< std20::ranges::sentinel_t< maybe_const< Const, Rs > >... >;
    Sentinels end_;

    constexpr explicit sentinel( Sentinels end ) : end_( std::move( end ) ) {}

    template < bool >
    friend class zip_view< Rs...>::iterator;

    friend class zip_view< Rs... >;

  public:

    sentinel() = default;

    template < bool C = Const,
               typename = std::enable_if_t<
                 C &&
                 ( std20::convertible_to<
                       std20::ranges::sentinel_t< Rs >,
                       std20::ranges::sentinel_t< maybe_const< C, Rs > > > && ... ), int > >
    constexpr sentinel( sentinel< ! C > iter ) : end_( std::move( iter.end_ ) ) {}

    template < bool Other >
    friend constexpr auto operator==( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< ( std20::ranges::sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ), bool > {

      return tuple_any_equals( zip_view_iterator_access::get_underlying( left ), right.end_ );
    }

    template < bool Other >
    friend constexpr auto operator==( const sentinel& left, const iterator< Other >& right )
    -> std::enable_if_t< ( std20::ranges::sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ), bool > {

      return right == left;
    }

    template < bool Other >
    friend constexpr auto operator!=( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< ( std20::ranges::sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ), bool > {

      return ! ( left == right );
    }

    template < bool Other >
    friend constexpr auto operator!=( const sentinel& left, const iterator< Other >& right )
    -> std::enable_if_t< ( std20::ranges::sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ), bool > {

      return ! ( left == right );
    }

    template < bool Other >
    friend constexpr auto operator-( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< ( std20::ranges::sized_sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ),
                         std::common_type_t< std20::ranges::range_difference_t< maybe_const< Other, Rs > >... > > {

      const auto diffs = tuple_zip_transform( std::minus<>(), zip_view_iterator_access::get_underlying( left ), right.end_ );
      return std::apply(
                 [] ( auto... differences ) {

                   return std20::ranges::min( { difference_type( differences )... },
                                              [] ( auto a, auto b ) { return ranges::abs( a ) < ranges::abs( b ); } );
                 },
                 diffs );
    }

    template < bool Other >
    friend constexpr auto operator-( const sentinel& left, const iterator< Other >& right)
    -> std::enable_if_t< ( std20::ranges::sized_sentinel_for<
                               std20::ranges::sentinel_t< maybe_const< Const, Rs > >,
                               std20::ranges::iterator_t< maybe_const< Other, Rs > > > && ... ),
                         std::common_type_t< std20::ranges::range_difference_t< maybe_const< Other, Rs > >... > > {

      return -( right - left );
    }

  };

public:

  zip_view() = default;

  constexpr explicit zip_view( Rs... views ) : views_( std::move( views )... ) {}

  template < bool Const = false >
  constexpr auto begin()
  -> std::enable_if_t< ! zip_all_simple< Const, Rs... >, iterator< false > > {

    return iterator< false >( tuple_transform( std20::ranges::begin, this->views_ ) );
  }

  template < bool Const = true >
  constexpr auto begin() const
  -> std::enable_if_t< zip_all_range< Const, Rs... >, iterator< true > > {

    return iterator< true >( tuple_transform( std20::ranges::begin, this->views_ ) );
  }

  template < bool Const = false >
  constexpr auto end()
  -> std::enable_if_t< ! zip_all_simple< Const, Rs... > && zip_is_common< Rs... >, iterator< false > >  {

    if constexpr ( ( std20::ranges::random_access_range< Rs > && ... ) ) {

      return this->begin() + std20::ranges::iter_difference_t< iterator< false > >( this->size() );
    }
    else {

      return iterator< false >( tuple_transform( std20::ranges::end, this->views_ ) );
    }
  }

  template < bool Const = false >
  constexpr auto end()
  -> std::enable_if_t< ! zip_all_simple< Const, Rs... > && ! zip_is_common< Rs... >, sentinel< false > >  {

      return sentinel< false >( tuple_transform( std20::ranges::end, this->views_ ));
  }


  template < bool Const = true >
  constexpr auto end() const
  -> std::enable_if_t< zip_all_range< Const, Rs... > && zip_is_common< Rs... >, iterator< true > > {

    if constexpr ( ( std20::ranges::random_access_range< Rs > && ... ) ) {

      return this->begin() + std20::ranges::iter_difference_t< iterator< true > >( this->size() );
    }
    else {

      return iterator< true >( tuple_transform( std20::ranges::end, this->views_ ) );
    }
  }

  template < bool Const = true >
  constexpr auto end() const
  -> std::enable_if_t< zip_all_range< Const, Rs... > && ! zip_is_common< Rs... >, sentinel< true > > {

      return sentinel< true >( tuple_transform( std20::ranges::end, this->views_ ));
  }


  template < bool Const = false >
  constexpr auto size()
  -> std::enable_if_t< zip_all_sized< Const, Rs... >, std::size_t > {

    return std::apply(
               []( auto... sizes ) {

                 using f = std::make_unsigned_t< std::common_type_t< decltype(sizes)...> >;
                 return std20::ranges::min( { f( sizes )... } );
               },
               tuple_transform( std20::ranges::size, this->views_ ) );
  }

  template < bool Const = true >
  constexpr auto size() const
  -> std::enable_if_t< zip_all_sized< Const, Rs... >, std::size_t > {

    return std::apply(
               []( auto... sizes ) {

                 using f = std::make_unsigned_t< std::common_type_t< decltype(sizes)...> >;
                 return std20::ranges::min( { f( sizes )... } );
               },
               tuple_transform( std20::ranges::size, this->views_ ) );
  }

};

template < typename... Rs >
zip_view( Rs&&... ) -> zip_view< std20::ranges::all_view< Rs >... >;

} // namespace ranges
} // namespace std23

namespace std20 {
inline namespace ranges {

template < typename... Rs >
inline constexpr bool enable_borrowed_range< std23::ranges::zip_view< Rs... > > = ( enable_borrowed_range< Rs > && ... );

} // namespace ranges
} // namespace std23

namespace std23 {
inline namespace ranges {

namespace detail {

struct zip_view_fn {

    template < typename... Rs >
    constexpr auto operator()( Rs&&... r ) const
    -> decltype( zip_view{ std::forward< Rs >( r )... } )
    {
        return zip_view{ std::forward< Rs >( r )... };
    }

};

}

namespace views {

NANO_INLINE_VAR(ranges::detail::zip_view_fn, zip)

}

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
