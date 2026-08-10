#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_CREATEFORMALISM
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_CREATEFORMALISM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Formalism.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the rmatrix formalism string from a dryad formalism enum
   *
   *  @param[in] formalism   the formalism type
   */
  inline std::string createFormalism( const dryad::resonances::Formalism& formalism ) {

    switch ( formalism ) {

      case dryad::resonances::Formalism::ReichMoore      : return "ReichMoore";
      case dryad::resonances::Formalism::GeneralRMatrix  : return "FullRMatrix";
      default : {

        throw std::runtime_error( "You have somehow reached unreachable code, "
                                  "contact an njoy developer." );
      }
    }
  }

} // rmatrix namespace
} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
