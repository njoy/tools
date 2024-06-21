#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_ZIP_TRANSFORM
#define NJOY_TOOLS_STD23_RANGES_VIEWS_ZIP_TRANSFORM

#include "tools/std20/detail/views/range_adaptors.hpp"
#include "tools/std20/detail/views/semiregular_box.hpp"
#include "tools/std20/views/interface.hpp"
#include "tools/std20/views/all.hpp"
#include "tools/std23/views/zip.hpp"

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

/**
 *  @brief A range adaptor takes an invocable object and one or more views,
 *         and produces a view whose element is the result of applying the
 *         invocable object to the corresponding elements of all views
 *
 *  See https://en.cppreference.com/w/cpp/ranges/zip_transform_view
 */
template < typename F, typename... Rs >
struct zip_transform_view : std20::ranges::view_interface< zip_transform_view< F, Rs... > > {

  static_assert( ( std20::ranges::view< Rs > && ... ) );
  static_assert( sizeof...( Rs ) > 0 );
  static_assert( std::is_object_v< F > );
  static_assert( std20::regular_invocable< F&, std20::ranges::range_reference_t< Rs >... > );

private :

  using InnerView = zip_view< Rs... >;
  template < bool Const >
  using InnerIterator = std20::ranges::iterator_t< maybe_const< Const, InnerView > >;
  template < bool Const >
  using InnerSentinel = std20::ranges::sentinel_t< maybe_const< Const, InnerView > >;

  zip_view< Rs... > zip_;
  std20::ranges::detail::semiregular_box< F > fun_;

  template < bool Const >
  struct sentinel;

  template < bool Const >
  struct iterator {

  private:

    using Parent = maybe_const< Const, zip_transform_view >;
    using Base   = maybe_const< Const, InnerView >;

    friend zip_transform_view< F, Rs... >;

    friend zip_view_iterator_access;

    Parent* parent_ = nullptr;
    InnerIterator< Const > current_;

    constexpr iterator( Parent& parent, InnerIterator< Const > current )
      : parent_( std::addressof( parent ) ), current_( std::move( current ) ) {}

    constexpr auto get_deref_and_invoke() const noexcept {

      return [this] ( const auto&... iters ) noexcept( noexcept( std::invoke( *parent_->fun_, *iters... ) ) ) -> decltype(auto) {

        return std::invoke( *parent_->fun_, *iters... );
      };
    }

  public:

    using value_type = std20::remove_cvref_t<
                           std20::invoke_result_t< maybe_const< Const, F >&,
                                                   std20::ranges::range_reference_t< maybe_const< Const, Rs > >... > >;
    using difference_type = std20::ranges::range_difference_t< Base >;
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
                 std20::convertible_to< InnerIterator< false >, InnerIterator< C > > > >
    constexpr iterator( iterator< ! Const > iter ) : parent_( iter.parent_ ), current_( std::move( iter.current_ ) ) {}

    constexpr decltype(auto) operator*() const {

      return std::apply( get_deref_and_invoke(), zip_view_iterator_access::get_underlying( current_ ) );
    }

    constexpr iterator& operator++() {

      ++current_;
      return *this;
    }

    template < typename B = Base >
    constexpr auto operator++(int)
    -> std::enable_if_t< std20::ranges::forward_range< B >, iterator > {

      auto temp = *this;
      ++*this;
      return temp;
    }

    template < typename B = Base >
    constexpr auto operator--()
    -> std::enable_if_t< std20::ranges::bidirectional_range< B >, iterator& > {

      --current_;;
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

      current_ += n;
      return *this;
    }

    template < typename B = Base >
    constexpr auto operator-=( difference_type n )
    -> std::enable_if_t< std20::ranges::random_access_range< B >, iterator& > {

      return *this += -n;
    }

    template < typename B = Base,
               typename = std::enable_if_t< std20::ranges::random_access_range< B > > >
    constexpr decltype(auto) operator[]( difference_type n ) const {

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

      return left.current_ - right.current_;
    }
  };

  template < bool Const >
  struct sentinel {

  private:

    InnerSentinel< Const > current_;

    friend zip_transform_view< F, Rs... >;

