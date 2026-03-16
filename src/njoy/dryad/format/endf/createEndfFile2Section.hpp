#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFFILE2SECTION

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
   *  @brief Create an ENDF MF2 section object from a ResonanceParameters object
   *
   *  @param[in] parameters   the resonance parameter data
   */
  inline ENDFtk::section::Type< 2, 151 >
  createEndfFile2Section( double awr, const dryad::resonances::ResonanceParameters& parameters ) {

    std::vector< ENDFtk::section::Type< 2, 151 >::ResonanceRange > ranges;
    int za = parameters.resolved().front().reactions().front().target().za();

    // go over the resolved resonance ranges
    for( const auto& region : parameters.resolved() ) {

      ranges.emplace_back( region.lowerEnergyLimit(), region.upperEnergyLimit(), 0,
                           resonances::lrf7::createEndfRMatrixLimited( region ) );
    };

    //! @todo go over the resolved resonance ranges

    ENDFtk::section::Type< 2, 151 >::Isotope isotope( za, 1.0, false, std::move( ranges ) );
    return ENDFtk::section::Type< 2, 151 >( za, awr, { isotope } );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
