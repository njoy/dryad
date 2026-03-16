#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRMATRIXLIMITED
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRMATRIXLIMITED

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfParticlePairs.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceChannels.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfResonanceParameters.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createEndfBackgroundChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create an LRF7 resolved resonance range
   *
   *  @param[in] compound   the compound system
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited
  createEndfRMatrixLimited( const dryad::resonances::CompoundSystem& compound ) {

    using SpinGroup     = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;
    using RMatrixLimited = ENDFtk::section::Type< 2, 151 >::RMatrixLimited;

    // flag for reduced widths - dryad converts to reduced widths at read time
    bool ifg = true;

    // kinematics flag
    bool krl = false;
    if ( compound.spinGroups().front().kinematicsType() == njoy::dryad::resonances::Kinematics::Relativistic ) {

      krl = true;
    }

    // formalism
    int krm = 3;
    if ( compound.spinGroups().front().formalism() ==  njoy::dryad::resonances::Formalism::GeneralRMatrix ) {

      krm = 4;
    }

    auto pairs = resonances::lrf7::createEndfParticlePairs( compound );
    std::vector< SpinGroup > groups;
    for ( const auto& group : compound.spinGroups() ) {

      if ( group.hasChannelsWithBackground() ) {

        groups.emplace_back( createEndfResonanceChannels( group, pairs ),
                             createEndfResonanceParameters( group.resonanceTable() ),
                             createEndfBackgroundChannels( group ) );
      } else {

        groups.emplace_back( createEndfResonanceChannels( group, pairs ),
                             createEndfResonanceParameters( group.resonanceTable() ) );
      }
    }

    return RMatrixLimited( ifg, krl, krm, std::move( pairs ), std::move( groups ) );
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
