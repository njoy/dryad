#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ReactionProduct.hpp"
#include "dryad/format/ace/createTabulatedAverageEnergy.hpp"
#include "dryad/format/ace/createTabulatedAngularDistributions.hpp"
#include "dryad/format/ace/createTabulatedEnergyDistributions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create reaction products for electroatomic data
   *
   *  @param[in] table   the ace table
   */
  std::vector< std::vector< ReactionProduct > >
  createReactionProducts( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< ReactionProduct > > products;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      products.push_back( {} );

      // ionisation - MT522
      products.push_back( {} );

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        products.push_back( {} );
        products.back().emplace_back(
          id::ParticleID( "e-" ), 1,
          TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                   createTabulatedAngularDistributions(
                                       table.electronElasticAngularDistributionBlock().value() ) ) );

        // total elastic - MT526
        products.push_back( {} );
      }
      else {

        // total elastic - MT526
        products.push_back( {} );
        products.back().emplace_back(
          id::ParticleID( "e-" ), 1,
          TwoBodyDistributionData( ReferenceFrame::CentreOfMass,
                                   createTabulatedAngularDistributions(
                                       table.electronElasticAngularDistributionBlock().value() ) ) );
      }

      // bremsstrahlung - MT527
      products.push_back( {} );
      products.back().emplace_back(
        id::ParticleID( "g" ), 1,
        UncorrelatedDistributionData( ReferenceFrame::CentreOfMass,
                                      IsotropicAngularDistributions(),
                                      createTabulatedEnergyDistributions(
                                        table.bremsstrahlungEnergyDistributionBlock().value() ) ) );
      products.back().emplace_back(
        id::ParticleID( "e-" ), 1,
        createTabulatedAverageEnergy( table.electronEnergyAfterBremsstrahlungBlock().value() ) );

      // excitation - MT528
      products.push_back( {} );
      products.back().emplace_back(
        id::ParticleID( "e-" ), 1,
        createTabulatedAverageEnergy( table.electronExcitationEnergyLossBlock().value() ) );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        products.push_back( {} );
        products.back().emplace_back(
          id::ParticleID( "e-" ), 1,
          UncorrelatedDistributionData( ReferenceFrame::CentreOfMass,
                                        IsotropicAngularDistributions(),
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
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
