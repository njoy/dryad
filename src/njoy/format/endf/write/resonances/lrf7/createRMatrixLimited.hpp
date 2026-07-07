#ifndef NJOY_FORMAT_ENDF_WRITE_RESONANCES_LRF7_CREATERMATRIXLIMITED
#define NJOY_FORMAT_ENDF_WRITE_RESONANCES_LRF7_CREATERMATRIXLIMITED

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/format/endf/write/resonances/lrf7/createParticlePairs.hpp"
#include "njoy/format/endf/write/resonances/lrf7/createResonanceChannels.hpp"
#include "njoy/format/endf/write/resonances/lrf7/createResonanceParameters.hpp"
#include "njoy/format/endf/write/resonances/lrf7/createBackgroundChannels.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create an LRF7 resolved resonance range
   *
   *  @param[in] compound                 the compound system
   *  @param[in] reducedWidthAmplitudes   use reduced width amplitudes
   */
  inline ENDFtk::section::Type< 2, 151 >::RMatrixLimited
  createRMatrixLimited( const dryad::resonances::CompoundSystem& compound,
                        bool reducedWidthAmplitudes = true ) {

    using SpinGroup      = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;
    using RMatrixLimited = ENDFtk::section::Type< 2, 151 >::RMatrixLimited;

    // flag for reduced widths
    bool ifg = reducedWidthAmplitudes;

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

    auto pairs = resonances::lrf7::createParticlePairs( compound );
    std::vector< SpinGroup > groups;
    for ( const auto& group : compound.spinGroups() ) {

      if ( group.hasChannelsWithBackground() ) {

        groups.emplace_back( createResonanceChannels( group, pairs ),
                             createResonanceParameters( group, reducedWidthAmplitudes ),
                             createBackgroundChannels( group ) );
      } else {

        groups.emplace_back( createResonanceChannels( group, pairs ),
                             createResonanceParameters( group, reducedWidthAmplitudes ) );
      }
    }

    return RMatrixLimited( ifg, krl, krm, std::move( pairs ), std::move( groups ) );
  }


} // lrf7 namespace
} // resonances namespace
} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
