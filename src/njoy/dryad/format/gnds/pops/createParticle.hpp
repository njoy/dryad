#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/dryad/format/gnds/pops/createMass.hpp"
#include "njoy/dryad/format/gnds/pops/createEnergy.hpp"
#include "njoy/dryad/format/gnds/pops/createSpin.hpp"
#include "njoy/dryad/format/gnds/pops/createParity.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace pops {

  /**
   *  @brief Create a Particle from a GNDS xml node
   *
   *  @param[in] node    the GNDS xml node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline Particle createParticle( const pugi::xml_node& node,
                                  const std::string& style = "eval" ) {

    id::ParticleID id;
    double mass;
    std::optional< double > nuclear_mass;
    std::optional< double > energy;
    std::optional< double > mass_uncertainty;
    std::optional< double > nuclear_mass_uncertainty;
    std::optional< double > energy_uncertainty;
    std::optional< double > spin;
    std::optional< short > parity;

    if ( strcmp( node.name(), "nuclide" ) == 0 ) {

      id = id::ParticleID( node.attribute( "id" ).as_string() );
      mass = createMass( node.child( "mass" ) ).value();

      auto nucleus = node.child( "nucleus" );
      auto child = nucleus.child( "spin" );
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

      id = id::ParticleID( node.attribute( "id" ).as_string() );
      mass = createMass( node.child( "mass" ) ).value();

      auto child = node.child( "spin" );
      spin = child ? createSpin( child, style ) : std::nullopt;
      child = node.child( "parity" );
      parity = child ? createParity( child, style ) : std::nullopt;
    }
    else {

      Log::error( "Expected either a nuclide, gaugeBoson or baryon node or regions1d node particle data" );
      throw std::exception();
    }

    return Particle( std::move( id ), std::move( mass ), std::move( spin ), std::move( parity ),
                     std::move( energy ), std::move( nuclear_mass ), std::move( mass_uncertainty ),
                     std::move( nuclear_mass_uncertainty ), std::move( energy_uncertainty ) );
  }

} // pops namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
