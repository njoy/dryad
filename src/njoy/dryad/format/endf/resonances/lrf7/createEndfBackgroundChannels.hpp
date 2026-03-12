#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFBACKGROUNDCHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFBACKGROUNDCHANNELS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/endf/createEndfInterpolants.hpp"
#include "njoy/dryad/format/endf/createEndfBoundaries.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Reads all channels in a spin group, and return an ENDFtk BackgroundChannels object
   *         for the spin group
   *
   *  @param[in] spingroup   dryad spin group
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels
  createEndfBackgroundChannels( const dryad::resonances::SpinGroup& spingroup ) {

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

          auto boundaries = createEndfBoundaries( bckg.boundaries() );
          auto interpolants = createEndfInterpolants( bckg.interpolants() );
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
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
