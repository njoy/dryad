#ifndef NJOY_UTILITY_FIND_CLOSEST
#define NJOY_UTILITY_FIND_CLOSEST

// system includes
#include <algorithm>
#include <cmath>
#include <vector>

// other includes

namespace njoy {
namespace utility {

/**
 *  @brief Return an iterator to the closest value within a given tolerance
 *
 *  @param[in] first       an input iterator to the initial position in a sequence
 *  @param[in] last        an input iterator to the final position in a sequence
 *  @param[in] value       the value we are looking for
 *  @param[in] tolerance   the relative comparison tolerance
 */
template < typename Iterator, typename X >
Iterator find_closest( const Iterator& first, const Iterator& last,
                       const X& value, const X& tolerance ) {

  auto iter = std::lower_bound( first, last, value - tolerance * value );
  if ( iter != last ) {

    if ( std::abs( *iter - value ) <= tolerance * value ) {

      return iter;
    }
  }

  return last;
}

} // utility namespace
} // njoy namespace

#endif
