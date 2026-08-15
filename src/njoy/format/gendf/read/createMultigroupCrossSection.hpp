#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPCROSSSECTION
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPCROSSSECTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/MultigroupCrossSection.hpp"
#include "njoy/format/createVector.hpp"
#include "ENDFtk/gsection/3g.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create a MultigroupCrossSection from a parsed GENDF MF3 section
   *
   *  @param[in] boundaries   the energy group boundaries
   *  @param[in] section      the parsed GENDF MF3 section
   *  @param[in] dilution     the dilution index to read
   */
  inline dryad::MultigroupCrossSection
  createMultigroupCrossSection( const std::vector< double >& boundaries,
                                const ENDFtk::section::GType< 3 >& section,
                                std::size_t dilution ) {

    try {

      Log::info( "Reading cross section data" );
      auto values = createVector( section.crossSection( 0, dilution ) );
      return dryad::MultigroupCrossSection( boundaries, std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a multigroup cross section" );
      throw;
    }
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
