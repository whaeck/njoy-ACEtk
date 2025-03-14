// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBins.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using EquiprobableOutgoingEnergyBins = continuous::EquiprobableOutgoingEnergyBins;

std::vector< double > chunk();
void verifyChunk( const EquiprobableOutgoingEnergyBins&, const std::vector< double >& );
EquiprobableOutgoingEnergyBins makeDummyBlock();

SCENARIO( "EquiprobableOutgoingEnergyBins" ) {

  GIVEN( "valid data for an EquiprobableOutgoingEnergyBins instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 2.1;
      std::vector< double > energies = { 1e-5, 2e-2, 1., 20. };

      EquiprobableOutgoingEnergyBins chunk( incident, std::move( energies ) );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      double incident = 2.1;
      EquiprobableOutgoingEnergyBins chunk( incident, xss.begin(), xss.end() );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      EquiprobableOutgoingEnergyBins chunk( 2.1, xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBins copy( chunk );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      EquiprobableOutgoingEnergyBins chunk( 2.1, xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBins move( std::move( chunk ) );

      THEN( "an EquiprobableOutgoingEnergyBins can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      EquiprobableOutgoingEnergyBins chunk( 2.1, xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBins copy = makeDummyBlock();
      copy = chunk;

      THEN( "an EquiprobableOutgoingEnergyBins can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      EquiprobableOutgoingEnergyBins chunk( 2.1, xss.begin(), xss.end() );
      EquiprobableOutgoingEnergyBins move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an EquiprobableOutgoingEnergyBins can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

     1.00000000000E-05,  2.00000000000E-02,  1.00000000000E+00,  2.00000000000E+01
  };
}

void verifyChunk( const EquiprobableOutgoingEnergyBins& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 4 == chunk.length() );
  CHECK( "EquiprobableOutgoingEnergyBins" == chunk.name() );

  CHECK_THAT( 2.1, WithinRel( chunk.incidentEnergy() ) );
  CHECK( 3 == chunk.numberBins() );

  CHECK( 4 == chunk.energies().size() );
  CHECK_THAT( 1e-5, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( .02, WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( chunk.energies()[3] ) );
}

EquiprobableOutgoingEnergyBins makeDummyBlock() {

  return { 1, { 1., 2. } };
}