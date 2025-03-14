// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedAngularDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedAngularDistribution = continuous::TabulatedAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedAngularDistribution&, const std::vector< double >& );
TabulatedAngularDistribution makeDummyBlock();

SCENARIO( "TabulatedAngularDistribution" ) {

  GIVEN( "valid data for a TabulatedAngularDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 2.1;
      int interpolation = 2;
      std::vector< double > cosines = { -1.0, 0.0, 1.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };

      TabulatedAngularDistribution chunk( energy, interpolation,
                                          std::move( cosines ),
                                          std::move( pdf ), std::move( cdf ) );

      THEN( "a TabulatedAngularDistribution can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      double energy = 2.1;
      TabulatedAngularDistribution chunk( energy, xss.begin(), xss.end() );

      THEN( "a TabulatedAngularDistribution can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      TabulatedAngularDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedAngularDistribution copy( chunk );

      THEN( "an TabulatedAngularDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      TabulatedAngularDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedAngularDistribution move( std::move( chunk ) );

      THEN( "an TabulatedAngularDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      TabulatedAngularDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedAngularDistribution copy = makeDummyBlock();
      copy = chunk;

      THEN( "an TabulatedAngularDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      TabulatedAngularDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedAngularDistribution move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an TabulatedAngularDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {                 2,                  3, -1.00000000000E+00,  0.00000000000E+00,
           1.00000000000E+00,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const TabulatedAngularDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "TabulatedAngularDistribution" == chunk.name() );

  CHECK_THAT( 2.1, WithinRel( chunk.energy() ) );
  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberCosines() );

  CHECK( 3 == chunk.cosines().size() );
  CHECK_THAT( -1., WithinRel( chunk.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( chunk.cosines().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK_THAT( .5, WithinRel( chunk.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK_THAT( 0., WithinRel( chunk.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( chunk.cdf().back() ) );
}

TabulatedAngularDistribution makeDummyBlock() {

  return {1., 2, { -1., 1. }, { 0.5, 0.5 }, { 0., 1. } };
}
