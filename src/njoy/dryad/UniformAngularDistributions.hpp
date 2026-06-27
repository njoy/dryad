#ifndef NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS
#define NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS

// system includes

// other includes
#include "njoy/dryad/base/GridDistributions.hpp"
#include "njoy/dryad/UniformAngularDistribution.hpp"
#include "njoy/dryad/TabulatedAverageCosine.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Angular distribution data given using uniform distributions
   */
  class UniformAngularDistributions :
      protected base::GridDistributions< UniformAngularDistribution > {

    /* type aliases */

    using Parent = base::GridDistributions< UniformAngularDistribution >;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UniformAngularDistributions() = default;

    UniformAngularDistributions( const UniformAngularDistributions& ) = default;
    UniformAngularDistributions( UniformAngularDistributions&& ) = default;

    UniformAngularDistributions& operator=( const UniformAngularDistributions& ) = default;
    UniformAngularDistributions& operator=( UniformAngularDistributions&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] grid            the grid values
     *  @param[in] distributions   the associated distributions
     *  @param[in] boundaries      the boundaries of the interpolation regions
     *  @param[in] interpolants    the interpolation types of the interpolation regions
     */
    UniformAngularDistributions( std::vector< double > grid,
                                 std::vector< UniformAngularDistribution > distributions,
                                 std::vector< std::size_t > boundaries,
                                 std::vector< InterpolationType > interpolants ) :
      Parent( std::move( grid ), std::move( distributions ),
              std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for angular distributions using a single interpolation zone
     *
     *  @param[in] grid            the grid values
     *  @param[in] distributions   the associated distributions
     *  @param[in] interpolant     the interpolation type of the data (default lin-lin)
     */
    UniformAngularDistributions( std::vector< double > grid,
                                 std::vector< UniformAngularDistribution > distributions,
                                 InterpolationType interpolant = InterpolationType::LinearLinear ) :
      Parent( std::move( grid ), std::move( distributions ), interpolant ) {}

    /* methods */

    using Parent::grid;
    using Parent::distributions;
    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;

    // there is no call operator on the uniform distribution, so we do not expose operator()

    /**
     *  @brief Return the average cosine values
     */
    TabulatedAverageCosine averageCosines() const {

      std::vector< double > cosines;
      cosines.reserve( this->numberPoints() );
      std::transform( this->distributions().begin(), this->distributions().end(),
                      std::back_inserter( cosines ),
                      [] ( auto&& distribution ) { return distribution.averageCosine(); } );
      return TabulatedAverageCosine( this->grid(), std::move( cosines ),
                                     this->boundaries(),
                                     this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UniformAngularDistributions& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UniformAngularDistributions& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
