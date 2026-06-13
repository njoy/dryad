#ifndef NJOY_FORMAT_GNDS_READ_THERMAL_CREATEINCOHERENTELASTICSCATTERING
#define NJOY_FORMAT_GNDS_READ_THERMAL_CREATEINCOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/format/gnds/read/thermal/createDebyeWallerIntegralData.hpp"
#include "njoy/format/gnds/read/convertCrossSection.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace thermal {

  /**
   *  @brief Create an IncoherentElasticScattering from a GNDS tsl node
   *
   *  @param[in] tsl   the GNDS tsl node
   */
  inline dryad::thermal::IncoherentElasticScattering
  createIncoherentElasticScattering( const pugi::xml_node& tsl ) {

    Log::info( "Reading incoherent elastic scattering data" );

    // check that this is a valid incoherent elastic thermal scattering node
    throwExceptionOnWrongNode( tsl, "thermalNeutronScatteringLaw_incoherentElastic" );

    // get the bound cross section
    auto node = tsl.child( "boundAtomCrossSection" );
    double xs = node.attribute( "value" ).as_double();
    convertCrossSection( xs, node.attribute( "unit" ).as_string() );

    // get the Debye-Waller integral
    node = tsl.child( "DebyeWallerIntegral" );
    dryad::thermal::DebyeWallerIntegralData integral = createDebyeWallerIntegralData( node );

    return dryad::thermal::IncoherentElasticScattering( xs, std::move( integral ) );
  }

} // thermal namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
