#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ReactionProduct.hpp"
#include "dryad/format/ace/createTabulatedScatteringFunction.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create partial reaction numbers for photoatomic data
   *
   *  @param[in] table   the ace table
   */
  std::vector< std::vector< ReactionProduct > >
  createReactionProducts( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< ReactionProduct > > products;

    // total - MT501
    products.push_back( {} );

    // coherent scattering - MT502
    products.push_back( {} );
    products.back().emplace_back(
      id::ParticleID( "g" ), 1,
      CoherentDistributionData( ReferenceFrame::CentreOfMass,
                                createTabulatedScatteringFunction( table.coherentFormFactorBlock() ) ) );

    // incoherent scattering - MT504
    products.push_back( {} );
    products.back().emplace_back(
      id::ParticleID( "g" ), 1,
      IncoherentDistributionData( ReferenceFrame::CentreOfMass,
                                  createTabulatedScatteringFunction( table.incoherentScatteringFunctionBlock() ) ) );

    // pair production - MT516 (sum of MT515 and MT517)
    products.push_back( {} );

    // photoelectric - MT522 (sum of MT534 and up)
    products.push_back( {} );
    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // partial: subshell photoelectric - MT534 and up
        products.push_back( {} );
      }
    }

    return products;
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
