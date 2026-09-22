#ifndef NJOY_FORMAT_GNDS_READ_THERMAL_CREATEINCOHERENTINELASTICSCATTERING
#define NJOY_FORMAT_GNDS_READ_THERMAL_CREATEINCOHERENTINELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "njoy/dryad/thermal/IncoherentInelasticScattering.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/gnds/read/convertCrossSection.hpp"
#include "njoy/format/gnds/read/convertMass.hpp"
#include "njoy/format/gnds/read/convertTemperatures.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readArray.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace thermal {

  /**
   *  @brief Create an IncoherentInelasticScattering from a GNDS tsl node
   *
   *  @param[in] lower            the lower energy limit
   *  @param[in] upper            the upper energy limit
   *  @param[in] projectileMass   the projectile mass (in amu)
   *  @param[in] tsl              the GNDS tsl node
   */
  inline dryad::thermal::IncoherentInelasticScattering
  createIncoherentInelasticScattering( double lower, double upper,
                                       double projectileMass,
                                       const pugi::xml_node& tsl ) {

    Log::info( "Reading incoherent inelastic scattering data" );

    // check that this is a valid incoherent inelastic thermal scattering node
    throwExceptionOnWrongNode( tsl, "thermalNeutronScatteringLaw_incoherentInelastic" );

    // verify if the alpha and beta grid are scaled to thermal energies
    bool scale = tsl.attribute( "calculatedAtThermal" ).as_bool(  );

    // look for scattering atom node of the principal scatterer
    pugi::xml_node atoms = tsl.child( "scatteringAtoms" );
    pugi::xml_node principal = atoms.find_child_by_attribute( "scatteringAtom", "primaryScatterer", "true" );

    // get the mass value - should actually be a PoPs node but that's not what is in the actual files
    pugi::xml_node node = principal.child( "mass" );
    double awr = node.attribute( "value" ).as_double();
    convertMass( awr, node.attribute( "unit" ).as_string() );
    awr /= projectileMass;

    // get the bound cross section - no need to weigh with the mass (ENDF stores the free xs)
    node = principal.child( "boundAtomCrossSection" );
    double xs = node.attribute( "value" ).as_double();
    convertCrossSection( xs, node.attribute( "unit" ).as_string() );

    // get the effective temperatures
    node = principal.child( "T_effective" ).first_child();
    auto data = readXYs1D( node );
    auto moderator = std::move( data.x );
    auto effective = std::move( data.y );
    convertTemperatures( moderator, data.x_unit.value() );
    convertTemperatures( effective, data.y_unit.value() );

    // get the S(a,b) data
    pugi::xml_node sab = principal.child( "selfScatteringKernel" ).first_child();
    if ( strcmp( sab.name(), "gridded3d" ) != 0 ) {

      Log::error( "Expected a GNDS \'gridded3d\' node, found a \'{}\' node instead",
                  sab.name() );
      throw std::exception();
    }

    auto axes = readAxes( sab.child( "axes" ) );
    auto array = readArray( sab.child( "array" ) );

    auto temperatures = std::move( axes[0].values.value() );
    convertTemperatures( temperatures, axes[0].unit.value() );
    auto betas = std::move( axes[1].values.value() );
    auto alphas = std::move( axes[2].values.value() );

    // we have to cast to int since std::size_t does not work
    using namespace njoy::tools;
    auto chunked = std20::views::all( array.values )
                   | std23::views::chunk( static_cast< long >( alphas.size() ) )
                   | std23::views::chunk( static_cast< long >( betas.size() ) );

    auto beta_interpolation = createInterpolationType( axes[1].interpolation.value() );
    auto alpha_interpolation = createInterpolationType( axes[2].interpolation.value() );
    bool uses_log_interpolation = false;

    if ( beta_interpolation == dryad::InterpolationType::LogLinear ||
         beta_interpolation == dryad::InterpolationType::LogLog ||
         alpha_interpolation == dryad::InterpolationType::LogLinear ||
         alpha_interpolation == dryad::InterpolationType::LogLog ) {

      uses_log_interpolation = true;
    }

    std::vector< dryad::thermal::ScatteringKernel > kernels;
    kernels.reserve( moderator.size() );
    for ( std::size_t i = 0; i < moderator.size(); ++i ) {

      std::vector< dryad::thermal::TabulatedScatteringKernelFunction > functions;
      functions.reserve( betas.size() );

      std::vector< double > current_betas = betas;
      if ( scale ) {

        double factor = constants::room_temperature / moderator[i];
        std::transform( current_betas.begin(), current_betas.end(), current_betas.begin(),
                        [&] ( auto&& value ) { return value * factor; } );
      }

      for ( std::size_t j = 0; j < betas.size(); ++j ) {

        auto current_alphas = alphas;
        auto values = createVector( chunked[i][j] );

        if ( scale ) {

          double factor = constants::room_temperature / moderator[i];
          std::transform( current_alphas.begin(), current_alphas.end(), current_alphas.begin(),
                          [&] ( auto&& value ) { return value * factor; } );
        }

        // log-xxx interpolation does not work when zero values are used, replace any zero with the
        // smallest possible float value to fix this issue
        if ( uses_log_interpolation ) {

          std::transform( values.begin(), values.end(), values.begin(),
                          [] ( double value ) { return value == 0.
                                                ? std::numeric_limits< double >::min()
                                                : value; } );
        }

        functions.emplace_back( std::move( current_alphas ), std::move( values ), alpha_interpolation );
      }

      kernels.emplace_back( moderator[i], effective[i], std::move( current_betas ), std::move( functions ),
                            beta_interpolation );
    }

    return dryad::thermal::IncoherentInelasticScattering( lower, upper, xs, awr, std::move( kernels ) );
  }

} // thermal namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
