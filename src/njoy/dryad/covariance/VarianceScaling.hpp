#ifndef NJOY_DRYAD_COVARIANCE_VARIANCESCALING
#define NJOY_DRYAD_COVARIANCE_VARIANCESCALING

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/ScalingType.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Variance scaling information
   *
   *  Some ENDF evaluations provide variance scaling information for cross section
   *  covariances. Each factor value for a given group characterises an uncorrelated
   *  contribution to the absolute variance of the cross section averaged over any
   *  energy subgroup that includes a portion of the energy interval over which the
   *  factor is defined.
   */
  class VarianceScaling {

    /* fields - variance scaling group structure and factors */
    std::vector< double > energies_;
    std::vector< double > factors_;

    /* fields - scaling type */
    ScalingType type_;

    /* auxiliary functions */

    static void verifySize( const std::vector< double >& energies,
                            const std::vector< double >& factors ) {

      // at least two elements in the energy boundary values
      if ( energies.size() < 2 ) {

        Log::error( "There must be at least 2 energy boundary values" );
        throw std::exception();
      }

      // the energy boundary values are sorted
      if ( !std::is_sorted( energies.begin(), energies.end() ) ) {

        Log::error( "The energy boundary values do not appear to be in ascending "
                    "order" );
        throw std::exception();
      }

      // the energy boundary values are unique
      if ( energies.end() != std::adjacent_find( energies.begin(), energies.end() ) ) {

        Log::error( "The energy boundary values do not appear to be unique" );

        auto iter = std::adjacent_find( energies.begin(), energies.end() );
        while ( iter != energies.end() ) {

          Log::info( "Duplicate energy found: ", *iter );
          iter = std::adjacent_find( ++iter, energies.end() );
        }
        throw std::exception();
      }

      // check if the group structure size and
      if ( energies.size() - 1 != factors.size() ) {

        Log::error( "The number of groups and the number of scaling factors are not consistent" );
        Log::info( "Number energies: {}", energies.size() );
        Log::info( "Number factors: {}", factors.size() );
        Log::info( "Expected factors: {}", energies.size() - 1 );
        throw std::exception();
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor for variance scaling
     *
     *  @param[in] type        the scaling procedure type
     *  @param[in] energies    the energy boundaries
     *  @param[in] factors     the scaling factors
     */
    VarianceScaling( ScalingType type,
                     std::vector< double > energies,
                     std::vector< double > factors ) :
        energies_( std::move( energies ) ),
        factors_( std::move( factors ) ),
        type_( std::move( type ) ) {

      verifySize( this->energies(), this->factors() );
    }

    /* methods */

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the scaling factors
     */
    const std::vector< double >& factors() const {

      return this->factors_;
    }

    /**
     *  @brief Return the number of energy groups
     */
    std::size_t numberGroups() const {

      return this->energies().size() - 1;
    }

    /**
     *  @brief Return the scaling procedure type
     */
    const ScalingType& type() const {

      return this->type_;
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
