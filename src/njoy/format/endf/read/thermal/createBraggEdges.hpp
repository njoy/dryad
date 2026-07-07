#ifndef NJOY_FORMAT_ENDF_READ_THERMAL_CREATEBRAGGEDGES
#define NJOY_FORMAT_ENDF_READ_THERMAL_CREATEBRAGGEDGES

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/BraggEdgeData.hpp"
#include "njoy/format/createVector.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace thermal {

  /**
   *  @brief Create the BraggEdgeData from a parsed coherent
   *         elastic thermal scattering component
   *
   *  @param[in] coherent   the coherent elastic thermal scattering component
   */
  inline std::vector< dryad::thermal::BraggEdgeData >
  createBraggEdges( const ENDFtk::section::Type< 7, 2 >::CoherentElastic& coherent ) {

    try {

      std::vector< dryad::thermal::BraggEdgeData > edges;

      auto energies = createVector( coherent.energies() );
      std::size_t number_temperatures = coherent.numberTemperatures();
      for ( std::size_t i = 0; i < number_temperatures; ++i ) {

        edges.emplace_back( coherent.temperatures()[i], energies,
                            createVector( coherent.thermalScatteringValues()[i] ) );
      }

      return edges;
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating Bragg edge data "
                 "for coherent elastic thermal scattering" );
      throw;
    }
  }

} // thermal namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
