FissionMultiplicityBlock() = default;

FissionMultiplicityBlock( const FissionMultiplicityBlock& base ) :
  Base( base ),
  prompt_( base.prompt_ ), total_( base.total_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

FissionMultiplicityBlock( FissionMultiplicityBlock&& base ) :
  Base( base ),
  prompt_( std::move( base.prompt_ ) ), total_( std::move( base.total_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

FissionMultiplicityBlock& operator=( const FissionMultiplicityBlock& base ) {

  if ( this != &base ) {

    Base::operator=( base );
    this->prompt_ = base.prompt_;
    this->total_ = base.total_;
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

FissionMultiplicityBlock& operator=( FissionMultiplicityBlock&& base ) {

  if ( this != &base ) {

    Base::operator=( std::move( base ) );
    this->prompt_ = std::move( base.prompt_ );
    this->total_ = std::move( base.total_ );
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param[in] prompt    the prompt fission multiplicity data
 */
FissionMultiplicityBlock( FissionMultiplicityData prompt ) :
  Base( "NU", generateXSS( std::move( prompt ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] prompt    the prompt fission multiplicity data
 *  @param[in] total     the total fission multiplicity data
 */
FissionMultiplicityBlock( FissionMultiplicityData prompt,
                          FissionMultiplicityData total ) :
  Base( "NU", generateXSS( std::move( prompt ), std::move( total ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the NU block in the XSS array
 *  @param[in] end      the end iterator of the NU block in the XSS array
 */
FissionMultiplicityBlock( Iterator begin, Iterator end ) :
  Base( "NU", begin, end ) {

  this->generateBlocks();
}
