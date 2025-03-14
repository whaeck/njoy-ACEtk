// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EvaporationSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EvaporationSpectrum = continuous::EvaporationSpectrum;

std::vector< double > chunk();
void verifyChunk( const EvaporationSpectrum&, const std::vector< double >& );
EvaporationSpectrum makeDummyBlock();

SCENARIO( "EvaporationSpectrum" ) {

  GIVEN( "valid data for a EvaporationSpectrum instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1e-5, 1., 10., 20. };
      std::vector< double > temperatures = { 1., 2., 3., 4. };
      double energy = 1.5e+6;

      EvaporationSpectrum chunk( std::move( energies ),
                                            std::move( temperatures ),
                                            energy );

      THEN( "a EvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );

      THEN( "an EvaporationSpectrum can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );
      EvaporationSpectrum copy( chunk );

      THEN( "an EvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );
      EvaporationSpectrum move( std::move( chunk ) );

      THEN( "an EvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );
      EvaporationSpectrum copy = makeDummyBlock();
      copy = chunk;

      THEN( "an EvaporationSpectrum can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      EvaporationSpectrum chunk( xss.begin(), xss.end() );
      EvaporationSpectrum move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an EvaporationSpectrum can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 0,
           4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
           1.5e+6 };
}

void verifyChunk( const EvaporationSpectrum& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "EvaporationSpectrum" == chunk.name() );

  CHECK( EnergyDistributionType::Evaporation == chunk.LAW() );
  CHECK( EnergyDistributionType::Evaporation == chunk.type() );

  CHECK( 0 == chunk.interpolationData().NB() );
  CHECK( 0 == chunk.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == chunk.interpolationData().INT().size() );
  CHECK( 0 == chunk.interpolationData().interpolants().size() );
  CHECK( 0 == chunk.interpolationData().NBT().size() );
  CHECK( 0 == chunk.interpolationData().boundaries().size() );

  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == chunk.INT().size() );
  CHECK( 0 == chunk.interpolants().size() );
  CHECK( 0 == chunk.NBT().size() );
  CHECK( 0 == chunk.boundaries().size() );

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberEnergyPoints() );

  CHECK( 4 == chunk.energies().size() );
  CHECK_THAT( 1e-05, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( chunk.energies()[3] ) );

  CHECK( 4 == chunk.temperatures().size() );
  CHECK_THAT( 1., WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.temperatures()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.temperatures()[3] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 1.5e+6 == chunk.U() );
  CHECK( 1.5e+6 == chunk.restrictionEnergy() );
}

EvaporationSpectrum makeDummyBlock() {

  return { { 1e-5, 20. }, { 1., 4. }, 1. };
}