#ifndef NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATECROSSSECTIONCOVARIANCEBLOCK
#define NJOY_DRYAD_FORMAT_ENDF_COVARIANCE_CREATECROSSSECTIONCOVARIANCEBLOCK

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/std20/algorithm.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/covariance/CrossSectionCovarianceBlock.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/covariance/createMatrix.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create a cross section covariance block from ENDF covariance pair data
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const dryad::id::ReactionID& reaction,
      const ENDFtk::section::CovariancePairs& block ) {

    std::vector< double > structure = createVector( block.firstArrayEnergies() );
    return dryad::covariance::CrossSectionCovarianceBlock(
               projectile, target, reaction, std::move( structure ),
               createMatrix( block ), block.procedure() == 0 ? false : true );
  }

  /**
   *  @brief Create an on-diagonal cross section covariance block from ENDF
   *         square matrix data
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const dryad::id::ReactionID& reaction,
      const ENDFtk::section::SquareMatrix& block ) {

    std::vector< double > structure = createVector( block.energies() );
    return dryad::covariance::CrossSectionCovarianceBlock(
               projectile, target, reaction, std::move( structure ),
               createMatrix( block ), true );
  }

  /**
   *  @brief Create an off-diagonal cross section covariance block from ENDF
   *         square matrix data
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& rowProjectile,
      const dryad::id::ParticleID& rowTarget,
      const dryad::id::ReactionID& rowReaction,
      const dryad::id::ParticleID& columnProjectile,
      const dryad::id::ParticleID& columnTarget,
      const dryad::id::ReactionID& columnReaction,
      const ENDFtk::section::SquareMatrix& block ) {

        std::vector< double > rowStructure = createVector( block.energies() );
        std::vector< double > columnStructure = createVector( block.energies() );
        return dryad::covariance::CrossSectionCovarianceBlock(
               rowProjectile, rowTarget, rowReaction,
               std::move( rowStructure ),
               columnProjectile, columnTarget, columnReaction,
               std::move( columnStructure ),
               createMatrix( block ), true );
  }

  /**
   *  @brief Create an on-diagonal cross section covariance block from ENDF
   *         rectangular matrix data
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const dryad::id::ReactionID& reaction,
      const ENDFtk::section::RectangularMatrix& block ) {

    if ( block.numberRowEnergies() == block.numberColumnEnergies() ) {

      if ( njoy::tools::std20::equal( block.rowEnergies(), block.columnEnergies() ) ) {

        std::vector< double > structure = createVector( block.rowEnergies() );
        return dryad::covariance::CrossSectionCovarianceBlock(
                   projectile, target, reaction, std::move( structure ),
                   createMatrix( block ), true );
      }
    }

    Log::error( "The covariance matrix provided by an ENDF rectangular matrix (LB=6) "
                "is not a square matrix for an on-diagonal covariance block" );
    throw std::exception();
  }

  /**
   *  @brief Create an off-diagonal cross section covariance block from ENDF
   *         square matrix data
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& rowProjectile,
      const dryad::id::ParticleID& rowTarget,
      const dryad::id::ReactionID& rowReaction,
      const dryad::id::ParticleID& columnProjectile,
      const dryad::id::ParticleID& columnTarget,
      const dryad::id::ReactionID& columnReaction,
      const ENDFtk::section::RectangularMatrix& block ) {

        std::vector< double > rowStructure = createVector( block.rowEnergies() );
        std::vector< double > columnStructure = createVector( block.columnEnergies() );
        return dryad::covariance::CrossSectionCovarianceBlock(
               rowProjectile, rowTarget, rowReaction,
               std::move( rowStructure ),
               columnProjectile, columnTarget, columnReaction,
               std::move( columnStructure ),
               createMatrix( block ), true );
  }

} // covariance namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
