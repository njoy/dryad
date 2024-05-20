#ifndef NJOY_DRYAD_TYPE_ALIASES
#define NJOY_DRYAD_TYPE_ALIASES

// system includes

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"

namespace njoy {
namespace dryad {

  using InterpolationType = scion::interpolation::InterpolationType;
  using ToleranceConvergence = scion::linearisation::ToleranceConvergence< double >;

} // dryad namespace
} // njoy namespace

#endif
