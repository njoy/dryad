#ifndef NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/matrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A base class representing a covariance matrix
   */
  template < typename Metadata, typename... Ts >
  class CovarianceMatrix {

    /* type aliases */
    using Key = std::tuple< Ts... >;
    using Selection = std::tuple< std::optional< Ts >... >;

  private:

    /* fields - row and column metadata */
    Metadata row_metadata_;
    std::optional< Metadata > column_metadata_;

    /* fields - flag to indicate relative or absolute data */
    bool relative_;

    /* fields - covariance matrix */
    matrix::Matrix< double > covariances_;

    /* fields - standard deviations and correlations */
    std::optional< std::vector< double > > sigmas_;
    std::optional< matrix::Matrix< double > > correlations_;

    /* fields - eigenvalues */
    std::optional< std::vector< double > > eigenvalues_;

    /* auxiliary function */
    #include "dryad/covariance/base/CovarianceMatrix/src/verifyMatrix.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/verifyStandardDeviations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateCovariances.hpp"

  public:

    /* constructor */
    #include "dryad/covariance/base/CovarianceMatrix/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the row metadata
     */
    const Metadata& rowMetadata() const { return this->row_metadata_; }

    /**
     *  @brief Return the column metadata
     */
    const Metadata& columnMetadata() const {

      if ( this->column_metadata_.has_value() ) {

        return this->column_metadata_.value();
      }
      else {

        return this->row_metadata_;
      }
    }

    /**
     *  @brief Return whether or not this covariance matrix is off diagonal
     */
    bool isOffDiagonal() const {

      return this->column_metadata_.has_value();
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
    bool isRelativeMatrix() const {

      return this->relative_;
    }

    /**
     *  @brief Return whether or not this covariance matrix is absolute or not
     */
    bool isAbsoluteMatrix() const {

      return ! this->isRelativeMatrix();
    }

    /**
     *  @brief Return the covariance matrix
     */
    const matrix::Matrix< double >& covariances() const {

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
    const std::optional< matrix::Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return this->eigenvalues_;
    }

    #include "dryad/covariance/base/CovarianceMatrix/src/calculateStandardDeviations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateCorrelations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateEigenvalues.hpp"

    #include "dryad/covariance/base/CovarianceMatrix/src/extract.hpp"

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CovarianceMatrix& right ) const {

      return this->rowMetadata() == right.rowMetadata() &&
             this->columnMetadata() == right.columnMetadata() &&
             this->covariances() == right.covariances();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
