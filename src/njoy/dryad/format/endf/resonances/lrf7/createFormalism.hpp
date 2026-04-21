#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEFORMALISM
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEFORMALISM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Formalism.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the formalism enum value
   *
   *  @param[in] endf   the parsed ENDF LRF7 data
   */
  inline auto createFormalism( const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    switch ( endf.formalism() ) {

      case 3 : return dryad::resonances::Formalism::ReichMoore;
      case 4 : return dryad::resonances::Formalism::GeneralRMatrix;
      default : {

        Log::error( "LRF7 resonance formalism (KRM) type \'{}\' is currently not supported", endf.formalism() );
        throw std::exception();
      }
    }
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
