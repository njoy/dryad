#ifndef NJOY_FORMAT_ENDF_READ_CREATEPOLYNOMIALMULTIPLICITY
#define NJOY_FORMAT_ENDF_READ_CREATEPOLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/createBoundaries.hpp"
#include "njoy/format/endf/read/createInterpolants.hpp"
#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a PolynomialMultiplicity from a parsed ENDF multiplicity
   */
  inline dryad::PolynomialMultiplicity
  createPolynomialMultiplicity( double lower, double upper,
                                const ENDFtk::section::PolynomialMultiplicity& multiplicity ) {

    try {

      Log::info( "Reading multiplicity data" );
      auto coefficients = createVector( multiplicity.coefficients() );
      return dryad::PolynomialMultiplicity(
               std::move( lower ), std::move( upper ),
               std::move( coefficients ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a polynomial multiplicity" );
      throw;
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
