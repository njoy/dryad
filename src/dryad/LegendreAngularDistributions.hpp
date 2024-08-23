#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONS
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONS

// system includes

// other includes
#include "dryad/base/GridDistributions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Angular distribution data given using Legendre expansions
   */
  class LegendreAngularDistributions :
      protected base::GridDistributions< LegendreAngularDistribution > {

    /* type aliases */
    using Parent = base::GridDistributions< LegendreAngularDistribution >;

  public:

    /* constructor */

    #include "dryad/LegendreAngularDistributions/src/ctor.hpp"

    /* methods */

    using Parent::grid;
    using Parent::distributions;
    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;
    using Parent::operator();

//    /**
//     *  @brief Return the LegendreAngularDistribution for a grid value
//     */
//    LegendreAngularDistribution operator()( double grid ) const noexcept {
//
//    }

//    /**
//     *  @brief Return the average cosine values
//     */
//    TabulatedAverageCosines averageCosines() const noexcept {
//
//    }
  };

} // dryad namespace
} // njoy namespace

#endif
