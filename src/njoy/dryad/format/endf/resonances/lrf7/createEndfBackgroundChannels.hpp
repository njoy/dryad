#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFBACKGROUNDCHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFBACKGROUNDCHANNELS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  using BackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundRMatrix;
  using ENDFtkBackgroundChannels  = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels;

  //! @todo used a safety fallback on interpolant to int conversion : "return 0", is it necesssary or risky ?

  /**
   *  @brief Reads all channels in a spin group, and return an ENDFtk BackgroundRMatrix
   *
   *  @param[in] spingroup dryad spin group
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels
  createEndfBackgroundChannels( const dryad::resonances::SpinGroup& spingroup ) {

    std::vector< BackgroundRMatrix > backgrounds;

    for (size_t i = 0; i < spingroup.channels().size(); i++) {

      const auto& channel = spingroup.channels()[i];

      if ( channel.background().has_value() ) {

        using TabulatedBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::TabulatedBackgroundRMatrix;
        using SammyBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix;
        using FrohnerBackgroundRMatrix = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::FrohnerBackgroundRMatrix;

        auto getBackground = tools::overload{
          [&] ( const njoy::dryad::resonances::SammyBackground& bckg ) {
            backgrounds.emplace_back( SammyBackgroundRMatrix( i + 1, 
                                                              bckg.lowerSingularity(), 
                                                              bckg.upperSingularity(), 
                                                              bckg.polynomialCoefficients()[0], bckg.polynomialCoefficients()[1], bckg.polynomialCoefficients()[2],
                                                              bckg.logarithmicCoefficients()[0], bckg.logarithmicCoefficients()[1] ) );
          },
          [&] ( const njoy::dryad::resonances::FrohnerBackground& bckg ) {
            backgrounds.emplace_back( FrohnerBackgroundRMatrix( i + 1, 
                                                                bckg.lowerSingularity(), 
                                                                bckg.upperSingularity(), 
                                                                bckg.distantLevelParameter(),
                                                                bckg.poleStrength(),
                                                                bckg.averageRadiationWidth() ) );
          },
          [&] ( const njoy::dryad::resonances::TabulatedBackground& bckg ) {

            std::vector<long> interpolants;
            std::transform(
              bckg.interpolants().begin(),
              bckg.interpolants().end(),
              std::back_inserter(interpolants),
              [](InterpolationType type) {
                  switch (type) {
                      case InterpolationType::Histogram : return 1;
                      case InterpolationType::LinearLinear : return 2;
                      case InterpolationType::LinearLog : return 3;
                      case InterpolationType::LogLinear : return 4;
                      case InterpolationType::LogLog : return 5;
                  }
                  return 0;
              }
            );

            std::vector<long> boundaries(bckg.boundaries().begin(), bckg.boundaries().end());
            
            std::vector<double> energies(bckg.energies().begin(), bckg.energies().end());

            std::vector< std::complex <double> > values(bckg.values().begin(), bckg.values().end());

            backgrounds.emplace_back( TabulatedBackgroundRMatrix( i + 1,
                                                                  std::move( boundaries ),
                                                                  std::move( interpolants ),
                                                                  std::move( energies ),
                                                                  std::move( values ) ) );
          }
        };

        std::visit( getBackground, channel.background().value() );
      }
    }

    return ENDFtkBackgroundChannels( spingroup.channels().size(), std::move(backgrounds) ) ;
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
