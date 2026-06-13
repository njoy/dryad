#ifndef NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATEVARIANCESCALING
#define NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATEVARIANCESCALING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/VarianceScaling.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/covariance/createScalingType.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readArray.hpp"
#include "njoy/format/gnds/read/convertEnergies.hpp"
#include "njoy/format/gnds/read/convertVarianceScalingFactors.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace covariance {

  /**
   *  @brief Create a VarianceScaling from a GNDS variance scaling node
   */
  inline dryad::covariance::VarianceScaling
  createVarianceScaling( const pugi::xml_node& scaling ) {

    // check that this is a valid variance scaling node
    throwExceptionOnWrongNode( scaling, "shortRangeSelfScalingVariance" );

    // get the type from the attribute
    auto attribute = scaling.attribute( "dependenceOnProcessedGroupWidth" ).as_string();
    dryad::covariance::ScalingType type = covariance::createScalingType( attribute );

    // get the group structure from the axes - convert units if required
    auto axes = readAxes( scaling.child( "gridded2d" ).child( "axes" ) );
    std::vector< double > energies = std::move( std::get< 2 >( axes[0] ).value() );
    convertEnergies( energies, std::get< 1 >( axes[0] ).value() );

    // read the array
    auto matrix = readArray( scaling.child( "gridded2d" ).child( "array" ) );
    std::vector< double > factors;
    factors.reserve( energies.size() - 1 );
    for ( unsigned int i = 0; i < energies.size() - 1; ++i ) {

      factors.push_back( matrix(i,i) );
    }
    convertVarianceScalingFactors( factors, std::get< 1 >( axes[2] ).value() );

    //! @todo we may have to convert the array values

    return dryad::covariance::VarianceScaling( std::move( type ),
                                               std::move( energies ),
                                               std::move( factors ) );
  }

} // covariance namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
