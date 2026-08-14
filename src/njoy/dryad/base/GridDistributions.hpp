#ifndef NJOY_DRYAD_BASE_GRIDDISTRIBUTIONS
#define NJOY_DRYAD_BASE_GRIDDISTRIBUTIONS

// system includes
#include <vector>

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "njoy/dryad/InterpolationType.hpp"

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

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    GridDistributions() = default;

    GridDistributions( const GridDistributions& ) = default;
    GridDistributions( GridDistributions&& ) = default;

    GridDistributions& operator=( const GridDistributions& ) = default;
    GridDistributions& operator=( GridDistributions&& ) = default;

    /**
     *  @brief Constructor
     *
     *   @param[in] grid            the grid values
     *   @param[in] distributions   the associated distributions
     *   @param[in] boundaries      the boundaries of the interpolation regions
     *   @param[in] interpolants    the interpolation types of the interpolation regions
     */
    GridDistributions( std::vector< double > grid,
                       std::vector< Distribution > distributions,
                       std::vector< std::size_t > boundaries,
                       std::vector< InterpolationType > interpolants ) :
      Parent( std::move( grid ), std::move( distributions ),
              std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for angular distributions using a single interpolation zone
     *
     *   @param[in] grid            the grid values
     *   @param[in] distributions   the associated distributions
     *   @param[in] interpolant     the interpolation type of the data (default lin-lin)
     */
    GridDistributions( std::vector< double > grid,
                       std::vector< Distribution > distributions,
                       InterpolationType interpolant = InterpolationType::LinearLinear ) :
      Parent( std::move( grid ), std::move( distributions ), interpolant ) {}

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
