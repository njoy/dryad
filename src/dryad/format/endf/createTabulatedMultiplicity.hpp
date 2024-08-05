#ifndef NJOY_DRYAD_FORMAT_ENDF_TABULATEDMULTIPLICITY
#define NJOY_DRYAD_FORMAT_ENDF_TABULATEDMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a TabulatedMultiplicity from a parsed ENDF multiplicity
   */
  template < typename Multiplicity >
  auto createTabulatedMultiplicity( const id::ParticleID& product, const Multiplicity& multiplicity, int mt )
  -> std::enable_if_t< ( std::is_same_v< Multiplicity, ENDFtk::section::Type< 6 >::Multiplicity > ||
                         std::is_same_v< Multiplicity, ENDFtk::section::Type< 26 >::Multiplicity > ),
                       TabulatedMultiplicity > {

    try {

      Log::info( "Reading multiplicity data for product \'{}\'", product );
      auto energies = createVector( multiplicity.energies() );
      auto values = createVector( multiplicity.multiplicities() );
      auto boundaries = createBoundaries( multiplicity.boundaries() );
      auto interpolants = createInterpolants( multiplicity.interpolants() );
      return TabulatedMultiplicity(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated "
                 "multiplicity for MT{}", mt );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
