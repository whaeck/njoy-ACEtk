// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/ComptonProfile.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ComptonProfile = photoatomic::ComptonProfile;

std::vector< double > chunk();
void verifyChunk( const ComptonProfile&, const std::vector< double >& );
ComptonProfile makeDummyBlock();

SCENARIO( "ComptonProfile" ) {

  GIVEN( "valid data for a ComptonProfile instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      int interpolation = 2;
      std::vector< double > momentum = { 1e-11, 1.0, 20.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };

      ComptonProfile chunk( interpolation,
                            std::move( momentum ),
                            std::move( pdf ),
                            std::move( cdf ) );

      THEN( "a ComptonProfile can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ComptonProfile chunk( xss.begin(), xss.end() );

      THEN( "a ComptonProfile can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ComptonProfile chunk( xss.begin(), xss.end() );
      ComptonProfile copy( chunk );

      THEN( "an ComptonProfile can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ComptonProfile chunk( xss.begin(), xss.end() );
      ComptonProfile move( std::move( chunk ) );

      THEN( "an ComptonProfile can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ComptonProfile chunk( xss.begin(), xss.end() );
      ComptonProfile copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ComptonProfile can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ComptonProfile chunk( xss.begin(), xss.end() );
      ComptonProfile move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ComptonProfile can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {                 2,                  3,  1.00000000000E-11,  1.00000000000E+00,
           2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const ComptonProfile& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "ComptonProfile" == chunk.name() );

  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberValues() );

  CHECK( 3 == chunk.momentum().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.momentum().front() ) );
  CHECK_THAT( 20., WithinRel( chunk.momentum().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK_THAT( .5, WithinRel( chunk.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK_THAT( 0., WithinRel( chunk.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( chunk.cdf().back() ) );
}

ComptonProfile makeDummyBlock() {

  return { 2, { 1., 2. }, { 3., 4. }, { 5., 6. } };
}
