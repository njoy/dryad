#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEINTERPOLANT
#define NJOY_DRYAD_FORMAT_ENDF_CREATEINTERPOLANT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/type-aliases.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an interpolation type from an ENDF interpolation type
   */
  InterpolationType createInterpolant( int interpolant ) {

    switch ( interpolant ) {

      case 1 : return InterpolationType::Histogram;
      case 2 : return InterpolationType::LinearLinear;
      case 3 : return InterpolationType::LinearLog;
      case 4 : return InterpolationType::LogLinear;
      case 5 : return InterpolationType::LogLog;
      default : {

        Log::error( "Cannot convert or handle ENDF interpolation type {}",
                    interpolant );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
