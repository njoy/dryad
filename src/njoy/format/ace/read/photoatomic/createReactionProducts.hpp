#ifndef NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONPRODUCTS
#define NJOY_FORMAT_ACE_READ_PHOTOATOMIC_CREATEREACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReactionProduct.hpp"
#include "njoy/format/ace/read/createTabulatedScatteringFunction.hpp"
#include "njoy/format/ace/read/photoatomic/createTabulatedComptonProfiles.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace read {
namespace photoatomic {

  /**
   *  @brief Create partial reaction numbers for photoatomic data
   *
   *  @param[in] table   the ace table
   */
  inline std::vector< std::vector< dryad::ReactionProduct > >
  createReactionProducts( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< dryad::ReactionProduct > > products;

    // total - MT501
    products.push_back( {} );

    // coherent scattering - MT502
    products.push_back( {} );
    products.back().emplace_back(
      dryad::id::ParticleID::photon(), 1,
      dryad::CoherentDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                       createTabulatedScatteringFunction( table.coherentFormFactorBlock() ) ) );

    // incoherent scattering - MT504
    products.push_back( {} );
    products.back().emplace_back(
      dryad::id::ParticleID::photon(), 1,
      dryad::IncoherentDistributionData( dryad::ReferenceFrame::CentreOfMass,
                                         createTabulatedScatteringFunction( table.incoherentScatteringFunctionBlock() ),
                                         table.comptonProfileBlock().has_value()
                                           ? std::make_optional( createTabulatedComptonProfiles(
                                                                     table.comptonProfileBlock().value(),
                                                                     table.Z() ) )
                                           : std::nullopt ) );

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
} // read namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
