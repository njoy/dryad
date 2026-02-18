#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEHEATINGNUMBERSBLOCK
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEHEATINGNUMBERSBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the heating numbers block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   *  @param[in] relaxation    the atomic relaxation data
   */
  inline njoy::ACEtk::photoatomic::HeatingNumbersBlock
  createAceHeatingNumbersBlock( const ProjectileTarget& photoatomic,
                                const AtomicRelaxation& relaxation ) {

    // identifiers
    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID incoherent_id( projectile, target, dryad::id::ReactionType( projectile, 504 ) );
    dryad::id::ReactionID coherent_id( projectile, target, dryad::id::ReactionType( projectile, 502 ) );
    dryad::id::ReactionID pairproduction_id( projectile, target, dryad::id::ReactionType( projectile, 516 ) );
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    // get the reactions
    decltype(auto) coherent = photoatomic.reaction( coherent_id );
    decltype(auto) incoherent = photoatomic.reaction( incoherent_id );
    decltype(auto) pairproduction = photoatomic.reaction( pairproduction_id );
    decltype(auto) totalionisation = photoatomic.reaction( totalionisation_id );

    // get the incident energy data
    decltype(auto) energies = photoatomic.reactions().front().crossSection().energies();
    TabulatedAverageEnergy incident( energies, energies );

    // calculate the average energy deposition for incoherent scattering
    double qvalue = 0.;
    decltype(auto) incoherent_average = incoherent.product( projectile ).averageEnergy().value();
    auto incoherent_heat = incident + qvalue - incoherent_average;

    // calculate the average energy deposition for pair production
    // outgoing electrons are assumed to be absorbed
    //! @todo this is how NJOY2016 does it, so maybe better to go over the partials instead?
    qvalue = -2. * constants::electron_rest_mass;
    auto pairproduction_heat = incident + qvalue;

    // calculate the average energy deposition for total ionisation
    // outgoing Auger electrons and X-rays from relaxations are assumed to be absorbed,
    // corrected by the MCP fluorescence model
    //! @todo this is how NJOY2016 does it, so maybe better to go over the partials instead?
    qvalue = 0.;
    auto totalionisation_heat = incident + qvalue;

    // calculate the total cross section value
    TabulatedCrossSection total = coherent.crossSection() + incoherent.crossSection() +
                                  pairproduction.crossSection() + totalionisation.crossSection();

    // calculate heating numbers
    std::vector< double > heating( energies.size() );
    for ( std::size_t i = 0; i < energies.size(); ++i ) {

      heating[i] = ( incoherent_heat.values()[i] * incoherent.crossSection().values()[i] +
                     pairproduction_heat.values()[i] * pairproduction.crossSection().values()[i] +
                     totalionisation_heat.values()[i] * totalionisation.crossSection().values()[i] )
                   / total.values()[i] / constants::mega;
    }

    return njoy::ACEtk::photoatomic::HeatingNumbersBlock( std::move( heating ) );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
