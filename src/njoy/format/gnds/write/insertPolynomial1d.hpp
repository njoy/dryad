#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTPOLYNOMIAL1D
#define NJOY_FORMAT_GNDS_WRITE_INSERTPOLYNOMIAL1D

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"
#include "njoy/format/gnds/write/insertAxes.hpp"
#include "njoy/format/gnds/write/insertValues.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a polynomial1d xml node
   *
   *  @param[in,out] parent         the parent node
   *  @param[in]     option         the gnds write options
   *  @param[in]     coefficients   the constant value
   *  @param[in]     min            the lower domain limit
   *  @param[in]     max            the upper domain limit
   *  @param[in]     xLabel         the x label
   *  @param[in]     yLabel         the y label
   *  @param[in]     xUnit          the optional x unit
   *  @param[in]     yUnit          the optional y unit
   *  @param[in]     label          the optional label for the node
   *  @param[in]     outer          the optional outer domain value
   */
  inline pugi::xml_node
  insertPolynomial1d( pugi::xml_node& parent,
                      const Options& options,
                      const std::vector< double >& coefficients,
                      double min,
                      double max,
                      const std::string& xLabel,
                      const std::string& yLabel,
                      const std::optional< std::string >& xUnit = std::nullopt,
                      const std::optional< std::string >& yUnit = std::nullopt,
                      const std::optional< std::string >& label = std::nullopt,
                      const std::optional< double > outer = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "polynomial1d" );
    if ( label.has_value() ) {

      node.append_attribute( "label" ) = label.value();
    }
    if ( outer.has_value() ) {

      node.append_attribute( "outerDomainValue" ) = toString( options, outer.value() ).c_str();
    }
    node.append_attribute( "domainMin" ) = toString( options, min ).c_str();
    node.append_attribute( "domainMax" ) = toString( options, max ).c_str();

    insertAxes( node, options, xLabel, yLabel, xUnit, yUnit );
    insertValues( node, options, coefficients );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
