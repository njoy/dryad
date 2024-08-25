#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPDFFROMCDF
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPDFFROMCDF

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create a pdf from a cdf
   */
  TabulatedAngularDistributionFunction
  createPdfFromCdf( const TabulatedAngularDistributionFunction& cdf ) {

    if ( ( cdf.numberRegions() != 1 ) ||
         ( cdf.interpolants().front() != InterpolationType::LinearLinear ) ) {

      Log::error( "Transforming a cdf into a pdf for a multi-region or non-linearised "
                  "cdf is not implemented yet." );
      throw std::exception();
    }

    try {

      std::vector< double > cosines;
      std::vector< double > values;
      for ( std::size_t i = 1; i < cdf.numberPoints(); ++i ) {

        auto probability = ( cdf.values()[i] - cdf.values()[i-1] ) / ( cdf.cosines()[i] - cdf.cosines()[i-1] );
        cosines.push_back( cdf.cosines()[i-1] );
        cosines.push_back( cdf.cosines()[i] );
        values.push_back( probability );
        values.push_back( probability );
      }
      std::vector< std::size_t > boundaries = { cosines.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedAngularDistributionFunction(
               std::move( cosines ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a angular pdf from an angular cdf" );
      throw;
    }
  }

  /**
   *  @brief Create a pdf from a cdf
   */
  TabulatedEnergyDistributionFunction
  createPdfFromCdf( const TabulatedEnergyDistributionFunction& cdf ) {

    if ( ( cdf.numberRegions() != 1 ) ||
         ( cdf.interpolants().front() != InterpolationType::LinearLinear ) ) {

      Log::error( "Transforming a cdf into a pdf for a multi-region or non-linearised "
                  "cdf is not implemented yet." );
      throw std::exception();
    }

    try {

      std::vector< double > energies;
      std::vector< double > values;
      for ( std::size_t i = 1; i < cdf.numberPoints(); ++i ) {

        auto probability = ( cdf.values()[i] - cdf.values()[i-1] ) / ( cdf.energies()[i] - cdf.energies()[i-1] );
        energies.push_back( cdf.energies()[i-1] );
        energies.push_back( cdf.energies()[i] );
        values.push_back( probability );
        values.push_back( probability );
      }
      std::vector< std::size_t > boundaries = { energies.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedEnergyDistributionFunction(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an energy pdf from an energy cdf" );
      throw;
    }
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
