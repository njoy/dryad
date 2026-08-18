#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONCOVARIANCEMATRIX

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/VarianceScaling.hpp"
#include "njoy/dryad/covariance/CrossSectionMetadata.hpp"
#include "njoy/dryad/covariance/base/CovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief A cross section covariance matrix block
   *
   *  This covariance matrix uses 2 dimensions as follows (from outer to inner
   *  dimension): the reactions and the energy groups.
   */
  class CrossSectionCovarianceMatrix :
    protected base::CovarianceMatrix< CrossSectionMetadata,
                                      id::ReactionID, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::CovarianceMatrix< CrossSectionMetadata,
                                           id::ReactionID, id::EnergyGroup >;

    /* fields */
    std::optional< VarianceScaling > scaling_;

    /* auxiliary functions */

  public:

    /* constructor */

    private:

    CrossSectionCovarianceMatrix( Parent&& base ) :
      Parent( std::move( base ) ) {}

    public:

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CrossSectionCovarianceMatrix() = default;

    CrossSectionCovarianceMatrix( const CrossSectionCovarianceMatrix& ) = default;
    CrossSectionCovarianceMatrix( CrossSectionCovarianceMatrix&& ) = default;

    CrossSectionCovarianceMatrix& operator=( const CrossSectionCovarianceMatrix& ) = default;
    CrossSectionCovarianceMatrix& operator=( CrossSectionCovarianceMatrix&& ) = default;

    /**
     *  @brief Constructor for an on-diagonal cross section covariance matrix
     *
     *  @param[in] metadata      the row and column metadata
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag (default is true)
     *  @param[in] scaling       the variance scaling information (default is none)
     */
    CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                                  matrix::Matrix< double > covariances,
                                  bool relative = true,
                                  std::optional< VarianceScaling > scaling = std::nullopt ) :
      Parent( std::move( metadata ), std::move( covariances ), relative ),
      scaling_( std::move( scaling ) ) {}

    /**
     *  @brief Constructor for an off-diagonal cross section covariance matrix
     *
     *  @param[in] rowMetadata       the row metadata
     *  @param[in] columnMetadata    the column metadata
     *  @param[in] covariances       the covariance matrix
     *  @param[in] relative          the relative covariance flag (default is true)
     */
    CrossSectionCovarianceMatrix( CrossSectionMetadata rowMetadata,
                                  CrossSectionMetadata columnMetadata,
                                  matrix::Matrix< double > covariances,
                                  bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              std::move( covariances ), relative ),
      scaling_( std::nullopt ) {}

    /**
     *  @brief Constructor for an on-diagonal cross section correlation matrix
     *
     *  @param[in] metadata       the row and column metadata
     *  @param[in] deviations     the standard deviations
     *  @param[in] correlations   the correlation matrix
     *  @param[in] relative       the relative covariance flag (default is true)
     *  @param[in] scaling        the variance scaling information (default is none)
     */
    CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                                  std::vector< double > deviations,
                                  matrix::Matrix< double > correlations,
                                  bool relative = true,
                                  std::optional< VarianceScaling > scaling = std::nullopt ) :
      Parent( std::move( metadata ), std::move( deviations ),
              std::move( correlations ), relative ),
      scaling_( std::move( scaling ) ) {}

    /**
     *  @brief Constructor for an off-diagonal cross section correlation matrix
     *
     *  @param[in] rowMetadata        the row metadata
     *  @param[in] columnMetadata     the column metadata
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     *  @param[in] correlations       the correlation matrix
     *  @param[in] relative           the relative covariance flag (default is true)
     */
    CrossSectionCovarianceMatrix( CrossSectionMetadata rowMetadata,
                                  CrossSectionMetadata columnMetadata,
                                  const std::vector< double >& rowDeviations,
                                  const std::vector< double >& columnDeviations,
                                  matrix::Matrix< double > correlations,
                                  bool relative = true ) :
      Parent( std::move( rowMetadata ), std::move( columnMetadata ),
              rowDeviations, columnDeviations,
              std::move( correlations ), relative ),
      scaling_( std::nullopt ) {}

    /**
     *  @brief Constructor using eigenvalues and eigenvectors for an on-diagonal
     *         cross section covariance matrix
     *
     *  @param[in] metadata       the row and column metadata
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the associated eigenvectors
     *  @param[in] relative       the relative covariance flag
     *  @param[in] scaling        the variance scaling information (default is none)
     */
    CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                                  std::vector< double > eigenvalues,
                                  std::vector< matrix::Vector< double > > eigenvectors,
                                  bool relative = true,
                                  std::optional< VarianceScaling > scaling = std::nullopt ) :
      Parent( std::move( metadata ), std::move( eigenvalues ),
              std::move( eigenvectors ), relative ),
      scaling_( std::move( scaling ) ) {}

    /* methods */

    /**
     *  @brief Return the variance scaling information
     *
     *  If this type of information is given, it will be for an on-diagonal
     *  covariance block.
     */
    const std::optional< VarianceScaling >& varianceScaling() const {

      return this->scaling_;
    }

    /**
     *  @brief Return whether or not the covariance block has variance scaling
     *         information
     */
    bool hasVarianceScaling() const {

      return this->scaling_.has_value();
    }

    using Parent::rowMetadata;
    using Parent::columnMetadata;
    using Parent::isRelativeMatrix;
    using Parent::isAbsoluteMatrix;
    using Parent::isOnDiagonal;
    using Parent::isOffDiagonal;
    using Parent::covariances;
    using Parent::standardDeviations;
    using Parent::correlations;
    using Parent::eigenvalues;
    using Parent::eigenvectors;
    using Parent::eigendata;
    using Parent::calculateCovariances;
    using Parent::calculateStandardDeviations;
    using Parent::calculateCorrelations;
    using Parent::calculateEigenvalues;

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    CrossSectionCovarianceMatrix
    extract( const std::optional< id::ReactionID >& reaction,
             const std::optional< id::EnergyGroup >& group ) const {

      return Parent::extract( reaction, group );
    }

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    CrossSectionCovarianceMatrix
    extract( const std::optional< id::ReactionID >& rowReaction,
             const std::optional< id::EnergyGroup >& rowGroup,
             const std::optional< id::ReactionID >& colReaction,
             const std::optional< id::EnergyGroup >& colGroup ) const {

      return Parent::extract( rowReaction, rowGroup,
                              colReaction, colGroup );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CrossSectionCovarianceMatrix& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionCovarianceMatrix& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
