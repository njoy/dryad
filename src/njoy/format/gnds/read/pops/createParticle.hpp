#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATEPARTICLE
#define NJOY_FORMAT_GNDS_READ_POPS_CREATEPARTICLE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/format/gnds/read/pops/createMass.hpp"
#include "njoy/format/gnds/read/pops/createEnergy.hpp"
#include "njoy/format/gnds/read/pops/createSpin.hpp"
#include "njoy/format/gnds/read/pops/createParity.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief Create a Particle from a GNDS xml node
   *
   *  @param[in] node    the GNDS xml node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline dryad::Particle createParticle( const pugi::xml_node& node,
                                         const std::string& style = "eval" ) {

    dryad::id::ParticleID id;
    std::optional< double > mass = std::nullopt;
    std::optional< double > nuclear_mass = std::nullopt;
    std::optional< double > energy = std::nullopt;
    std::optional< double > mass_uncertainty = std::nullopt;
    std::optional< double > nuclear_mass_uncertainty = std::nullopt;
    std::optional< double > energy_uncertainty = std::nullopt;
    std::optional< double > spin = std::nullopt;
    std::optional< short > parity = std::nullopt;

    if ( strcmp( node.name(), "nuclide" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "id" ).as_string() );
      auto child = node.child( "mass" );
      if ( child ) {

        auto data = createMass( child, style );
        mass = data.value;
        mass_uncertainty = data.uncertainty;
      }

      auto nucleus = node.child( "nucleus" );
      child = nucleus.child( "spin" );
      spin = child ? createSpin( child, style ) : std::nullopt;
      child = nucleus.child( "parity" );
      parity = child ? createParity( child, style ) : std::nullopt;
      child = nucleus.child( "energy" );
      if ( child ) {

        auto data = createEnergy( child, style );
        energy = data.value;
        energy_uncertainty = data.uncertainty;
      }
      child = nucleus.child( "mass" );
      if ( child ) {

        auto data = createMass( child, style );
        nuclear_mass = data.value;
        nuclear_mass_uncertainty = data.uncertainty;
      }
    }
    else if ( strcmp( node.name(), "gaugeBoson" ) == 0 ||
              strcmp( node.name(), "baryon" ) == 0 ||
              strcmp( node.name(), "lepton" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "id" ).as_string() );

      auto child = node.child( "mass" );
      if ( child ) {

        auto data = createMass( child, style );
        mass = data.value;
        mass_uncertainty = data.uncertainty;
      }
      child = node.child( "spin" );
      spin = child ? createSpin( child, style ) : std::nullopt;
      child = node.child( "parity" );
      parity = child ? createParity( child, style ) : std::nullopt;
    }
    else if ( strcmp( node.name(), "chemicalElement" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "symbol" ).as_string() );

      auto child = node.child( "mass" );
      if ( child ) {

        auto data = createMass( child, style );
        mass = data.value;
        mass_uncertainty = data.uncertainty;
      }
    }
    else {

      Log::error( "Expected either a nuclide, gaugeBoson, baryon, lepton or chemicalElement "
                  "node with particle data" );
      throw std::exception();
    }

    return dryad::Particle( std::move( id ), std::move( mass ), std::move( spin ), std::move( parity ),
                            std::move( energy ), std::move( nuclear_mass ), std::move( mass_uncertainty ),
                            std::move( nuclear_mass_uncertainty ), std::move( energy_uncertainty ) );
  }

} // pops namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
