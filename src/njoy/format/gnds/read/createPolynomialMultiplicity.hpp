#ifndef NJOY_FORMAT_GNDS_READ_CREATEPOLYNOMIALMULTIPLICITY
#define NJOY_FORMAT_GNDS_READ_CREATEPOLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/format/gnds/read/readPolynomial1d.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a PolynomialMultiplicity from a GNDS multiplicity node
   *
   *  @param[in] multiplicity   the gnds multiplicity node
   *  @param[in] style          the gnds style to process (default is eval)
   */
  inline dryad::PolynomialMultiplicity
  createPolynomialMultiplicity( const pugi::xml_node& multiplicity,
                                const std::string& style = "eval" ) {

    double lower;
    double upper;
    std::vector< double > coefficients;

    // check that this is a valid multiplicity node
    throwExceptionOnWrongNode( multiplicity, "multiplicity" );

    auto node = multiplicity.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( node.name(), "polynomial1d" ) == 0 ) {

      // read the multiplicity data
      auto data = readPolynomial1d( node );

      // convert units - if necessary
      convertEnergy( std::get< 2 >( data ), std::get< 5 >( data ) );
      convertEnergy( std::get< 3 >( data ), std::get< 5 >( data ) );
      if ( std::get< 5 >( data ) != "eV" ) {

        double conversion = 1;
        convertEnergy( conversion, std::get< 5 >( data ) );
        for ( unsigned int i = 1; i < std::get< 4 >( data ).size(); ++i ) {

          std::get< 4 >( data )[i] /= conversion;
          conversion *= conversion;
        }
      }

      // assign data
      lower = std::move( std::get< 2 >( data ) );
      upper = std::move( std::get< 3 >( data ) );
      coefficients = std::move( std::get< 4 >( data ) );
    }
    else {

      Log::error( "Expected a polynomial1d node for multiplicity data" );
      throw std::exception();
    }

    return dryad::PolynomialMultiplicity( std::move( lower ), std::move( upper ),
                                          std::move( coefficients ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
