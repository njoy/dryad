#ifndef NJOY_FORMAT_ENDF_WRITE_CREATEINTERPOLANT
#define NJOY_FORMAT_ENDF_WRITE_CREATEINTERPOLANT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InterpolationType.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create an interpolation type from an ENDF interpolation type
   */
  inline long createInterpolant( dryad::InterpolationType interpolant ) {

    switch ( interpolant ) {

      case dryad::InterpolationType::Histogram : return 1;
      case dryad::InterpolationType::LinearLinear : return 2;
      case dryad::InterpolationType::LinearLog : return 3;
      case dryad::InterpolationType::LogLinear : return 4;
      case dryad::InterpolationType::LogLog : return 5;
      default : {

        Log::error( "Cannot convert or handle interpolation type {}",
                    static_cast< int >( interpolant ) );
        throw std::exception();
      }
    }
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
