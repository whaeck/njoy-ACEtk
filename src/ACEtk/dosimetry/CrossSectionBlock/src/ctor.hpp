CrossSectionBlock() = default;

CrossSectionBlock( const CrossSectionBlock& ) = default;
CrossSectionBlock( CrossSectionBlock&& ) = default;

CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
CrossSectionBlock( std::vector< CrossSectionData > xs ) :
  BlockWithLocators( "SIGD", std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
 *  @param[in] sig     the begin iterator of the SIGD block in the XSS array
 *  @param[in] end     the end iterator of the SIGD block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
CrossSectionBlock( Iterator lsig, Iterator sig, Iterator end, unsigned int ntr ) :
  BlockWithLocators( "SIGD", lsig, sig, end, ntr ) {}
