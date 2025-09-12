#ifndef NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/covariance/matrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A base class representing a covariance matrix with row and column keys
   */
  template < typename Key >
  class CovarianceMatrix {

    /* fields - row and column keys */
    std::vector< Key > row_;
    std::optional< std::vector< Key > > column_;

    /* fields - flag to indicate relative or absolute data */
    bool relative_;

    /* fields - covariance matrix */
    std::optional< Matrix< double > > covariances_;

    /* fields - standard deviations and correlations */
    std::optional< std::vector< double > > sigmas_;
    std::optional< Matrix< double > > correlations_;

    /* fields - eigenvalues */
    std::optional< std::vector< double > > eigenvalues_;

    /* auxiliary function */
    #include "dryad/covariance/base/CovarianceMatrix/src/verifyMatrix.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/verifyStandardDeviations.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/base/CovarianceMatrix/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row keys
     */
    const std::vector< Key >& rowKeys() const { return this->row_; }

    /**
     *  @brief Return the column keys
     *
     *  This returns the row heys if the covariance matrix is on-diagonal
     */
    const std::vector< Key >& columnKeys() const {

      if ( this->column_ ) {

        return this->column_.value();
      }
      else {

        return this->row_;
      }
    }

    /**
     *  @brief Return whether or not this covariance matrix is off diagonal
     */
    bool isOffDiagonal() const {

      return this->column_.has_value();
    }

    /**
     *  @brief Return whether or not this covariance matrix is on diagonal
     */
    bool isOnDiagonal() const {

      return ! this->isOffDiagonal();
    }

    /**
     *  @brief Return whether or not this covariance matrix is relative or not
     */
    bool isRelativeBlock() const {

      return this->relative_;
    }

    /**
     *  @brief Return whether or not this covariance matrix is absolute or not
     */
    bool isAbsoluteBlock() const {

      return ! this->isRelativeBlock();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const std::optional< Matrix< double > >& covariances() const {

      return this->covariances_;
    }

    /**
     *  @brief Return the standard deviations
     */
    const std::optional< std::vector< double > >& standardDeviations() const {

      return this->sigmas_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return this->eigenvalues_;
    }

    #include "dryad/covariance/base/CovarianceMatrix/src/calculateCovariances.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateStandardDeviations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateCorrelations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateEigenvalues.hpp"
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
