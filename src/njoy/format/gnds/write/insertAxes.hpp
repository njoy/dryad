#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTAXES
#define NJOY_FORMAT_GNDS_WRITE_INSERTAXES

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertAxis.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert an axes xml node for an x and y axis
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     xLabel   the x label
   *  @param[in]     yLabel   the y label
   *  @param[in]     xUnit    the optional x unit
   *  @param[in]     yUnit    the optional y unit
   */
  inline pugi::xml_node
  insertAxes( pugi::xml_node& parent,
              const Options& options,
              const std::string& xLabel,
              const std::string& yLabel,
              const std::optional< std::string >& xUnit,
              const std::optional< std::string >& yUnit ) {

    pugi::xml_node node = parent.append_child( "axes" );
    insertAxis( node, options, xLabel, 1, xUnit );
    insertAxis( node, options, yLabel, 0, yUnit );

    return node;
  }

  /**
   *  @brief Insert an axes xml node for an x, y and z axis
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     xLabel   the x label
   *  @param[in]     yLabel   the y label
   *  @param[in]     zLabel   the z label
   *  @param[in]     xUnit    the optional x unit
   *  @param[in]     yUnit    the optional y unit
   *  @param[in]     zUnit    the optional z unit
   */
  inline pugi::xml_node
  insertAxes( pugi::xml_node& parent,
              const Options& options,
              const std::string& xLabel,
              const std::string& yLabel,
              const std::string& zLabel,
              const std::optional< std::string >& xUnit,
              const std::optional< std::string >& yUnit,
              const std::optional< std::string >& zUnit ) {

    pugi::xml_node node = parent.append_child( "axes" );
    insertAxis( node, options, xLabel, 2, xUnit );
    insertAxis( node, options, yLabel, 1, yUnit );
    insertAxis( node, options, zLabel, 0, zUnit );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
