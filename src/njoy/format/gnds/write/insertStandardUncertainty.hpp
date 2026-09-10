#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTSTANDARDUNCERTAINTY
#define NJOY_FORMAT_GNDS_WRITE_INSERTSTANDARDUNCERTAINTY

// system includes

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertDouble.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a standard normally distributed uncertainty xml node
   *
   *  @param[in,out] parent        the parent node
   *  @param[in]     options       the gnds write options
   *  @param[in]     uncertainty   the uncertainty value
   */
  inline pugi::xml_node
  insertStandardUncertainty( pugi::xml_node& value,
                             const Options& options,
                             double uncertainty ) {

    pugi::xml_node node = value.append_child( "uncertainty" );
    auto standard = node.append_child( "standard" );
    insertDouble( standard, options, uncertainty );

    return node;
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
