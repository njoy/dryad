#ifndef NJOY_DRYAD_FORMAT_ACE_ATOMIC_CREATEACESUBSHELLTRANSITIONDATABLOCK
#define NJOY_DRYAD_FORMAT_ACE_ATOMIC_CREATEACESUBSHELLTRANSITIONDATABLOCK

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/electroatomic/SubshellTransitionDataBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace atomic {

  /**
   *  @brief Create the atomic relaxation data block for electroatomic data
   *
   *  It is assumed that the AtomicRelaxation instance used is valid atomic
   *  relaxation data, and ACE compatible (i.e. transition energies are
   *  calculated, etc.)
   *
   *  @param[in] relaxation   the atomic relaxation data
   */
  inline njoy::ACEtk::electroatomic::SubshellTransitionDataBlock
  createAceSubshellTransitionDataBlock( const dryad::AtomicRelaxation& relaxation ) {

    constexpr unsigned int offset = 533;

    std::vector< njoy::ACEtk::electroatomic::SubshellTransitionData > transitiondata;
    for ( const auto& shell : relaxation.subshells() ) {

      std::vector< unsigned int > primary;
      std::vector< unsigned int > secondary;
      std::vector< double > energies;
      std::vector< double > cdf;

      if ( shell.hasTransitions() ) {

        double probability = 0;

        for ( const auto& transition : shell.radiativeTransitions() ) {

          primary.emplace_back( transition.originatingShell().mt().value() - offset );
          secondary.emplace_back( 0 );
          energies.emplace_back( transition.energy().value() * constants::micro );

          probability += transition.probability();
          cdf.emplace_back( probability );
        }

        for ( const auto& transition : shell.nonRadiativeTransitions() ) {

          primary.emplace_back( transition.originatingShell().mt().value() - offset );
          secondary.emplace_back( transition.emittingShell().mt().value() - offset );
          energies.emplace_back( transition.energy().value() * constants::micro );

          probability += transition.probability();
          cdf.emplace_back( probability );
        }

        cdf.back() = 1.;
      }

      transitiondata.emplace_back( std::move( primary ), std::move( secondary ),
                                   std::move( energies ), std::move( cdf ) );
    }

    return njoy::ACEtk::electroatomic::SubshellTransitionDataBlock( std::move( transitiondata ) );
  }

} // atomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
