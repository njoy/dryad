#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATEMASS
#define NJOY_FORMAT_GNDS_READ_POPS_CREATEMASS

// system includes
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/readDouble.hpp"
#include "njoy/format/gnds/read/convertMass.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief Create a mass values from a GNDS mass xml node
   *
   *  @param[in] mass    the GNDS mass node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline std::optional< double >
  createMass( const pugi::xml_node& mass, const std::string& style = "eval" ) {

    // check that this is a valid mass node
    throwExceptionOnWrongNode( mass, "mass" );

    // get a double node if it exists, else return nullopt
    auto child = mass.find_child_by_attribute( "double", "label", style.c_str() );
    if ( child ) {

      auto content = readDouble( child );
      convertMass( content.first, content.second.value() );
      return content.first;
    }

    return std::nullopt;
  }

} // pops namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
