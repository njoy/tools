#ifndef NJOY_TOOLS_DISCO_RECORD
#define NJOY_TOOLS_DISCO_RECORD

// system includes
#include "tools/disco/functions.hpp"
#include "tools/disco/Column.hpp"

// other includes

namespace njoy {
namespace tools {
namespace disco {

struct RetainCarriage{};

template < typename... Components >
struct Record;

template<>
struct Record<> {

  template< typename Iterator >
  static void read( Iterator& iter, const Iterator& end ) {

    while ( iter != end && ! ( isNewLine( iter ) ) ) {

      ++iter;
    }
    std::advance( iter, iter != end && isNewLine( iter ) );
  }

  template< typename Iterator, typename... Args >
  static void write( Iterator& it, const Args&... ) {

    *it++='\n';
  }
};

template<>
struct Record< RetainCarriage > {

  template< typename Iterator >
  static void read( Iterator&, const Iterator& ) {}

  template< typename Iterator, typename... Args >
  static void write( Iterator&, const Args&... ) {}

};

template< unsigned int w, typename... Components >
struct Record< Column< w >, Components... > {

  template< typename Iterator, typename... Args >
  static void read( Iterator& it, const Iterator& end, Args&... args ) {

    Column< w >::read( it, end );
    Record< Components... >::read( it, end, args... );
  }

  template< typename Iterator, typename... Args >
  static void write( Iterator& it, const Args&... args ) {

    Column< w >::write( it );
    Record< Components... >::write( it, args... );
  }
};

template< typename Component, typename... Components >
struct Record< Component, Components... > {

  using Subrecord =  Record< Components... >;

  template< typename Iterator >
  static void read( Iterator& it, const Iterator& end ) {

    Component::read( it, end );
    Subrecord::read( it, end );
  }

  template< typename Iterator, typename SinkType, typename... Args >
  static void read( Iterator& it, const Iterator& end, SinkType& sink, Args&... args ) {

    sink = Component::template read< SinkType >( it, end );
    Subrecord::read( it, end, args... );
  }

  template< typename Iterator >
  static void write( Iterator& it ) {

    Component::write( it );
    Subrecord::write( it );
  }

  template< typename Iterator, typename SourceType, typename... Args >
  static void write( Iterator& it, const SourceType& source, const Args&... args ) {

    Component::write( source, it );
    Subrecord::write( it, args... );
  }
};

} // disco namespace
} // tools namespace
} // njoy namespace

#endif
