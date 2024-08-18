#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPARTIALREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPARTIALREACTIONNUMBERS

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
   *  @brief Create partial reaction numbers for electroatomic data
   */
  std::vector< std::vector< int > >
  createPartialReactionNumbers( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< int > > partials;

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      // total - MT501
      partials.push_back( {} );

      // ionisation - MT522
      partials.push_back( {} );
      if ( table.numberElectronSubshells() > 0 ) {

        for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

          // partial: subshell ionisation - MT534 and up
          partials.back().push_back( 534 + index - 1 );
        }
      }
      else {

        partials.front().push_back( 522 );
      }

      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // large angle elastic - MT525
        partials.push_back( {} );
        partials.front().push_back( 525 );
      }

      // total elastic - MT526
      partials.push_back( {} );
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // partial: large angle elastic - MT525
        partials.back().push_back( 525 );
        // partial: elastic deficit
        partials.back().push_back( -526 );
      }
      else {

        partials.front().push_back( 526 );
      }

      // bremsstrahlung - MT527
      partials.push_back( {} );
      partials.front().push_back( 527 );

      // excitation - MT528
      partials.push_back( {} );
      partials.front().push_back( 528 );

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell ionisation - MT534 and up
        partials.push_back( {} );
        partials.front().push_back( 534 + index - 1 );
      }

      // eprdata14 and higher has large angle and total elastic -> add deficit elastic
      if ( table.electronPhotonRelaxationFormat() > 2 ) {

        // elastic deficit
        partials.push_back( {} );
        partials.front().push_back( -526 );
      }
    }

    return partials;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
