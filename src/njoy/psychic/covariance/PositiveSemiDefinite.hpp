#ifndef NJOY_PSYCHIC_COVARIANCES_ISPOSITIVESEMIDEFINITE
#define NJOY_PSYCHIC_COVARIANCES_ISPOSITIVESEMIDEFINITE

// system includes
#include <algorithm>

// other includes
#include "scion/verification/ranges.hpp"
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace psychic {
namespace covariance {

  /**
   *  @class
   *  @brief Test to verify if a covariance matrix is positive semi-definite
   */
  class IsPositiveSemiDefinite : protected base::Test< IsPositiveSemiDefinite > {

    /* friend declarations */
    friend class base::Test< IsPositiveSemiDefinite >;

    /* type aliases */
    using Parent = base::Test< IsPositiveSemiDefinite >;

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

    IsPositiveSemiDefinite(
        double negative = constants::psychic::largest_allowed_negative_eigenvalue ) :
      Parent( "psychic.covariance.IsPositiveSemiDefinite" ),
      allowed_negative_eigenvalue_( negative ) {}

    /* methods */

    using Parent::name;
    using Parent::status;

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
     *  A covariance matrix is positive semi-definite if it is a square symmetric matrix
     *  that has eigenvalues that are larger than or equal to zero. Construction of
     *  on-diagonal covariance matrices already requires square and symmetric matrices so
     *  this particular aspect is not tested here.
     *
     *  The test returns the following status values:
     *    - Success : the on-diagonal covariance matrix is positive semi-definite
     *    - Warning : the on-diagonal covariance matrix is can be considered positive
     *                semi-definite by accepting small negative eigenvalues
     *    - Fail : the on-diagonal covariance matrix is not positive semi-definite
     *    - Skipped : the covariance matrix provided is not on-diagonal (ie its eigenvalues)
     *                cannot be calculated
     *
     *  The largest negative eigenvalue is available for the Warning and Fail state.
     *
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                         const std::optional< TestStatus >& > {

      using namespace scion::verification;

      this->clear();
      if ( covariance.eigenvalues().has_value() ) {

        if ( isAllLargerThanOrEqualTo( covariance.eigenvalues().value(), 0. ) ) {

          this->status( TestStatus::Success );
        }
        else {

          double eigenvalue = *std::min_element( covariance.eigenvalues()->begin(), covariance.eigenvalues()->end() );
          this->largestNegativeEigenValue( eigenvalue );

          if ( isAllLargerThanOrEqualTo( covariance.eigenvalues().value(), this->allowedNegativeEigenValue() ) ) {

            this->status( TestStatus::Warning );
          }
          else {

            this->status( TestStatus::Fail );
          }
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
