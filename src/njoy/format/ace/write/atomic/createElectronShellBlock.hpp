#ifndef NJOY_FORMAT_ACE_WRITE_ATOMIC_CREATEACEELECTRONSHELLBLOCK
#define NJOY_FORMAT_ACE_WRITE_ATOMIC_CREATEACEELECTRONSHELLBLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/electroatomic/ElectronShellBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace atomic {

  /**
   *  @brief Create the electron shell data block for atomic data
   *
   *  It is assumed that the AtomicRelaxation instance used is valid atomic
   *  relaxation data, and ACE compatible (i.e. transition energies are
   *  calculated, etc.)
   *
   *  The electron shell block links to the Compton profile data, which can be
   *  given for non-relativistic or relativistic electron shells. When
   *  non-relativistic shells are used, the electron population has to be
   *  summed over the relativistic shells and the binding energy has to be
   *  averaged (we currently use the electron population by shell to perform
   *  this averaging).
   *
   *  @param[in] relativistic   flag to indicate whether or not the shell data
   *                            has to use relativistic shells
   *  @param[in] relaxation     the atomic relaxation data
   */
  inline njoy::ACEtk::electroatomic::ElectronShellBlock
  createElectronShellBlock( bool relativistic,
                            const dryad::AtomicRelaxation& relaxation ) {

    std::vector< double > electrons;
    std::vector< double > binding_energies;
    std::vector< double > probabilities;

    double total = 0.;
    if ( relativistic ) {

      for ( const auto& shell : relaxation.subshells() ) {

        total += shell.population();

        electrons.emplace_back( shell.population() );
        probabilities.emplace_back( total );
        binding_energies.emplace_back( shell.bindingEnergy() * constants::micro );
      }
    }
    else {

      auto iter = relaxation.subshells().begin();
      while ( iter != relaxation.subshells().end() ) {

        auto id = iter->identifier();
        auto compare = [&id] ( auto&& subshell ) {

          return id.principalQuantumNumber() == subshell.identifier().principalQuantumNumber() &&
                 id.azimuthalQuantumNumber() == subshell.identifier().azimuthalQuantumNumber();
        };
        auto end = std::find_if_not( iter, relaxation.subshells().end(), compare );

        electrons.emplace_back( 0. );
        probabilities.emplace_back( total );
        binding_energies.emplace_back( 0. );
        for ( ; iter != end; ++iter ) {

          total += iter->population();

          electrons.back() += iter->population();
          probabilities.back() += iter->population();
          binding_energies.back() += iter->population() * iter->bindingEnergy() * constants::micro;
        }
        binding_energies.back() /= electrons.back();
      }
    }

    std::transform( probabilities.begin(), probabilities.end(), probabilities.begin(),
                    [&] ( const auto& value ) { return value / total; } );

    return njoy::ACEtk::electroatomic::ElectronShellBlock(
               std::move( electrons ),
               std::move( binding_energies ),
               std::move( probabilities ) );
  }

} // atomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
