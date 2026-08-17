#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTPARTICLEDATABASE
#define NJOY_FORMAT_GNDS_WRITE_INSERTPARTICLEDATABASE

// system includes
#include <algorithm>
#include <cctype>
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/format/gnds/write/insertParticle.hpp"
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a properties of particles xml node
   *
   *  @param[in,out] parent     the parent node
   *  @param[in]     option     the gnds write options
   *  @param[in]     database   the particle database instance
   *  @param[in]     style      the optional gnds style
   */
  inline pugi::xml_node
  insertParticleDatabase( pugi::xml_node& parent,
                          const Options& options,
                          const dryad::ParticleDatabase& database,
                          const std::string& style = "eval" ) {

    Options local_options = options;
    if ( options.precision < 13 ) {

      local_options.precision = 13;
    }

    pugi::xml_node node = parent.append_child( "PoPs" );
    node.append_attribute( "name" ) = "particles";
    node.append_attribute( "version" ) = "1.0";
    node.append_attribute( "format" ) = "2.1";

    pugi::xml_node aliases;
    if ( database.hasParticle( dryad::id::ParticleID::deuteron() ) ||
         database.hasParticle( dryad::id::ParticleID::triton() ) ||
         database.hasParticle( dryad::id::ParticleID::helion() ) ||
         database.hasParticle( dryad::id::ParticleID::alpha() )) {

      aliases = node.append_child( "aliases" );
    }

    if ( database.hasParticle( dryad::id::ParticleID::photon() ) ) {

      pugi::xml_node bosons = node.append_child( "gaugeBosons" );

      decltype(auto) particle = database.particle( dryad::id::ParticleID::photon() );
      insertParticle( bosons, local_options, "gaugeBoson", particle, style );
    }

    if ( database.hasParticle( dryad::id::ParticleID::electron() ) ||
         database.hasParticle( dryad::id::ParticleID::positron() ) ) {

      pugi::xml_node leptons = node.append_child( "leptons" );

      if ( database.hasParticle( dryad::id::ParticleID::electron() ) ) {

        decltype(auto) particle = database.particle( dryad::id::ParticleID::electron() );
        insertParticle( leptons, local_options, "lepton", particle, style );
      }
      if ( database.hasParticle( dryad::id::ParticleID::positron() ) ) {

        decltype(auto) particle = database.particle( dryad::id::ParticleID::positron() );
        insertParticle( leptons, local_options, "lepton", particle, style );
      }
    }

    if ( database.hasParticle( dryad::id::ParticleID::neutron() ) ||
         database.hasParticle( dryad::id::ParticleID::proton() ) ) {

      pugi::xml_node baryons = node.append_child( "baryons" );

      if ( database.hasParticle( dryad::id::ParticleID::neutron() ) ) {

        decltype(auto) particle = database.particle( dryad::id::ParticleID::neutron() );
        insertParticle( baryons, local_options, "baryon", particle, style );
      }
      if ( database.hasParticle( dryad::id::ParticleID::proton() ) ) {

        decltype(auto) particle = database.particle( dryad::id::ParticleID::proton() );
        insertParticle( baryons, local_options, "baryon", particle, style );
      }
    }

    auto compare = [] ( const auto& particle, const auto& id )
                      { return particle.identifier() < id; };
    auto iter = std::lower_bound( database.particles().begin(), database.particles().end(),
                                  dryad::id::ParticleID( "H" ), compare );
    std::vector< dryad::Particle > particles( iter, database.particles().end() );

    std::vector< std::pair< dryad::id::ParticleID, dryad::id::ParticleID > > elementary = {

      { dryad::id::ParticleID::deuteron(), dryad::id::ParticleID( "H2" ) },
      { dryad::id::ParticleID::triton(), dryad::id::ParticleID( "H3" ) },
      { dryad::id::ParticleID::helion(), dryad::id::ParticleID( "He3" ) },
      { dryad::id::ParticleID::alpha(), dryad::id::ParticleID( "He4" ) }
    };
    for ( const auto& [particle, nuclide] : elementary ) {

      if ( database.hasParticle( particle ) ) {

        if ( ! database.hasParticle( nuclide ) ) {

          particles.insert( std::lower_bound( particles.begin(), particles.end(), nuclide, compare ),
                            dryad::Particle::defaultParticle( nuclide ) );
        }

        auto id = nuclide.symbol();
        std::transform( id.begin(), id.end(), id.begin(),
                        [] ( auto&& character ) { return std::tolower( character ); } );

        auto alias = aliases.append_child( "alias" );
        alias.append_attribute( "id" ) = particle.symbol().c_str();
        alias.append_attribute( "pid" ) = id.c_str();
      }
    }

    iter = particles.begin();
    if ( iter != particles.end() ) {

      pugi::xml_node elements = node.append_child( "chemicalElements" );
      while ( iter != particles.end() ) {

        dryad::id::ElementID element_id( iter->identifier().z() );
        auto next = std::lower_bound( iter, particles.cend(),
                                      dryad::id::ParticleID::nuclide( ( element_id.number() + 1 ) * 1000 ),
                                      compare );

        auto element = elements.append_child( "chemicalElement" );
        element.append_attribute( "symbol" ) = element_id.symbol().c_str();
        element.append_attribute( "Z" ) = element_id.number();
        element.append_attribute( "name" ) = element_id.name().c_str();

        if ( iter->identifier().a() == 0 ) {

          //! @todo mass value?

          ++iter;
        }

        pugi::xml_node isotopes;
        while ( iter != next ) {

          if ( isotopes.empty() ) {

            isotopes = element.append_child( "isotopes" );
          }

          auto next_isotope = std::lower_bound(
                                  iter, next,
                                  dryad::id::ParticleID::nuclide( iter->identifier().za() + 1 ),
                                  compare );

          auto groundstate = iter->identifier().groundState();
          auto isotope = isotopes.append_child( "isotope" );
          isotope.append_attribute( "symbol" ) = groundstate.symbol().c_str();
          isotope.append_attribute( "A" ) = groundstate.a();
          auto nuclides = isotope.append_child( "nuclides" );

          while ( iter != next_isotope ) {

            insertParticle( nuclides, local_options, "nuclide", *iter, style );

            ++iter;
          }
        }
      }
    }
    else {

      // only elementary particles are present
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
