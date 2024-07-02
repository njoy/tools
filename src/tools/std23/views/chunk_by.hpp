#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_CHUNK_BY
#define NJOY_TOOLS_STD23_RANGES_VIEWS_CHUNK_BY

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/detail/views/semiregular_box.hpp"
#include "tools/std23/detail/views/nonpropagating_box.hpp"
#include "tools/std20/algorithm/adjacent_find.hpp"
#include "tools/std20/functional.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std20/views/reverse.hpp"
#include "tools/std20/views/subrange.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

/**
 *  @brief A range adaptor that takes a view and produces a view of subranges
 *         based on a predicate
 *
 *  See https://en.cppreference.com/w/cpp/ranges/chunk_by_view
 */
template < typename R, typename Pred >
struct chunk_by_view : std20::ranges::view_interface< chunk_by_view< R, Pred > > {

  static_assert( std20::ranges::view< R > );
  static_assert( std20::ranges::input_range< R > );
  static_assert( std::is_object_v< Pred > );
  static_assert( std20::ranges::indirect_binary_predicate<
                     const Pred, std20::ranges::iterator_t< R >,
                     std20::ranges::iterator_t< R > > );

private:

  R base_;
  std20::ranges::detail::semiregular_box< Pred > pred_;
  std23::ranges::detail::nonpropagating_box< std20::ranges::iterator_t< R > > begin_;

  struct iterator {

  private:

    friend chunk_by_view;

    chunk_by_view* parent_ = nullptr;
    std20::ranges::iterator_t< R > current_ = std20::ranges::iterator_t< R >();
    std20::ranges::iterator_t< R > next_ = std20::ranges::iterator_t< R >();

    constexpr iterator( chunk_by_view& parent, std20::ranges::iterator_t< R > current,
                        std20::ranges::iterator_t< R > next ) :
        parent_( std::addressof( parent ) ), current_( current ), next_( next ) {}

  public:

    using value_type        = std20::ranges::subrange< std20::ranges::iterator_t< R > >;
    using difference_type   = std20::ranges::range_difference_t< R >;
    using iterator_category = std::conditional_t< std20::ranges::bidirectional_range< R >,
                                                  std20::bidirectional_iterator_tag,
                                                  std20::forward_iterator_tag >;

    iterator() = default;

    constexpr value_type operator*() const { return { this->current_, this->next_ }; }

    constexpr iterator& operator++() {

      this->current_ = this->next_;
      this->next_ = this->parent_->find_next( this->current_ );
      return *this;
    }

    constexpr iterator operator++(int) {

      auto temp = *this;
      ++*this;
      return temp;
    }

    template < typename B = R >
    constexpr auto operator--()
    -> std::enable_if_t< std20::ranges::bidirectional_range< B >, iterator& > {

      this->next_ = this->current_;
      this->current_ = this->parent_->find_prev( this->next_ );
      return *this;
    }

    template < typename B = R >
    constexpr auto operator--(int)
    -> std::enable_if_t< std20::ranges::bidirectional_range< B >, iterator > {

      auto temp = *this;
      --*this;
      return temp;
    }

    template < typename B = R >
    friend constexpr auto operator==( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::equality_comparable< std20::ranges::iterator_t< B > >, bool > {

      return left.current_ == right.current_;
    }

    friend constexpr bool operator==( const iterator& left, std20::ranges::default_sentinel_t ) {

      return left.current_ == left.next_;
    }

    template < typename B = R >
    friend constexpr auto operator!=( const iterator& left, const iterator& right )
    -> std::enable_if_t< std20::equality_comparable< std20::ranges::iterator_t< B > >, bool > {

      return ! ( left == right );
    }
  };

  constexpr std20::ranges::iterator_t< R > find_next( std20::ranges::iterator_t< R > current ) {

    assert( this->pred_.has_value() );

    auto not_pred = [&pred = this->pred_.value()] ( auto&& x, auto&& y ) -> bool {

      return !std20::ranges::invoke( pred,
                                     std::forward< decltype(x) >( x ),
                                     std::forward< decltype(y) >( y ) );
    };

    auto end = std20::ranges::end( this->base_ );
    return std20::ranges::next( std20::ranges::adjacent_find( current, end, not_pred ), 1, end );
  }

  template < typename RR = R,
             typename = std::enable_if_t< std20::ranges::bidirectional_range< RR > > >
  constexpr std20::ranges::iterator_t< R > find_prev( std20::ranges::iterator_t< R > current ) {

    assert( current != std20::ranges::begin( this->base_ ) );
    assert( this->pred_.has_value() );

    auto not_pred = [&pred = this->pred_.value()] ( auto&& x, auto&& y ) -> bool {

      return !std20::ranges::invoke( pred,
                                     std::forward< decltype(y) >( y ),
                                     std::forward< decltype(x) >( x ) );
    };

    auto begin = std20::ranges::begin( this->base_ );
    std20::ranges::reverse_view reverse( std20::ranges::subrange( begin, current ) );
    return std20::ranges::prev(
               // reverse.end() is an iterator pointing to the element before begin
               std20::ranges::adjacent_find( reverse.begin(), --reverse.end(), not_pred ).base(),
               1, std::move( begin ) );
  }

public:

  chunk_by_view() = default;

  constexpr chunk_by_view( R base, Pred pred ) :
      base_( std::move( base ) ), pred_( std::move( pred ) ) {}

  constexpr R base() const { return base_; }

  constexpr const Pred& pred() const { return *pred_; }

  constexpr iterator begin() {

    auto first = std20::ranges::begin( this->base_ );
    if ( ! this->begin_.has_value() ) {

      this->begin_.emplace( this->find_next( first ) );
    }
    return { *this, std::move( first ), *this->begin_ };
  }

  constexpr iterator end() {

    if constexpr ( std20::ranges::common_range< R > ) {

      return { *this, std20::ranges::end( this->base_ ), std20::ranges::end( this->base_ ) };
    }
    else {

      return std20::ranges::default_sentinel;
    }
  }

};

template < typename R, typename Pred >
chunk_by_view( R&&, Pred ) -> chunk_by_view< std20::ranges::all_view<R>, Pred >;

namespace detail {

struct chunk_by_view_fn {

    template < typename E, typename F >
    constexpr auto operator()( E&& e, F&& f ) const
    -> decltype( chunk_by_view{ std::forward< E >( e ), std::forward< F >( f ) } )
    {
        return chunk_by_view{ std::forward< E >( e ), std::forward< F >( f ) };
    }

    template < typename Pred >
    constexpr auto operator()( Pred&& pred ) const
    {
        return std20::ranges::detail::rao_proxy{ [p = std::forward< Pred >( pred ) ] ( auto&& r ) mutable
#ifndef NANO_MSVC_LAMBDA_PIPE_WORKAROUND
            -> decltype( chunk_by_view{ std::forward< decltype( r ) >( r ), std::declval< Pred&& >() } )
#endif
        {
            return chunk_by_view{ std::forward< decltype( r ) >( r ), std::move( p ) };
        }};
    }

};

}

namespace views {

NANO_INLINE_VAR(ranges::detail::chunk_by_view_fn, chunk_by)

}

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
