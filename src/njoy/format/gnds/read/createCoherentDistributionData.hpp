#ifndef NJOY_FORMAT_GNDS_READ_CREATECOHERENTDISTRIBUTIONDATA
#define NJOY_FORMAT_GNDS_READ_CREATECOHERENTDISTRIBUTIONDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/CoherentDistributionData.hpp"
#include "njoy/format/gnds/read/createReferenceFrame.hpp"
#include "njoy/format/gnds/read/createTabulatedFormFactorFromNodes.hpp"
#include "njoy/format/gnds/read/createTabulatedScatteringFunctionFromNodes.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a CoherentDistributionData from a GNDS coherentPhotonScattering node
   *
   *  @param[in] coherent    the GNDS coherentPhotonScattering node
   */
  inline dryad::CoherentDistributionData
  createCoherentDistributionData( const pugi::xml_node& coherent ) {

    // check that this is a valid coherentPhotonScattering node
    throwExceptionOnWrongNode( coherent, "coherentPhotonScattering" );

    // get the reference frame
    auto frame = createReferenceFrame( coherent.attribute( "productFrame" ).as_string() );

    auto node = coherent.child( "formFactor" ).first_child();
    auto function = createTabulatedScatteringFunctionFromNodes( node );
    std::optional< dryad::TabulatedFormFactor > real = std::nullopt;
    std::optional< dryad::TabulatedFormFactor > imaginary = std::nullopt;

    node = coherent.child( "realAnomalousFactor" ).first_child();
    if ( node ) {

      real = createTabulatedFormFactorFromNodes( node );
    }

    node = coherent.child( "imaginaryAnomalousFactor" ).first_child();
    if ( node ) {

      imaginary = createTabulatedFormFactorFromNodes( node );
    }

    if ( real.has_value() || imaginary.has_value() ) {

      return dryad::CoherentDistributionData( std::move( frame ),
                                              std::move( function ),
                                              std::move( real.value() ),
                                              std::move( imaginary.value() ) );
    }
    else {

      return dryad::CoherentDistributionData( std::move( frame ),
                                              std::move( function ) );
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
