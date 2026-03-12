#ifndef NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTURELOCATORBLOCK
#define NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTURELOCATORBLOCK

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup ERG2L block with locators for the group structure block(s)
 *         for the secondary particle(s)
 *
 *  The SecondaryParticleGroupStructureLocatorBlock class contains NSEC locators, one 
 *  for each secondary particle type given in the IPT block.
 *
 *  The number of secondary particles is stored in NXS(8).
 */
class SecondaryParticleGroupStructureLocatorBlock : protected base::Base {

  /* fields */
  unsigned int nsec_ = 0;

  /* auxiliary functions */
  #include "ACEtk/multigroup/SecondaryParticleGroupStructureLocatorBlock/src/generateXSS.hpp"
  #include "ACEtk/multigroup/SecondaryParticleGroupStructureLocatorBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/multigroup/SecondaryParticleGroupStructureLocatorBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle types 
   */
  unsigned int NSEC() const { return this->nsec_; }

  /**
   *  @brief Return the number of secondary particle types 
   */
  unsigned int numberSecondaryParticleTypes() const {

    return this->NSEC();
  }

  /**
   *  @brief Return the locator for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based)
   */
  std::size_t ERG2( std::size_t particle ) const {

    return this->IXSS( particle );
  }

  /**
   *  @brief Return the locator for a secondary particle index 
   *
   *  @param[in] particle    the secondary particle index (one-based)
   */
  std::size_t locator( std::size_t particle ) const {

    return this->ERG2( particle );
  }



  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ERG2L = SecondaryParticleGroupStructureLocatorBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
