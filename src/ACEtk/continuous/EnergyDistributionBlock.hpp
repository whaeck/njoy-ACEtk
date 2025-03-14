#ifndef NJOY_ACETK_CONTINUOUS_ENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_ENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBinData.hpp"
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"
#include "ACEtk/continuous/LevelScatteringDistribution.hpp"
#include "ACEtk/continuous/OutgoingEnergyDistributionData.hpp"
#include "ACEtk/continuous/GeneralEvaporationSpectrum.hpp"
#include "ACEtk/continuous/SimpleMaxwellianFissionSpectrum.hpp"
#include "ACEtk/continuous/EvaporationSpectrum.hpp"
#include "ACEtk/continuous/EnergyDependentWattSpectrum.hpp"
#include "ACEtk/continuous/KalbachMannDistributionData.hpp"
#include "ACEtk/continuous/NBodyPhaseSpaceDistribution.hpp"
#include "ACEtk/continuous/TwoBodyTransferDistribution.hpp"
#include "ACEtk/continuous/EnergyAngleDistributionData.hpp"
#include "ACEtk/continuous/AngleEnergyDistributionData.hpp"
#include "ACEtk/continuous/MultiDistributionData.hpp"
#include "ACEtk/continuous/UndefinedDistribution.hpp"
#include "ACEtk/continuous/TabulatedMultiplicity.hpp"
#include "ACEtk/ReferenceFrame.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/* type alias */
using EnergyDistributionData = std::variant< EquiprobableOutgoingEnergyBinData,
                                             DiscretePhotonDistribution,
                                             LevelScatteringDistribution,
                                             OutgoingEnergyDistributionData,
                                             GeneralEvaporationSpectrum,
                                             SimpleMaxwellianFissionSpectrum,
                                             EvaporationSpectrum,
                                             EnergyDependentWattSpectrum,
                                             KalbachMannDistributionData,
                                             NBodyPhaseSpaceDistribution,
                                             TwoBodyTransferDistribution,
                                             EnergyAngleDistributionData,
                                             AngleEnergyDistributionData,
                                             MultiDistributionData,
                                             UndefinedDistribution >;
using MultiplicityData = std::variant< unsigned int, TabulatedMultiplicity >;

/**
 *  @class
 *  @brief The continuous energy LDLW and DLW block with the energy
 *         distribution data
 *
 *  The EnergyDistributionBlock class contains energy distribution data,
 *  one for each the first NXS(5) reaction numbers on the MTR block. The order
 *  of the distribution data sets is the same as the order of the reaction
 *  numbers in the MTR block.
 */
class EnergyDistributionBlock : protected base::Base {

  /* fields */
  unsigned int nr_ = 0; // the number of reactions
  Iterator iterator_;   // the begin iterator of the data block
  continuous::TYR tyr_;      // the associated TYR block
  std::vector< EnergyDistributionData > data_;
  std::vector< MultiplicityData > multiplicities_;
  std::vector< ReferenceFrame > frames_;

  /* auxiliary functions */
  #include "ACEtk/continuous/EnergyDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/EnergyDistributionBlock/src/generateBlocks.hpp"
  #include "ACEtk/continuous/EnergyDistributionBlock/src/verifyDataIndex.hpp"
  #include "ACEtk/continuous/EnergyDistributionBlock/src/verifySize.hpp"

  /**
   *  @brief Return the iterator to the start of the sig block
   */
  Iterator iter() const { return this->iterator_; }

  /**
   *  @brief Return the associated TYR block
   *
   *  Note: this TYR block may not be completely compatible with the normal TYR
   *        block since it only contains data for the first NR reactions (instead
   *        of NTR).
   */
  const continuous::TYR& TYR() const { return this->tyr_; }

public:

  /* constructor */
  #include "ACEtk/continuous/EnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return this->nr_; }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int numberReactions() const { return this->NR(); }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LDLW( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->IXSS( index );
  }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int energyDistributionLocator( std::size_t index ) const {

    return this->LDLW( index );
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< EnergyDistributionData >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the energy distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const EnergyDistributionData& energyDistributionData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->data_[ index - 1 ];
  }

  /**
   *  @brief Return all multiplicity data
   */
  const std::vector< MultiplicityData >& multiplicities() const {

    return this->multiplicities_;
  }

  /**
   *  @brief Return the multiplicity data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const MultiplicityData& multiplicityData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->multiplicities_[ index - 1 ];
  }

  /**
   *  @brief Return all reference frames
   */
  const std::vector< ReferenceFrame >& referenceFrames() const {

    return this->frames_;
  }

  /**
   *  @brief Return the reference frame for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const ReferenceFrame& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->frames_[ index - 1 ];
  }

  /**
   *  @brief Return the associated TYR multiplicity entries (internal only)
   */
  auto tyrMultiplicities() const {

    return this->tyr_.multiplicities();
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLW = EnergyDistributionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
