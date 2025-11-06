#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFINTERPOLANT
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFINTERPOLANT

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
  long createEndfInterpolant( InterpolationType interpolant ) {

    switch ( interpolant ) {

      case InterpolationType::Histogram : return 1;
      case InterpolationType::LinearLinear : return 2;
      case InterpolationType::LinearLog : return 3;
      case InterpolationType::LogLinear : return 4;
      case InterpolationType::LogLog : return 5;
      default : {

        Log::error( "Cannot convert or handle interpolation type {}",
                    static_cast< int >( interpolant ) );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
