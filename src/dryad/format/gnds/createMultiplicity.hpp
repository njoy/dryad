#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEMULTIPLICITY
#define NJOY_DRYAD_FORMAT_GNDS_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/createTabulatedMultiplicity.hpp"
#include "dryad/format/gnds/readConstant1d.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create an integer or tabulated multiplicity from a GNDS multiplicity node
   */
  static std::variant< int, TabulatedMultiplicity >
  createMultiplicity( pugi::xml_node multiplicity, const std::string& style = "eval" ) {

    // check that this is a valid multiplicity node
    throwExceptionOnWrongNode( multiplicity, "multiplicity" );

    // check the first child with the requested style and act accordingly
    auto child = multiplicity.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( child.name(), "constant1d" ) == 0 ) {

      auto data = readConstant1dAsInteger( child );
      return data.first;
    }
    else {

      return createTabulatedMultiplicity( multiplicity );
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
