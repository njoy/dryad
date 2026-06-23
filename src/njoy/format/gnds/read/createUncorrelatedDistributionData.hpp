#ifndef NJOY_FORMAT_GNDS_READ_CREATEUNCORRELATEDDISTRIBUTIONDATA
#define NJOY_FORMAT_GNDS_READ_CREATEUNCORRELATEDDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/IsotropicAngularDistributions.hpp"
#include "njoy/dryad/UncorrelatedDistributionData.hpp"
#include "njoy/format/gnds/read/createReferenceFrame.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunctions.hpp"
#include "njoy/format/gnds/read/createTabulatedAngularDistributionFunctions.hpp"
#include "njoy/format/gnds/read/createTabulatedEnergyDistributionFunctions.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a UncorrelatedDistributionData from a GNDS uncorrelated node
   */
  inline dryad::UncorrelatedDistributionData
  createUncorrelatedDistributionData( const pugi::xml_node& uncorrelated,
                                      bool normalise ) {

    // check that this is a valid uncorrelated node
    throwExceptionOnWrongNode( uncorrelated, "uncorrelated" );

    // get the reference frame
    auto frame = createReferenceFrame( uncorrelated.attribute( "productFrame" ).as_string() );

    // get the angular data
    auto angle = uncorrelated.child( "angle" );
    dryad::UncorrelatedDistributionData::AngularDistributions angular;
    if ( angle ) {

      auto node = angle.first_child();
      if ( strcmp( node.name(), "isotropic2d" ) == 0 ) {

        angular = dryad::IsotropicAngularDistributions();
      }
      else if ( strcmp( node.name(), "XYs2d" ) == 0 ) {

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

            angular = dryad::LegendreAngularDistributions( std::move( grid ), std::move( distributions ) );
          }
          else {

            std::vector< double > grid;
            std::vector< dryad::TabulatedAngularDistribution > distributions;

            auto data = createTabulatedAngularDistributionFunctions( function1ds, units );
            for ( std::size_t i = 0; i < data.first.size(); ++i ) {

              grid.emplace_back( data.first[i].value() );
              distributions.emplace_back( std::move( data.second[i] ), normalise );
            }

            angular = dryad::TabulatedAngularDistributions( std::move( grid ), std::move( distributions ) );
          }
        }
        else {

          Log::error( "Only Legendre or XYs1d nodes are allowed in an angular XYs2d" );
          throw std::exception();
        }
      }
      else if ( strcmp( node.name(), "regions2d" ) == 0 ) {

        Log::error( "Mixed Legendre and tabulated angular distribution data is "
                    "currently unsupported" );
        throw std::exception();
      }
      else {

        Log::error( "Expected either an isotropic or XYs2d node "
                    "for uncorrelated angular distribution data" );
        throw std::exception();
      }
    }

    // get the energy data
    auto energy = uncorrelated.child( "energy" );
    dryad::UncorrelatedDistributionData::EnergyDistributions energyd;
    if ( energy ) {

      auto node = energy.first_child();
      if ( strcmp( node.name(), "XYs2d" ) == 0 ) {

        // read the axes
        auto units = readAxes( node.child( "axes" ) );

        // get the functions
        auto function1ds = node.child( "function1ds" );
        auto function = function1ds.first_child();
        if ( strcmp( function.name(), "XYs1d" ) == 0 ) {

          std::vector< double > grid;
          std::vector< dryad::TabulatedEnergyDistribution > distributions;

          auto data = createTabulatedEnergyDistributionFunctions( function1ds, units );
          for ( std::size_t i = 0; i < data.first.size(); ++i ) {

            grid.emplace_back( data.first[i].value() );
            distributions.emplace_back( std::move( data.second[i] ), normalise );
          }

          energyd = dryad::TabulatedEnergyDistributions( std::move( grid ), std::move( distributions ) );
        }
        else {

          Log::error( "Only XYs1d nodes are allowed in an angular XYs2d" );
          throw std::exception();
        }
      }
      else if ( strcmp( node.name(), "evaporation" ) == 0 ) {

        throw std::runtime_error( "evaporation" );
      }
      else if ( strcmp( node.name(), "NBodyPhaseSpace" ) == 0 ) {

        throw std::runtime_error( "NBodyPhaseSpace" );
      }
      else if ( strcmp( node.name(), "weightedFunctionals" ) == 0 ) {

        throw std::runtime_error( "weightedFunctionals" );
      }
      else if ( strcmp( node.name(), "simpleMaxwellianFission" ) == 0 ) {

        throw std::runtime_error( "simpleMaxwellianFission" );
      }
      else if ( strcmp( node.name(), "regions2d" ) == 0 ) {

        throw std::runtime_error( "regions2d" );
      }
      else if ( strcmp( node.name(), "MadlandNix" ) == 0 ) {

        throw std::runtime_error( "MadlandNix" );
      }
      else {

        Log::error( "Expected an XYs2d node for uncorrelated energy distribution data, found \'{}\'",
                    node.name() );
        throw std::exception();
      }
    }

    return dryad::UncorrelatedDistributionData( std::move( frame ), std::move( angular ), std::move( energyd ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
