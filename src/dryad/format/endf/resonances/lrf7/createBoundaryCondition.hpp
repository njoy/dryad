#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEBOUNDARYCONDITION
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEBOUNDARYCONDITION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/BoundaryCondition.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the boundary condition value based on the particle pairs
   *
   *  @param[in] endfPairs    the parsed ENDF particle pairs
   */
  auto createBoundaryCondition( const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    // see if we have to read boundary conditions
    bool boundaries = std::any_of( endfPairs.shiftFactorFlag().begin(),
                                   endfPairs.shiftFactorFlag().end(),
                                   [] ( auto&& flag ) { return flag == 1; } );
    return boundaries ? dryad::resonances::BoundaryCondition::Constant
                      : dryad::resonances::BoundaryCondition::EliminateShift;
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
