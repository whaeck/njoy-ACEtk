private:

/**
 *  @brief Private constructor
 */
SecondaryParticleGroupStructureLocatorBlock(
    std::vector< unsigned int > && locators,
    std::size_t nsec ) :
  Base( "ERG2L", generateXSS( std::move( locators ) ) ),
  nsec_( nsec ) {}

public:

SecondaryParticleGroupStructureLocatorBlock() = default;

SecondaryParticleGroupStructureLocatorBlock( const SecondaryParticleGroupStructureLocatorBlock& ) = default;
SecondaryParticleGroupStructureLocatorBlock( SecondaryParticleGroupStructureLocatorBlock&& ) = default;

SecondaryParticleGroupStructureLocatorBlock& operator=( const SecondaryParticleGroupStructureLocatorBlock& ) = default;
SecondaryParticleGroupStructureLocatorBlock& operator=( SecondaryParticleGroupStructureLocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] locators    the locators for each secondary particle type
 */
SecondaryParticleGroupStructureLocatorBlock(
    std::vector< unsigned int > locators ) :
  SecondaryParticleGroupStructureLocatorBlock( std::move( locators ), locators.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] erg2l     the begin iterator of the ERG2L block in the XSS array
 *  @param[in] end       the end iterator of the ERG2L block in the XSS array
 *  @param[in] nsec      the number of secondary particle types
 */
SecondaryParticleGroupStructureLocatorBlock( Iterator erg2l, Iterator end, unsigned int nsec ) :
  Base( "ERG2L", erg2l, end ), nsec_( nsec ) {

  verifySize( this->begin(), this->end(), this->NSEC() );
}
