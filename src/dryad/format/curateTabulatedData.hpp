#ifndef NJOY_DRYAD_FORMAT_CURATETABULATEDDATA
#define NJOY_DRYAD_FORMAT_CURATETABULATEDDATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/format/createIndex.hpp"
#include "scion/verification.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Curate tabulated data
   *
   *  This function provides additional curation of tabulated data to correct common
   *  issues encountered with tabulated data in ENDF files. The issues curated by this
   *  function are:
   *    - duplicate points at the beginning of the grid
   *
   *  @param energies       the x values
   *  @param values         the y values
   *  @param boundaries     the boundaries of the interpolation regions
   *  @param interpolants   the interpolation types of the interpolation regions
   */
  void curateTabulatedData( std::vector< double >& x, std::vector< double >& y,
                            std::vector< std::size_t >& boundaries,
                            std::vector< InterpolationType >& interpolants ) {

    bool curated = false;
    auto xIter = std::adjacent_find( x.begin(), x.end() );
    auto yIter = std::next( y.begin(), std::distance( x.begin(), xIter ) );
    if ( xIter == x.begin() ) {

      unsigned int number = 0;
      while ( *yIter == *( yIter + 1 ) ) {

        xIter = x.erase( xIter );
        yIter = y.erase( yIter );
        std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(), createIndex );

        ++number;
      }

      if ( number ) {

        Log::warning( "Removed {} duplicate point(s) at the beginning of the x grid", number );
      }
    }
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
