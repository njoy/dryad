#ifndef NJOY_FORMAT_GNDS_READ_CREATEINIncoherentDistributionData
#define NJOY_FORMAT_GNDS_READ_CREATEINIncoherentDistributionData

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/IncoherentDistributionData.hpp"
#include "njoy/format/gnds/read/createReferenceFrame.hpp"
#include "njoy/format/gnds/read/createTabulatedScatteringFunctionFromNodes.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a IncoherentDistributionData from a GNDS coherentPhotonScattering node
   */
  inline dryad::IncoherentDistributionData
  createIncoherentDistributionData( const pugi::xml_node& incoherent ) {

    // check that this is a valid coherentPhotonScattering node
    throwExceptionOnWrongNode( incoherent, "incoherentPhotonScattering" );

    // get the reference frame
    auto frame = createReferenceFrame( incoherent.attribute( "productFrame" ).as_string() );

    auto node = incoherent.child( "scatteringFactor" ).first_child();
    auto function = createTabulatedScatteringFunctionFromNodes( node );

    return dryad::IncoherentDistributionData( std::move( frame ),
                                              std::move( function ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
