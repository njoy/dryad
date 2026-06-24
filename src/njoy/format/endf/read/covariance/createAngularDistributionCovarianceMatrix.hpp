#ifndef NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX
#define NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/covariance/createMatrix.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace covariance {

  /**
   *  @brief Create an angular distribution covariance matrix from an ENDF explicit
   *         covariance component
   *
   *  For ENDF angular distribution matrices, only LB = 0, 1, 2, 5 and 6 are allowed.
   *
   *  @param[in] frame            the reference frame
   *  @param[in] rowReaction      the row reaction identifier
   *  @param[in] columnReaction   the column reaction identifier
   *  @param[in] rowMoment        the row Legendre moment
   *  @param[in] columnMoment     the column Legendre moment
   *  @param[in] covariance       the ENDF explicit covariance matrix component
   */
  inline dryad::covariance::AngularDistributionCovarianceMatrix
  createAngularDistributionCovarianceMatrix(
      const dryad::ReferenceFrame& frame,
      const dryad::id::ReactionID& rowReaction,
      const dryad::id::ReactionID& columnReaction,
      std::size_t rowMoment,
      std::size_t columnMoment,
      const ENDFtk::section::ExplicitCovariance& covariance ) {

    using Metadata = dryad::covariance::AngularDistributionMetadata;
    using CovarianceMatrix = dryad::covariance::AngularDistributionCovarianceMatrix;

    bool on_diagonal = ( rowReaction == columnReaction ) && ( rowMoment == columnMoment );
    std::vector< double > rowStructure;
    std::vector< double > columnStructure;
    matrix::Matrix< double > matrix;
    bool relative = true;

    auto type = std::visit( [] ( const auto& component )
                               { return component.procedure(); },
                            covariance );

    switch ( type ) {

      case 0:
      case 1:
      case 2: {

        // LB == 0 is for absolute covariances
        if ( type == 0 ) {

          relative = false;
        }

        // CovariancePairs that represent a matrix
        decltype(auto) block = std::get< ENDFtk::section::CovariancePairs >( covariance );

        rowStructure = createVector( block.firstArrayEnergies() );
        if ( ! on_diagonal ) {

          columnStructure = rowStructure;
        }
        matrix = createMatrix( block );
        break;
      }
      case 5: {

        // SquareMatrix
        decltype(auto) block = std::get< ENDFtk::section::SquareMatrix >( covariance );

        rowStructure = createVector( block.energies() );
        if ( ! on_diagonal ) {

          columnStructure = rowStructure;
        }
        matrix = createMatrix( block );
        break;
      }
      case 6: {

        // RectangularMatrix
        auto block = std::get< ENDFtk::section::RectangularMatrix >( covariance );

        rowStructure = createVector( block.rowEnergies() );
        columnStructure = createVector( block.columnEnergies() );
        on_diagonal = on_diagonal && ( rowStructure == columnStructure );
        matrix = createMatrix( block );
        break;
      }
      default: {

        Log::error( "Unknown or not allowed ENDF covariance component: LB={}", type );
        throw std::exception();
      }
    }

    if ( on_diagonal ) {

      return CovarianceMatrix( std::move( frame ), Metadata( rowReaction, rowMoment, std::move( rowStructure ) ),
                               std::move( matrix ),
                               relative );
    }
    else {

      return CovarianceMatrix( std::move( frame ),
                               Metadata( rowReaction, rowMoment, std::move( rowStructure ) ),
                               Metadata( columnReaction, columnMoment, std::move( columnStructure ) ),
                               std::move( matrix ),
                               relative );
    }
  }

} // covariance namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
