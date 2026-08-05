#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTTABULATEDFUNCTION
#define NJOY_FORMAT_GNDS_WRITE_INSERTTABULATEDFUNCTION

// system includes
#include <iterator>
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/toString.hpp"
#include "njoy/format/gnds/write/createInterpolationType.hpp"
#include "njoy/format/gnds/write/insertAxes.hpp"
#include "njoy/format/gnds/write/insertXYs1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a regions1d or Xys1d xml node (whichever is appropriate) for
   *         1D tabulated functions
   *
   *  An axes node is only added when the x label, y label, x unit or y unit are defined.
   *
   *  @param[in,out] parent         the parent node
   *  @param[in]     option         the gnds write options
   *  @param[in]     x              the x values
   *  @param[in]     y              the y values
   *  @param[in]     boundaries     the boundaries of the interpolation regions
   *  @param[in]     interpolants   the interpolation types of the interpolation regions
   *  @param[in]     xLabel         the optional x label
   *  @param[in]     yLabel         the optional y label
   *  @param[in]     xUnit          the optional x unit
   *  @param[in]     yUnit          the optional y unit
   *  @param[in]     label          the optional label for the node
   *  @param[in]     index          the optional index (inside a regions1d)
   *  @param[in]     outer          the optional outer domain value (inside a regions2d)
   */
  inline pugi::xml_node
  insertTabulatedFunction( pugi::xml_node& parent,
                           const Options& options,
                           const std::vector< double >& x,
                           const std::vector< double >& y,
                           std::vector< std::size_t > boundaries,
                           std::vector< dryad::InterpolationType > interpolants,
                           const std::optional< std::string >& xLabel = std::nullopt,
                           const std::optional< std::string >& yLabel = std::nullopt,
                           const std::optional< std::string >& xUnit = std::nullopt,
                           const std::optional< std::string >& yUnit = std::nullopt,
                           const std::optional< std::string >& label = std::nullopt,
                           const std::optional< std::size_t >& index = std::nullopt,
                           const std::optional< double > outer = std::nullopt ) {

    if ( x.size() != y.size() || boundaries.size() != interpolants.size() ||
         x.size() < 2 || boundaries.size() == 0 ) {

      // using Interpolationtable avoids getting to this point, but our AI overlords
      // tend to complain about missing checks
      throw std::runtime_error( "You have somehow reached unreachable code, contact an njoy developer\n"
                                "Function: format::gnds::write::insertTabulatedFunction" );
    }

    pugi::xml_node node;
    if ( boundaries.size() == 1 ) {

      std::optional< std::string > interpolation = std::nullopt;
      if ( interpolants.front() != dryad::InterpolationType::LinearLinear ) {

        interpolation = createInterpolationType( interpolants.front() );
      }
      node = insertXYs1d( parent, options, x, y, xLabel, yLabel, xUnit, yUnit, interpolation,
                          label, index, outer );
    }
    else {

      node = parent.append_child( "regions1d" );
      if ( label.has_value() ) {

        node.append_attribute( "label" ) = label.value();
      }
      if ( index.has_value() ) {

        node.append_attribute( "index" ) = index.value();
      }
      if ( outer.has_value() ) {

        node.append_attribute( "outerDomainValue" ) = toString( options, outer.value() );
      }

      if ( xLabel.has_value() || yLabel.has_value() || xUnit.has_value() || yUnit.has_value() ) {

        if ( ! ( xLabel.has_value() && yLabel.has_value() ) ) {

          // this should never happen, but our AI overlords tend to complain about missing checks
          throw std::runtime_error( "You have somehow reached unreachable code, contact an njoy developer\n"
                                    "Function: format::gnds::write::insertTabulatedFunction" );
        }

        insertAxes( node, options, xLabel.value(), yLabel.value(), xUnit, yUnit );
      }

      auto functions = node.append_child( "function1ds" );

      auto xBegin = x.begin();
      auto yBegin = y.begin();
      for ( std::size_t index = 0; index < boundaries.size(); ++index ) {

        auto xEnd = std::next( x.begin(), boundaries[index] );
        auto yEnd = std::next( y.begin(), boundaries[index] );

        std::vector< double > xCurrent( xBegin, std::next( xEnd ) );
        std::vector< double > yCurrent( yBegin, std::next( yEnd ) );

        std::optional< std::string > interpolation = std::nullopt;
        if ( interpolants[index] != dryad::InterpolationType::LinearLinear ) {

          interpolation = createInterpolationType( interpolants[index] );
        }

        // insert XYs1d with an index, do not add axes node to this one
        insertXYs1d( functions, options, xCurrent, yCurrent,
                     std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                     interpolation, std::nullopt, index );

        xBegin = xEnd;
        yBegin = yEnd;
        auto iter = std::next( xEnd );
        if ( iter != x.end() && *iter == *xBegin ) {

          xBegin = iter;
          yBegin = std::next( yBegin );
        }
      }
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
