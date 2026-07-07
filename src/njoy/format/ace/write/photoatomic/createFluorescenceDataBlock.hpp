#ifndef NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATEFLUORESCENCEDATABLOCK
#define NJOY_FORMAT_ACE_WRITE_PHOTOATOMIC_CREATEFLUORESCENCEDATABLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "scion/math/compare.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace photoatomic {

  /**
   *  @brief Create the fluorescence data block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget and AtomicRelaxation instance used
   *  is valid data, and ACE compatible (i.e. unionised energy grid, etc.).
   *
   *  This function applies the MCN fluorescence model using the atomic relaxation
   *  data and the total photon ionisation cross section. See the following
   *  reference for more information:
   *    C. J. Everett, E. D. Cashwell, MCP Code Fluorescence -  Routine Revision,
   *    LA-05240-MS, 1973
   *
   *  The code in this function reproduces the results from the alax subroutine
   *  in NJOY2016. The eprdata files contain the atomic relaxation data in addition
   *  to this fluorescence model so technically speaking one could use the relaxation
   *  data instead of this model to generate X-rays and Auger electrons. However, the
   *  heating numbers still assume the use of this older fluorescence model.
   *
   *  @param[in] photoatomic   the photoatomic data
   *  @param[in] relaxation    the atomic relaxation data
   */
  inline njoy::ACEtk::photoatomic::FluorescenceDataBlock
  createFluorescenceDataBlock( const dryad::ProjectileTarget& photoatomic,
                               const dryad::AtomicRelaxation& relaxation ) {

    // the data to be put in the block
    std::vector< double > edges;
    std::vector< double > probabilities;
    std::vector< double > yields;
    std::vector< double > energies;

    // energy is converted to MeV
    auto convertEnergy = [] ( auto&& energy ) {

      return energy * constants::micro;
    };

    // common identifiers
    dryad::id::ParticleID projectile = photoatomic.projectileIdentifier();
    dryad::id::ParticleID target = photoatomic.targetIdentifier();
    dryad::id::ElectronSubshellID k( "K" );
    dryad::id::ElectronSubshellID l1( "L1" );
    dryad::id::ElectronSubshellID l2( "L2" );
    dryad::id::ElectronSubshellID l3( "L3" );
    dryad::id::ElectronSubshellID m1( "M1" );
    dryad::id::ElectronSubshellID m5( "M5" );
    dryad::id::ElectronSubshellID n1( "N1" );
    dryad::id::ElectronSubshellID q13( "Q13" );
    dryad::id::ReactionID total_ionisation( projectile, target, 522 );

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
    auto calculate_edge_ratio = [] ( double edge, const dryad::TabulatedCrossSection& xs ) {

      for ( std::size_t index : xs.boundaries() ) {

        if ( scion::math::isClose( edge, xs.energies()[index] ) ) {

          return xs.values()[index] / xs.values()[index + 1];
        }
      }
      throw std::runtime_error( "Could not find edge at " + std::to_string( edge ) +
                                " as a jump in the total ionisation cross section" );
    };
    decltype(auto) xs = photoatomic.reaction( total_ionisation ).crossSection();
    double k_ratio = has_k ? calculate_edge_ratio( k_edge, xs ) : 0.;
    double l1_ratio = has_l1 ? calculate_edge_ratio( l1_edge, xs ) : 0.;
    double l2_ratio = has_l2 ? calculate_edge_ratio( l2_edge, xs ) : 0.;
    double l3_ratio = has_l3 ? calculate_edge_ratio( l3_edge, xs ) : 0.;
    double l_ratio = l1_ratio * l2_ratio * l3_ratio;

    // calculate k shell related data:
    // - k shell average energy and probability
    // - l2 and l3 transition energy and probability
    // - outer shell transition average energies and probabilities
    decltype(auto) k_shell = relaxation.subshell( k );
    auto has_l2_transition = k_shell.hasRadiativeTransition( l2 );
    auto has_l3_transition = k_shell.hasRadiativeTransition( l3 );
    double k_average_energy = k_shell.averageRadiativeEnergy();
    double k_probability = k_shell.totalRadiativeProbability();
    double l2_energy = has_l2_transition ? k_shell.radiativeTransition( l2 ).energy().value() : 0.;
    double l3_energy = has_l3_transition ? k_shell.radiativeTransition( l3 ).energy().value() : 0.;
    double l2_probability = has_l2_transition ? k_shell.radiativeTransition( l2 ).probability() : 0.;
    double l3_probability = has_l3_transition ? k_shell.radiativeTransition( l3 ).probability() : 0.;
    double m_probability = target.z() < 37 ? 0. : k_shell.radiativeProbability( m1, m5 );
    double m_energy = target.z() < 37 ? 0. : k_shell.averageRadiativeEnergy( m1, m5 );
    double outer_probability = target.z() > 19 ? k_shell.radiativeProbability( target.z() < 37 ? m1 : n1, q13 ) : 0.;
    double outer_energy = target.z() > 19 ? k_shell.averageRadiativeEnergy( target.z() < 37 ? m1 : n1, q13 ) : 0.;

    // note: when z > 37, NJOY2016 calculates the outer_probability and outer_energy
    // for transitions originating from shell N1 to N7. Here, we use transitions from
    // shell N1 and higher instead to be in line with how it is calculated for z > 19 and
    // z <= 36. This may lead to small differences with older ACE files or NJOY2016.

    // as a function of the z value
    if ( target.z() > 11 && target.z() < 20 ) {

      // fill the data
      edges = { k_edge, k_edge };
      probabilities = { k_ratio, 1. };
      yields = { 0., ( 1 - k_ratio ) * k_probability };
      energies = { 0., k_average_energy };
    }
    else if ( target.z() > 19 && target.z() < 31 ) {

      // fill the data
      double factor = ( 1. - k_ratio ) / ( l3_probability + l2_probability + outer_probability );
      edges = { k_edge, k_edge, k_edge, k_edge };
      probabilities = { k_ratio,
                        k_ratio + factor * l3_probability,
                        k_ratio + factor * ( l3_probability + l2_probability ),
                        1. };
      yields = { 0.,
                 ( 1. - k_ratio ) * l3_probability,
                 ( 1. - k_ratio ) * ( l3_probability + l2_probability ),
                 ( 1. - k_ratio ) * ( l3_probability + l2_probability + outer_probability ) };
      energies = { 0., l3_energy, l2_energy, outer_energy };
    }
    else if ( target.z() > 30 ) {

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

      // fill the data
      double factor = ( 1. - k_ratio ) / k_ratio;
      if ( target.z() < 37 ) {

        double total = k_ratio * ( l2_probability + l3_probability +
                                   outer_probability ) / ( 1. - k_ratio );

        edges = { l_edge, l_edge, k_edge, k_edge, k_edge };
        probabilities = { l_ratio, 1.,
                          1. + l3_probability / total,
                          1. + ( l3_probability + l2_probability ) / total,
                          1. / k_ratio };
        yields = { 0.,
                   ( 1. - l_ratio ) * l_probability,
                   ( 1. - l_ratio ) * l_probability + factor * l3_probability,
                   ( 1. - l_ratio ) * l_probability + factor * ( l3_probability + l2_probability ),
                   ( 1. - l_ratio ) * l_probability + factor * ( l3_probability + l2_probability +
                                                                 outer_probability ) };
        energies = { 0., l_average_energy, l3_energy, l2_energy, outer_energy };
      }
      else {

        double total = k_ratio * ( l2_probability + l3_probability +
                                   m_probability + outer_probability ) / ( 1. - k_ratio );

        edges = { l_edge, l_edge, k_edge, k_edge, k_edge, k_edge };
        probabilities = { l_ratio, 1.,
                          1. + l3_probability / total,
                          1. + ( l3_probability + l2_probability ) / total,
                          1. + ( l3_probability + l2_probability + m_probability ) / total,
                          1. / k_ratio };
        yields = { 0.,
                   ( 1. - l_ratio ) * l_probability,
                   ( 1. - l_ratio ) * l_probability + factor * l3_probability,
                   ( 1. - l_ratio ) * l_probability + factor * ( l3_probability + l2_probability ),
                   ( 1. - l_ratio ) * l_probability + factor * ( l3_probability + l2_probability +
                                                                 m_probability ),
                   ( 1. - l_ratio ) * l_probability + factor * ( l3_probability + l2_probability +
                                                                 m_probability + outer_probability ) };
        energies = { 0., l_average_energy, l3_energy, l2_energy, m_energy, outer_energy };
      }
    }

    std::transform( edges.begin(), edges.end(), edges.begin(), convertEnergy );
    std::transform( energies.begin(), energies.end(), energies.begin(), convertEnergy );

    return njoy::ACEtk::photoatomic::FluorescenceDataBlock(
               std::move( edges ), std::move( probabilities ),
               std::move( yields ), std::move( energies ) );
  }

} // photoatomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
