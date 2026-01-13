#ifndef NJOY_MEDIC_PRUNECROSSECTION
#define NJOY_MEDIC_PRUNECROSSECTION

// system includes
#include <vector>

// other includes
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include <iostream>
namespace njoy {
namespace medic {

  /**
   *  @brief Prune cross section data
   *
   *  @param[in]     lowerEnergy   the new lower energy limit
   *  @param[in]     upperEnergy   the new upper energy limit
   *  @param[in,out] xs            the cross section table to be modified
   */
  inline void pruneCrossSection( double lowerEnergy, double upperEnergy,
                                 dryad::TabulatedCrossSection& xs ) {

    if ( upperEnergy <= lowerEnergy ) {

      throw std::runtime_error( "Error during pruning operation: the upper energy smaller than or "
                                "equal to the lower energy" );
    }
    if ( xs.upperEnergyLimit() <= lowerEnergy ) {

      throw std::runtime_error( "Error during pruning operation: the lower energy is larger than or "
                                "equal to the upper energy of the cross section table" );
    }

    if ( xs.lowerEnergyLimit() < lowerEnergy || xs.upperEnergyLimit() > upperEnergy ) {

      std::vector< double > energies = xs.energies();
      std::vector< double > values = xs.values();
      std::vector< std::size_t > boundaries = xs.boundaries();
      std::vector< dryad::InterpolationType > interpolants = xs.interpolants();

      if ( xs.lowerEnergyLimit() < lowerEnergy ) {

        auto iter = std::lower_bound( energies.begin(), energies.end(), lowerEnergy );
        auto index = std::distance( energies.begin(), iter );

        if ( *iter != lowerEnergy ) {

          // the new lower energy is not present: add it, calculate the value and
          // increment the boundaries by 1
          iter = energies.insert( iter, lowerEnergy );
          values.insert( values.begin() + index, xs( lowerEnergy ) );
          std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                          [] ( auto&& value ) { return value + 1; } );
        }
        else if ( *std::next( iter ) == lowerEnergy ) {

          // this is a jump: we'll have to remove it
          ++iter;
          ++index;
        }

        // erase the energies and values we do not want, decrement the boundaries by
        // the number of energies we have removed
        energies.erase( energies.begin(), iter );
        values.erase( values.begin(), values.begin() + index );

        // erase boundaries and interpolants
        auto biter = std::lower_bound( boundaries.begin(), boundaries.end(), index + 1 );
        auto bindex = std::distance( boundaries.begin(), biter );
        boundaries.erase( boundaries.begin(), biter );
        interpolants.erase( interpolants.begin(), interpolants.begin() + bindex );

        // adjust boundary values
        std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                        [index] ( auto&& value ) { return value - index; } );
      }

      if ( xs.upperEnergyLimit() > upperEnergy ) {

        auto iter = std::lower_bound( energies.begin(), energies.end(), upperEnergy );
        auto index = std::distance( energies.begin(), iter );

        if ( *iter != upperEnergy ) {

          // the new upper energy is not present: add it, calculate the value and
          // increment the boundaries by 1
          iter = energies.insert( iter, upperEnergy );
          values.insert( values.begin() + index, xs( upperEnergy ) );
          std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                          [] ( auto&& value ) { return value + 1; } );
        }

        // erase the energies and values we do not want, decrement the boundaries by
        // the number of energies we have removed
        energies.erase( iter + 1, energies.end() );
        values.erase( values.begin() + index + 1, values.end() );

        // erase boundaries and interpolants
        auto biter = std::lower_bound( boundaries.begin(), boundaries.end(), index );
        auto bindex = std::distance( boundaries.begin(), biter );
        boundaries.erase( biter + 1, boundaries.end() );
        interpolants.erase( interpolants.begin() + bindex + 1, interpolants.end() );

        // adjust boundary values
        boundaries.back() = energies.size() - 1;
      }

      xs = dryad::TabulatedCrossSection( std::move( energies ), std::move( values ),
                                         std::move( boundaries ), std::move( interpolants ) );
    }
  }

} // medic namespace
} // njoy namespace

#endif
