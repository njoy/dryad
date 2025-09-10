#ifndef NJOY_DRYAD_COVARIANCE_COVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_COVARIANCEMATRIX

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
   *  @brief A base class representing a covariance matrix block with
   *         structure information
   *
   *  The only requirement on the Structure template is that it has a size()
   *  function. For example: the number of groups for an energy structure when
   *  the matrix is related to grouped energy data (xs, spectrum, etc.) or the
   *  number of fission products when the matrix is related to fission product
   *  yields.
   */
  template < typename Structure >
  class CovarianceMatrix {

    /* fields - row and column structure data */
    Structure row_;
    std::optional< Structure > column_;

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
     *  @brief Return the row structure data
     */
    const Structure& rowStructure() const { return this->row_; }

    /**
     *  @brief Return the column structure data
     *
     *  This returns the row structure data if the covariance block is a diagonal block
     */
    const Structure& columnStructure() const {

      if ( this->column_ ) {

        return this->column_.value();
      }
      else {

        return this->row_;
      }
    }

    /**
     *  @brief Return whether or not this covariance block is an off diagonal block
     */
    bool isOffDiagonalBlock() const {

      return this->column_.has_value();
    }

    /**
     *  @brief Return whether or not this covariance block is a diagonal block
     */
    bool isDiagonalBlock() const {

      return ! this->isOffDiagonalBlock();
    }

    /**
     *  @brief Return whether or not this covariance block is relative or not
     */
    bool isRelativeBlock() const {

      return this->relative_;
    }

    /**
     *  @brief Return whether or not this covariance block is absolute or not
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

    #include "dryad/covariance/base/CovarianceMatrix/src/calculateStandardDeviations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateCorrelations.hpp"
    #include "dryad/covariance/base/CovarianceMatrix/src/calculateEigenvalues.hpp"
  };

} // base namespace
} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
