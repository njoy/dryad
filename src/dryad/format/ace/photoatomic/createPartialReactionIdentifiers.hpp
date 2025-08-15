#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPARTIALREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEPARTIALREACTIONNUMBERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create partial reaction numbers for photoatomic data
   */
  std::vector< std::vector< int > >
  createPartialReactionNumbers( const ACEtk::PhotoatomicTable& table ) {

    std::vector< std::vector< int > > partials;

    // total - MT501
    partials.push_back( {} );

    // coherent scattering - MT502
    partials.push_back( {} );
    partials.front().push_back( 502 );

    // incoherent scattering - MT504
    partials.push_back( {} );
    partials.front().push_back( 504 );

    // pair production - MT516 (sum of MT515 and MT517)
    partials.push_back( {} );
    partials.front().push_back( 516 );

    // photoelectric - MT522 (sum of MT534 and up)
    partials.push_back( {} );
    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      auto sum = partials.size() - 1;
      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // partial: subshell photoelectric - MT534 and up
        partials.push_back( {} );
        partials.front().push_back( 534 + index - 1 );
        partials[sum].push_back( 534 + index - 1 );
      }
    }
    else {

      partials.front().push_back( 522 );
    }

    return partials;
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
