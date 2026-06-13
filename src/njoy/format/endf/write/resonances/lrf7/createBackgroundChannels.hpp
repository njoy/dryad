#ifndef NJOY_FORMAT_ENDF_WRITE_RESONANCES_LRF7_CREATEBACKGROUNDCHANNELS
#define NJOY_FORMAT_ENDF_WRITE_RESONANCES_LRF7_CREATEBACKGROUNDCHANNELS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/endf/write/createInterpolants.hpp"
#include "njoy/format/endf/write/createBoundaries.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the background channel data for LRF7 resonance parameters
   *
   *  @param[in] spingroup   the spin group
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels
  createBackgroundChannels( const dryad::resonances::SpinGroup& spingroup ) {

    using BackgroundChannels = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels;
    using BackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundRMatrix;
    using TabulatedBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::TabulatedBackgroundRMatrix;
    using SammyBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;
    using FrohnerBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::FrohnerBackgroundRMatrix;

    std::vector< BackgroundRMatrix > backgrounds;

    for ( std::size_t i = 0; i < spingroup.channels().size(); ++i ) {

      auto getBackground = tools::overload{

        [&] ( const njoy::dryad::resonances::SammyBackground& bckg ) -> BackgroundRMatrix {

          return SammyBackgroundRMatrix( i + 1,
                                         bckg.lowerSingularity(),
                                         bckg.upperSingularity(),
                                         bckg.polynomialCoefficients()[0], bckg.polynomialCoefficients()[1], bckg.polynomialCoefficients()[2],
                                         bckg.logarithmicCoefficients()[0], bckg.logarithmicCoefficients()[1] );
        },
        [&] ( const njoy::dryad::resonances::FrohnerBackground& bckg ) -> BackgroundRMatrix {

          return FrohnerBackgroundRMatrix( i + 1,
                                           bckg.lowerSingularity(),
                                           bckg.upperSingularity(),
                                           bckg.distantLevelParameter(),
                                           bckg.poleStrength(),
                                           bckg.averageRadiationWidth() );
        },
        [&] ( const njoy::dryad::resonances::TabulatedBackground& bckg ) -> BackgroundRMatrix {

          auto boundaries = createBoundaries( bckg.boundaries() );
          auto interpolants = createInterpolants( bckg.interpolants() );
          auto energies = bckg.energies();
          auto values = bckg.values();
          return TabulatedBackgroundRMatrix( i + 1,
                                             std::move( boundaries ),
                                             std::move( interpolants ),
                                             std::move( energies ),
                                             std::move( values ) );
        }
      };

      decltype(auto) channel = spingroup.channels()[i];
      if ( channel.background().has_value() ) {

        backgrounds.emplace_back( std::visit( getBackground, channel.background().value() ) );
      }
    }

    return BackgroundChannels( spingroup.channels().size(), std::move(backgrounds) ) ;
  }

} // lrf7 namespace
} // resonances namespace
} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
