#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTRMATRIX
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTRMATRIX

// system includes
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/pops/insertParticleDatabase.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/createFormalism.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/createBoundaryCondition.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertResonanceReactions.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertSpinGroup.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Collect all particle information in the compound system and create a particle database
   *
   *  @param[in] compound   the compound system
   */
  inline dryad::ParticleDatabase collectParticles( const dryad::resonances::CompoundSystem& compound ) {

    std::vector< dryad::Particle > particles;
    auto compare = [] ( auto&& left, auto&&right ) {

      return left.identifier() < right.identifier();
    };
    auto add_particle = [&] ( std::vector< dryad::Particle >& particles, auto&& pair ) {

      auto iter = std::lower_bound( particles.begin(), particles.end(), pair, compare );
      if ( iter == particles.end() || iter->identifier() != pair.identifier() ) {

        particles.insert( iter, pair );
      }
    };

    decltype(auto) incident = compound.spinGroups().front().channels().front().incidentParticlePair();
    add_particle( particles, incident.lightParticle() );
    add_particle( particles, incident.heavyParticle() );

    for ( const auto& group : compound.spinGroups() ) {

      for ( const auto& channel : group.channels() ) {

        decltype(auto) outgoing = channel.outgoingParticlePair();
        if ( outgoing.has_value() ) {

          add_particle( particles, outgoing->lightParticle() );
          add_particle( particles, outgoing->heavyParticle() );
        }
      }
    }

    return dryad::ParticleDatabase( std::move( particles ) );
  }

  /**
   *  @brief Insert the RMatrix node into a gnds node
   *
   *  @param[in,out] parent                   the parent node
   *  @param[in]     option                   the gnds write options
   *  @param[in]     compound                 the compound system to be written out
   *  @param[in]     style                    the style label to be used
   *  @param[in]     reducedWidthAmplitudes   use reduced width amplitudes (default is true)
   */
  inline pugi::xml_node
  insertRMatrix( pugi::xml_node& parent,
                 const Options& options,
                 const dryad::resonances::CompoundSystem& compound,
                 const std::map< dryad::id::ReactionID, double >& qvalues,
                 const std::string& style,
                 bool reducedWidthAmplitudes = true ) {

    pugi::xml_node node = parent.append_child( "RMatrix" );
    node.append_attribute( "label" ) = style;
    node.append_attribute( "approximation" ) = createFormalism( compound.formalism() );
    node.append_attribute( "boundaryCondition" ) = createBoundaryCondition( compound.boundaryCondition() );
    if ( reducedWidthAmplitudes ) {

      node.append_attribute( "reducedWidthAmplitudes" ) = "true";
    }

    pops::insertParticleDatabase( node, options, collectParticles( compound ), style );
    insertResonanceReactions( node, options, compound, qvalues, style, true );

    pugi::xml_node groups = node.append_child( "spinGroups" );
    for ( const auto& group : compound.spinGroups() ) {

      insertSpinGroup( groups, options, group,
                       compound.lowerEnergyLimit(), compound.upperEnergyLimit(),
                       style, reducedWidthAmplitudes );
    }

    return node;
  }

} // rmatrix namespace
} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
