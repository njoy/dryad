#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETWOBODYDISTRIBUTIONDATA
#define NJOY_DRYAD_FORMAT_GNDS_CREATETWOBODYDISTRIBUTIONDATA

// system includes
#include <vector>
#include <iostream>
// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReferenceFrame.hpp"
#include "dryad/format/gnds/createLegendreAngularDistribution.hpp"
#include "dryad/format/gnds/createTabulatedAngularDistribution.hpp"
#include "dryad/TwoBodyDistributionData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TwoBodyDistributionData from a GNDS angularTwoBody node
   */
  TwoBodyDistributionData 
  createTwoBodyDistributionData( const pugi::xml_node& twobody, 
                                 const std::string& style = "eval" ) {

    // check that this is a valid angularTwoBody node
    throwExceptionOnWrongNode( twobody, "angularTwoBody" );

    // get the reference frame
    auto frame = createReferenceFrame( twobody.attribute( "productFrame" ).as_string() );

    auto node = twobody.first_child();
    if ( strcmp( node.name(), "XYs2d" ) == 0 ) {

      // read the axes
      auto units = readAxes( node.child( "axes" ) );

      // get the functions
      auto function = node.child( "function1ds" ).first_child();
      if ( strcmp( function.name(), "Legendre" ) == 0 || 
           strcmp( function.name(), "XYs1d" ) == 0 ) {

        std::vector< double > grid;
        if ( strcmp( function.name(), "Legendre" ) == 0 ) {
          
          std::vector< LegendreAngularDistribution > distributions;
          for ( ; function; function = function.next_sibling( "Legendre" ) ) {

            auto legendre = createLegendreAngularDistribution( function, units );
            grid.push_back( legendre.first.value() );
            distributions.emplace_back( std::move( legendre.second ) );
          }

          return TwoBodyDistributionData( 
                   std::move( frame ), 
                   LegendreAngularDistributions( std::move( grid ), std::move( distributions ) ) );
        }
        else {

          std::vector< TabulatedAngularDistribution > distributions;
          for ( ; function; function = function.next_sibling( "XYs1d" ) ) {

            auto tabulated = createTabulatedAngularDistribution( function, units );
            grid.push_back( tabulated.first.value() );
            distributions.emplace_back( std::move( tabulated.second ) );
          }

          return TwoBodyDistributionData( 
                   std::move( frame ), 
                   TabulatedAngularDistributions( std::move( grid ), std::move( distributions ) ) );
        }
      }
      else {

        Log::error( "Only Legendre or XYs1d nodes are allowed in an angular XYs2d" );
        throw std::exception();
      }
    }
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      Log::error( "Mixed Legendre and tabulated angular distribution data is "
                  "currently unsupported" );
      throw std::exception();
    }
    else {

      Log::error( "Expected either an XYs2d node or regions1d node with XYs1d nodes "
                  "for two body angular distribution data" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
