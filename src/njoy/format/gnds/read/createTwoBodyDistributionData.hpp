#ifndef NJOY_FORMAT_GNDS_READ_CREATETWOBODYDISTRIBUTIONDATA
#define NJOY_FORMAT_GNDS_READ_CREATETWOBODYDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TwoBodyDistributionData.hpp"
#include "njoy/format/gnds/read/createReferenceFrame.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunctions.hpp"
#include "njoy/format/gnds/read/createTabulatedAngularDistributionFunctions.hpp"

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
      auto function1ds = node.child( "function1ds" );
      auto function = function1ds.first_child();
      if ( strcmp( function.name(), "Legendre" ) == 0 ||
           strcmp( function.name(), "XYs1d" ) == 0 ) {

        if ( strcmp( function.name(), "Legendre" ) == 0 ) {

          std::vector< double > grid;
          std::vector< dryad::LegendreAngularDistribution > distributions;

          auto data = createLegendreAngularDistributionFunctions( function1ds, units );
          for ( std::size_t i = 0; i < data.first.size(); ++i ) {

            grid.emplace_back( data.first[i].value() );
            distributions.emplace_back( std::move( data.second[i] ), normalise );
          }

          return dryad::TwoBodyDistributionData(
                   std::move( frame ),
                   dryad::LegendreAngularDistributions( std::move( grid ), std::move( distributions ) ) );
        }
        else {

          std::vector< double > grid;
          std::vector< dryad::TabulatedAngularDistribution > distributions;

          auto data = createTabulatedAngularDistributionFunctions( function1ds, units );
          for ( std::size_t i = 0; i < data.first.size(); ++i ) {

            grid.emplace_back( data.first[i].value() );
            distributions.emplace_back( std::move( data.second[i] ), normalise );
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
    else if ( strcmp( node.name(), "regions2d" ) == 0 ) {





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
