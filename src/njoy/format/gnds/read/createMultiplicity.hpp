#ifndef NJOY_FORMAT_GNDS_READ_CREATEMULTIPLICITY
#define NJOY_FORMAT_GNDS_READ_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/createPolynomialMultiplicity.hpp"
#include "njoy/format/gnds/read/createTabulatedMultiplicity.hpp"
#include "njoy/format/gnds/read/readConstant1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create an integer, tabulated or polynomial multiplicity from a GNDS multiplicity node
   *
   *  @param[in] multiplicity   the GNDS multiplicity node
   *  @param[in] style          the style to be extracted (default is "eval")
   */
  inline std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity >
  createMultiplicity( pugi::xml_node multiplicity, const std::string& style = "eval" ) {

    // check that this is a valid multiplicity node
    throwExceptionOnWrongNode( multiplicity, "multiplicity" );

    // check the first child with the requested style and act accordingly
    auto child = multiplicity.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( child.name(), "constant1d" ) == 0 ) {

      auto data = readConstant1dAsInteger( child );
      return data.first;
    }
    else if ( strcmp( child.name(), "polynomial1d" ) == 0 ) {

      return createPolynomialMultiplicity( multiplicity );
    }
    else if ( strcmp( child.name(), "branching1d" ) == 0 ) {

      Log::info( "Photon production due to deexcitation has not been implemented yet, "
                 "setting multiplicity to 1 for now" );
      return 1;
    }
    else {

      return createTabulatedMultiplicity( multiplicity );
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
