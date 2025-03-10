// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/PhotonProductionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotonProductionBlock = continuous::PhotonProductionBlock;

std::vector< double > chunk();
void verifyChunk( const PhotonProductionBlock&, const std::vector< double >& );
PhotonProductionBlock makeDummyBlock();

SCENARIO( "PhotonProductionBlock" ) {

  GIVEN( "valid data for a PhotonProductionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > production = {

                                                                 1.17771501000E+03,
        8.32878160000E+02, 5.26963255000E+02, 3.72860705000E+02, 2.63993524000E+02,
        1.67610483000E+02, 1.19277715000E+02, 8.54096130000E+01, 5.60122893000E+01,
        4.18877751000E+01, 3.26778146000E+01, 3.04231461000E+01, 2.57923581000E+01,
        2.31941021000E+01, 2.18532558000E+01, 2.10313719000E+01, 2.07491966000E+01,
        2.06037794000E+01, 2.05115346000E+01, 2.04777658000E+01, 2.04585030000E+01,
        2.04422859000E+01, 2.04307615000E+01, 2.04144624000E+01, 2.03721297000E+01,
        2.03046009000E+01, 2.01723458000E+01, 1.99144127000E+01, 1.97892313000E+01,
        1.96641245000E+01, 1.94210094000E+01, 1.91847439000E+01, 1.86220408000E+01,
        1.80961984000E+01, 1.62960783000E+01, 1.55815917000E+01, 1.48677251000E+01,
        1.37062041000E+01, 1.27427238000E+01, 1.09238445000E+01, 9.64358528000E+00,
        7.95229561000E+00, 6.87663428000E+00, 6.12560229000E+00, 5.56699890000E+00,
        5.13210634000E+00, 4.78165124000E+00, 4.49154240000E+00, 4.24618070000E+00,
        3.85053146000E+00, 3.54181422000E+00, 3.29137287000E+00, 3.08224139000E+00,
        2.90369677000E+00, 2.74859202000E+00, 2.61196516000E+00, 2.49024321000E+00,
        2.38078120000E+00, 2.28156513000E+00, 2.19103601000E+00, 2.10795886000E+00,
        2.03134269000E+00, 1.96037450000E+00, 1.89438931000E+00, 1.83282710000E+00,
        1.77521589000E+00, 1.72115668000E+00, 1.67030247000E+00, 1.62235727000E+00,
        1.51359377000E+00, 1.41819631000E+00, 1.33374287000E+00, 1.25840048000E+00,
        1.19073011000E+00, 1.12959677000E+00, 1.07408446000E+00, 1.02344716000E+00,
        9.77066588000E-01, 9.34429025000E-01, 8.95099875000E-01, 8.58710735000E-01,
        8.24946302000E-01, 7.93535076000E-01, 7.64241754000E-01, 7.36861535000E-01,
        7.11214819000E-01, 6.87143905000E-01, 6.64509492000E-01, 6.43187979000E-01,
        6.23069267000E-01, 6.04055154000E-01, 5.86057740000E-01, 5.68997726000E-01,
        5.52804011000E-01, 5.37412095000E-01, 5.22763779000E-01, 5.08805961000E-01,
        4.95490443000E-01, 4.82773424000E-01
      };

      PhotonProductionBlock chunk( std::move( production ) );

      THEN( "a PhotonProductionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      PhotonProductionBlock chunk( xss.begin(), xss.end(), 99 );

      THEN( "a PhotonProductionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      PhotonProductionBlock chunk( xss.begin(), xss.end(), 99 );
      PhotonProductionBlock copy( chunk );

      THEN( "an PhotonProductionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      PhotonProductionBlock chunk( xss.begin(), xss.end(), 99 );
      PhotonProductionBlock move( std::move( chunk ) );

      THEN( "an PhotonProductionBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      PhotonProductionBlock chunk( xss.begin(), xss.end(), 99 );
      PhotonProductionBlock copy = makeDummyBlock();
      copy = chunk;

      THEN( "an PhotonProductionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      PhotonProductionBlock chunk( xss.begin(), xss.end(), 99 );
      PhotonProductionBlock move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an PhotonProductionBlock can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                                                             1.17771501000E+03,
    8.32878160000E+02, 5.26963255000E+02, 3.72860705000E+02, 2.63993524000E+02,
    1.67610483000E+02, 1.19277715000E+02, 8.54096130000E+01, 5.60122893000E+01,
    4.18877751000E+01, 3.26778146000E+01, 3.04231461000E+01, 2.57923581000E+01,
    2.31941021000E+01, 2.18532558000E+01, 2.10313719000E+01, 2.07491966000E+01,
    2.06037794000E+01, 2.05115346000E+01, 2.04777658000E+01, 2.04585030000E+01,
    2.04422859000E+01, 2.04307615000E+01, 2.04144624000E+01, 2.03721297000E+01,
    2.03046009000E+01, 2.01723458000E+01, 1.99144127000E+01, 1.97892313000E+01,
    1.96641245000E+01, 1.94210094000E+01, 1.91847439000E+01, 1.86220408000E+01,
    1.80961984000E+01, 1.62960783000E+01, 1.55815917000E+01, 1.48677251000E+01,
    1.37062041000E+01, 1.27427238000E+01, 1.09238445000E+01, 9.64358528000E+00,
    7.95229561000E+00, 6.87663428000E+00, 6.12560229000E+00, 5.56699890000E+00,
    5.13210634000E+00, 4.78165124000E+00, 4.49154240000E+00, 4.24618070000E+00,
    3.85053146000E+00, 3.54181422000E+00, 3.29137287000E+00, 3.08224139000E+00,
    2.90369677000E+00, 2.74859202000E+00, 2.61196516000E+00, 2.49024321000E+00,
    2.38078120000E+00, 2.28156513000E+00, 2.19103601000E+00, 2.10795886000E+00,
    2.03134269000E+00, 1.96037450000E+00, 1.89438931000E+00, 1.83282710000E+00,
    1.77521589000E+00, 1.72115668000E+00, 1.67030247000E+00, 1.62235727000E+00,
    1.51359377000E+00, 1.41819631000E+00, 1.33374287000E+00, 1.25840048000E+00,
    1.19073011000E+00, 1.12959677000E+00, 1.07408446000E+00, 1.02344716000E+00,
    9.77066588000E-01, 9.34429025000E-01, 8.95099875000E-01, 8.58710735000E-01,
    8.24946302000E-01, 7.93535076000E-01, 7.64241754000E-01, 7.36861535000E-01,
    7.11214819000E-01, 6.87143905000E-01, 6.64509492000E-01, 6.43187979000E-01,
    6.23069267000E-01, 6.04055154000E-01, 5.86057740000E-01, 5.68997726000E-01,
    5.52804011000E-01, 5.37412095000E-01, 5.22763779000E-01, 5.08805961000E-01,
    4.95490443000E-01, 4.82773424000E-01
  };
}

void verifyChunk( const PhotonProductionBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 99 == chunk.length() );
  CHECK( "GPD" == chunk.name() );

  CHECK( 99 == chunk.XSS().size() );

  CHECK( 99 == chunk.NES() );
  CHECK( 99 == chunk.numberEnergyPoints() );
  CHECK( 99 == chunk.totalProduction().size() );

  CHECK_THAT( 1.17771501000E+03, WithinRel( chunk.totalProduction().front() ) );
  CHECK_THAT( 4.82773424000E-01, WithinRel( chunk.totalProduction().back() ) );
}

PhotonProductionBlock makeDummyBlock() {

  return { { 1., 2. } };
}
