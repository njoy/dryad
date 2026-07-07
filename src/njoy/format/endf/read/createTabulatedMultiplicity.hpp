#ifndef NJOY_FORMAT_ENDF_READ_CREATETABULATEDMULTIPLICITY
#define NJOY_FORMAT_ENDF_READ_CREATETABULATEDMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedMultiplicity.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a TabulatedMultiplicity from a parsed ENDF multiplicity
   *
   *  @param[in] multiplicity   the parsed ENDF tabulated multiplicity (MF1, MF6 or MF26)
   */
  template < typename Multiplicity >
  auto createTabulatedMultiplicity( const Multiplicity& multiplicity )
  -> std::enable_if_t< ( std::is_same_v< Multiplicity, ENDFtk::section::TabulatedMultiplicity > ||
                         std::is_same_v< Multiplicity, ENDFtk::section::Type< 6 >::Multiplicity > ||
                         std::is_same_v< Multiplicity, ENDFtk::section::Type< 26 >::Multiplicity > ),
                       dryad::TabulatedMultiplicity > {

    try {

      Log::info( "Reading multiplicity data" );
      auto energies = createVector( multiplicity.energies() );
      auto values = createVector( multiplicity.multiplicities() );
      auto boundaries = createBoundaries( multiplicity.boundaries() );
      auto interpolants = createInterpolants( multiplicity.interpolants() );
      return dryad::TabulatedMultiplicity(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated multiplicity" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
