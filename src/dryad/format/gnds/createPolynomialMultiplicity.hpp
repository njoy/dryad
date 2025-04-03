#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEPOLYNOMIALMULTIPLICITY
#define NJOY_DRYAD_FORMAT_GNDS_CREATEPOLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/readPolynomial1d.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/PolynomialMultiplicity.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a PolynomialMultiplicity from a GNDS multiplicity node
   */
  static PolynomialMultiplicity
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

    return PolynomialMultiplicity( std::move( lower ), std::move( upper ),
                                   std::move( coefficients ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
