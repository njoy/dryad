#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTQ
#define NJOY_FORMAT_GNDS_WRITE_INSERTQ

// system includes
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertConstant1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a q value into a gnds node
   *
   *  @param[in,out] parent    the parent node
   *  @param[in]     option    the gnds write options
   *  @param[in]     q_value   the q value
   *  @param[in]     min       the lower domain limit
   *  @param[in]     max       the upper domain limit
   *  @param[in]     label     the optional label for the node
   */
  inline pugi::xml_node
  insertQ( pugi::xml_node& parent,
           const Options& options,
           double q_value,
           double min,
           double max,
           const std::optional< std::string >& label = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "Q" );

    //! @todo this is where we would convert units if we really wanted to

    //! @todo when we have multiple options: visit on the option and call the appropriate function

    insertConstant1d( node, options, q_value, min, max,
                      "incidentEnergy", "Q", "eV", "eV",
                      label, std::nullopt );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
