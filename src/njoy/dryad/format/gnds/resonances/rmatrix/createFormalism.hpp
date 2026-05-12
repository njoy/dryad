#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATEFORMALISM
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATEFORMALISM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Formalism.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the rmatrix formalism from a GNDS string
   */
  inline dryad::resonances::Formalism createFormalism( const std::string& formalism ) {

    if ( formalism == "ReichMoore" ) {

      return dryad::resonances::Formalism::ReichMoore;
    }
    else if ( formalism == "FullRMatrix" ) {

      return dryad::resonances::Formalism::GeneralRMatrix;
    }
    else {

      Log::error( "GNDS rmatrix formalism \'{}\' is not recognised", formalism );
      throw std::exception();
    }
  }

} // rmatrix namespace
} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
