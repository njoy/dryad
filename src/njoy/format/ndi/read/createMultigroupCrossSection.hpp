#ifndef NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPCROSSSECTION
#define NJOY_FORMAT_NDI_READ_CREATEMULTIGROUPCROSSSECTION

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupCrossSection.hpp"
#include "njoy/format/createVector.hpp"
#include "NDItk/multigroup/TotalCrossSection.hpp"
#include "NDItk/multigroup/CrossSection.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create a MultigroupCrossSection from a parsed NDI total cross section record
   *
   *  @param[in] boundaries   the energy group boundaries
   *  @param[in] record       the total cross section record
   */
  inline dryad::MultigroupCrossSection
  createMultigroupCrossSection( const std::vector< double >& boundaries,
                                const NDItk::multigroup::TotalCrossSection& record ) {

    try {

      Log::info( "Reading cross section data" );
      auto values = createVector( record.values() );
      std::reverse( values.begin(), values.end() );
      return dryad::MultigroupCrossSection( boundaries, std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a multigroup cross section" );
      throw;
    }
  }

  /**
   *  @brief Create a MultigroupCrossSection from a parsed NDI cross section subrecord
   *
   *  @param[in] boundaries   the energy group boundaries
   *  @param[in] record       the cross section subrecord
   */
  inline dryad::MultigroupCrossSection
  createMultigroupCrossSection( const std::vector< double >& boundaries,
                                const NDItk::multigroup::CrossSection& record ) {

    try {

      Log::info( "Reading cross section data" );
      auto values = createVector( record.crossSections() );
      std::reverse( values.begin(), values.end() );
      return dryad::MultigroupCrossSection( boundaries, std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a multigroup cross section" );
      throw;
    }
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
