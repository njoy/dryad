#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEINIncoherentDistributionData
#define NJOY_DRYAD_FORMAT_GNDS_CREATEINIncoherentDistributionData

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createReferenceFrame.hpp"
#include "dryad/format/gnds/createTabulatedScatteringFunctionFromNodes.hpp"
#include "dryad/IncoherentDistributionData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a IncoherentDistributionData from a GNDS coherentPhotonScattering node
   */
  static IncoherentDistributionData 
  createIncoherentDistributionData( const pugi::xml_node& incoherent ) {

    // check that this is a valid coherentPhotonScattering node
    throwExceptionOnWrongNode( incoherent, "incoherentPhotonScattering" );

    // get the reference frame
    auto frame = createReferenceFrame( incoherent.attribute( "productFrame" ).as_string() );

    auto node = incoherent.child( "scatteringFactor" ).first_child();
    auto function = createTabulatedScatteringFunctionFromNodes( node );

    return IncoherentDistributionData( std::move( frame ),
                                       std::move( function ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
