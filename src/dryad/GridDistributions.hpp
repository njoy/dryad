#ifndef NJOY_DRYAD_GRIDDISTRIBUTIONS
#define NJOY_DRYAD_GRIDDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/LegendreAngularDistribution.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Distribution data given as x,f(y)
   */
  template < typename Distribution >
  class GridDistributions :
      protected scion::math::InterpolationTableFunction< double, Distribution > {

    /* type aliases */
    using Parent = scion::math::InterpolationTableFunction< double, Distribution >;

  public:

    /* constructor */

    #include "dryad/GridDistributions/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the grid values for which distributions are given
     */
    const std::vector< double >& grid() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the associated distributions
     */
    const std::vector< Distribution >& distributions() const noexcept {

      return this->f();
    }

    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;

    using Parent::operator();
  };

} // dryad namespace
} // njoy namespace

#endif
