#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATEBOUNDARYCONDITION
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATEBOUNDARYCONDITION

// system includes

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  enum class BoundaryCondition : short {

    ShiftFactor = 1,
    Constant = 2,
    NegativeOrbitalMomentum = 3
};

  /**
   *  @brief Create the rmatrix boundary condition from a GNDS string
   */
  inline BoundaryCondition createBoundaryCondition( const std::string& boundary ) {

    if ( boundary == "EliminateShiftFunction" ) {

      return BoundaryCondition::ShiftFactor;
    }
    else if ( boundary == "NegativeOrbitalMomentum" ) {

      return BoundaryCondition::NegativeOrbitalMomentum;
    }
    else if ( boundary == "Given" ) {

      return BoundaryCondition::Constant;
    }
    else {

      Log::error( "GNDS rmatrix boundary condition \'{}\' is not recognised", boundary );
      throw std::exception();
    }
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
