#ifndef NJOY_DRYAD_COVARIANCE_LINEARCOMBINATIONCOVARIANCE
#define NJOY_DRYAD_COVARIANCE_LINEARCOMBINATIONCOVARIANCE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance data for a reaction defined as a linear
   *         combination of other reactions' covariance data
   */
  class LinearCombinationCovariance {

    /* fields */
    double lower_;
    double upper_;
    std::vector< id::ReactionID > reactions_;
    std::vector< double > coefficients_;

    /* auxiliary function */

    static void verifySize( std::size_t reactions, std::size_t coefficients ) {

      if ( reactions != coefficients ) {

        Log::error( "The number of reactions and number of coefficients provided are not consistent" );
        Log::info( "Number reactions: {}", reactions );
        Log::info( "Number coefficients: {}", coefficients );
        throw std::exception();
      }
      if ( reactions < 1 ) {

        Log::error( "Expected at least one reaction involved in the linear combination" );
        Log::info( "Number reactions: {}", reactions );
        Log::info( "Number coefficients: {}", coefficients );
        throw std::exception();
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    LinearCombinationCovariance() = default;

    LinearCombinationCovariance( const LinearCombinationCovariance& ) = default;
    LinearCombinationCovariance( LinearCombinationCovariance&& ) = default;

    LinearCombinationCovariance& operator=( const LinearCombinationCovariance& ) = default;
    LinearCombinationCovariance& operator=( LinearCombinationCovariance&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lower          the lower energy limit
     *  @param[in] upper          the upper energy limit
     *  @param[in] reactions      the reactions in the linear combination
     *  @param[in] coefficients   the coefficients of the linear combination
     */
    LinearCombinationCovariance( double lower, double upper,
                                 std::vector< id::ReactionID > reactions,
                                 std::vector< double > coefficients ) :
      lower_( std::move( lower ) ), upper_( std::move( upper ) ),
      reactions_( std::move( reactions ) ),
      coefficients_( std::move( coefficients ) ) {

      verifySize( this->reactions().size(), this->coefficients().size() );
    }

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

    /**
     *  @brief Return the reactions in the linear combination
     */
    const std::vector< id::ReactionID >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the coefficients for the linear combination
     */
    const std::vector< double >& coefficients() const {

      return this->coefficients_;
    }

    /**
     *  @brief Return the number of reactions in the linear combination
     */
    std::size_t numberReactions() const {

      return this->reactions().size();
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
