#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_CREATEBOUNDARYCONDITION
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_CREATEBOUNDARYCONDITION

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/BoundaryCondition.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the rmatrix boundary condition string from a dryad boundary condition enum
   *
   *  @param[in] type   the boundary condition type
   */
  inline std::string createBoundaryCondition( const dryad::resonances::BoundaryCondition& type ) {

    switch ( type ) {

      case dryad::resonances::BoundaryCondition::ShiftFactor : return "EliminateShiftFunction";
      case dryad::resonances::BoundaryCondition::Constant    : return "Given";
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
