#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEREACTIONNUMBERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create reaction numbers for electroatomic data
   */
  std::vector< int >
  createReactionNumbers( const ACEtk::PhotoatomicTable& table ) {

    std::vector< int > numbers;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      numbers.push_back( 501 );

      // ionisation - MT522
      numbers.push_back( 522 );

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        numbers.push_back( 525 );
      }

      // total elastic - MT526
      numbers.push_back( 526 );

      // bremsstrahlung - MT527
      numbers.push_back( 527 );

      // excitation - MT528
      numbers.push_back( 528 );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        numbers.push_back( 534 + index - 1 );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        numbers.push_back( -526 );
      }
    }

    return numbers;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
