#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_CREATERADIUS
#define NJOY_FORMAT_GNDS_READ_RESONANCES_CREATERADIUS

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "njoy/format/gnds/read/resonances/createTabulatedRadius.hpp"
#include "njoy/format/gnds/read/readConstant1d.hpp"
#include "njoy/format/gnds/read/convertRadius.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {

  /**
   *  @brief Create a double or tabulated radius from a GNDS scattering radius node
   *
   *  @param[in] radius   the GNDS scattering radius or hardsphere radius node
   */
  inline std::variant< double, dryad::resonances::TabulatedRadius >
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
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif //NJOY_DRYAD_FORMAT_GNDS_RESONANCES_CREATERADIUS
