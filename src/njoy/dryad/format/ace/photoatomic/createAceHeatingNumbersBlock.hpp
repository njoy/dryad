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

  inline TabulatedAverageEnergy
  calculateAverageFluorescenceEnergy( const ProjectileTarget& photoatomic,
                                      const AtomicRelaxation& relaxation ) {

    std::vector< double > energies = photoatomic.reactions().front().crossSection().energies();
    std::vector< double > fluorescence( energies.size(), 0. );

    // identifiers
    decltype(auto) projectile = photoatomic.projectileIdentifier();
    decltype(auto) target = photoatomic.targetIdentifier();
    dryad::id::ReactionID totalionisation_id( projectile, target, dryad::id::ReactionType( projectile, 522 ) );

    // electron subshell identifiers
    id::ElectronSubshellID k( "K" );
    id::ElectronSubshellID l1( "L1" );
    id::ElectronSubshellID l2( "L2" );
    id::ElectronSubshellID l3( "L3" );
    id::ElectronSubshellID m1( "M1" );
    id::ElectronSubshellID m5( "M5" );
    id::ElectronSubshellID n1( "N1" );
    id::ElectronSubshellID q13( "Q13" );

    // a few booleans
    auto has_k = relaxation.hasSubshell( k );
    auto has_l1 = relaxation.hasSubshell( l1 );
    auto has_l2 = relaxation.hasSubshell( l2 );
    auto has_l3 = relaxation.hasSubshell( l3 );

    // binding/edge energies for K, L1, L2 and L3 shells (zero if they do not exist)
    double k_edge = ( has_k ? relaxation.subshell( k ).bindingEnergy() : 0. );
    double l1_edge = ( has_l1 ? relaxation.subshell( l1 ).bindingEnergy() : 0. );
    double l2_edge = ( has_l2 ? relaxation.subshell( l2 ).bindingEnergy() : 0. );
    double l3_edge = ( has_l3 ? relaxation.subshell( l3 ).bindingEnergy() : 0. );
    double l_edge = ( l1_edge + l2_edge + l3_edge ) / 3.;

    // search for the edges in the total ionisation xs and calculate low/high
    auto calculate_edge_ratio = [] ( double edge, const TabulatedCrossSection& xs ) {

      for ( std::size_t index : xs.boundaries() ) {

        if ( scion::math::isClose( edge, xs.energies()[index] ) ) {

          return xs.values()[index] / xs.values()[index + 1];
        }
      }
      throw std::runtime_error( "Could not find edge at " + std::to_string( edge ) +
                                " as a jump in the total ionisation cross section" );
    };
    decltype(auto) xs = photoatomic.reaction( totalionisation_id ).crossSection();
    double k_ratio = has_k ? calculate_edge_ratio( k_edge, xs ) : 0.;
    double l1_ratio = has_l1 ? calculate_edge_ratio( l1_edge, xs ) : 0.;
    double l2_ratio = has_l2 ? calculate_edge_ratio( l2_edge, xs ) : 0.;
    double l3_ratio = has_l3 ? calculate_edge_ratio( l3_edge, xs ) : 0.;
    double l_ratio = l1_ratio * l2_ratio * l3_ratio;

    // calculate k shell related data:
    // - k shell average energy and probability
    // - l2 and l3 transition energy and probability
    // - outer shell transition average energies and probabilities
    auto z = relaxation.elementIdentifier().number();
    decltype(auto) k_shell = relaxation.subshell( k );
    auto has_l2_transition = k_shell.hasRadiativeTransition( l2 );
    auto has_l3_transition = k_shell.hasRadiativeTransition( l3 );
    double k_average_energy = k_shell.averageRadiativeEnergy();
    double k_probability = k_shell.totalRadiativeProbability();
    double l2_energy = has_l2_transition ? k_shell.radiativeTransition( l2 ).energy().value() : 0.;
    double l3_energy = has_l3_transition ? k_shell.radiativeTransition( l3 ).energy().value() : 0.;
    double l2_probability = has_l2_transition ? k_shell.radiativeTransition( l2 ).probability() : 0.;
    double l3_probability = has_l3_transition ? k_shell.radiativeTransition( l3 ).probability() : 0.;
    double m_probability = z < 37 ? 0. : k_shell.radiativeProbability( m1, m5 );
    double m_energy = z < 37 ? 0. : k_shell.averageRadiativeEnergy( m1, m5 );
    double outer_probability = z > 19 ? k_shell.radiativeProbability( z < 37 ? m1 : n1, q13 ) : 0.;
    double outer_energy = z > 19 ? k_shell.averageRadiativeEnergy( z < 37 ? m1 : n1, q13 ) : 0.;

    // set average outgoing energies

    // as a function of the z value
    if ( z > 11 && z < 20 ) {

      auto iter = std::upper_bound( energies.begin(), energies.end(), k_edge );
      auto fiter = std::next( fluorescence.begin(), std::distance( energies.begin(), iter ) );
      std::transform( fiter, fluorescence.end(), fiter,
                      [&] ( const auto& ) { return k_probability * k_average_energy; } );
    }
    else {

      auto iter = std::upper_bound( energies.begin(), energies.end(), k_edge );
      auto fiter = std::next( fluorescence.begin(), std::distance( energies.begin(), iter ) );
      std::transform( fiter, fluorescence.end(), fiter,
                      [&] ( const auto& ) { return l2_probability * l2_energy + l3_probability * l3_energy +
                                                   m_probability * m_energy +outer_probability * outer_energy; } );

      if ( z > 30 ) {

        // calculate l1, l2 and l3 shell related data
        decltype(auto) l1_shell = relaxation.subshell( l1 );
        decltype(auto) l2_shell = relaxation.subshell( l2 );
        decltype(auto) l3_shell = relaxation.subshell( l3 );
        double l1_weight = ( l2_ratio * l3_ratio - l_ratio ) / ( 1. - l_ratio );
        double l2_weight = ( l3_ratio - l2_ratio * l3_ratio ) / ( 1. - l_ratio );
        double l3_weight = ( 1. - l3_ratio ) / ( 1. - l_ratio );

        double l_probability = ( l1_shell.totalRadiativeProbability() * l1_weight +
                                 l2_shell.totalRadiativeProbability() * l2_weight +
                                 l3_shell.totalRadiativeProbability() * l3_weight );
        double l_average_energy = ( l1_shell.averageRadiativeEnergy() * l1_shell.totalRadiativeProbability() * l1_weight +
                                    l2_shell.averageRadiativeEnergy() * l2_shell.totalRadiativeProbability() * l2_weight +
                                    l3_shell.averageRadiativeEnergy() * l3_shell.totalRadiativeProbability() * l3_weight ) /
                                  l_probability;

        iter = std::upper_bound( energies.begin(), energies.end(), l_edge );
        fiter = std::next( fluorescence.begin(), std::distance( energies.begin(), iter ) );
        std::transform( fiter, fluorescence.end(), fiter,
                        [&] ( const auto& ) { return l_probability * l_average_energy; } );
      }
    }

    return TabulatedAverageEnergy( std::move( energies ), std::move( fluorescence ) );
  }

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
    auto totalionisation_average = calculateAverageFluorescenceEnergy( photoatomic, relaxation );
    auto totalionisation_heat = incident + qvalue - totalionisation_average;

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
