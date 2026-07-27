#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTCONSTANT1D
#define NJOY_FORMAT_GNDS_WRITE_INSERTCONSTANT1D

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"
#include "njoy/format/gnds/write/insertAxes.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a constant1d xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     value    the constant value
   *  @param[in]     min      the lower domain limit
   *  @param[in]     max      the upper domain limit
   *  @param[in]     xLabel   the x label
   *  @param[in]     yLabel   the y label
   *  @param[in]     xUnit    the optional x unit
   *  @param[in]     yUnit    the optional y unit
   *  @param[in]     label    the optional label for the node
   *  @param[in]     outer    the optional outer domain value
   */
  inline pugi::xml_node
  insertConstant1d( pugi::xml_node& parent,
                    const Options& options,
                    double value,
                    double min,
                    double max,
                    const std::string& xLabel,
                    const std::string& yLabel,
                    const std::optional< std::string >& xUnit,
                    const std::optional< std::string >& yUnit,
                    const std::optional< std::string >& label,
                    const std::optional< double > outer ) {

    pugi::xml_node node = parent.append_child( "constant1d" );
    if ( label.has_value() ) {

      node.append_attribute( "label" ) = label.value();
    }
    node.append_attribute( "value" ) = toString( options, value );
    if ( outer.has_value() ) {

      node.append_attribute( "outerDomainValue" ) = toString( options, outer.value() );
    }
    node.append_attribute( "domainMin" ) = toString( options, min );
    node.append_attribute( "domainMax" ) = toString( options, max );

    insertAxes( node, options, xLabel, yLabel, xUnit, yUnit );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
