#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEMULTIPLICITY
#define NJOY_DRYAD_FORMAT_GNDS_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "njoy/dryad/format/gnds/resonances/createTabulatedRadius.hpp"
#include "njoy/dryad/format/gnds/readConstant1d.hpp"
#include "njoy/dryad/format/gnds/convertRadius.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {

  /**
   *  @brief Create a double or tabulated radius from a GNDS scattering radius node
   *
   *  @param[in] radius   the GNDS scattering radius or hardsphere radius node
   */
  static std::variant< double, dryad::resonances::TabulatedRadius >
  createRadius( pugi::xml_node radius ) {

    // check that this is a valid hard sphere or scattering radius node
    if ( strcmp( radius.name(), "scatteringRadius" ) != 0 &&
         strcmp( radius.name(), "hardSphereRadius" ) != 0 ) {

      Log::error( "The XML element does not define a GNDS scatteringRadius or "
                  "hardSphereRadius node, found a \'{}\' node",
                  radius.name() );
      throw std::exception();
    }

    // check the first child with the requested style and act accordingly
    auto child = radius.first_child();
    if ( strcmp( child.name(), "constant1d" ) == 0 ) {

      auto data = readConstant1dAsDouble( child );
      convertRadius( data.first, data.second );
      return data.first;
    }
    else {

      return createTabulatedRadius( child );
    }
  }

} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
