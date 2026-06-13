#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_CREATERESONANCEPARAMETERS
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_CREATERESONANCEPARAMETERS

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/dryad/format/gnds/convertEnergy.hpp"
#include "njoy/dryad/format/gnds/resonances/createRadius.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createCompoundSystem.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {

  /**
   *  @brief Create the resonance parameters from a parsed ENDF section
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] pops         the global particle database
   *  @param[in] resonances   the GNDS resonances node
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline std::optional< dryad::resonances::ResonanceParameters >
  createResonanceParameters( const id::ParticleID& projectile,
                             const id::ParticleID& target,
                             const ParticleDatabase& pops,
                             const pugi::xml_node& resonances,
                             const std::string& style = "eval" ) {

    // check that this is a valid resonances node
    throwExceptionOnWrongNode( resonances, "resonances" );

    // create the channel radii
    dryad::resonances::ChannelRadii radii;
    auto radius = resonances.child( "scatteringRadius" );
    if ( radius ) {

      radii.penetrabilityRadius( createRadius( radius ) );
    }
    radius = resonances.child( "hardSphereRadius" );
    if ( radius ) {

      radii.phaseShiftRadius( createRadius( radius ) );
    }

    // loop over the resolved nodes
    std::vector< dryad::resonances::CompoundSystem > resolved;
    for ( pugi::xml_node region = resonances.child( "resolved" );
          region; region = region.next_sibling( "resolved" ) ) {

      // get the lower and upper energy
      double lower = region.attribute( "domainMin" ).as_double();
      double upper = region.attribute( "domainMax" ).as_double();
      std::string unit = region.attribute( "domainUnit" ).as_string();
      convertEnergy( lower, unit );
      convertEnergy( upper, unit );

      Log::info( "Reading resolved resonance region between {} and {} eV", lower, upper );

      // get the resonance data
      auto node = region.find_child_by_attribute( "RMatrix", "label", style.c_str() );
      if ( node ) {

        resolved.emplace_back( rmatrix::createCompoundSystem( projectile, target, lower, upper,
                                                              pops, radii, node, style ) );
      }
      else {

        node = region.find_child_by_attribute( "BreitWigner", "label", style.c_str() );

        if ( node ) {

          Log::info( "  Resolved formalism \'{}\' is currently unsupported, skipping", node.name() );
          continue;
        }
        else {

          node = region.find_child_by_attribute( "energyIntervals", "label", style.c_str() );

          if ( node ) {

            Log::info( "  Resolved formalism \'{}\' is currently unsupported, skipping", node.name() );
            continue;
          }
          else {

            Log::error( "  Expected an RMatrix, BreitWigner or energyIntervals node" );
            throw std::exception();
          }
        }
      }
    }

    // loop over the unresolved nodes
    for ( pugi::xml_node region = resonances.child( "unresolved" );
          region; region = region.next_sibling( "unresolved" ) ) {

      // get the lower and upper energy
      double lower = region.attribute( "domainMin" ).as_double();
      double upper = region.attribute( "domainMax" ).as_double();
      std::string unit = region.attribute( "domainUnit" ).as_string();
      convertEnergy( lower, unit );
      convertEnergy( upper, unit );

      Log::info( "Reading unresolved resonance region between {} and {} eV", lower, upper );
      Log::info( "  Unresolved resonance parameters are currently unsupported, skipping" );
    }

    if ( resolved.size() != 0 ) {

      return dryad::resonances::ResonanceParameters( std::move( resolved ) );
    }
    else {

      return std::nullopt;
    }
  }

} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
