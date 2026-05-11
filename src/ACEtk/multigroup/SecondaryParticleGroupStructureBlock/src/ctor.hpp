SecondaryParticleGroupStructureBlock() = default;

SecondaryParticleGroupStructureBlock( const SecondaryParticleGroupStructureBlock& ) = default;
SecondaryParticleGroupStructureBlock( SecondaryParticleGroupStructureBlock&& ) = default;

SecondaryParticleGroupStructureBlock& operator=( const SecondaryParticleGroupStructureBlock& ) = default;
SecondaryParticleGroupStructureBlock& operator=( SecondaryParticleGroupStructureBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] groupMeans         the mean energies of the groups in MeV
 *  @param[in] groupWidths        the widths of each group in MeV
 */
SecondaryParticleGroupStructureBlock( std::vector< double > groupMeans, std::vector< double > groupWidths ) :
  ArrayData( "ERG2",
             std::move( groupMeans ), std::move( groupWidths ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the iterator to the second element of the  of the ERG2 block in the XSS array
 *  @param[in] end      the end iterator of the ERG2 block in the XSS array
 *  @param[in] ngrp     the number of energy groups
 */
SecondaryParticleGroupStructureBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
  ArrayData( "ERG2", begin, end, ngrp, 2 ) {}
