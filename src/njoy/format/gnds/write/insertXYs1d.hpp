#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTXYS1D
#define NJOY_FORMAT_GNDS_WRITE_INSERTXYS1D

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertAxes.hpp"
#include "njoy/format/gnds/write/insertValues.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert an XYs1d xml node
   *
   *  An axes node is only added when the x label, y label, x unit or y unit are defined.
   *
   *  @param[in,out] parent          the parent node
   *  @param[in]     option          the gnds write options
   *  @param[in]     x               the x values
   *  @param[in]     y               the y values
   *  @param[in]     xLabel          the optional x label
   *  @param[in]     yLabel          the optional y label
   *  @param[in]     xUnit           the optional x unit
   *  @param[in]     yUnit           the optional y unit
   *  @param[in]     interpolation   the optional interpolation value
   *  @param[in]     label           the optional label for the node
   *  @param[in]     index           the optional index (inside a regions1d)
   *  @param[in]     outer           the optional outer domain value (inside a regions2d)
   */
  inline pugi::xml_node
  insertXYs1d( pugi::xml_node& parent,
               const Options& options,
               const std::vector< double >& x,
               const std::vector< double >& y,
               const std::optional< std::string >& xLabel = std::nullopt,
               const std::optional< std::string >& yLabel = std::nullopt,
               const std::optional< std::string >& xUnit = std::nullopt,
               const std::optional< std::string >& yUnit = std::nullopt,
               const std::optional< std::string >& interpolation = std::nullopt,
               const std::optional< std::string >& label = std::nullopt,
               const std::optional< std::size_t >& index = std::nullopt,
               const std::optional< double > outer = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "XYs1d" );
    if ( label.has_value() ) {

      node.append_attribute( "label" ) = label.value();
    }
    if ( index.has_value() ) {

      node.append_attribute( "index" ) = index.value();
    }
    if ( interpolation.has_value() ) {

      node.append_attribute( "interpolation" ) = interpolation.value();
    }
    if ( outer.has_value() ) {

      node.append_attribute( "outerDomainValue" ) = toString( options, outer.value() );
    }

    if ( xLabel.has_value() || yLabel.has_value() || xUnit.has_value() || yUnit.has_value() ) {

      if ( ! ( xLabel.has_value() && yLabel.has_value() ) ) {

        // this should never happen, but our AI overlords tend to complain about missing checks
        throw std::runtime_error( "You have somehow reached unreachable code, contact an njoy developer\n"
                                  "Function: format::gnds::write::insertXYs1d" );
      }

      insertAxes( node, options, xLabel.value(), yLabel.value(), xUnit, yUnit );
    }
    insertValues( node, options, x, y );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
