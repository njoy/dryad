#ifndef NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATECrossSectionCovarianceMatrix
#define NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATECrossSectionCovarianceMatrix

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/CrossSectionMetadata.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/covariance/createMatrix.hpp"
#include "njoy/dryad/format/endf/covariance/createVarianceScaling.hpp"
#include "ENDFtk/section/ReactionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create a cross section covariance matrix from an ENDF ReactionBlock
   *         that defines an on-diagonal covariance matrix
   */
  inline dryad::covariance::CrossSectionCovarianceMatrix
  createCrossSectionCovarianceMatrix(
      const dryad::id::ReactionID& reaction,
      const ENDFtk::section::ReactionBlock& block ) {

    if ( block.numberExplicit() == 0 ) {

      Log::error( "No explicit covariance components are defined" );
      throw std::exception();
    }

    auto components = block.explicitCovariances();

    bool relative = true;
    std::vector< std::vector< double > > structures;
    std::vector< matrix::Matrix< double > > matrices;
    std::optional< dryad::covariance::VarianceScaling > scaling = std::nullopt;

    for ( const auto& component : components ) {

      auto type = std::visit( [] ( const auto& component )
                                 { return component.procedure(); },
                              component );

      switch ( type ) {

        case 0:
        case 1:
        case 2:
        case 3:
        case 4: {

          // LB == 0 is for absolute covariances
          if ( type == 0 ) {

            relative = false;
          }

          // CovariancePairs that represent a matrix
          auto block = std::get< ENDFtk::section::CovariancePairs >( component );

          structures.emplace_back( createVector( block.firstArrayEnergies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        case 8:
        case 9: {

          // CovariancePairs that represent a variance scaling

          // there can be only one
          if ( scaling.has_value() ) {

            Log::error( "ENDF reaction covariance block has more than one variance "
                        "scaling component." );
            throw std::exception();
          }

          // read the scalong information
          scaling = createVarianceScaling( std::get< ENDFtk::section::CovariancePairs >( component ) );
          break;
        }
        case 5: {

          // SquareMatrix
          auto block = std::get< ENDFtk::section::SquareMatrix >( component );

          structures.emplace_back( createVector( block.energies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        case 6: {

          // RectangularMatrix
          auto block = std::get< ENDFtk::section::RectangularMatrix >( component );

          structures.emplace_back( createVector( block.rowEnergies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        default: {

          Log::error( "Unknown ENDF covariance component: LB={}, contact a developer", type );
          throw std::exception();
        }
      }
    }

    if ( structures.size() == 1 ) {

      return dryad::covariance::CrossSectionCovarianceMatrix(
                 dryad::covariance::CrossSectionMetadata( { reaction },
                                                          std::move( structures.front() ) ),
                 std::move( matrices.front() ),
                 relative, std::move( scaling ) );
    }
    else {

      Log::error( "Not implemented yet, contact a developer" );
      throw std::exception();
    }
  }

  /**
   *  @brief Create a cross section covariance matrix from an ENDF ReactionBlock
   *         that defines an off-diagonal covariance matrix (a cross term)
   */
  inline dryad::covariance::CrossSectionCovarianceMatrix
  createCrossSectionCovarianceMatrix(
      const dryad::id::ReactionID& rowReaction,
      const dryad::id::ReactionID& columnReaction,
      const ENDFtk::section::ReactionBlock& block ) {

    if ( block.numberExplicit() == 0 ) {

      Log::error( "No explicit covariance components are defined" );
      throw std::exception();
    }

    auto components = block.explicitCovariances();

    bool relative = true;
    std::vector< std::vector< double > > rowStructures;
    std::vector< std::vector< double > > columnStructures;
    std::vector< matrix::Matrix< double > > matrices;

    for ( const auto& component : components ) {

      auto type = std::visit( [] ( const auto& component )
                                 { return component.procedure(); },
                              component );

      switch ( type ) {

        case 0:
        case 1: {

          // LB == 0 is for absolute covariances
          if ( type == 0 ) {

            relative = false;
          }

          // CovariancePairs that represent a matrix
          auto block = std::get< ENDFtk::section::CovariancePairs >( component );

          rowStructures.emplace_back( createVector( block.firstArrayEnergies() ) );
          columnStructures.emplace_back( createVector( block.firstArrayEnergies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        case 2:
        case 3:
        case 4: {

          // CovariancePairs that represent a matrix
          auto block = std::get< ENDFtk::section::CovariancePairs >( component );

          if ( block.numberSecondPairs() == 0 ) {

            rowStructures.emplace_back( createVector( block.firstArrayEnergies() ) );
            columnStructures.emplace_back( createVector( block.firstArrayEnergies() ) );
          }
          else {

            rowStructures.emplace_back( createVector( block.firstArrayEnergies() ) );
            columnStructures.emplace_back( createVector( block.secondArrayEnergies() ) );
          }
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        case 8:
        case 9: {

          Log::error( "Off-diagonal ENDF reaction covariance blocks cannot have "
                      "a variance scaling component." );
          throw std::exception();
        }
        case 5: {

          // SquareMatrix
          auto block = std::get< ENDFtk::section::SquareMatrix >( component );

          rowStructures.emplace_back( createVector( block.energies() ) );
          columnStructures.emplace_back( createVector( block.energies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        case 6: {

          // RectangularMatrix
          auto block = std::get< ENDFtk::section::RectangularMatrix >( component );

          rowStructures.emplace_back( createVector( block.rowEnergies() ) );
          columnStructures.emplace_back( createVector( block.columnEnergies() ) );
          matrices.emplace_back( createMatrix( block ) );
          break;
        }
        default: {

          Log::error( "Unknown ENDF covariance component: LB={}, contact a developer", type );
          throw std::exception();
        }
      }
    }

    if ( rowStructures.size() == 1 ) {

      return dryad::covariance::CrossSectionCovarianceMatrix(
                 dryad::covariance::CrossSectionMetadata( { rowReaction },
                                                          std::move( rowStructures.front() ) ),
                 dryad::covariance::CrossSectionMetadata( { columnReaction },
                                                          std::move( columnStructures.front() ) ),
                 std::move( matrices.front() ), relative );
    }
    else {

      Log::error( "Not implemented yet, contact a developer" );
      throw std::exception();
    }
  }

} // covariance namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
