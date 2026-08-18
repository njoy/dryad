#ifndef NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX
#define NJOY_DRYAD_COVARIANCE_BASE_COVARIANCEMATRIX

// system includes
#include <algorithm>
#include <optional>
#include <numeric>
#include <vector>

// other includes
#include "scion/math/compare.hpp"
#include "tools/Log.hpp"
#include "tools/apply_permutation.hpp"
#include "njoy/matrix.hpp"

namespace njoy {
namespace dryad {
namespace covariance {
namespace base {

  /**
   *  @class
   *  @brief A base class representing a covariance matrix
   *
   *  For on-diagonal covariance matrice, the following data is always available
   *  (regardless of how the covariance matrix instance was constructed):
   *  - the covariance matrix
   *  - the standard deviations and correlation matrix
   *  - the eigenvalues and eigenvectors
   *
   *  Eigenvalues (and assocaited eigenvectors) are store in descending order.
   */
  template < typename Metadata, typename... Ts >
  class CovarianceMatrix {

    /* type aliases */
    using Key = std::tuple< Ts... >;
    using Selection = std::tuple< std::optional< Ts >... >;

    using Eigenvalues = std::optional< std::vector< double > >;
    using Eigenvectors = std::optional< std::vector< matrix::Vector< double > > >;
    using Eigendata = std::tuple< Eigenvalues, Eigenvectors >;

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

    /* fields - eigenvalues and eigenvectors */
    Eigendata eigendata_;

    /* auxiliary function */

    static void verifyMatrix( const matrix::Matrix< double >& matrix,
                              unsigned int order ) {

      // check if the matrix is square
      if ( ! matrix::isSquare( matrix ) ) {

        Log::error( "The matrix for a diagonal block must be square" );
        throw std::exception();
      }

      // check if the matrix is symmetric
      if ( ! matrix::isSymmetric( matrix ) ) {

        Log::error( "The matrix for a diagonal block must be symmetric" );
        throw std::exception();
      }

      // check if the order of the square matrix is consistent with the
      // order obtained from the structure
      if ( matrix.rows() != order ) {

        Log::error( "The order of the square matrix and the order from the structure are not consistent" );
        Log::info( "Number rows: {}", matrix.rows() );
        Log::info( "Number columns: {}", matrix.cols() );
        Log::info( "Expected order: {}", order );
        throw std::exception();
      }
    }

    static void verifyMatrix( const std::vector< double >& deviations,
                              const matrix::Matrix< double >& matrix,
                              unsigned int order ) {

      verifyMatrix( matrix, order );

      // check if the number of deviation values is consistent with the
      // order obtained from the structure
      if ( deviations.size() != order ) {

        Log::error( "The number of standard deviation values and the order from the "
                    "structure are not consistent" );
        Log::info( "Number standard deviation values: {}", deviations.size() );
        Log::info( "Expected order: {}", order );
        throw std::exception();
      }
    }

    static void verifyMatrix( const matrix::Matrix< double >& matrix,
                              unsigned int rows,
                              unsigned int columns ) {

      // check if the matrix dimensions are consistent with the structure
      if ( ( matrix.rows() != rows ) ||
           ( matrix.cols() != columns ) ) {

        Log::error( "The matrix dimensions and the structure are not consistent" );
        Log::info( "Number rows: {}", matrix.rows() );
        Log::info( "Number columns: {}", matrix.cols() );
        Log::info( "Expected number of rows: {}", rows );
        Log::info( "Expected number of columns: {}", columns );
        throw std::exception();
      }
    }

