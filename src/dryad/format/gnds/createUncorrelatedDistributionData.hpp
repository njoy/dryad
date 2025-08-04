#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEUNCORRELATEDDISTRIBUTIONDATA
#define NJOY_DRYAD_FORMAT_GNDS_CREATEUNCORRELATEDDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReferenceFrame.hpp"
#include "dryad/format/gnds/createLegendreAngularDistribution.hpp"
#include "dryad/format/gnds/createTabulatedAngularDistribution.hpp"
#include "dryad/format/gnds/createTabulatedEnergyDistribution.hpp"
#include "dryad/IsotropicAngularDistributions.hpp"
#include "dryad/UncorrelatedDistributionData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a UncorrelatedDistributionData from a GNDS uncorrelated node
   */
  static UncorrelatedDistributionData
  createUncorrelatedDistributionData( const pugi::xml_node& uncorrelated,
                                      bool normalise ) {

    // check that this is a valid uncorrelated node
    throwExceptionOnWrongNode( uncorrelated, "uncorrelated" );

    // get the reference frame
    auto frame = createReferenceFrame( uncorrelated.attribute( "productFrame" ).as_string() );

    // get the angular data
    auto angle = uncorrelated.child( "angle" );
    UncorrelatedDistributionData::AngularDistributions angular;
    if ( angle ) {

      auto node = angle.first_child();
      if ( strcmp( node.name(), "isotropic2d" ) == 0 ) {

        angular = IsotropicAngularDistributions();
      }
      else if ( strcmp( node.name(), "XYs2d" ) == 0 ) {

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

            angular = LegendreAngularDistributions( std::move( grid ), std::move( distributions ) );
          }
          else {

            std::vector< TabulatedAngularDistribution > distributions;
            for ( ; function; function = function.next_sibling( "XYs1d" ) ) {

              auto tabulated = createTabulatedAngularDistribution( function, units, normalise );
              grid.push_back( tabulated.first.value() );
              distributions.emplace_back( std::move( tabulated.second ) );
            }

            angular = TabulatedAngularDistributions( std::move( grid ), std::move( distributions ) );
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

        Log::error( "Expected either an isotropic or XYs2d node "
                    "for uncorrelated angular distribution data" );
        throw std::exception();
      }
    }

    // get the energy data
    auto energy = uncorrelated.child( "energy" );
    UncorrelatedDistributionData::EnergyDistributions energyd;
    if ( energy ) {

      auto node = energy.first_child();
      if ( strcmp( node.name(), "XYs2d" ) == 0 ) {

        // read the axes
        auto units = readAxes( node.child( "axes" ) );

        // get the functions
        auto function = node.child( "function1ds" ).first_child();

        std::vector< double > grid;
        std::vector< TabulatedEnergyDistribution > distributions;
        for ( ; function; function = function.next_sibling() ) {

          auto tabulated = createTabulatedEnergyDistribution( function, units, normalise );
          grid.push_back( tabulated.first.value() );
          distributions.emplace_back( std::move( tabulated.second ) );
        }

        energyd = TabulatedEnergyDistributions( std::move( grid ), std::move( distributions ) );
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

    return UncorrelatedDistributionData( std::move( frame ), std::move( angular ), std::move( energyd ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
