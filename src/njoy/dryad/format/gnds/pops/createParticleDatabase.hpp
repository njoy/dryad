#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLEDATABASE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPARTICLEDATABASE

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/format/gnds/pops/createParticle.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace pops {

  /**
   *  @brief Create a ParticleDatabase from a GNDS pops xml node
   *
   *  @param[in] pops    the GNDS pops xml node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline ParticleDatabase
  createParticleDatabase( const pugi::xml_node& pops,
                          const std::string& style = "eval" ) {

    // check that this is a valid coherentPhotonScattering node
    throwExceptionOnWrongNode( pops, "PoPs" );

    std::vector< Particle > particles;

    // loop over bosons
    auto bosons = pops.child( "gaugeBosons" );
    for ( pugi::xml_node boson = bosons.child( "gaugeBoson" );
          boson; boson = boson.next_sibling( "gaugeBoson" ) ) {

      particles.emplace_back( createParticle( boson, style ) );
    }

    // loop over baryons
    auto baryons = pops.child( "baryons" );
    for ( pugi::xml_node baryon = baryons.child( "baryon" );
          baryon; baryon = baryon.next_sibling( "baryon" ) ) {

      particles.emplace_back( createParticle( baryon, style ) );
    }

    // loop over leptons
    auto leptons = pops.child( "leptons" );
    for ( pugi::xml_node lepton = leptons.child( "lepton" );
          lepton; lepton = lepton.next_sibling( "lepton" ) ) {

      particles.emplace_back( createParticle( lepton, style ) );
    }

    // lambda that fills missing data from left to right
    auto fill_missing_data = [] ( auto&& left, auto&& right ) {

      if ( left.mass().has_value() && ! right.mass().has_value() ) {

        right.mass( left.mass() );
        if ( left.massUncertainty().has_value() ) {

          right.massUncertainty( left.massUncertainty() );
        }
      }
      if ( left.nuclearMass().has_value() && ! right.nuclearMass().has_value() ) {

        right.nuclearMass( left.nuclearMass() );
        if ( left.nuclearMassUncertainty().has_value() ) {

          right.nuclearMassUncertainty( left.nuclearMassUncertainty() );
        }
      }

      // energy, spin and parity are supposed to be unique by nuclide
    };

    // loop over chemical elements
    auto elements = pops.child( "chemicalElements" );
    for ( pugi::xml_node element = elements.child( "chemicalElement" );
          element; element = element.next_sibling( "chemicalElement" ) ) {

      // if the element has a mass node: make it into a Particle
      if ( element.child( "mass" ) ) {

        particles.emplace_back( createParticle( element, style ) );
      }

      // loop over the isotopes
      auto isotopes = element.child( "isotopes" );
      for ( pugi::xml_node isotope = isotopes.child( "isotope" );
            isotope; isotope = isotope.next_sibling( "isotope" ) ) {

        // note: we assume that mass and nuclear mass are inherited from the
        //       the first nuclide read from the element

        // loop over the nuclides
        std::size_t index = particles.size();
        auto nuclides = isotope.child( "nuclides" );
        for ( pugi::xml_node nuclide = nuclides.child( "nuclide" );
              nuclide; nuclide = nuclide.next_sibling( "nuclide" ) ) {

          particles.emplace_back( createParticle( nuclide, style ) );
          fill_missing_data( particles[index], particles.back() );
        }
      }
    }

    return ParticleDatabase( std::move( particles ) );
  }

} // pops namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
