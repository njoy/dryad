#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATEKINEMATICS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATEKINEMATICS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Kinematics.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the formalism enum value
   *
   *  @param[in] endf   the parsed ENDF LRF7 data
   */
  inline auto createKinematics( const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    //! @todo this ENDFtk function is misleading, false means non-relativistic
    return endf.nonRelativisticKinematics() ? dryad::resonances::Kinematics::Relativistic
                                            : dryad::resonances::Kinematics::NonRelativistic;
  }

} // lrf7 namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
