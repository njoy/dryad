#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTPROJECTILEENERGYDOMAIN
#define NJOY_FORMAT_GNDS_WRITE_INSERTPROJECTILEENERGYDOMAIN

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a double xml node
   *
   *  @param[in,out] parent      the parent node
   *  @param[in]     option      the gnds write options
   *  @param[in]     reactions   the reactions
   */
  inline pugi::xml_node
  insertProjectileEnergyDomain( pugi::xml_node& parent,
                                const Options& options,
                                const std::vector< dryad::Reaction >& reactions ) {

    double min = reactions.front().crossSection().lowerEnergyLimit();
    double max = reactions.front().crossSection().upperEnergyLimit();

    for ( const auto& reaction : reactions ) {

      if ( min > reaction.crossSection().lowerEnergyLimit() ) {

        min = reaction.crossSection().lowerEnergyLimit();
      }
      if ( max < reaction.crossSection().upperEnergyLimit() ) {

        max = reaction.crossSection().upperEnergyLimit();
      }
    }

    pugi::xml_node node = parent.append_child( "projectileEnergyDomain" );
    node.append_attribute( "min" ) = toString( options, min ).c_str();
    node.append_attribute( "max" ) = toString( options, max ).c_str();
    node.append_attribute( "unit" ) = "eV";

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
