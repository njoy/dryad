#ifndef NJOY_PSYCHIC_COVARIANCE_POSITIVESEMIDEFINITE
#define NJOY_PSYCHIC_COVARIANCE_POSITIVESEMIDEFINITE

// system includes
#include <algorithm>

// other includes
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace psychic {
namespace covariance {

  /**
   *  @class
   *  @brief Test to verify if a covariance matrix is positive semi-definite
   */
  class PositiveSemiDefinite : protected base::Test< PositiveSemiDefinite > {

    /* friend declarations */
    friend class base::Test< PositiveSemiDefinite >;

    /* type aliases */
    using Parent = base::Test< PositiveSemiDefinite >;

    /* fields */

    // test tolerances
    double allowed_negative_eigenvalue_;

    // test result information
    std::optional< double > largest_negative_eigenvalue_;

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {

      this->largestNegativeEigenValue( std::nullopt );
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] negative   the largest allowed negative eigenvalue
     */
    PositiveSemiDefinite( double negative = constants::psychic::largest_allowed_negative_eigenvalue ) :
      Parent( "psychic.covariance.PositiveSemiDefinite" ),
      allowed_negative_eigenvalue_( negative ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    /**
     *  @brief Return the largest allowed negative eigenvalue
     */
    double allowedNegativeEigenValue() const {

      return this->allowed_negative_eigenvalue_;
    }

    /**
     *  @brief Return the largest negative eigenvalue that was found
     */
    const std::optional< double >& largestNegativeEigenValue() const {

      return this->largest_negative_eigenvalue_;
    }

    /**
     *  @brief Set the largest negative eigenvalue that was found
     *
     *  @param[in] eigenvalue   the eigenvalue
     */
    void largestNegativeEigenValue( std::optional< double > eigenvalue ) {

      this->largest_negative_eigenvalue_ = std::move( eigenvalue );
    }

    /**
     *  @brief Verify if the provided covariance matrix is positive semi-definite
     *
     *  This test can be run only for on-diagonal covariance matrices if the eigenvalues are
     *  available.
     *
     *  A covariance matrix is positive semi-definite if it is a square symmetric matrix
     *  that has eigenvalues that are larger than or equal to zero. Construction of
     *  on-diagonal covariance matrices already requires square and symmetric matrices so
     *  this particular aspect is not tested here.
     *
     *  The test returns the following status values:
     *    - Success : the on-diagonal covariance matrix is positive semi-definite
     *    - Warning : the on-diagonal covariance matrix is can be considered positive
     *                semi-definite by accepting small negative eigenvalues
     *    - Fail    : the on-diagonal covariance matrix is not positive semi-definite
     *    - Skipped : the test was skipped
     *
     *  The largest negative eigenvalue is available for the Warning and Fail state.
     *
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::AngularDistributionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                         const std::optional< TestStatus >& > {

      this->clear();
      if ( covariance.isOnDiagonal() && covariance.eigenvalues().has_value() ) {

        this->status( TestStatus::Success );

        auto min = *std::min_element( covariance.eigenvalues()->begin(), covariance.eigenvalues()->end() );

        if ( min < 0. ) {

          this->largestNegativeEigenValue( min );
          this->status( min < this->allowedNegativeEigenValue() ? TestStatus::Fail : TestStatus::Warning );
        }
      }
      else {

        this->status( TestStatus::Skipped );
      }

      return this->status();
    }
  };

} // covariance namespace
} // psychic namespace
} // njoy namespace

#endif
