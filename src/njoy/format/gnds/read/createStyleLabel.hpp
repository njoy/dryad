#ifndef NJOY_FORMAT_GNDS_READ_CREATESTYLELABEL
#define NJOY_FORMAT_GNDS_READ_CREATESTYLELABEL

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/StyleType.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create the style label to look for
   *
   *  @param[in] styles   the GNDS styles node
   *  @param[in] style    the style enum
   */
  inline std::string
  createStyleLabel( pugi::xml_node styles, const StyleType& style = StyleType::Evaluation ) {

    // check that this is a valid styles node
    throwExceptionOnWrongNode( styles, "styles" );

    std::string node_name;
    switch ( style ) {

      case StyleType::Evaluation : {

        node_name = "evaluated";
        break;
      }
      default : {

        throw std::runtime_error( "You have somehow reached unreachable code in the createStyleLabel function, "
                                  "contact an njoy developer" );
      }
    }

    auto child = styles.child( node_name.c_str() );
    if ( child ) {

      auto label = child.attribute( "label" );
      if ( label ) {

        return label.as_string();
      }
    }

    Log::error( "The GNDS node named \'{}\' or its label attribute is not defined", node_name );
    throw std::exception();
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