    static void verifyMatrix( const std::vector< double >& eigenvalues,
                              const std::vector< matrix::Vector< double > >& eigenvectors,
                              unsigned int order ) {

      // check if the number of eigenvalues is non-zero
      if ( eigenvalues.size() == 0 ) {

        Log::error( "The number of eigenvalues cannot be zero" );
        Log::info( "Number eigenvalues: {}", eigenvalues.size() );
        Log::info( "Number eigenvectors: {}", eigenvectors.size() );
        throw std::exception();
      }

      // check if the number of eigenvalues and eigenvectors are consistent
      if ( eigenvalues.size() != eigenvectors.size() ) {

        Log::error( "The number of eigenvalues and eigenvectors are not consistent" );
        Log::info( "Number eigenvalues: {}", eigenvalues.size() );
        Log::info( "Number eigenvectors: {}", eigenvectors.size() );
        throw std::exception();
      }

      // check if the order is consistent with the size of the eigenvectors
      for ( std::size_t i = 0; i < eigenvectors.size(); ++i ) {

        if ( eigenvectors[i].rows() != order ) {

          Log::error( "The order of the eigenvector with index {} and the order from the structure are not consistent", i );
          Log::info( "Number rows: {}", eigenvectors[i].rows() );
          Log::info( "Expected order: {}", order );
          throw std::exception();
        }
      }
    }

    static void verifyStandardDeviations( std::size_t rows,
                                          std::size_t columns,
                                          std::size_t rowDeviations,
                                          std::size_t columnDeviations ) {

      if ( ( rowDeviations != rows ) || ( columnDeviations != columns ) ) {

        Log::error( "The provided number of standard deviations and the covariance "
                    "matrix size are not consistent" );
        Log::info( "Covariance matrix number rows: {}", rows );
        Log::info( "Covariance matrix number columns: {}", columns );
        Log::info( "Number row standard deviations: {}", rowDeviations );
        Log::info( "Number column standard deviations: {}", columnDeviations );
        throw std::exception();
      }
    }

    /**
     *  @brief Sort the eigenvalues in descending order
     */
    void sortEigenvalues() {

      if ( this->eigenvalues().has_value() ) {

        // get the order (eigenvalues are in descending order)
        std::vector< std::size_t > order( this->eigenvalues()->size() );
        std::iota( order.begin(), order.end(), 0 );
        std::sort( order.begin(), order.end(),
                   [&] ( auto&& i, auto&& j ) {

                     return this->eigenvalues().value()[i] > this->eigenvalues().value()[j];
                   } );

        // sort the eigenvalues (descending order) and perform a permutation on the eigenvectors
        std::sort( this->eigenvalues()->rbegin(), this->eigenvalues()->rend() );
        tools::apply_permutation( this->eigenvectors().value(), order );
      }
    }

  public:

    /* constructor */

    //! @todo the keys are currently required in the ctors. they can be removed
    //!       when we are capable of using cartesian_product

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CovarianceMatrix() = default;

    CovarianceMatrix( const CovarianceMatrix& ) = default;
    CovarianceMatrix( CovarianceMatrix&& ) = default;

    CovarianceMatrix& operator=( const CovarianceMatrix& ) = default;
    CovarianceMatrix& operator=( CovarianceMatrix&& ) = default;

    /**
     *  @brief Constructor for an on-diagonal covariance matrix (relative or absolute)
     *
     *  @param[in] metadata      the metadata
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag
     */
    CovarianceMatrix( Metadata metadata,
                      matrix::Matrix< double > covariances,
                      bool relative = true ) :
        row_metadata_( std::move( metadata ) ),
        column_metadata_( std::nullopt ),
        relative_( relative ),
        covariances_( std::move( covariances ) ),
        sigmas_( std::nullopt ),
        correlations_( std::nullopt ) {

      verifyMatrix( this->covariances(), this->rowMetadata().keys().size() );
      this->calculateCorrelations();
      this->calculateEigenvalues();
    }

    /**
     *  @brief Constructor for an on-diagonal correlation matrix (relative or absolute)
     *
     *  @param[in] metadata       the metadata from which the keys are derived
     *  @param[in] deviations     the standard deviations
     *  @param[in] correlations   the correlation matrix
     *  @param[in] relative       the relative covariance flag
     */
    CovarianceMatrix( Metadata metadata,
                      std::vector< double > deviations,
                      matrix::Matrix< double > correlations,
                      bool relative = true ) :
        row_metadata_( std::move( metadata ) ),
        column_metadata_( std::nullopt ),
        relative_( relative ),
        sigmas_( std::move( deviations ) ),
        correlations_( std::move( correlations ) ) {

      verifyMatrix( this->standardDeviations().value(),
                    this->correlations().value(),
                    this->rowMetadata().keys().size() );
      this->calculateCovariances();
      this->calculateEigenvalues();
    }

