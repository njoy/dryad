#ifndef NJOY_DRYAD_UNIFORMDISTRIBUTION
#define NJOY_DRYAD_UNIFORMDISTRIBUTION

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/UniformDistributionType.hpp"

namespace njoy {
namespace dryad {
namespace base {

  /**
   *  @class
   *  @brief A uniform or equally probable distribution
   *
   *  The uniform distribution can be defined for discrete values
   *  (e.g. as used in inelastic thermal scattering ACE files) or
   *  cosine intervals (e.g. as used in older incident neutron ACE
   *  files).
   */
  class UniformDistribution {

    /* fields */
    UniformDistributionType type_;
    std::vector< double > values_;

    /* auxiliary functions */
    #include "dryad/base/UniformDistribution/src/verifySize.hpp"

  public:

    /* type aliases */

    /* constructor */

    #include "dryad/base/UniformDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution type
     */
    const UniformDistributionType& type() const noexcept {

      return this->type_;
    }

    /**
     *  @brief Return the values for the distribution
     */
    const std::vector< double >& values() const noexcept {

      return this->values_;
    }

    /**
     *  @brief Return the number of discrete values or intervals
     */
    std::size_t number() const noexcept {

      if ( this->type() == UniformDistributionType::Discrete ) {

        return this->values().size();
      }
      else {

        return this->values().size() - 1;
      }
    }

    /**
     *  @brief Return the mean defined by the distribution
     */
    double mean() const noexcept {

      double sum = std::accumulate( this->values().begin(), this->values().end(), 0. );
      if ( this->type() == UniformDistributionType::Interval ) {

        sum -= 0.5 * ( this->values().front() + this->values().back() );
      }

      return sum / static_cast< double >( this->number() );
    }
  };

} // base namespace
} // dryad namespace
} // njoy namespace

#endif
