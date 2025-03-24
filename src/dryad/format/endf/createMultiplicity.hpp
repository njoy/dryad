#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEMULTIPLICITY
#define NJOY_DRYAD_FORMAT_ENDF_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createTabulatedMultiplicity.hpp"
#include "dryad/PolynomialMultiplicity.hpp"
#include "dryad/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an integer multiplicity
   */
  std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity >
  createMultiplicity( int multiplicity ) {

    return multiplicity;
  }

  /**
   *  @brief Create an integer or tabulated multiplicity from a parsed ENDF multiplicity
   */
  template < typename Multiplicity >
  auto createMultiplicity( const Multiplicity& multiplicity )
  -> std::enable_if_t< ( std::is_same_v< Multiplicity, ENDFtk::section::Type< 6 >::Multiplicity > ||
                         std::is_same_v< Multiplicity, ENDFtk::section::Type< 26 >::Multiplicity > ),
                         std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity > > {

    if ( scion::verification::isAllSameElement( multiplicity.multiplicities() ) ) {

      return static_cast< int >( std::round( multiplicity.multiplicities().front() ) );
    }
    else {

      return createTabulatedMultiplicity( multiplicity );
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