    /**
     *  @brief Constructor using eigenvalues and eigenvectors (relative or absolute)
     *
     *  @param[in] metadata       the metadata from which the keys are derived
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the associated eigenvalues
     *  @param[in] relative       the relative covariance flag
     */
    CovarianceMatrix( Metadata metadata,
                      std::vector< double > eigenvalues,
                      std::vector< matrix::Vector< double > > eigenvectors,
                      bool relative = true ) :
        row_metadata_( std::move( metadata ) ),
        column_metadata_( std::nullopt ),
        relative_( relative ),
        eigendata_( std::make_tuple( std::move( eigenvalues ), std::move( eigenvectors ) ) ) {

      this->sortEigenvalues();
      verifyMatrix( this->eigenvalues().value(),
                    this->eigenvectors().value(),
                    this->rowMetadata().keys().size() );
      this->calculateCovariances();
      this->calculateCorrelations();
    }

    /**
     *  @brief Constructor for an off-diagonal covariance matrix (relative or absolute)
     *
     *  @param[in] rowKeys       the row keys
     *  @param[in] columnKeys    the column keys
     *  @param[in] covariances   the covariance matrix
     *  @param[in] relative      the relative covariance flag
     */
    CovarianceMatrix( Metadata rowMetadata,
                      Metadata columnMetadata,
                      matrix::Matrix< double > covariances,
                      bool relative = true ) :
        row_metadata_( std::move( rowMetadata ) ),
        column_metadata_( std::move( columnMetadata ) ),
        relative_( relative ),
        covariances_( std::move( covariances ) ),
        sigmas_( std::nullopt ),
        correlations_( std::nullopt ) {

      verifyMatrix( this->covariances(),
                    this->rowMetadata().keys().size(),
                    this->columnMetadata().keys().size() );
    }

    /**
     *  @brief Constructor for an off-diagonal correlation matrix (relative or absolute)
     *
     *  The standard deviations are not stored for off-diagonal data.
     *
     *  @param[in] rowKeys            the row keys
     *  @param[in] columnKeys         the column keys
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     *  @param[in] correlations       the correlation matrix
     *  @param[in] relative           the relative covariance flag
     */
    CovarianceMatrix( Metadata rowMetadata,
                      Metadata columnMetadata,
                      const std::vector< double >& rowDeviations,
                      const std::vector< double >& columnDeviations,
                      matrix::Matrix< double > correlations,
                      bool relative = true ) :
        row_metadata_( std::move( rowMetadata ) ),
        column_metadata_( std::move( columnMetadata ) ),
        relative_( relative ),
        sigmas_( std::nullopt ),
        correlations_( std::move( correlations ) ) {

      verifyMatrix( this->correlations().value(),
                    this->rowMetadata().keys().size(),
                    this->columnMetadata().keys().size() );
      this->calculateCovariances( rowDeviations, columnDeviations );
    }

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
     *  @brief Return the covariance matrix
     */
    matrix::Matrix< double >& covariances() {

      return this->covariances_;
    }

    /**
     *  @brief Set the covariance matrix
     *
     *  @param[in] covariances   the covariance matrix
     */
    void covariances( matrix::Matrix< double > covariances ) {

      this->covariances_ = std::move( covariances );
      if ( this->isOnDiagonal() ) {

        verifyMatrix( this->covariances(), this->rowMetadata().keys().size() );
        this->calculateCorrelations();
        this->calculateEigenvalues();
      }
      else {

        verifyMatrix( this->covariances(), this->rowMetadata().keys().size(),
                      this->columnMetadata().keys().size() );
        this->correlations( std::nullopt );
      }
    }

