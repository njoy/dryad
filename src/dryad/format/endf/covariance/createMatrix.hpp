#ifndef NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATEMATRIX
#define NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATEMATRIX

// system includes

// other includes
#include "ENDFtk/section/CovariancePairs.hpp"
#include "ENDFtk/section/SquareMatrix.hpp"
#include "ENDFtk/section/RectangularMatrix.hpp"
#include "dryad/covariance/matrix.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create matrix data from an ENDF covariance pair component
   *
   *  This interprets the data based on the LB flag and returns a full
   *  covariance matrix. Depending on the LB flag, this can be a square
   *  or rectangular matrix and be relative or absolute covariances.
   */
  dryad::covariance::Matrix< double >
  createMatrix( const ENDFtk::section::CovariancePairs& endf ) {

    switch ( endf.procedure() ) {

      case 0 :
      case 1 : {

        // square matrix, only diagonal elements are given
        // either relative or absolute covariances
        // only one E,F array (LT=0)

        unsigned int size = endf.numberPairs() - 1;
        dryad::covariance::Matrix< double > matrix( size, size );
        for ( unsigned int i = 0; i < size; ++i ) {

          matrix( i, i ) = endf.firstArrayFValues()[i];
          for ( unsigned int j = i + 1; j < size; ++j ) {

            matrix( i, j ) = 0.;
            matrix( j, i ) = 0.;
          }
        }
        return matrix;
      }
      case 2 : {

        // square matrix
        // relative covariances
        // only one E,F array (LT=0)

        unsigned int size = endf.numberPairs() - 1;
        dryad::covariance::Matrix< double > matrix( size, size );
        for ( unsigned int i = 0; i < size; ++i ) {

          for ( unsigned int j = 0; j < size; ++j ) {

            matrix( i, j ) = endf.firstArrayFValues()[i] * endf.firstArrayFValues()[j];
          }
        }
        return matrix;
      }
      case 3 : {

        // rectangular matrix
        // relative covariances
        // two E,F arrays (LT=1)

        unsigned int size1 = endf.numberPairs() - 1;
        unsigned int size2 = endf.numberSecondPairs() - 1;
        dryad::covariance::Matrix< double > matrix( size1, size2 );
        for ( unsigned int i = 0; i < size1; ++i ) {

          for ( unsigned int j = 0; j < size2; ++j ) {

            matrix( i, j ) = endf.firstArrayFValues()[i] * endf.secondArrayFValues()[j];
          }
        }
        return matrix;
      }
      case 4 : {

        // square matrix
        // relative covariances
        // two E,F arrays (LT=1)

        unsigned int size = endf.numberPairs() - 1;
        dryad::covariance::Matrix< double > matrix( size, size );
        for ( unsigned int i = 0; i < size; ++i ) {

          for ( unsigned int j = 0; j < size; ++j ) {

            matrix( i, j ) = endf.firstArrayFValues()[i] * endf.secondArrayFValues()[i]
                           * endf.secondArrayFValues()[j];
          }
        }
        return matrix;
      }
      case 8 :
      case 9 : {

        Log::error( "ENDF covariance components with LB={} represent variance scaling, "
                    "and do not represent a covariance matrix" );
        throw std::exception();
      }
      default : {

        // unreachable code
        throw std::runtime_error( "how did you get here?, contact a developer" );
      }
    }
  }

  /**
   *  @brief Create matrix data from an ENDF square matrix component
   *
   *  This interprets the data based on the LS flag and returns a full
   *  covariance matrix.
   */
  dryad::covariance::Matrix< double >
  createMatrix( const ENDFtk::section::SquareMatrix& endf ) {

    unsigned int size = endf.numberEnergies() - 1;
    dryad::covariance::Matrix< double > matrix( size, size );
    unsigned int index = 0;
    if ( endf.isSymmetric() ) {

      for ( unsigned int i = 0; i < size; ++i ) {

        for ( unsigned int j = i; j < size; ++j ) {

          matrix( i, j ) = endf.values()[ index++ ];
          if ( i != j ) {

            matrix( j, i ) = matrix( i, j );
          }
        }
      }
    }
    else {

      for ( unsigned int i = 0; i < size; ++i ) {

        for ( unsigned int j = 0; j < size; ++j ) {

          matrix( i, j ) = endf.values()[ index++ ];
        }
      }
    }
    return matrix;
  }

  /**
   *  @brief Create matrix data from an ENDF rectangular matrix component
   */
  dryad::covariance::Matrix< double >
  createMatrix( const ENDFtk::section::RectangularMatrix& endf ) {

    unsigned int rows = endf.numberRowEnergies() - 1;
    unsigned int columns = endf.numberColumnEnergies() - 1;
    dryad::covariance::Matrix< double > matrix( rows, columns );

    unsigned int index = 0;
    for ( unsigned int i = 0; i < rows; ++i ) {

      for ( unsigned int j = 0; j < columns; ++j ) {

        matrix( i, j ) = endf.values()[ index++ ];
      }
    }

    return matrix;
  }

} // covariance namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
