#ifndef NJOY_FORMAT_ACE_READ_PHOTONUCLEAR_CREATEREACTION
#define NJOY_FORMAT_ACE_READ_PHOTONUCLEAR_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/ace/read/continuous/createTabulatedCrossSection.hpp"
#include "ACEtk/PhotonuclearTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photonuclear {

  /**
   *  @brief Create the reactions for photonuclear data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   *  @param[in] index        the reaction index in the ACE file
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline dryad::Reaction
  createReaction( const dryad::id::ParticleID& projectile,
                  const dryad::id::ParticleID& target,
                  const ACEtk::PhotonuclearTable& table,
                  std::size_t index,
                  bool /* normalise */ ) {

    auto mt = table.reactionNumberBlock().reactionNumber( index );
    Log::info( "Reading data for MT{}", mt );

    std::optional< double > qValue = std::nullopt;
    if ( index <= table.reactionQValueBlock().numberReactions() ) {

      qValue = table.reactionQValueBlock().QValue( index ) * constants::mega;
    }

    return dryad::Reaction( dryad::id::ReactionID( projectile, target, mt ),
                            continuous::createTabulatedCrossSection( table, index ),
                            {}, std::nullopt, std::move( qValue ) );
  }

} // photonuclear namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
