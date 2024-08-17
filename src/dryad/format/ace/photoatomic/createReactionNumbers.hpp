#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONNUMBERS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONNUMBERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedCrossSection.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create TabulatedCrossSection instances for photoatomic data
   */
  std::vector< int >
  createReactionNumbers( const ACEtk::PhotoatomicTable& table ) {

    std::vector< int > numbers;

    // total - MT501
    numbers.push_back( 501 );

    // coherent scattering - MT502
    numbers.push_back( 502 );

    // coherent scattering - MT504
    numbers.push_back( 504 );

    // coherent scattering - MT516 (sum of MT515 and MT517)
    numbers.push_back( 516 );

    // photoelectric - MT522 (sum of MT534 and up)
    numbers.push_back( 522 );

    if ( table.electronPhotonRelaxationFormat() > 0 ) {

      for ( std::size_t index = 1; index <= table.numberElectronSubshells(); ++index ) {

        // subshell photoelectric - MT534 and up
        numbers.push_back( 534 + index - 1 );
      }
    }

    return numbers;
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
