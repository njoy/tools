#ifndef NJOY_TOOLS_OVERLOAD
#define NJOY_TOOLS_OVERLOAD

// system includes

// other includes

namespace njoy {
namespace tools {

  /**
   *  @brief Overload struct for collecting lambdas for std::visit
   *
   *  For example:
   *
   *    auto value = std::visit(
   *        tools::overload{ [] ( const Foo& ) -> std::string
   *                            { return "Foo"; },
   *                         [] ( const Bar& )
   *                            { return "Bar"; } },
   *        variant );
   */
  template < class... Types > struct overload : Types... {

    using Types::operator()...;
  };

  /**
   *  @brief Overload struct for collecting lambdas for std::visit
   *
   *  For example:
   *
   *    auto value = std::visit(
   *        tools::overload( [] ( const Foo& ) -> std::string
   *                            { return "Foo"; },
   *                         [] ( const Bar& )
   *                            { return "Bar"; } ),
   *        variant );
   */
  template < class... Types >
  overload( Types... ) -> overload< Types... >;

} // tools namespace
} // njoy namespace

#endif
