#ifndef NJOY_FORMAT_ENDF_READ_CREATEMULTIPLICITY
#define NJOY_FORMAT_ENDF_READ_CREATEMULTIPLICITY

// system includes
#include <variant>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/dryad/TabulatedMultiplicity.hpp"
#include "njoy/format/endf/read/createPolynomialMultiplicity.hpp"
#include "njoy/format/endf/read/createTabulatedMultiplicity.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/26.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create an integer multiplicity
   *
   *  @param[in] multiplicity   the integer multiplicity
   */
  inline std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity >
  createMultiplicity( int multiplicity ) {

    return multiplicity;
  }

  /**
   *  @brief Create a polynomial multiplicity from a parsed ENDF multiplicity
   *
   *  @param[in] lower          the lower energy limit
   *  @param[in] upper          the upper energy limit
   *  @param[in] multiplicity   the parsed ENDF polynomial multiplicity
   */
  std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity >
  createMultiplicity( double lower, double upper,
                      const ENDFtk::section::PolynomialMultiplicity& multiplicity ) {

    return createPolynomialMultiplicity( lower, upper, multiplicity );
  }

  /**
   *  @brief Create a tabulated multiplicity from a parsed ENDF multiplicity
   *
   *  @param[in] multiplicity   the parsed ENDF tabulated multiplicity
   */
  std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity >
  createMultiplicity( double, double,
                      const ENDFtk::section::TabulatedMultiplicity& multiplicity ) {

    return createTabulatedMultiplicity( multiplicity );
  }

  /**
   *  @brief Create an integer or tabulated multiplicity from a parsed ENDF multiplicity
   *
   *  @param[in] multiplicity   the integer, polynomial or tabulated multiplicity
   */
  template < typename Multiplicity >
  auto createMultiplicity( const Multiplicity& multiplicity )
  -> std::enable_if_t< ( std::is_same_v< Multiplicity, ENDFtk::section::Type< 6 >::Multiplicity > ||
                         std::is_same_v< Multiplicity, ENDFtk::section::Type< 26 >::Multiplicity > ),
                         std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity > > {

    if ( scion::verification::isAllSameElement( multiplicity.multiplicities() ) ) {

      int value = static_cast< int >( std::round( multiplicity.multiplicities().front() ) );
      if ( multiplicity.multiplicities().front() == value ) {

        return value;
      }
      else {

        return createTabulatedMultiplicity( multiplicity );
      }
    }
    else {

      return createTabulatedMultiplicity( multiplicity );
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
