#ifndef NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEELASTICREACTION
#define NJOY_DRYAD_FORMAT_ACE_CONTINUOUS_CREATEELASTICREACTION

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
   *  @brief Create the elastic reaction for continuous energy data
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] table        the ace table
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline Reaction
  createElasticReaction( const id::ParticleID& projectile,
                         const id::ParticleID& target,
                         const ACEtk::ContinuousEnergyTable& table,
                         bool normalise ) {

    Log::info( "Reading data for MT2" );

    // function to convert MeV to eV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::mega;
    };

    // raw cross section data
    auto energies = createVector( table.principalCrossSectionBlock().energies() );
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );
    auto values = createVector( table.principalCrossSectionBlock().elastic() );

    return Reaction( id::ReactionID( projectile, target, 2 ),
                     TabulatedCrossSection( std::move( energies ), std::move( values ) ) );
  }

} // continuous namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
