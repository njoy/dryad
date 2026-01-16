#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEHEATINGNUMBERSBLOCK
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEHEATINGNUMBERSBLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the heating numbers block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   *  @param[in] relaxation    the atomic relaxation data
   */
  inline njoy::ACEtk::photoatomic::HeatingNumbersBlock
  createAceHeatingNumbersBlock( const ProjectileTarget& photoatomic,
                                const AtomicRelaxation& relaxation ) {

    std::vector< double > heating( photoatomic.reactions().front().crossSection().numberPoints(), 0. );

    return njoy::ACEtk::photoatomic::HeatingNumbersBlock( std::move( heating ) );
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
