#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION151
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION151

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfRMatrixLimited.hpp"
#include "ENDFtk/section/2.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an ENDF MF2 MT151 section object from a ResonanceParameters object
   *
   *  @param[in] parameters   the resonance parameter data
   */
  inline ENDFtk::section::Type< 2, 151 >
  createEndfFile2Section151( double awr, const dryad::resonances::ResonanceParameters& parameters ) {

    std::vector< ENDFtk::section::Type< 2, 151 >::ResonanceRange > ranges;
    int za = parameters.resolved().front().reactions().front().target().za();

    // go over the resolved resonance ranges
    for( const auto& region : parameters.resolved() ) {

      // LRF=7 : no energy dependent scattering radius possible (NRO=0),
      //         naps does not matter so we set it to 1
      ranges.emplace_back( region.lowerEnergyLimit(), region.upperEnergyLimit(), 1,
                           resonances::lrf7::createEndfRMatrixLimited( region ),
                           std::nullopt );
    };

    //! @todo go over the unresolved resonance ranges

    ENDFtk::section::Type< 2, 151 >::Isotope isotope( za, 1.0, false, std::move( ranges ) );
    return ENDFtk::section::Type< 2, 151 >( za, awr, { isotope } );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
