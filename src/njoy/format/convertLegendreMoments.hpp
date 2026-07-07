#ifndef NJOY_FORMAT_CONVERTLEGENDREMOMENTS
#define NJOY_FORMAT_CONVERTLEGENDREMOMENTS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/ranges.hpp"
#include "njoy/format/createVector.hpp"

namespace njoy {
namespace format {

  /**
   *  @brief Convert a range of Legendre moments into coefficients
   */
  void convertLegendreMoments( std::vector< double >& moments ) {

    std::size_t index = 0;
    std::transform( moments.begin(), moments.end(), moments.begin(),
                    [&] ( double moment ) { return moment * 0.5 * ( 2 * index++ + 1 ); } );
  }

} // format namespace
} // njoy namespace

#endif
