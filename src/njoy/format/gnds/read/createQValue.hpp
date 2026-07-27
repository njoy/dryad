#ifndef NJOY_FORMAT_GNDS_READ_CREATEQVALUE
#define NJOY_FORMAT_GNDS_READ_CREATEQVALUE

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/readConstant1d.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a Q value from a GNDS q node
   *
   *  @param[in] q       the gnds q node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline double createQValue( pugi::xml_node q, const std::string& style = "eval" ) {

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

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
