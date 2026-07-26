#ifndef NJOY_FORMAT_ENDF_READ_THERMAL_CREATEINCOHERENTINELASTICSCATTERING
#define NJOY_FORMAT_ENDF_READ_THERMAL_CREATEINCOHERENTINELASTICSCATTERING

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/math/compare.hpp"
#include "njoy/dryad/thermal/IncoherentInelasticScattering.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/7/4.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace thermal {

  /**
   *  @brief Create an IncoherentInelasticScattering from a parsed incoherent
   *         elastic thermal scattering component
   *
   *  @param[in] lower       the lower energy limit
   *  @param[in] upper       the upper energy limit
   *  @param[in] inelastic   the incoherent inelastic thermal scattering component
   */
  inline dryad::thermal::IncoherentInelasticScattering
  createIncoherentInelasticScattering(
      double lower, double upper,
      const ENDFtk::section::Type< 7, 4 >& inelastic ) {

    Log::info( "Reading incoherent inelastic scattering data" );

    auto to_exp = [] ( double value ) { return std::exp( value ); };
    auto is_log_interpolant = [] ( const dryad::InterpolationType& interpolant ) {

      return interpolant == dryad::InterpolationType::LogLinear ||
             interpolant == dryad::InterpolationType::LogLog;
    };
    auto to_interpolant = [] ( const dryad::InterpolationType& interpolant ) {

      switch ( interpolant ) {

        case dryad::InterpolationType::LinearLinear : return dryad::InterpolationType::LogLinear;
        case dryad::InterpolationType::LinearLog : return dryad::InterpolationType::LogLog;
        default : {

          throw std::runtime_error( "Something went wrong when converting interpolation type, "
                                    "contact njoy developers." );
        }
      };
    };

    decltype(auto) temperatures = inelastic.principalEffectiveTemperature();
    auto moderator = createVector( temperatures.moderatorTemperatures() );
    auto effective = createVector( temperatures.effectiveTemperatures() );

    double awr = inelastic.constants().atomicWeightRatios()[0];
    double xs = inelastic.constants().totalFreeCrossSections()[0] / inelastic.constants().numberAtoms()[0];
    xs *= ( awr + 1. ) * ( awr + 1. ) / awr / awr;

    decltype(auto) law = std::get< ENDFtk::section::Type< 7, 4 >::TabulatedFunctions >( inelastic.scatteringLaw() );

    bool uses_log_interpolation = false;

    auto betas = createVector( law.betas() );
    auto boundaries = createBoundaries( law.boundaries() );
    auto interpolants = createInterpolants( law.interpolants() );
    if ( inelastic.constants().sabStorageType() == 1 ) {

      uses_log_interpolation = true;
      std::transform( interpolants.begin(), interpolants.end(), interpolants.begin(), to_interpolant );
    }

    if ( uses_log_interpolation == false ) {

      for ( std::size_t j = 0; j < betas.size(); ++j ) {

        auto interpolants = createInterpolants( law.scatteringFunctions()[j].interpolants() );
        uses_log_interpolation = uses_log_interpolation ||
                                 std::any_of( interpolants.begin(), interpolants.end(),
                                              is_log_interpolant );
        if ( uses_log_interpolation ) {

          break;
        }
      }
    }

    if ( uses_log_interpolation ) {

      Log::warning( "S(a,b) uses logarithmic based interpolation, zero values will be set to "
                    "a small non-zero value" );
    }

    std::vector< dryad::thermal::ScatteringKernel > kernels;
    kernels.reserve( moderator.size() );
    for ( std::size_t i = 0; i < moderator.size(); ++i ) {

      std::vector< dryad::thermal::TabulatedScatteringKernelFunction > functions;
      functions.reserve( betas.size() );

      for ( std::size_t j = 0; j < betas.size(); ++j ) {

        auto alphas = createVector( law.scatteringFunctions()[j].alphas() );
        auto values = createVector( law.scatteringFunctions()[j].thermalScatteringValues()[i] );
        auto boundaries = createBoundaries( law.scatteringFunctions()[j].boundaries() );
        auto interpolants = createInterpolants( law.scatteringFunctions()[j].interpolants() );

        if ( inelastic.constants().sabStorageType() == 1 ) {

          std::transform( values.begin(), values.end(), values.begin(), to_exp );
          std::transform( interpolants.begin(), interpolants.end(), interpolants.begin(), to_interpolant );
        }

        // log-xxx interpolation does not work when zero values are used, replace any zero with the
        // smallest possible float value to fix this issue
        if ( uses_log_interpolation ) {

          std::transform( values.begin(), values.end(), values.begin(),
                          [] ( double value ) { return value == 0.
                                                ? std::numeric_limits< double >::min()
                                                : value; } );
        }

        functions.emplace_back( std::move( alphas ), std::move( values ),
                                std::move( boundaries ), std::move( interpolants ) );
      }

      kernels.emplace_back( moderator[i], effective[i], betas, std::move( functions ),
                            boundaries, interpolants );
    }

    return dryad::thermal::IncoherentInelasticScattering( lower, upper, xs, awr, std::move( kernels ) );
  }

} // thermal namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
