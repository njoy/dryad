#ifndef NJOY_DRYAD_FORMAT_CURATETABULATEDDATA
#define NJOY_DRYAD_FORMAT_CURATETABULATEDDATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/format/createIndex.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Curate tabulated data
   *
   *  @param energies       the x values
   *  @param values         the y values
   *  @param boundaries     the boundaries of the interpolation regions
   *  @param interpolants   the interpolation types of the interpolation regions
   */
  bool curateTabulatedData( std::vector< double >& x, std::vector< double >& y,
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

        curated = true;
        ++number;
      }

      if ( number ) {

        Log::warning( "Found {} duplicate point(s) at the beginning of the x grid", number );
      }
    }

    return curated;
  }

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
