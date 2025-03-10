AngularDistributionData() = default;

AngularDistributionData( const AngularDistributionData& base ) :
  Base( base ), locb_( base.locb_ ),
  values_( base.values_ ),
  distributions_( base.distributions_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

AngularDistributionData( AngularDistributionData&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ),
  values_( std::move( base.values_ ) ),
  distributions_( std::move( base.distributions_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

AngularDistributionData& operator=( const AngularDistributionData& base ) {

  if ( this != &base ) {

    Base::operator=( base );
    this->locb_ = base.locb_;
    this->values_ = base.values_;
    this->distributions_ = base.distributions_;
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

AngularDistributionData& operator=( AngularDistributionData&& base ) {

  if ( this != &base ) {

    Base::operator=( std::move( base ) );
    this->locb_ = base.locb_;
    this->values_ = std::move( base.values_ );
    this->distributions_ = std::move( base.distributions_ );
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the angular distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the AND block
 */
AngularDistributionData( std::vector< Distribution > distributions,
                         std::size_t locb = 1 ) :
  Base( "AngularDistributionData",
        generateXSS( std::move( distributions ), locb ) ),
  locb_( locb ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the AND block
 *  @param[in] begin   the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
AngularDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  Base( "AngularDistributionData", begin, end ), locb_( locb ) {

  this->generateBlocks();
  verifySize( this->begin(), this->end(), this->numberIncidentEnergies() );
}
