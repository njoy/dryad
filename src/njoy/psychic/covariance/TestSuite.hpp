#ifndef NJOY_PSYCHIC_COVARIANCE_TESTSUITE
#define NJOY_PSYCHIC_COVARIANCE_TESTSUITE

// system includes

// other includes
#include "njoy/psychic/base/Test.hpp"
#include "njoy/psychic/TestStatus.hpp"
#include "njoy/psychic/covariance/TestSuite.hpp"
#include "njoy/psychic/covariance/PositiveVariances.hpp"
#include "njoy/psychic/covariance/EigenvalueRatio.hpp"
#include "njoy/psychic/covariance/PositiveSemiDefinite.hpp"
#include "njoy/psychic/covariance/BoundedCorrelations.hpp"
#include "njoy/psychic/covariance/DiagonalCorrelations.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace psychic {
namespace covariance {

  /**
   *  @class
   *  @brief A comprehensive covariance test suite
   */
  class TestSuite : protected base::Test< TestSuite > {

    /* friend declarations */
    friend class base::Test< TestSuite >;

    /* type aliases */
    using Parent = base::Test< TestSuite >;

    /* fields */

    PositiveVariances positive_variances_;
    PositiveSemiDefinite positive_semi_definite_;
    EigenvalueRatio eigenvalue_ratio_;
    BoundedCorrelations bounded_correlations_;
    DiagonalCorrelations diagonal_correlations_;

    /* auxiliary functions */

    /**
     *  @brief Reset the test result information
     */
    void reset() {

      this->positiveVariances().clear();
      this->positiveSemiDefinite().clear();
      this->boundedCorrelations().clear();
      this->diagonalCorrelations().clear();
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] tolerance   the absolute comparison tolerance
     *  @param[in] negative    the largest allowed negative eigenvalue
     *  @param[in] ratio       the smallest allowable positive eigenvalue ratio
     */
    TestSuite( double tolerance = constants::psychic::tolerance,
               double negative = constants::psychic::largest_allowed_negative_eigenvalue,
               double ratio = njoy::constants::psychic::smallest_eigenvalue_ratio ) :
      Parent( "psychic.covariance.TestSuite" ),
      positive_variances_(),
      positive_semi_definite_( negative ),
      eigenvalue_ratio_( ratio ),
      bounded_correlations_( tolerance ),
      diagonal_correlations_( tolerance ) {}

    /* methods */

    using Parent::name;
    using Parent::status;
    using Parent::clear;

    /**
     *  @brief Return the positive variance test
     */
    const PositiveVariances& positiveVariances() const {

      return this->positive_variances_;
    }

    /**
     *  @brief Return the positive variance test
     */
    PositiveVariances& positiveVariances() {

      return this->positive_variances_;
    }

    /**
     *  @brief Return the positive semi-definite test
     */
    const PositiveSemiDefinite& positiveSemiDefinite() const {

      return this->positive_semi_definite_;
    }

    /**
     *  @brief Return the positive semi-definite test
     */
    PositiveSemiDefinite& positiveSemiDefinite() {

      return this->positive_semi_definite_;
    }

    /**
     *  @brief Return the eigenvalue ratio test
     */
    const EigenvalueRatio& eigenvalueRatio() const {

      return this->eigenvalue_ratio_;
    }

    /**
     *  @brief Return the eigenvalue ratio test
     */
    EigenvalueRatio& eigenvalueRatio() {

      return this->eigenvalue_ratio_;
    }

    /**
     *  @brief Return the correlations between -1 and 1 test
     */
    const BoundedCorrelations& boundedCorrelations() const {

      return this->bounded_correlations_;
    }

    /**
     *  @brief Return the correlations between -1 and 1 test
     */
    BoundedCorrelations& boundedCorrelations() {

      return this->bounded_correlations_;
    }

    /**
     *  @brief Return the diagonal correlations are all 1 test
     */
    const DiagonalCorrelations& diagonalCorrelations() const {

      return this->diagonal_correlations_;
    }

    /**
     *  @brief Return the diagonal correlations are all 1 test
     */
    DiagonalCorrelations& diagonalCorrelations() {

      return this->diagonal_correlations_;
    }

    /**
     *  @brief Return the comparison tolerance
     */
    double tolerance() const {

      return this->boundedCorrelations().tolerance();
    }

    /**
     *  @brief Return the largest allowed negative eigenvalue
     */
    double allowedNegativeEigenValue() const {

      return this->positiveSemiDefinite().allowedNegativeEigenValue();
    }

    /**
     *  @brief Return the smallest acceptable eigenvalue ratio
     */
    double smallestAcceptableEigenvalueRatio() const {

      return this->eigenvalueRatio().smallestAcceptableEigenvalueRatio();
    }

    /**
     *  @brief Perform the test suite on the provided covariance matrix
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
      this->status( this->positiveVariances()( covariance ).value() );
      this->status( this->positiveSemiDefinite()( covariance ).value() && this->status().value() );
      this->status( this->eigenvalueRatio()( covariance ).value() && this->status().value() );
      this->status( this->boundedCorrelations()( covariance ).value() && this->status().value() );
      this->status( this->diagonalCorrelations()( covariance ).value() && this->status().value() );

      return this->status();
    }
  };

} // covariance namespace
} // psychic namespace
} // njoy namespace

#endif
