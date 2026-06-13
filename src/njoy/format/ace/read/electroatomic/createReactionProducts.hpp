#ifndef NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEREACTIONPRODUCTS
#define NJOY_FORMAT_ACE_READ_ELECTROATOMIC_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReactionProduct.hpp"
#include "njoy/format/ace/read/createTabulatedAverageEnergy.hpp"
#include "njoy/format/ace/read/createTabulatedAngularDistributions.hpp"
#include "njoy/format/ace/read/createTabulatedEnergyDistributions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace electroatomic {

  /**
   *  @brief Create reaction products for electroatomic data
   *
   *  @param[in] table   the ace table
   */
  inline std::vector< std::vector< dryad::ReactionProduct > >
  createReactionProducts( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< dryad::ReactionProduct > > products;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      products.push_back( {} );

      // ionisation - MT522
      products.push_back( {} );

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        products.push_back( {} );
        products.back().emplace_back(
          dryad::id::ParticleID::electron(), 1,
          dryad::TwoBodyDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                          createTabulatedAngularDistributions(
                                              table.electronElasticAngularDistributionBlock().value() ) ) );

        // total elastic - MT526
        products.push_back( {} );
      }
      else {

        // total elastic - MT526
        products.push_back( {} );
        products.back().emplace_back(
          dryad::id::ParticleID::electron(), 1,
          dryad::TwoBodyDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                          createTabulatedAngularDistributions(
                                              table.electronElasticAngularDistributionBlock().value() ) ) );
      }

      // bremsstrahlung - MT527
      products.push_back( {} );
      products.back().emplace_back(
        dryad::id::ParticleID::photon(), 1,
        dryad::UncorrelatedDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                             dryad::IsotropicAngularDistributions(),
                                             createTabulatedEnergyDistributions(
                                               table.bremsstrahlungEnergyDistributionBlock().value() ) ) );
      products.back().emplace_back(
        dryad::id::ParticleID::electron(), 1,
        createTabulatedAverageEnergy( table.electronEnergyAfterBremsstrahlungBlock().value() ) );

      // excitation - MT528
      products.push_back( {} );
      products.back().emplace_back(
        dryad::id::ParticleID::electron(), 1,
        createTabulatedAverageEnergy( table.electronExcitationEnergyLossBlock().value() ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        products.push_back( {} );
        products.back().emplace_back(
          dryad::id::ParticleID::electron(), 1,
          dryad::UncorrelatedDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                               dryad::IsotropicAngularDistributions(),
                                               createTabulatedEnergyDistributions(
                                                 table.electroionisationEnergyDistributionBlock( index ) ) ) );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        products.push_back( {} );
      }
    }

    return products;
  }

} // electroatomic namespace
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
