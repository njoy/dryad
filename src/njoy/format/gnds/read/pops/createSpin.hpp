#ifndef NJOY_FORMAT_GNDS_READ_POPS_CREATESPIN
#define NJOY_FORMAT_GNDS_READ_POPS_CREATESPIN

// system includes
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/readFraction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace pops {

  /**
   *  @brief Create a spin values from a GNDS spin xml node
   *
   *  @param[in] spin    the GNDS spin node
   *  @param[in] style   the gnds style to process (default is eval)
   */
  inline std::optional< double >
  createSpin( const pugi::xml_node& spin, const std::string& style = "eval" ) {

    // check that this is a valid spin node
    throwExceptionOnWrongNode( spin, "spin" );

    // get a double node if it exists, else return nullopt
    auto child = spin.find_child_by_attribute( "fraction", "label", style.c_str() );
    if ( child ) {

      auto content = readFraction( child );
      if ( "hbar" == content.second || ! content.second.has_value() ) {

        return content.first;
      }
      else {

        Log::error( "Cannot convert spin with unit \'{}\' to hbar, "
                    "contact dryad developers", content.second.value() );
        throw std::exception();
      }
    }

    return std::nullopt;
  }

} // pops namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
