#ifndef NJOY_FORMAT_ENDF_READ_CREATEINTERPOLANT
#define NJOY_FORMAT_ENDF_READ_CREATEINTERPOLANT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InterpolationType.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create an interpolation type from an ENDF interpolation type
   *
   *  @param[in] interpolant    the ENDF interpolation value
   */
  inline dryad::InterpolationType
  createInterpolant( int interpolant ) {

    switch ( interpolant ) {

      case 1 : return dryad::InterpolationType::Histogram;
      case 2 : return dryad::InterpolationType::LinearLinear;
      case 3 : return dryad::InterpolationType::LinearLog;
      case 4 : return dryad::InterpolationType::LogLinear;
      case 5 : return dryad::InterpolationType::LogLog;
      default : {

        Log::error( "Cannot convert or handle ENDF interpolation type {}",
                    interpolant );
        throw std::exception();
      }
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
