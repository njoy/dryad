#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONS
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONS

// system includes

// other includes
#include "dryad/GridDistributions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace dryad {

  using TabulatedAngularDistributions = GridDistributions< TabulatedAngularDistribution >;

} // dryad namespace
} // njoy namespace

#endif
