#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATERESONANCEREACTION
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATERESONANCEREACTION

// system includes
#include <algorithm>
#include <optional>
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/resonances/ParticlePair.hpp"
#include "njoy/dryad/resonances/ChannelRadii.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/resolveLink.hpp"
#include "njoy/format/gnds/read/createQValue.hpp"
#include "njoy/format/gnds/read/resonances/createRadius.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  // reaction id, Q value, radii, boundary condition (if defined)
  using ResonanceReaction = std::tuple< dryad::id::ReactionID,
                                        dryad::resonances::ParticlePair,
                                        std::optional< dryad::resonances::ParticlePair >,
                                        double,
                                        dryad::resonances::ChannelRadii,
                                        std::optional< double >,
                                        bool >;

  inline dryad::Particle
  retrieveParticle( const dryad::id::ParticleID& id,
                    const std::vector< dryad::Particle >& particles ) {

    // lambda to find a particle in a sorted vector
    auto compare = [&] ( auto&& particle ) {

      return particle.identifier() == id;
    };

    auto iter = std::find_if( particles.begin(), particles.end(), compare );
    if ( iter != particles.end() ) {

      return *iter;
    }
    else {

      throw std::runtime_error( "Particle not found in PoPs: \'" + id.symbol() + "\'" );
    }
  }

  /**
   *  @brief Create the information for a resonance reaction
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] reaction     the GNDS resonanceReaction node
   *  @param[in] particles    the particle data from the global and local pops
   *  @param[in] radii        the previously read channel radii
   *  @param[in] style        the gnds style to process (default is eval)
   */
  inline ResonanceReaction
  createResonanceReaction( const dryad::id::ParticleID& projectile,
                           const dryad::id::ParticleID& target,
                           const pugi::xml_node& reaction,
                           const std::vector< dryad::Particle >& particles,
                           const dryad::resonances::ChannelRadii& radii,
                           const std::string& style = "eval" ) {

    // check that this is a valid resonanceReaction node
    throwExceptionOnWrongNode( reaction, "resonanceReaction" );

    // the data for the resonance reaction
    ResonanceReaction data;

    // go to the reaction and get the information we need: id and Q value
    auto link = reaction.child( "link" );
    if ( link ) {

      auto node = resolveLink( link );

      // the reaction identifier
      int mt = adjustScatterLevel( projectile, target, node.attribute( "ENDF_MT" ).as_int() );
      std::get< 0 >( data ) = dryad::id::ReactionID( projectile, target, mt );

      // create the incident particle type
      std::get< 1 >( data ) = dryad::resonances::ParticlePair(
                                retrieveParticle( projectile, particles ),
                                retrieveParticle( target, particles ) );

      // create the outgoing particle type
      if ( std::get< 0 >( data ).particles().has_value() ) {

        dryad::id::ParticleID ejectile( reaction.attribute( "ejectile" ).as_string() );
        if ( ejectile == dryad::id::ParticleID( "H1" ) ) {

          ejectile = dryad::id::ParticleID::proton();
        }
        else if ( ejectile == dryad::id::ParticleID( "H2" ) ) {

          ejectile = dryad::id::ParticleID::deuteron();
        }
        else if ( ejectile == dryad::id::ParticleID( "H3" ) ) {

          ejectile = dryad::id::ParticleID::triton();
        }
        else if ( ejectile == dryad::id::ParticleID( "He3" ) ) {

          ejectile = dryad::id::ParticleID::helion();
        }
        else if ( ejectile == dryad::id::ParticleID( "He4" ) ) {

          ejectile = dryad::id::ParticleID::alpha();
        }
        std::get< 2 >( data ) = dryad::resonances::ParticlePair(
                                  retrieveParticle( ejectile, particles ),
                                  retrieveParticle( std::get< 0 >( data ).residual().value(), particles ) );
      }
      else {

        std::get< 2 >( data ) = std::nullopt;
      }

      // the Q value
      auto output = node.child( "outputChannel" );
      std::get< 3 >( data ) = createQValue( output.child( "Q" ), style );

      // assign the default radii
      std::get< 4 >( data ) = radii;

      // assign the default boundary condition
      std::get< 5 >( data ) = std::nullopt;

      // assign the default elimination flag
      std::get< 6 >( data ) = false;
    }
    else {

      Log::error( "Could not find the link to the reaction node for a resonance reaction" );
      throw std::exception();
    }

    // check for a Q value
    auto node = reaction.child( "Q" );
    if ( node ) {

      std::get< 3 >( data ) = createQValue( node, style );
    }

    // check for radii
    node = reaction.child( "scatteringRadius" );
    if ( node ) {

      std::get< 4 >( data ).penetrabilityRadius( createRadius( node ) );
    }
    node = reaction.child( "hardSphereRadius" );
    if ( node ) {

      std::get< 4 >( data ).phaseShiftRadius( createRadius( node ) );
    }

    // check the node for a boundary condition value
    auto attribute = reaction.attribute( "boundaryConditionValue" );
    if ( attribute ) {

      std::get< 5 >( data ) = attribute.as_double();
    }

    // check for eliminated reaction
    attribute = reaction.attribute( "eliminated" );
    if ( attribute ) {

      std::get< 6 >( data ) = attribute.as_bool();

      // set the radii for the eliminated channel to 0
      std::get< 4 >( data ).penetrabilityRadius( 0. );
      std::get< 4 >( data ).phaseShiftRadius( 0. );
    }

    return data;
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
