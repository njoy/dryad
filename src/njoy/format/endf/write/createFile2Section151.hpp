#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEFILE2SECTION151
#define NJOY_FORMAT_ENDF_WRITE_CREATEFILE2SECTION151

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/format/endf/write/resonances/lrf7/createRMatrixLimited.hpp"
#include "ENDFtk/section/2.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an ENDF MF2 MT151 section object from a ResonanceParameters object
   *
   *  @param[in] awr                      the atomic weight ratio
   *  @param[in] parameters               the resonance parameter data
   *  @param[in] reducedWidthAmplitudes   use reduced width amplitudes
   */
  inline ENDFtk::section::Type< 2, 151 >
  createFile2Section151( double awr,
                         const dryad::resonances::ResonanceParameters& parameters,
                         bool reducedWidthAmplitudes = true ) {

    std::vector< ENDFtk::section::Type< 2, 151 >::ResonanceRange > ranges;
    int za = parameters.resolved().front().reactions().front().target().za();

    // go over the resolved resonance ranges
    for( const auto& region : parameters.resolved() ) {

      // LRF=7 : no energy dependent scattering radius possible (NRO=0),
      //         naps does not matter so we set it to 0
      ranges.emplace_back( region.lowerEnergyLimit(), region.upperEnergyLimit(), 0,
                           resonances::lrf7::createRMatrixLimited( region, reducedWidthAmplitudes ),
                           std::nullopt );
    };

    //! @todo go over the unresolved resonance ranges

    ENDFtk::section::Type< 2, 151 >::Isotope isotope( za, 1.0, false, std::move( ranges ) );
    return ENDFtk::section::Type< 2, 151 >( za, awr, { isotope } );
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
