#ifndef NJOY_PSYCHIC_COVARIANCE_EIGENVALUERATIO
#define NJOY_PSYCHIC_COVARIANCE_EIGENVALUERATIO

// system includes
#include <algorithm>

// other includes
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
   *  @brief Test to verify if the positive eigenvalue ratio looks reasonable
   */
  class EigenvalueRatio : protected base::Test< EigenvalueRatio > {

    /* friend declarations */
    friend class base::Test< EigenvalueRatio >;

    /* type aliases */
    using Parent = base::Test< EigenvalueRatio >;

    /* fields */

    // test tolerances
    double acceptable_ratio_;

    // test result information
    std::optional< double > smallest_positive_eigenvalue_;
    std::optional< double > largest_positive_eigenvalue_;
    std::optional< double > eigenvalue_ratio_;

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {

      this->smallestPositiveEigenvalue( std::nullopt );
      this->largestPositiveEigenvalue( std::nullopt );
      this->eigenvalueRatio( std::nullopt );
    }

  public:

    /* constructor */

    EigenvalueRatio( double ratio = njoy::constants::psychic::smallest_eigenvalue_ratio ) :
      Parent( "psychic.covariance.EigenvalueRatio" ),
      acceptable_ratio_( ratio ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    /**
     *  @brief Return the smallest acceptable eigenvalue ratio
     */
    double smallestAcceptableRatio() const {

      return this->acceptable_ratio_;
    }

    /**
     *  @brief Return the smallest positive eigenvalue that was found
     */
    const std::optional< double >& smallestPositiveEigenvalue() const {

      return this->smallest_positive_eigenvalue_;
    }

    /**
     *  @brief Set the smallest positive eigenvalue that was found
     *
     *  @param[in] eigenvalue   the eigenvalue
     */
    void smallestPositiveEigenvalue( std::optional< double > eigenvalue ) {

      this->smallest_positive_eigenvalue_ = std::move( eigenvalue );
    }

    /**
     *  @brief Return the largest positive eigenvalue that was found
     */
    const std::optional< double >& largestPositiveEigenvalue() const {

      return this->largest_positive_eigenvalue_;
    }

    /**
     *  @brief Set the largest positive eigenvalue that was found
     *
     *  @param[in] eigenvalue   the eigenvalue
     */
    void largestPositiveEigenvalue( std::optional< double > eigenvalue ) {

      this->largest_positive_eigenvalue_ = std::move( eigenvalue );
    }

    /**
     *  @brief Return the positive eigenvalue ratio
     */
    const std::optional< double >& eigenvalueRatio() const {

      return this->eigenvalue_ratio_;
    }

    /**
     *  @brief Set the positive eigenvalue ratio
     *
     *  @param[in] ratio   the eigenvalue ratio
     */
    void eigenvalueRatio( std::optional< double > ratio ) {

      this->eigenvalue_ratio_ = std::move( ratio );
    }

    /**
     *  @brief Verify if the provided covariance matrix has a reasonable eigenvalue ratio
     *
     *  This test can be run only for on-diagonal covariance matrices if the eigenvalues are
     *  available.
     *
     *  The test returns the following status values:
     *    - Success : the eigenvalue ratio is larger than or equal to the tolerance
     *    - Fail    : the eigenvalue ratio is smaller than the tolerance
     *    - Skipped : the test was skipped
     *
     *  The smallest and largest positive eigenvalue and their ratio is always available.
     *
     *  @param[in] covariance   the covariance matrix instance to be tested
     */
    template < typename Covariance >
    auto operator()( const Covariance& covariance )
    -> std::enable_if_t< std::is_same_v< Covariance, dryad::covariance::CrossSectionCovarianceMatrix > ||
                         std::is_same_v< Covariance, dryad::covariance::ProductMultiplicityCovarianceMatrix >,
                         const std::optional< TestStatus >& > {

      this->clear();
      if ( covariance.isOnDiagonal() && covariance.eigenvalues().has_value() ) {

        this->status( TestStatus::Success );

        auto eigenvalues = covariance.eigenvalues().value();
        std::sort( eigenvalues.begin(), eigenvalues.end() );

        auto iter = std::upper_bound( eigenvalues.begin(), eigenvalues.end(), 0. );
        if ( iter != eigenvalues.end() ) {

          this->smallestPositiveEigenvalue( *iter );
          this->largestPositiveEigenvalue( eigenvalues.back() );
          this->eigenvalueRatio( this->smallestPositiveEigenvalue().value()
                                 / this->largestPositiveEigenvalue().value() );

          if ( this->eigenvalueRatio().value() < this->smallestAcceptableRatio() ) {

            this->status( TestStatus::Fail );
          }
        }
        else {

          this->status( TestStatus::Fail );
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
