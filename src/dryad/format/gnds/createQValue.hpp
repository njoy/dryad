#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEQVALUE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEQVALUE

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createTabulatedMultiplicity.hpp"
#include "dryad/format/gnds/readConstant1d.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a Q value from a GNDS q node
   */
  double createQValue( pugi::xml_node q, const std::string& style = "eval" ) {

    // check that this is a valid q node
    throwExceptionOnWrongNode( q, "Q" );

    // check the first child with the requested style and act accordingly
    auto child = q.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( child.name(), "constant1d" ) == 0 ) {

      auto data = readConstant1dAsDouble( child );
      convertEnergy( data.first, data.second );
      return data.first;
    }
    else {

      Log::error( "The GNDS node named \'{}\' does not define supported q value data", q.name() );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
