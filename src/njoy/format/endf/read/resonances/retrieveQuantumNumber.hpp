#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_RETRIEVEQUANTUMNUMBER
#define NJOY_FORMAT_ENDF_READ_RESONANCES_RETRIEVEQUANTUMNUMBER

// system includes
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

// other includes
#include "njoy/dryad/resonances/ChannelQuantumNumbers.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {

  /**
   *  @brief Retrieve and consume the channel quantum numbers matching a given
   *         orbital angular momentum and total angular momentum
   *
   *  @param[in] l           the orbital angular momentum
   *  @param[in] j           the (signed) total angular momentum
   *  @param[in,out] available   the quantum number combinations that are still available
   */
  inline dryad::resonances::ChannelQuantumNumbers
  retrieveQuantumNumber( unsigned int l, double j,
                         std::vector< dryad::resonances::ChannelQuantumNumbers >& available ) {

    auto find = [l,j] ( auto&& numbers ) {

      return numbers.orbitalAngularMomentum() == l &&
             numbers.totalAngularMomentum() == std::abs( j );
    };

    auto first = std::find_if( available.begin(), available.end(), find );
    if ( first != available.end() ) {

      auto second = std::find_if( std::next( first ), available.end(), find );
      if ( second != available.end() ) {

        if ( j > 0 ) {

          first = second;
        }
      }

      auto numbers = *first;
      available.erase( first );
      return numbers;
    }
    else {

      throw std::runtime_error( "None of the expected spin groups has l = "
                                + std::to_string( l ) + " and J = "
                                + std::to_string( std::abs( j ) ) );
    }
  }

} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
