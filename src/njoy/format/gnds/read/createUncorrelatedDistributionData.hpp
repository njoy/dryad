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
#include "njoy/format/gnds/read/createLegendreAngularDistributions.hpp"
#include "njoy/format/gnds/read/createTabulatedAngularDistributions.hpp"
#include "njoy/format/gnds/read/createMixedAngularDistributions.hpp"
#include "njoy/format/gnds/read/createTabulatedEnergyDistributions.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a UncorrelatedDistributionData from a GNDS uncorrelated node
   *
   *  @param[in] uncorrelated   the gnds angularTwoBody node
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
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

        // get the functions
        auto function1ds = node.child( "function1ds" );
        auto function = function1ds.first_child();
        if ( strcmp( function.name(), "Legendre" ) == 0 ||
             strcmp( function.name(), "XYs1d" ) == 0 ) {

          if ( strcmp( function.name(), "Legendre" ) == 0 ) {

            angular = createLegendreAngularDistributions( node, normalise );
          }
          else {

            angular = createTabulatedAngularDistributions( node, normalise );
          }
        }
        else {

          Log::error( "Only Legendre or XYs1d nodes are allowed in an angular XYs2d" );
          throw std::exception();
        }
      }
      else if ( strcmp( node.name(), "regions2d" ) == 0 ) {

        angular = createMixedAngularDistributions( node, normalise );
      }
      else {

        Log::error( "Expected either an isotropic, XYs2d or regions2d node "
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

          energyd = createTabulatedEnergyDistributions( node, normalise );
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
