#ifndef NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS
#define NJOY_DRYAD_UNIFORMANGULARDISTRIBUTIONS

// system includes

// other includes
#include "dryad/base/GridDistributions.hpp"
#include "dryad/UniformAngularDistribution.hpp"
#include "dryad/TabulatedAverageCosine.hpp"

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

    #include "dryad/UniformAngularDistributions/src/ctor.hpp"

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
    TabulatedAverageCosine averageCosines() const noexcept {

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
    bool operator==( const UniformAngularDistributions& right ) const noexcept {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UniformAngularDistributions& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
