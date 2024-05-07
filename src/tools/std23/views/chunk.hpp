#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_CHUNK
#define NJOY_TOOLS_STD23_RANGES_VIEWS_CHUNK

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std20/views/subrange.hpp"
#include "tools/std20/views/take.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

template < class Integer >
constexpr Integer div_ceil( Integer num, Integer denom ) {

  Integer r = num / denom;
  if ( num % denom ) {

    ++r;
  }
  return r;
}

/**
 *  @brief A range adaptor that takes a view and a number n and produces a
 *         range of views such that each chunk, except maybe the last one, has the size n
 *
 *  See https://en.cppreference.com/w/cpp/ranges/chunk_view
 */
template < typename R >
struct chunk_view : std20::ranges::view_interface< chunk_view< R > > {

  static_assert( std20::ranges::view< R > );
  static_assert( std20::ranges::forward_range< R > );

private:

  R base_;
  std20::ranges::range_difference_t< R > n_;

  template < bool Const >
  struct iterator {

  private:

    friend chunk_view;

    using Parent = std20::ranges::detail::conditional_t< Const, const chunk_view, chunk_view >;
    using Base = std20::ranges::detail::conditional_t< Const, const R, R >;

    chunk_view* parent_ = nullptr;
    std20::ranges::iterator_t< Base > current_ = std20::ranges::iterator_t< Base >();
    std20::ranges::iterator_t< Base > end_ = std20::ranges::iterator_t< Base >();
    std20::ranges::range_difference_t< Base > n_ = 0;
    std20::ranges::range_difference_t< Base > missing_ = 0;

    constexpr iterator( Parent* parent, std20::ranges::iterator_t< Base > current,
                        std20::ranges::range_difference_t< Base > missing = 0 ) :
        current_( std::move( current ) ),
        end_( std20::ranges::end( parent->base_ ) ),
        n_( parent->n_ ),
        missing_( missing ) {}

  public:

    using value_type        = decltype( std20::views::take( std20::ranges::subrange( current_, end_ ), n_ ) );
    using difference_type   = std20::ranges::range_difference_t< R >;
    using iterator_category = std::conditional_t<
                                  std20::ranges::random_access_range< R >,
                                  std20::random_access_iterator_tag,
                                  std::conditional_t< std20::ranges::bidirectional_range< R >,
                                                  std20::bidirectional_iterator_tag,
                                                  std20::forward_iterator_tag > >;

    iterator() = default;

    template < typename Iterator,
               std::enable_if_t< std20::same_as< Iterator, iterator< ! Const > >, int > = 0,
               bool C = Const, typename RR = R,
               std::enable_if_t< C && std20::convertible_to< std20::ranges::iterator_t< RR >,
                                                             std20::ranges::iterator_t< Base > >, int > = 0 >
    constexpr iterator( Iterator iter ) :
        current_( std::move( iter.current_ ) ),
        end_( std::move( iter.end_ ) ),
        n_( iter.n_ ),
        missing_( iter.missing_ ) {}

    constexpr std20::ranges::iterator_t< Base > base() const { return this->current_; }

    constexpr value_type operator*() const {

      return std20::views::take( std20::ranges::subrange( this->current_, this->end_ ), this->n_ );
    }

    constexpr iterator& operator++() {

      this->missing_ = std20::ranges::advance( this->current_, this->n_, this->end_ );
      return *this;
    }

    constexpr iterator operator++(int) {

      auto temp = *this;
      ++*this;
      return temp;
    }

    template < typename B = Base >
    constexpr auto operator--()
    -> std::enable_if_t< std20::ranges::bidirectional_range< B >, iterator& > {

      std20::ranges::advance( this->current_, this->missing_ - this->n_ );
      this->missing_ = 0;
      return *this;
    }

    template < typename B = Base >
    constexpr auto operator--(int)
    -> std::enable_if_t< std20::ranges::bidirectional_range< B >, iterator > {

      auto temp = *this;
      --*this;
      return temp;
    }

    template < typename B = Base >
    constexpr auto operator+=( difference_type n )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator& > {

      if ( n > 0 ) {

        std20::ranges::advance( this->current_, this->n_ * ( n - 1 ) );
        this->missing_ = std20::ranges::advance( this->current_, this->n_, this->end_ );
      }
      else if ( n < 0 ) {

        std20::ranges::advance( this->current_, this->n_ * n + this->missing_ );
        this->missing_ = 0;
      }
      return *this;
    }

    template < typename B = Base >
    constexpr auto operator-=( difference_type n )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator& > {

      return *this += -n;
    }

    template < typename B = Base >
    constexpr auto operator[]( difference_type n ) const
    -> std::enable_if_t< std20::ranges::random_access_range< B >, value_type > {

      return *( *this + n );
    }

