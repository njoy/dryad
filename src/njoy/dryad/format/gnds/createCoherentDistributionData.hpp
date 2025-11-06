#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATECOHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_FORMAT_GNDS_CREATECOHERENTDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReferenceFrame.hpp"
#include "dryad/format/gnds/createTabulatedFormFactorFromNodes.hpp"
#include "dryad/format/gnds/createTabulatedScatteringFunctionFromNodes.hpp"
#include "dryad/CoherentDistributionData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a CoherentDistributionData from a GNDS coherentPhotonScattering node
   */
  static CoherentDistributionData
  createCoherentDistributionData( const pugi::xml_node& coherent ) {

    // check that this is a valid coherentPhotonScattering node
    throwExceptionOnWrongNode( coherent, "coherentPhotonScattering" );

    // get the reference frame
    auto frame = createReferenceFrame( coherent.attribute( "productFrame" ).as_string() );

    auto node = coherent.child( "formFactor" ).first_child();
    auto function = createTabulatedScatteringFunctionFromNodes( node );
    std::optional< TabulatedFormFactor > real = std::nullopt;
    std::optional< TabulatedFormFactor > imaginary = std::nullopt;

    node = coherent.child( "realAnomalousFactor" ).first_child();
    if ( node ) {

      real = createTabulatedFormFactorFromNodes( node );
    }

    node = coherent.child( "imaginaryAnomalousFactor" ).first_child();
    if ( node ) {

      imaginary = createTabulatedFormFactorFromNodes( node );
    }

    if ( real.has_value() || imaginary.has_value() ) {

      return CoherentDistributionData( std::move( frame ),
                                       std::move( function ),
                                       std::move( real.value() ),
                                       std::move( imaginary.value() ) );
    }
    else {

      return CoherentDistributionData( std::move( frame ),
                                       std::move( function ) );
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
