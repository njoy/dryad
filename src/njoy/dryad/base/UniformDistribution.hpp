#ifndef NJOY_DRYAD_BASE_UNIFORMDISTRIBUTION
#define NJOY_DRYAD_BASE_UNIFORMDISTRIBUTION

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/UniformDistributionType.hpp"

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

    /**
     *  @brief Verify the size of the data
     *
     *  @param[in] size   the number of cosine values
     *  @param[in] type   the uniform distribution type
     */
    static void verifySize( std::size_t size, const UniformDistributionType& type ) {

      if ( type == UniformDistributionType::Discrete ) {

        if ( size == 0 ) {

          Log::error( "Expected at least 1 discrete value, found {}", size );
          throw std::exception();
        }
      }
      else {

        if ( size < 2 ) {

          Log::error( "Expected at least 2 values for an interval, found {}", size );
          throw std::exception();
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UniformDistribution() = default;

    UniformDistribution( const UniformDistribution& ) = default;
    UniformDistribution( UniformDistribution&& ) = default;

    UniformDistribution& operator=( const UniformDistribution& ) = default;
    UniformDistribution& operator=( UniformDistribution&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param values   the values
     *  @param type     the uniform distribution type
     */
    UniformDistribution( std::vector< double > values,
                         UniformDistributionType type ) :
      type_( std::move( type ) ), values_( std::move( values ) ) {

      verifySize( this->values_.size(), this->type() );
    }

    /* methods */

    /**
     *  @brief Return the distribution type
     */
    const UniformDistributionType& type() const {

      return this->type_;
    }

    /**
     *  @brief Return the values for the distribution
     */
    const std::vector< double >& values() const {

      return this->values_;
    }

    /**
     *  @brief Return the number of discrete values or intervals
     */
    std::size_t number() const {

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
    double mean() const {

      double sum = std::accumulate( this->values().begin(), this->values().end(), 0. );
      if ( this->type() == UniformDistributionType::Interval ) {

        sum -= 0.5 * ( this->values().front() + this->values().back() );
      }

      return sum / static_cast< double >( this->number() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const UniformDistribution& right ) const {

      return this->type() == right.type() && this->values() == right.values();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const UniformDistribution& right ) const {

      return ! this->operator==( right );
    }
  };

} // base namespace
} // dryad namespace
} // njoy namespace

#endif
