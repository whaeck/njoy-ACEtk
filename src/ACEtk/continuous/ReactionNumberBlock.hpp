#ifndef NJOY_ACETK_CONTINUOUS_REACTIONNUMBERBLOCK
#define NJOY_ACETK_CONTINUOUS_REACTIONNUMBERBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy MTR block with the reaction MT numbers
 *
 *  The ReactionNumberBlock class contains the reaction MT numbers for all
 *  available reactions (excluding elastic)
 *
 *  The number of available reactions (excluding elastic) is stored in NXS(4).
 */
class ReactionNumberBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/ReactionNumberBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->N(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int MT( std::size_t index ) const {

    return static_cast< unsigned int >( this->ivalue( 1, index ) );
  }

  /**
   *  @brief Return the reaction number for a reaction index
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int reactionNumber( std::size_t index ) const {

    return this->MT( index );
  }

  /**
   *  @brief Return the reaction numbers
   */
  auto MTs() const { return this->iarray( 1 ); }

  /**
   *  @brief Return the reaction numbers
   */
  auto reactionNumbers() const { return this->MTs(); }

  /**
   *  @brief Return whether or not the reaction number is present
   *
   *  @param[in] reaction    the reaction number
   */
  bool hasMT( unsigned int reaction ) const {

    // need to round the value before comparing due to roundoff errors
    return std::find_if(
               this->begin(),
               this->begin() + this->NTR(),
               [reaction] ( auto&& value ) {

                 return static_cast< unsigned int >( std::round( value ) )
                        == reaction;
               } ) != this->end();
  }

  /**
   *  @brief Return whether or not the reaction number is present
   *
   *  @param[in] reaction    the reaction number
   */
  bool hasReactionNumber( unsigned int reaction ) const {

    return this->hasMT( reaction );
  }

  /**
   *  @brief Return the index (one-based) of the reaction number
   *
   *  @param[in] reaction    the reaction number
   */
  std::size_t index( unsigned int reaction ) const {

    auto iter = std::find_if(
                    this->begin(), this->begin() + this->NTR(),
                    [reaction] ( auto&& value ) {

                      return static_cast< unsigned int >( std::round( value ) )
                             == reaction;
                    } );
    if ( iter != this->end() ) {

      return std::distance( this->begin(), iter ) + 1;
    }
    else {

      Log::error( "The requested reaction number MT{} is not present", reaction );
      throw std::exception();
    }
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using MTR = ReactionNumberBlock;
using MTRP = ReactionNumberBlock;
using MTRH = ReactionNumberBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
