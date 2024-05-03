#ifndef NJOY_TOOLS_STD23_RANGES_VIEWS_NONPROPEGATING_BOX
#define NJOY_TOOLS_STD23_RANGES_VIEWS_NONPROPEGATING_BOX

#include <optional>

namespace njoy {
namespace tools {
namespace std23 {
inline namespace ranges {

namespace detail {

/**
 *  @brief A helper type containing a value that gets reset upon move or copy
 *
 *  Similar to the semiregular_box, the nonpropegating_box is a helper type for
 *  implementing views. It stores an optional containing a value that gets
 *  reset upon move or copy.
 */
template < typename T >
struct nonpropegating_box : std::optional<T> {

  static_assert( std::is_object_v< T > );

private:

  std::optional< T > value_ = std::nullopt;

public:

  nonpropegating_box() = default;

  constexpr nonpropegating_box( const nonpropegating_box& ) : value_( std::nullopt ) {}

  constexpr nonpropegating_box( nonpropegating_box&& other ) :
      value_( std::nullopt ) {

    other.value_.reset();
  }

  constexpr nonpropegating_box& operator=( const nonpropegating_box& other ) {

    if ( this != std::addressof( other ) ) {

      this->value_.reset();
    }
    return *this;
  }

  constexpr nonpropegating_box& operator=( nonpropegating_box&& other ) {

    this->value_.reset();
    other.value_.reset();
    return *this;
  }

  constexpr T& operator*() { return this->value_.value(); }

  constexpr const T& operator*() const { return this->value_.value(); }

  constexpr bool has_value() const { return this->value_.has_value(); }

  template < typename... Args >
  constexpr T& emplace( Args&&... args ) {

    return this->value_.emplace( std::forward< Args >( args )... );
  }
};

} // namespace detail

} // namespace ranges
} // namespace std23
} // namespace tools
} // namespace njoy

#endif
