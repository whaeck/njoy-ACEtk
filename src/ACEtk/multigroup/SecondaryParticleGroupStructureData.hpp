#ifndef NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTUREDATA
#define NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTUREDATA

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup energy ERG2 block with the secondary particle group structures
 *
 *  The SecondaryParticleGroupStructureData class contains 2 arrays of the same length:
 *    - the mean energies of each group (in MeV)
 *    - the widths of each group (in MeV)
 *
 *  The size of each (the total number of energy groups), NERG, is LERG2(i).
 */
class SecondaryParticleGroupStructureData : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/multigroup/SecondaryParticleGroupStructureData/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int NERG() const { return this->N(); }

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int numberEnergyGroups() const { return this->NERG(); }

  /**
   *  @brief Return the mean energies of the groups
   */
  auto ECENT2() const { return this->darray( 1 ); }

  /**
   *  @brief Return the mean energies of the groups
   */
  auto groupMeans() const { return this->ECENT2(); }


  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto EWID2() const { return this->darray( 2 ); }

  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto groupWidths() const { return this->EWID2(); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ERG2 = SecondaryParticleGroupStructureData;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
