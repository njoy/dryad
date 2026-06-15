#ifndef NJOY_FORMAT_GNDS_READ_CREATETWOBODYDISTRIBUTIONDATA
#define NJOY_FORMAT_GNDS_READ_CREATETWOBODYDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TwoBodyDistributionData.hpp"
#include "njoy/format/gnds/read/createReferenceFrame.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistribution.hpp"
#include "njoy/format/gnds/read/createTabulatedAngularDistribution.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TwoBodyDistributionData from a GNDS angularTwoBody node
   */
  inline dryad::TwoBodyDistributionData
  createTwoBodyDistributionData( const pugi::xml_node& twobody,
                                 bool normalise ) {

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

          std::vector< dryad::LegendreAngularDistribution > distributions;
          for ( ; function; function = function.next_sibling( "Legendre" ) ) {

            auto legendre = createLegendreAngularDistribution( function, units, normalise );
            grid.push_back( legendre.first.value() );
            distributions.emplace_back( std::move( legendre.second ) );
          }

          return dryad::TwoBodyDistributionData(
                   std::move( frame ),
                   dryad::LegendreAngularDistributions( std::move( grid ), std::move( distributions ) ) );
        }
        else {

          std::vector< dryad::TabulatedAngularDistribution > distributions;
          for ( ; function; function = function.next_sibling( "XYs1d" ) ) {

            auto tabulated = createTabulatedAngularDistribution( function, units, normalise );
            grid.push_back( tabulated.first.value() );
            distributions.emplace_back( std::move( tabulated.second ) );
          }

          return dryad::TwoBodyDistributionData(
                   std::move( frame ),
                   dryad::TabulatedAngularDistributions( std::move( grid ), std::move( distributions ) ) );
        }
      }
      else {

        Log::error( "Only Legendre or XYs1d nodes are allowed in an angular XYs2d" );
        throw std::exception();
      }
    }
    else if ( strcmp( node.name(), "isotropic2d" ) == 0 ) {

      return dryad::TwoBodyDistributionData( std::move( frame ), dryad::IsotropicAngularDistributions() );
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

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