    /**
     *  @brief Return the standard deviations
     */
    const std::optional< std::vector< double > >& standardDeviations() const {

      return this->sigmas_;
    }

    /**
     *  @brief Return the standard deviations
     */
    std::optional< std::vector< double > >& standardDeviations() {

      return this->sigmas_;
    }

    /**
     *  @brief Set the standard deviations
     *
     *  @param[in] deviations   the standard deviations
     */
    void standardDeviations( std::optional< std::vector< double > > deviations ) {

      if ( this->isOnDiagonal() ) {

        this->sigmas_ = std::move( deviations );
        if ( this->standardDeviations().has_value() ) {

          verifyMatrix( this->standardDeviations().value(),
                        this->correlations().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateEigenvalues();
        }
      }
      else {

        throw std::runtime_error( "Standard deviations cannot be set for an off-diagonal covariance matrix" );
      }
    }

    /**
     *  @brief Return the correlation matrix
     */
    const std::optional< matrix::Matrix< double > >& correlations() const {

      return this->correlations_;
    }

    /**
     *  @brief Return the correlation matrix
     */
    std::optional< matrix::Matrix< double > >& correlations() {

      return this->correlations_;
    }

    /**
     *  @brief Set the correlation matrix
     *
     *  @param[in] correlations   the correlation matrix
     */
    void correlations( std::optional< matrix::Matrix< double > > correlations ) {

      if ( this->isOnDiagonal() ) {

        this->correlations_ = std::move( correlations );
        if ( this->correlations().has_value() ) {


          verifyMatrix( this->standardDeviations().value(),
                        this->correlations().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateEigenvalues();
        }
      }
      else {

        throw std::runtime_error( "Correlations cannot be set for an off-diagonal covariance matrix "
                                  "without specifying row and column deviations" );
      }
    }

    /**
     *  @brief Return the eigenvalues
     */
    const std::optional< std::vector< double > >& eigenvalues() const {

      return std::get< 0 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvalues
     */
    std::optional< std::vector< double > >& eigenvalues() {

      return std::get< 0 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvectors
     */
    const std::optional< std::vector< matrix::Vector< double > > >& eigenvectors() const {

      return std::get< 1 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvectors
     */
    std::optional< std::vector< matrix::Vector< double > > >& eigenvectors() {

      return std::get< 1 >( this->eigendata_ );
    }

    /**
     *  @brief Return the eigenvalues and eigenvectors
     */
    const Eigendata& eigendata() const {

      return this->eigendata_;
    }

    /**
     *  @brief Return the eigenvalues and eigenvectors
     */
    Eigendata& eigendata() {

      return this->eigendata_;
    }

    /**
     *  @brief Set the eigenvalues and eigenvectors
     *
     *  @param[in] eigenvalues    the eigenvalues
     *  @param[in] eigenvectors   the eigenvectors
     */
    void eigendata( Eigendata eigendata ) {

      if ( this->isOnDiagonal() ) {

        this->eigendata_ = std::move( eigendata );
        if ( this->eigenvalues().has_value() && this->eigenvectors().has_value() ) {

          this->sortEigenvalues();
          verifyMatrix( this->eigenvalues().value(),
                        this->eigenvectors().value(),
                        this->rowMetadata().keys().size() );
          this->calculateCovariances();
          this->calculateCorrelations();
        }
      }
      else {

        throw std::runtime_error( "Eigenvalues and eigenvectors cannot be set for an off-diagonal "
                                  "covariance matrix" );
      }
    }

    /**
     *  @brief Calculate the covariances (for on diagonal blocks)
     *
     *  The covariances can be calculated without input of the standard
     *  deviations for blocks on the diagonal of the matrix.
     *
     *  When this method is called on an off diagonal block, the method has no effect.
     *
     *  When this method is called on a block that has no correlations, the method
     *  has no effect.
     */
    void calculateCovariances() {

      if ( this->isOnDiagonal() ) {

        if ( this->correlations().has_value() ) {

          auto nrows = this->rowMetadata().keys().size();
          matrix::DiagonalMatrix< double > temporary( nrows );
          temporary.setIdentity();
          for ( unsigned int i = 0; i < nrows; ++i ) {

            temporary.diagonal()[i] = this->standardDeviations().value()[i];
          }

          this->covariances_ = temporary * this->correlations().value() * temporary;
        }
        else if ( this->eigenvalues().has_value() && this->eigenvectors().has_value() ) {

          auto nrows = this->rowMetadata().keys().size();
          auto ncols = this->eigenvalues().value().size();
          matrix::Matrix< double > matrix( nrows, ncols );
          matrix::DiagonalMatrix< double > lambda( ncols );

          for ( unsigned int i = 0; i < ncols; ++i ) {

            lambda.diagonal()[i] = this->eigenvalues().value()[i];
            matrix.col(i) = this->eigenvectors().value()[i];
          }

          this->covariances_ = matrix * lambda * matrix.transpose();
        }
      }
    }

    /**
     *  @brief Calculate the covariances (for off diagonal blocks)
     *
     *  The covariances can only be calculated with input of the standard deviations
     *  for blocks that are off diagonal in the matrix. Standard deviations will not
     *  be stored.
     *
     *  When this method is called on a block that has no correlations, the method
     *  has no effect.
     *
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     */
    void calculateCovariances( const std::vector< double >& rowDeviations,
                               const std::vector< double >& columnDeviations ) {

      if ( this->correlations().has_value() ) {

        auto nrows = this->rowMetadata().keys().size();
        auto ncols = this->columnMetadata().keys().size();

        verifyStandardDeviations( nrows,
                                  ncols,
                                  rowDeviations.size(),
                                  columnDeviations.size() );

        matrix::DiagonalMatrix< double > left( nrows );
        left.setIdentity();
        for ( unsigned int i = 0; i < nrows; ++i ) {

          left.diagonal()[i] = rowDeviations[i];
        }

        matrix::DiagonalMatrix< double > right( ncols );
        right.setIdentity();
        for ( unsigned int i = 0; i < ncols; ++i ) {

          right.diagonal()[i] = columnDeviations[i];
        }

        this->covariances_ = left * this->correlations().value() * right;
      }
    }

    /**
     *  @brief Calculate the standard deviations from the covariances
     *
     *  The standard deviations can only be calculated from covariance matrices on the
     *  diagonal of the full covariance matrix. When this function is called on an
     *  off diagonal matrix, the function has no effect.
     */
    void calculateStandardDeviations() {

      if ( this->isOnDiagonal() ) {

        std::vector< double > sigmas;
        sigmas.reserve( this->rowMetadata().keys().size() );

        for ( const auto& value : this->covariances().diagonal().reshaped() ) {

          sigmas.emplace_back( std::sqrt( value ) );
        }

        this->sigmas_ = sigmas;
      }
    }

    /**
     *  @brief Calculate the correlations (for on diagonal matrices)
     *
     *  The correlations can be calculated without input of the standard
     *  deviations for matrices on the diagonal of the full matrix. Standard
     *  deviations will be calculated and stored as well.
     *
     *  When a diagonal correlation value is equal to one within 10 times epsilon,
     *  the diagonal correlation value will get set to one exactly.
     *
     *  When this method is called on an off diagonal matrix, the method has
     *  no effect.
     */
    void calculateCorrelations() {

      if ( this->isOnDiagonal() ) {

        this->calculateStandardDeviations();

        auto nrows = this->rowMetadata().keys().size();
        matrix::DiagonalMatrix< double > temporary( nrows );
        temporary.setIdentity();
        for ( unsigned int i = 0; i < nrows; ++i ) {

          temporary.diagonal()[i] /= this->standardDeviations().value()[i];
          if ( std::isnan( temporary.diagonal()[i] ) ) {

            temporary.diagonal()[i] = 0;
          }
        }

        matrix::Matrix< double > correlations = temporary * this->covariances() * temporary;
        for ( unsigned int i = 0; i < nrows; ++i ) {

          for ( unsigned int j = i + 1; j < nrows; ++j ) {

            if ( scion::math::isClose( 1., correlations(i,j), 10. * std::numeric_limits< double >::epsilon() ) ) {

              correlations(i,j) = 1.;
              correlations(j,i) = 1.;
            }
            else if ( scion::math::isClose( -1., correlations(i,j), 10. * std::numeric_limits< double >::epsilon() ) ) {

              correlations(i,j) = -1.;
              correlations(j,i) = -1.;
            }
          }
          correlations(i,i) = 1.;
        }

        this->correlations_ = std::move( correlations );
      }
    }

    /**
     *  @brief Calculate the correlations (for off diagonal matrices)
     *
     *  The correlations can only be calculated with input of the standard deviations
     *  for covariance matrices that are off diagonal in the full covariance matrix.
     *  Standard deviations will not be stored.
     *
     *  @param[in] rowDeviations      the standard deviations to be applied to each row
     *  @param[in] columnDeviations   the standard deviations to be applied to each column
     */
    void calculateCorrelations( const std::vector< double >& rowDeviations,
                                const std::vector< double >& columnDeviations ) {

      auto nrows = this->rowMetadata().keys().size();
      auto ncols = this->columnMetadata().keys().size();

      verifyStandardDeviations( nrows,
                                ncols,
                                rowDeviations.size(),
                                columnDeviations.size() );

      matrix::DiagonalMatrix< double > left( nrows );
      left.setIdentity();
      for ( unsigned int i = 0; i < nrows; ++i ) {

        left.diagonal()[i] /= rowDeviations[i];
        if ( std::isnan( left.diagonal()[i] ) ) {

          left.diagonal()[i] = 0;
        }
      }

      matrix::DiagonalMatrix< double > right( ncols );
      right.setIdentity();
      for ( unsigned int i = 0; i < ncols; ++i ) {

        right.diagonal()[i] /= columnDeviations[i];
        if ( std::isnan( right.diagonal()[i] ) ) {

          right.diagonal()[i] = 0;
        }
      }

      matrix::Matrix< double > correlations = left * this->covariances() * right;
      for ( unsigned int i = 0; i < nrows; ++i ) {

        for ( unsigned int j = 0; j < ncols; ++j ) {

          if ( scion::math::isClose( 1., correlations(i,j), 10. * std::numeric_limits< double >::epsilon() ) ) {

            correlations(i,j) = 1.;
          }
          else if ( scion::math::isClose( -1., correlations(i,j), 10. * std::numeric_limits< double >::epsilon() ) ) {

            correlations(i,j) = -1.;
          }
        }
      }

      this->correlations_ = std::move( correlations );
    }

    /**
     *  @brief Calculate the eigenvalues and eigenvectors from the covariances
     *
     *  The eigenvalues and eigenvectors can only be calculated from matrices on the
     *  diagonal of the full matrix. When this function is called on an off diagonal
     *  matrix, the function has no effect.
     *
     *  When the absolute value of an eigenvalue is equal to zero within 10 times epsilon,
     *  the eigenvalue will get set to zero exactly.
     */
    void calculateEigenvalues() {

      if ( this->isOnDiagonal() ) {

        // the SelfAdjointEigenSolver exploits the symmetric features of the matrix
        // eigenvalues are returned in ascending order
        Eigen::SelfAdjointEigenSolver< matrix::Matrix< double > > solver( this->covariances() );

        // create a vector for eigenvalues and eigenvectors
        std::size_t size = this->rowMetadata().keys().size();
        std::vector< double > eigenvalues;
        std::vector< matrix::Vector< double > > eigenvectors;
        eigenvalues.reserve( size );
        eigenvectors.reserve( size );

        // loop over the eigenvalues and eigenvectors
        for ( std::size_t i = 0; i < size; ++i ) {

          double eigenvalue = solver.eigenvalues()(i);
          if ( scion::math::isCloseToZero( eigenvalue, 10. * std::numeric_limits< double >::epsilon() ) ) {

            eigenvalue = 0.;
          }
          eigenvalues.emplace_back( eigenvalue );

          matrix::Vector< double > eigenvector = solver.eigenvectors().col(i);
          eigenvectors.emplace_back( eigenvector );
        }

        // reverse the order (eigenvalues are stored in descending order)
        std::reverse( eigenvalues.begin(), eigenvalues.end() );
        std::reverse( eigenvectors.begin(), eigenvectors.end() );

        //! @todo check efficiency compared to using std::upper_bound

        // move the vectors into the fields
        this->eigenvalues() = std::move( eigenvalues );
        this->eigenvectors() = std::move( eigenvectors );
      }
    }

    private:

    static std::vector< Key >
    extractKeys( const std::vector< std::size_t >& indices,
                 const std::vector< Key >& keys ) {

      std::vector< Key > extracted;
      extracted.reserve( indices.size() );
      for ( std::size_t index : indices ) {

        extracted.emplace_back( keys[index] );
      }
      return extracted;
    }

    matrix::Matrix< double >
    extractMatrix( const std::vector< std::size_t >& rows,
                   const std::vector< std::size_t >& columns ) const {

      auto size1 = rows.size();
      auto size2 = columns.size();
      matrix::Matrix< double > matrix( size1, size2 );
      for ( unsigned int i = 0; i < size1; ++i ) {

        for ( unsigned int j = 0; j < size2; ++j ) {

          matrix( i, j ) = this->covariances()( rows[i], columns[j] );
        }
      }
      return matrix;
    }

    public:

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    CovarianceMatrix extract( const std::optional< Ts >&... args ) const {

      auto rows = this->rowMetadata().selection( args... );
      auto rowKeys = extractKeys( rows, this->rowMetadata().keys() );
      if ( this->isOnDiagonal() ) {

        return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                                 this->extractMatrix( rows, rows ),
                                 this->isRelativeMatrix() );
      }
      else {

        auto columns = this->columnMetadata().selection( args... );
        auto columnKeys = extractKeys( columns, this->columnMetadata().keys() );
        if ( rowKeys == columnKeys ) {

          return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                                   this->extractMatrix( rows, columns ),
                                   this->isRelativeMatrix() );
        }
        else {

          return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                                   Metadata( std::move( columnKeys ) ),
                                   this->extractMatrix( rows, columns ),
                                   this->isRelativeMatrix() );
        }
      }
    }

    /**
     *  @brief Extract a submatrix from the covariance matrix based
     *         on selected values of the keys
     */
    CovarianceMatrix extract( const std::optional< Ts >&... row_args,
                              const std::optional< Ts >&... col_args ) const {

      if ( std::tie( row_args... ) == std::tie( col_args... ) ) {

        return this->extract( row_args... );
      }
      else {

        auto rows = this->rowMetadata().selection( row_args... );
        auto columns = this->columnMetadata().selection( col_args... );
        auto rowKeys = extractKeys( rows, this->rowMetadata().keys() );
        auto columnKeys = extractKeys( columns, this->columnMetadata().keys() );

        if ( rowKeys == columnKeys ) {

          return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                                   this->extractMatrix( rows, columns ),
                                   this->isRelativeMatrix() );
        }
        else {

          return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                                   Metadata( std::move( columnKeys ) ),
                                   this->extractMatrix( rows, columns ),
                                   this->isRelativeMatrix() );
        }
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CovarianceMatrix& right ) const {

      return std::tie( this->rowMetadata(), this->columnMetadata(), this->covariances(),
                       this->standardDeviations(), this->correlations(),
                       this->eigenvalues(), this->eigenvectors() ) ==
             std::tie( right.rowMetadata(), right.columnMetadata(), right.covariances(),
                       right.standardDeviations(), right.correlations(),
                       right.eigenvalues(), right.eigenvectors() );
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
