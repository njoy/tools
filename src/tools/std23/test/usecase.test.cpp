// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

// other includes
#include <vector>
#include <complex>

// convenience typedefs
using namespace njoy::tools;

class TestCase {

  std::vector< double > vector_ = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                                    11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
  std::vector< double > other_ = {  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
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

  auto chunk_transform_drop() const {

    using namespace njoy::tools;
    return this->all() | std23::views::chunk( 2 )
                       | std20::views::transform( [] ( auto&& values ) { return values.front(); } )
                       | std20::views::drop( 2 );
  }

  auto zip_drop_stride() const {

    using namespace njoy::tools;
    return std23::views::zip(
               this->all(),
               this->other_ | std20::views::all );
  }

  auto zip_transform_drop_stride() const {

    using namespace njoy::tools;
    return std23::views::zip_transform(
               [] ( auto&& left, auto&& right ) { return std::complex( left, right ); },
               this->all(),
               this->other_ | std20::views::all );
  }
};

SCENARIO( "use case" ) {

  TestCase test;

  using Iota = decltype( test.iota() );
  CHECK( std20::view< Iota > );
  CHECK( std20::range< Iota > );
  CHECK( std20::random_access_range< Iota > );
//  CHECK( std20::sized_range< Iota > );
  CHECK( std20::same_as< std20::ranges::range_value_t< Iota >, int > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< Iota >, int > );

  using IotaTransform = decltype( test.iota_transform() );
  CHECK( std20::view< IotaTransform > );
  CHECK( std20::range< IotaTransform > );
  CHECK( std20::random_access_range< IotaTransform > );
//  CHECK( std20::sized_range< IotaTransform > );
  CHECK( std20::same_as< std20::ranges::range_value_t< IotaTransform >, int > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< IotaTransform >, int > );

  using All = decltype( test.all() );
  CHECK( std20::view< All > );
  CHECK( std20::range< All > );
  CHECK( std20::random_access_range< All > );
  CHECK( std20::sized_range< All > );
  CHECK( std20::same_as< std20::ranges::range_value_t< All >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< All >, const double& > );

  using Transform = decltype( test.transform() );
  CHECK( std20::view< Transform > );
  CHECK( std20::range< Transform > );
  CHECK( std20::random_access_range< Transform > );
  CHECK( std20::sized_range< Transform > );
  CHECK( std20::same_as< std20::ranges::range_value_t< Transform >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< Transform >, double > );

  using Drop = decltype( test.drop() );
  CHECK( std20::view< Drop > );
  CHECK( std20::range< Drop > );
  CHECK( std20::random_access_range< Drop > );
  CHECK( std20::sized_range< Drop > );
  CHECK( std20::same_as< std20::ranges::range_value_t< Drop >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< Drop >, const double& > );

  using Stride = decltype( test.stride() );
  CHECK( std20::view< Stride > );
  CHECK( std20::range< Stride > );
  CHECK( std20::random_access_range< Stride > );
  CHECK( std20::sized_range< Stride > );
  CHECK( std20::same_as< std20::ranges::range_value_t< Stride >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< Stride >, const double& > );

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
  CHECK( std20::same_as< std20::ranges::range_value_t< DropStride >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< DropStride >, const double& > );

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
  CHECK( std20::same_as< std20::ranges::range_value_t< StrideDrop >, double > );
  CHECK( std20::same_as< std20::ranges::range_reference_t< StrideDrop >, const double& > );

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

  using ChunkTransformDrop = decltype( test.chunk_transform_drop() );
  CHECK( std20::view< ChunkTransformDrop > );
  CHECK( std20::range< ChunkTransformDrop > );
  CHECK( std20::random_access_range< ChunkTransformDrop > );
  CHECK( std20::sized_range< ChunkTransformDrop > );

  using ZipDropStride = decltype( test.zip_drop_stride() );
  CHECK( std20::view< ZipDropStride > );
  CHECK( std20::range< ZipDropStride > );
//  CHECK( std20::random_access_range< ZipDropStride > );
  CHECK( std20::sized_range< ZipDropStride > );
  CHECK( std20::same_as< std20::ranges::range_value_t< ZipDropStride >, std::pair< double, double > > );

  using ZipTransformDropStride = decltype( test.zip_transform_drop_stride() );
//  CHECK( std20::view< ZipTransformDropStride > );
//  CHECK( std20::range< ZipTransformDropStride > );
//  CHECK( std20::random_access_range< ZipTransformDropStride > );
//  CHECK( std20::sized_range< ZipTransformDropStride > );
//  CHECK( std20::same_as< std20::ranges::range_value_t< ZipTransformDropStride >, std::complex< double > > );
} // SCENARIO
