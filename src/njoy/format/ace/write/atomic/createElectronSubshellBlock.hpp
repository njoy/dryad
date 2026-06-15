#ifndef NJOY_FORMAT_ACE_WRITE_ATOMIC_CREATEACEELECTRONSUBSHELLBLOCK
#define NJOY_FORMAT_ACE_WRITE_ATOMIC_CREATEACEELECTRONSUBSHELLBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/electroatomic/ElectronSubshellBlock.hpp"

namespace njoy {
namespace format {
namespace ace {
namespace write {
namespace atomic {

  /**
   *  @brief Create the electron subshell data block for atomic data
   *
   *  It is assumed that the AtomicRelaxation instance used is valid atomic
   *  relaxation data, and ACE compatible (i.e. transition energies are
   *  calculated, etc.)
   *
   *  @param[in] relaxation   the atomic relaxation data
   */
  inline njoy::ACEtk::electroatomic::ElectronSubshellBlock
  createElectronSubshellBlock( const dryad::AtomicRelaxation& relaxation ) {

    constexpr unsigned int offset = 533;

    std::vector< unsigned int > designators;
    std::vector< double > electrons;
    std::vector< double > binding_energies;
    std::vector< unsigned int > number_transitions;
    std::vector< double > probabilities;

    double total = 0.;
    for ( const auto& shell : relaxation.subshells() ) {

      total += shell.population();
      electrons.emplace_back( shell.population() );
      probabilities.emplace_back( total );
      designators.emplace_back( shell.identifier().mt().value() - offset );
      binding_energies.emplace_back( shell.bindingEnergy() * constants::micro );
      number_transitions.emplace_back( shell.numberTransitions() );
    }

    std::transform( probabilities.begin(), probabilities.end(), probabilities.begin(),
                    [&] ( const auto& value ) { return value / total; } );

    return njoy::ACEtk::electroatomic::ElectronSubshellBlock(
               std::move( designators ),
               std::move( electrons ),
               std::move( binding_energies ),
               std::move( probabilities ),
               std::move( number_transitions ) );
  }

} // atomic namespace
} // write namespace
} // ace namespace
} // format namespace
} // njoy namespace

#endif