    template < typename B = Base >
    friend constexpr auto operator==( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::equality_comparable< std20::ranges::iterator_t< B > >, bool > {

      return left.current_ == right.current_;
    }

    template < typename B = Base >
    friend constexpr auto operator!=( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::equality_comparable< std20::ranges::iterator_t< B > >, bool > {

      return ! ( left == right );
    }

    template < typename B = Base >
    friend constexpr auto operator<( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, bool > {

      return left.current_ < right.current_;
    }

    template < typename B = Base>
    friend constexpr auto operator>( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, bool > {

      return right < left;
    }

    template < typename B = Base >
    friend constexpr auto operator<=( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, bool > {

      return ! ( right < left );
    }

    template < typename B = Base >
    friend constexpr auto operator>=( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, bool > {

        return ! ( left < right );
    }

    template < typename B = Base >
    friend constexpr auto operator+( const iterator& left, const difference_type n )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator > {

      return iterator{ left } += n;
    }

    template < typename B = Base >
    friend constexpr auto operator+( const difference_type n, const iterator& right )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator > {

      return right + n;
    }

    template < typename B = Base >
    friend constexpr auto operator-( const iterator& left, const difference_type n )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator > {

      return iterator{ left } -= n;
    }

    template < typename B = Base >
    friend constexpr auto operator-( const iterator& left, const iterator& right )
    -> std::enable_if_t<
        std20::ranges::sized_sentinel_for< std20::ranges::iterator_t< B >,
                                           std20::ranges::iterator_t< B > >,
        difference_type > {

      return ( left.current_ - right.current_ + left.missing_ - right.missing_ ) / left.n_;
    }

    template < typename B = Base >
    friend constexpr auto operator-( const std20::ranges::default_sentinel_t, const iterator& right )
    -> std::enable_if_t<
        std20::ranges::sized_sentinel_for< std20::ranges::sentinel_t< B >,
                                           std20::ranges::iterator_t< B > >,
        difference_type > {

      return div_ceil( right.end_ - right.current_, right.n_ );
    }

    template < typename B = Base >
    friend constexpr auto operator-( const iterator& left, const std20::ranges::default_sentinel_t right )
    -> std::enable_if_t<
        std20::ranges::sized_sentinel_for< std20::ranges::sentinel_t< B >,
                                           std20::ranges::iterator_t< B > >,
        difference_type > {

      return -( right - left );
    }
  };

public:

  chunk_view() = default;

  constexpr chunk_view( R base, std20::ranges::range_difference_t< R > n ) :
      base_( std::move( base ) ), n_( n ) {

    assert( this->n_ > 0 );
  }

  constexpr R base() const { return base_; }

  constexpr iterator< false > begin() {

    return { this, std20::ranges::begin( this->base_ ) };
  }

  constexpr iterator< true > begin() const {

    return { this, std20::ranges::begin( this->base_ ) };
  }

  constexpr iterator< false > end() {

    if constexpr ( std20::ranges::common_range< R > && std20::ranges::sized_range< R >) {

      auto missing = ( this->n_ - std20::ranges::distance( this->base_ ) % this->n_ ) % this->n_;
      return iterator< false >( this, std20::ranges::end( this->base_ ), missing );
    }
    else if constexpr ( std20::ranges::common_range< R > && ! std20::ranges::bidirectional_range< R >) {

      return iterator< false >( this, std20::ranges::end( this->base_ ) );
    }
    else {

      return std20::ranges::default_sentinel;
    }
  }

  constexpr iterator< true > end() const {

    if constexpr ( std20::ranges::common_range< R > && std20::ranges::sized_range< R >) {

      auto missing = ( this->n_ - std20::ranges::distance( this->base_ ) % this->n_ ) % this->n_;
      return iterator< true >( this, std20::ranges::end( this->base_ ), missing );
    }
    else if constexpr ( std20::ranges::common_range< R > && ! std20::ranges::bidirectional_range< R >) {

      return iterator< true >( this, std20::ranges::end( this->base_ ) );
    }
    else {

      return std20::ranges::default_sentinel;
    }
  }

  template < typename B = R >
  constexpr auto size()
  -> std::enable_if_t< std20::ranges::sized_range< B >, std::size_t > {

    return div_ceil( std20::ranges::distance( this->base_ ), this->n_ );
  }

  template < typename B = R >
  constexpr auto size() const
  -> std::enable_if_t< std20::ranges::sized_range< B >, std::size_t > {

    return div_ceil( std20::ranges::distance( this->base_ ), this->n_ );
  }

};

template < typename R >
chunk_view( R&&, std20::ranges::range_difference_t< R > ) -> chunk_view< std20::ranges::all_view< R > >;

namespace detail {

struct chunk_view_fn {

    template < typename E, typename F >
    constexpr auto operator()( E&& e, F&& f ) const
    -> decltype( chunk_view{ std::forward< E >( e ), std::forward< F >( f ) } )
    {
        return chunk_view{ std::forward< E >( e ), std::forward< F >( f ) };
    }

    template < typename C >
    constexpr auto operator()( C&& c ) const
    {
        return std20::ranges::detail::rao_proxy{ [p = std::forward< C >( c ) ] ( auto&& r ) mutable
#ifndef NANO_MSVC_LAMBDA_PIPE_WORKAROUND
            -> decltype( chunk_view{ std::forward< decltype(r) >( r ), std::declval< C&& >() } )
#endif
        {
            return chunk_view{ std::forward< decltype(r) >( r ), std::move( p ) };
        }};
    }

};

}

namespace views {

NANO_INLINE_VAR(ranges::detail::chunk_view_fn, chunk)

}

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
