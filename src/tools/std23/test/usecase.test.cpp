// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

// other includes
#include <vector>

// convenience typedefs
using namespace njoy::tools;

class TestCase {

  std::vector< double > vector_ = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

public:

  TestCase() = default;

  auto iota() const {

    using namespace njoy::tools;
    return std20::views::iota( 20 );
  }

  auto iota_transform() const {

    using namespace njoy::tools;
    return this->iota() | std20::views::transform( [] ( auto&& value ) { return value + 1; } );
  }

  auto all() const {

    using namespace njoy::tools;
    return this->vector_ | std20::views::all;
  }

  auto transform() const {

    using namespace njoy::tools;
    return this->all() | std20::views::transform( [] ( auto&& value ) { return value + 1; } );
  }

  auto drop() const {

    using namespace njoy::tools;
    return this->all() | std20::views::drop( 2 );
  }

  auto stride() const {

    using namespace njoy::tools;
    return this->all() | std23::views::stride( 2 );
  }

  auto chunk() const {

    using namespace njoy::tools;
    return this->all() | std23::views::chunk( 2 );
  }

  auto drop_stride() const {

    using namespace njoy::tools;
    return this->all() | std20::views::drop( 2 )
                       | std23::views::stride( 2 );
  }

  auto drop_chunk() const {

    using namespace njoy::tools;
    return this->all() | std20::views::drop( 2 )
                       | std23::views::chunk( 2 );
  }

  auto stride_drop() const {

    using namespace njoy::tools;
    return this->all() | std23::views::stride( 2 )
                       | std20::views::drop( 2 );
  }

  auto chunk_drop() const {

    using namespace njoy::tools;
    return this->all() | std23::views::chunk( 2 )
                       | std20::views::drop( 2 );
  }

  auto chunk_stride() const {

    using namespace njoy::tools;
    return this->all() | std23::views::chunk( 2 )
                       | std23::views::stride( 2 );
  }

  auto stride_chunk() const {

    using namespace njoy::tools;
    return this->all() | std23::views::stride( 2 )
                       | std23::views::chunk( 2 );
  }

  auto repeat_bound() const {

    using namespace njoy::tools;
    return std23::views::repeat( 5, 2 );
  }

  auto repeat_unbound() const {

    using namespace njoy::tools;
    return std23::views::repeat( 4.0 );
  }
};

SCENARIO( "use case" ) {

  TestCase test;

  using Iota = decltype( test.iota() );
  CHECK( std20::view< Iota > );
  CHECK( std20::range< Iota > );
  CHECK( std20::random_access_range< Iota > );
//  CHECK( std20::sized_range< Iota > );

  using IotaTransform = decltype( test.iota_transform() );
  CHECK( std20::view< IotaTransform > );
  CHECK( std20::range< IotaTransform > );
  CHECK( std20::random_access_range< IotaTransform > );
//  CHECK( std20::sized_range< IotaTransform > );

  using All = decltype( test.all() );
  CHECK( std20::view< All > );
  CHECK( std20::range< All > );
  CHECK( std20::random_access_range< All > );
  CHECK( std20::sized_range< All > );

  using Transform = decltype( test.transform() );
  CHECK( std20::view< Transform > );
  CHECK( std20::range< Transform > );
  CHECK( std20::random_access_range< Transform > );
  CHECK( std20::sized_range< Transform > );

  using Drop = decltype( test.drop() );
  CHECK( std20::view< Drop > );
  CHECK( std20::range< Drop > );
  CHECK( std20::random_access_range< Drop > );
  CHECK( std20::sized_range< Drop > );

  using Stride = decltype( test.stride() );
  CHECK( std20::view< Stride > );
  CHECK( std20::range< Stride > );
  CHECK( std20::random_access_range< Stride > );
  CHECK( std20::sized_range< Stride > );

  using Chunk = decltype( test.chunk() );
  CHECK( std20::view< Chunk > );
  CHECK( std20::range< Chunk > );
  CHECK( std20::random_access_range< Chunk > );
  CHECK( std20::sized_range< Chunk > );

  using DropStride = decltype( test.drop_stride() );
  CHECK( std20::view< DropStride > );
  CHECK( std20::range< DropStride > );
  CHECK( std20::random_access_range< DropStride > );
  CHECK( std20::sized_range< DropStride > );

  using DropChunk = decltype( test.drop_chunk() );
  CHECK( std20::view< DropChunk > );
  CHECK( std20::range< DropChunk > );
  CHECK( std20::random_access_range< DropChunk > );
  CHECK( std20::sized_range< DropChunk > );

  using StrideDrop = decltype( test.stride_drop() );
  CHECK( std20::view< StrideDrop > );
  CHECK( std20::range< StrideDrop > );
  CHECK( std20::random_access_range< StrideDrop > );
  CHECK( std20::sized_range< StrideDrop > );

  using ChunkDrop = decltype( test.chunk_drop() );
  CHECK( std20::view< ChunkDrop > );
  CHECK( std20::range< ChunkDrop > );
  CHECK( std20::random_access_range< ChunkDrop > );
  CHECK( std20::sized_range< ChunkDrop > );

  using ChunkStride = decltype( test.chunk_stride() );
  CHECK( std20::view< ChunkStride > );
  CHECK( std20::range< ChunkStride > );
  CHECK( std20::random_access_range< ChunkStride > );
  CHECK( std20::sized_range< ChunkStride > );

  using StrideChunk = decltype( test.stride_chunk() );
  CHECK( std20::view< StrideChunk > );
  CHECK( std20::range< StrideChunk > );
  CHECK( std20::random_access_range< StrideChunk > );
  CHECK( std20::sized_range< StrideChunk > );

  using RepeatBound = decltype( test.repeat_bound() );
  CHECK( std20::view< RepeatBound > );
  CHECK( std20::range< RepeatBound > );
  CHECK( std20::random_access_range< RepeatBound > );
  CHECK( std20::sized_range< RepeatBound > );

  using RepeatUnbound = decltype( test.repeat_unbound() );
  CHECK( std20::view< RepeatUnbound > );
  CHECK( std20::range< RepeatUnbound > );
  CHECK( std20::random_access_range< RepeatUnbound > );
  CHECK( !std20::sized_range< RepeatUnbound > );

} // SCENARIO
