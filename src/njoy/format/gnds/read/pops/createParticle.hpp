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
    std::optional< double > mass;
    std::optional< double > nuclear_mass;
    std::optional< double > energy;
    std::optional< double > mass_uncertainty;
    std::optional< double > nuclear_mass_uncertainty;
    std::optional< double > energy_uncertainty;
    std::optional< double > spin;
    std::optional< short > parity;

    if ( strcmp( node.name(), "nuclide" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "id" ).as_string() );
      auto child = node.child( "mass" );
      mass = child ? createMass( child, style ) : std::nullopt;

      auto nucleus = node.child( "nucleus" );
      child = nucleus.child( "spin" );
      spin = child ? createSpin( child, style ) : std::nullopt;
      child = nucleus.child( "parity" );
      parity = child ? createParity( child, style ) : std::nullopt;
      child = nucleus.child( "energy" );
      energy = child ? createEnergy( child, style ) : std::nullopt;
      child = nucleus.child( "mass" );
      nuclear_mass = child ? createMass( child, style ) : std::nullopt;
    }
    else if ( strcmp( node.name(), "gaugeBoson" ) == 0 ||
              strcmp( node.name(), "baryon" ) == 0 ||
              strcmp( node.name(), "lepton" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "id" ).as_string() );

      auto child = node.child( "mass" );
      mass = child ? createMass( child, style ) : std::nullopt;
      child = node.child( "spin" );
      spin = child ? createSpin( child, style ) : std::nullopt;
      child = node.child( "parity" );
      parity = child ? createParity( child, style ) : std::nullopt;
    }
    else if ( strcmp( node.name(), "chemicalElement" ) == 0 ) {

      id = dryad::id::ParticleID( node.attribute( "symbol" ).as_string() );

      auto child = node.child( "mass" );
      mass = child ? createMass( child, style ) : std::nullopt;
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
