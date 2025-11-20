#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEREACTION
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEREACTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/ace/continuous/createTabulatedCrossSection.hpp"
#include "ACEtk/ContinuousEnergyTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace continuous {

  /**
   *  @brief Create the reactions for continuous energy data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   *  @param[in] index        the reaction index in the ACE file
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline Reaction
  createReaction( const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const ACEtk::ContinuousEnergyTable& table,
                  std::size_t index,
                  bool normalise ) {

    auto mt = table.reactionNumberBlock().reactionNumber( index );
    Log::info( "Reading data for MT{}", mt );

    return Reaction( id::ReactionID( projectile, target, mt ),
                     continuous::createTabulatedCrossSection( table, index ) );
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
