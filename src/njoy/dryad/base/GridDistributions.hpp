#ifndef NJOY_DRYAD_GRIDDISTRIBUTIONS
#define NJOY_DRYAD_GRIDDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "dryad/type-aliases.hpp"

namespace njoy {
namespace dryad {
namespace base {

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

    #include "dryad/base/GridDistributions/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the grid values for which distributions are given
     */
    const std::vector< double >& grid() const {

      return this->x();
    }

    /**
     *  @brief Return the associated distributions
     */
    const std::vector< Distribution >& distributions() const {

      return this->f();
    }

    /**
     *  @brief Return the associated distributions
     */
    std::vector< Distribution >& distributions() {

      return this->f();
    }

    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;

    using Parent::operator();
  };

} // base namespace
} // dryad namespace
} // njoy namespace

#endif
