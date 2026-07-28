#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTPROJECTILEENERGYDOMAIN
#define NJOY_FORMAT_GNDS_WRITE_INSERTPROJECTILEENERGYDOMAIN

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a double xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     min      the lower domain limit
   *  @param[in]     max      the upper domain limit
   *  @param[in]     unit     the optional unit
   */
  inline pugi::xml_node
  insertProjectileEnergyDomain( pugi::xml_node& parent,
                                const Options& options,
                                double min,
                                double max,
                                const std::string& unit ) {

    pugi::xml_node node = parent.append_child( "projectileEnergyDomain" );
    node.append_attribute( "min" ) = toString( options, min );
    node.append_attribute( "max" ) = toString( options, max );
    node.append_attribute( "unit" ) = unit;

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
