#ifndef NJOY_DRYAD_UNIFORMANGULARDISTRIBUTION
#define NJOY_DRYAD_UNIFORMANGULARDISTRIBUTION

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/UniformDistributionType.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A uniform or equally probably angular distribution
   *
   *  The uniform distribution can be defined for discrete values
   *  (e.g. as used in inelastic thermal scattering ACE files) or
   *  cosine intervals (e.g. as used in older incident neutron ACE
   *  files).
   */
  class UniformAngularDistribution {

    /* fields */
    UniformDistributionType type_;
    std::vector< double > cosines_;

    /* auxiliary functions */

  public:

    /* type aliases */

    /* constructor */

    #include "dryad/UniformAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution type
     */
    const UniformDistributionType& type() const noexcept {

      return this->type_;
    }

    /**
     *  @brief Return the cosine values for the distribution
     */
    const std::vector< double >& cosines() const noexcept {

      return this->cosines_;
    }

    /**
     *  @brief Return the number of discrete values or intervals
     */
    std::size_t number() const noexcept {

      if ( this->type() == UniformDistributionType::Discrete ) {

        return this->cosines().size();
      }
      else {

        return this->cosines().size() - 1;
      }
    }

    /**
     *  @brief Return the average cosine defined by the distribution
     */
    double averageCosine() const noexcept {

      double sum = std::accumulate( this->cosines().begin(), this->cosines().end(), 0. );
      if ( this->type() == UniformDistributionType::Interval ) {

        sum -= 0.5 * ( this->cosines().front() + this->cosines().back() );
      }

      return sum / static_cast< double >( this->number() );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
