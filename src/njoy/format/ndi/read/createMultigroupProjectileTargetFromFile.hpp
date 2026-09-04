#ifndef NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPPROJECTILETARGETFROMFILE
#define NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPPROJECTILETARGETFROMFILE

// system includes
#include <string>
#include <variant>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/format/ndi/read/createMultigroupProjectileTarget.hpp"
#include "NDItk/MultigroupLibrary.hpp"
#include "NDItk/fromFile.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create MultigroupProjectileTarget instances from an NDI file
   *
   *  @param[in] filename   the NDI file name
   */
  inline std::vector< dryad::MultigroupProjectileTarget >
  createMultigroupProjectileTargetFromFile( const std::string& filename ) {

    Log::info( "Reading NDI file \'{}\'", filename );

    using Library = njoy::NDItk::MultigroupLibrary;
    auto library = njoy::NDItk::fromFile< Library >( filename );

    std::vector< dryad::MultigroupProjectileTarget > targets;
    for ( auto&& table : library.tables() ) {

      targets.emplace_back( createMultigroupProjectileTarget( table ) );
    }

    return targets;
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
