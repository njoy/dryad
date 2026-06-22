#ifndef NJOY_FORMAT_ENDF_READ_CREATEMIXEDANGULARDISTRIBUTION
#define NJOY_FORMAT_ENDF_READ_CREATEMIXEDANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MixedAngularDistribution.hpp"
#include "njoy/format/createVector.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a MixedAngularDistribution from a range of moments
   */
  inline dryad::MixedAngularDistribution
  createMixedAngularDistribution(
      const ENDFtk::section::Type< 4 >::LegendreCoefficients& distribution,
      bool normalise ) {

    try {

      auto coefficients = createVector( distribution.coefficients() );
      coefficients.insert( coefficients.begin(), 1. );
      convertLegendreMoments( coefficients );

      return dryad::MixedAngularDistribution( std::move( coefficients ), normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Legendre angular distribution" );
      throw;
    }
  }

  /**
   *  @brief Create a MixedAngularDistribution
   *
   *  @param[in] distribution   the parsed ENDF tabulated distribution
   *  @param[in] normalise      the flag to indicate whether or not distributions
   *                            need to be normalised
   */
  inline dryad::MixedAngularDistribution
  createMixedAngularDistribution(
      const ENDFtk::section::Type< 4 >::TabulatedDistribution& distribution,
      bool normalise ) {

    try {

      auto cosines = createVector( distribution.cosines() );
      auto values = createVector( distribution.probabilities() );
      auto boundaries = createBoundaries( distribution.boundaries() );
      auto interpolants = createInterpolants( distribution.interpolants() );
      return dryad::MixedAngularDistribution( std::move( cosines ), std::move( values ),
                                              std::move( boundaries ), std::move( interpolants ),
                                              normalise );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an angular distribution table" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
