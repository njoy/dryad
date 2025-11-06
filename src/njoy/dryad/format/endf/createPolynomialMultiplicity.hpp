#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPOLYNOMIALMULTIPLICITY
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPOLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/format/endf/createBoundaries.hpp"
#include "dryad/format/endf/createInterpolants.hpp"
#include "dryad/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a PolynomialMultiplicity from a parsed ENDF multiplicity
   */
  PolynomialMultiplicity
  createPolynomialMultiplicity( double lower, double upper,
                                const ENDFtk::section::PolynomialMultiplicity& multiplicity ) {

    try {

      Log::info( "Reading multiplicity data" );
      auto coefficients = createVector( multiplicity.coefficients() );
      return PolynomialMultiplicity(
               std::move( lower ), std::move( upper ),
               std::move( coefficients ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a polynomial multiplicity" );
      throw;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