    constexpr explicit sentinel( InnerSentinel< Const > current ) : current_( current ) {}

  public:

    sentinel() = default;

    template < bool C = Const,
               typename = std::enable_if_t<
                 C &&
                 std20::convertible_to< InnerSentinel< false >, InnerSentinel< C > > > >
    constexpr sentinel( sentinel< ! Const > iter ) : current_( std::move( iter.current_ ) ) {}

    template < bool Other >
    friend constexpr auto operator==( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< std20::ranges::sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >, bool > {

      return zip_view_iterator_access::get_underlying( left ) == right.current_;
    }

    template < bool Other >
    friend constexpr auto operator==( const sentinel& left, const iterator< Other >& right )
    -> std::enable_if_t< std20::ranges::sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >, bool > {

      return right == left;
    }

    template < bool Other >
    friend constexpr auto operator!=( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< std20::ranges::sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >, bool > {

      return ! ( left == right );
    }

    template < bool Other >
    friend constexpr auto operator!=( const sentinel& left, const iterator< Other >& right )
    -> std::enable_if_t< std20::ranges::sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >, bool > {

      return right != left;
    }

    template < bool Other >
    friend constexpr auto operator-( const iterator< Other >& left, const sentinel& right )
    -> std::enable_if_t< std20::ranges::sized_sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >,
                         std20::ranges::range_difference_t< maybe_const< Other, InnerView > > > {

      return left.current_ - right.__current_;
    }

    template < bool Other >
    friend constexpr auto operator-( const sentinel& left, const iterator< Other >& right )
    -> std::enable_if_t< std20::ranges::sized_sentinel_for< InnerSentinel< Const >, InnerIterator< Other > >,
                         std20::ranges::range_difference_t< maybe_const< Other, InnerView > > > {

      return -( right - left );
    }
  };

public:

  zip_transform_view() = default;

  constexpr explicit zip_transform_view( F f, Rs... views ) :
      zip_( std::move( views )... ),
      fun_( std::move( f ) ) {}

  constexpr auto begin() { return iterator< false >( *this, zip_.begin() ); }

  constexpr auto begin() const
  -> std::enable_if_t< std20::range< InnerView > &&
                          std20::regular_invocable< const F&, std20::ranges::range_reference_t< const Rs >... >,
                       iterator< true > > {

    return iterator< true >( *this, zip_.begin() );
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto end()
  -> std::enable_if_t< std20::ranges::common_range< R >, iterator< false > > {

    return iterator< false >( *this, zip_.end() );
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto end()
  -> std::enable_if_t< ! std20::ranges::common_range< R >, sentinel< false > > {

    return sentinel< false >( zip_.end() );
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto end() const
  -> std::enable_if_t< std20::ranges::common_range< const R >
                           && std20::regular_invocable< const F&, std20::ranges::range_reference_t< const Rs >... >,
                       iterator< true > > {

    return iterator< true >( *this, zip_.end() );
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto end() const
  -> std::enable_if_t< ! std20::ranges::common_range< const R >
                           && std20::regular_invocable< const F&, std20::ranges::range_reference_t< const Rs >... >,
                       sentinel< true > > {

    return sentinel< true >( zip_.end() );
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto size()
  -> std::enable_if_t< std20::ranges::sized_range< R >, std::size_t > {

    return zip_.size();
  }

  template < typename R = zip_view< Rs... > >
  constexpr auto size() const
  -> std::enable_if_t< std20::ranges::sized_range< const R >, std::size_t > {

    return zip_.size();
  }
};

template < typename F, typename... Rs >
zip_transform_view( F, Rs&&... ) -> zip_transform_view< F, std20::ranges::all_view< Rs >... >;

namespace detail {

struct zip_transform_view_fn {

    template < typename F, typename... Rs >
    constexpr auto operator()( F f, Rs&&... r ) const
    -> decltype( zip_transform_view{ std::forward< F >( f ), std::forward< Rs >( r )... } )
    {
        return zip_transform_view{ std::forward< F >( f ), std::forward< Rs >( r )... };
    }

};

}

namespace views {

NANO_INLINE_VAR(ranges::detail::zip_transform_view_fn, zip_transform)

}

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
