#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTPARTICLE
#define NJOY_FORMAT_GNDS_WRITE_INSERTPARTICLE

// system includes
#include <algorithm>
#include <cctype>
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/Particle.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertDouble.hpp"
#include "njoy/format/gnds/write/insertInteger.hpp"
#include "njoy/format/gnds/write/insertFraction.hpp"
#include "njoy/format/gnds/write/toString.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a particle xml node
   *
   *  @param[in,out] parent     the parent node
   *  @param[in]     option     the gnds write options
   *  @param[in]     name       the name of the particle node
   *  @param[in]     particle   the particle instance
   *  @param[in]     style      the optional gnds style
   */
  inline pugi::xml_node
  insertParticle( pugi::xml_node& parent,
                  const Options& options,
                  const std::string& name,
                  const dryad::Particle& particle,
                  const std::string& style = "eval" ) {

    if ( name != "nuclide" && name != "gaugeBoson" && name != "baryon" && name != "lepton" ) {

      throw std::runtime_error( "Unknown GNDS node name requested for particle data: " + name );
    }

    std::string id = particle.identifier().symbol();

    pugi::xml_node node = parent.append_child( name );
    node.append_attribute( "id" ) = id;

    if ( particle.mass().has_value() ) {

      auto mass = node.append_child( "mass" );
      insertDouble( mass, options, particle.mass().value(), style, "amu" );
    }

    if ( name == "nuclide" ) {

      auto charge = node.append_child( "charge" );
      insertDouble( charge, options, 0., style, "e" );

      node = node.append_child( "nucleus" );
      std::transform( id.begin(), id.end(), id.begin(),
                      [] ( auto&& character ) { return std::tolower( character ); } );
      node.append_attribute( "id" ) = id;
    }

    if ( particle.spin().has_value() ) {

      auto spin = node.append_child( "spin" );
      double half;
      if ( std::modf( particle.spin().value(), &half ) == 0. ) {

        // a is a full integer
        insertFraction( spin, options, static_cast< int >( half ), 1, style, std::nullopt );
      }
      else {

        // a is a half integer value
        insertFraction( spin, options, 2 * static_cast< int >( std::round( half ) ) + 1, 2, style, std::nullopt );
      }
    }

    if ( particle.parity().has_value() ) {

      auto parity = node.append_child( "parity" );
      insertInteger( parity, options, particle.parity().value(), style, "e" );
    }

    auto charge = node.append_child( "charge" );
    insertDouble( charge, options, particle.identifier().z(), style, "e" );

    if ( particle.energy().has_value() ) {

      auto energy = node.append_child( "energy" );
      insertInteger( energy, options, particle.energy().value(), style, "eV" );
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
