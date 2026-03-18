#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONANCEPARAMETERS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONANCEPARAMETERS

// system includes
#include <vector>

// other includes
#include "njoy/dryad/resonances/ResonanceTable.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the background channel data for LRF7 resonance parameters
   *
   *  @param[in] spingroup   the spin group
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceParameters
  createEndfResonanceParameters( const dryad::resonances::ResonanceTable& table ) {

    using ResonanceParameters = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceParameters;

    std::size_t nrs = table.numberEnergies();
    std::size_t nch = table.numberChannels();

    std::vector< double > energies = table.energies();
    std::vector< std::vector< double > > parameters( nrs,
                                                     std::vector< double >( nch ) );

    decltype(auto) widths = table.reducedWidthAmplitudes();
    for ( std::size_t i = 0; i < nch; ++i ) {

      for ( std::size_t j = 0; j < nrs; ++j ) {

        parameters[j][i] = widths[i][j];
      }
    }

    return ResonanceParameters( std::move( energies ), std::move( parameters ) ) ;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
