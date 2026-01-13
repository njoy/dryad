#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEFLUORESCENDATABLOCK
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEACEFLUORESCENDATABLOCK

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/ProjectileTarget.hpp"
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the fluorescence data block for photoatomic data
   *
   *  It is assumed that the ProjectileTarget instance used is valid photoatomic
   *  data, and ACE compatible (i.e. unionised energy grid, etc.)
   *
   *  @param[in] photoatomic   the photoatomic data
   */
  inline njoy::ACEtk::photoatomic::FluorescenceDataBlock
  createAceFluorescenceDataBlock( const ProjectileTarget& photoatomic ) {


    


    return njoy::ACEtk::photoatomic::FluorescenceDataBlock();
  }

} // photoatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
