#ifndef NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATEBACKGROUND
#define NJOY_FORMAT_GNDS_READ_RESONANCES_RMATRIX_CREATEBACKGROUND

// system includes
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"
#include "njoy/format/gnds/read/readDouble.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"
#include "njoy/format/gnds/read/convertInverseEnergy.hpp"
#include "njoy/format/gnds/read/convertInverseEnergySquared.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create a SammyBackground from a GNDS externalRMatrix node
   *
   *  @param[in] node   the GNDS XYs1d or regions1d node
   */
  inline std::variant< njoy::dryad::resonances::FrohnerBackground,
                       njoy::dryad::resonances::SammyBackground,
                       njoy::dryad::resonances::TabulatedBackground >
  createBackground( const pugi::xml_node& external ) {

    // check that this is a valid externalRMatrix node
    throwExceptionOnWrongNode( external, "externalRMatrix" );

    // get the type of external r-matrix element
    auto type = external.attribute( "type" );
    if ( type ) {

      if ( strcmp( type.as_string(), "Froehner" ) == 0 ) {

        auto r = readDouble( external.find_child_by_attribute( "double", "label", "constantExternalR" ) );
        auto s = readDouble( external.find_child_by_attribute( "double", "label", "poleStrength" ) );
        auto gamma = readDouble( external.find_child_by_attribute( "double", "label", "averageRadiationWidth" ) );
        convertEnergy( gamma.first, gamma.second.value() );

        auto lower = readDouble( external.find_child_by_attribute( "double", "label", "singularityEnergyBelow" ) );
        auto upper = readDouble( external.find_child_by_attribute( "double", "label", "singularityEnergyAbove" ) );
        convertEnergy( lower.first, lower.second.value() );
        convertEnergy( upper.first, upper.second.value() );
        return njoy::dryad::resonances::FrohnerBackground(
                 r.first, s.first, gamma.first,
                 lower.first, upper.first );
      }
      else if ( strcmp( type.as_string(), "SAMMY" ) == 0 ) {

        auto r0 = readDouble( external.find_child_by_attribute( "double", "label", "constantExternalR" ) );
        auto r1 = readDouble( external.find_child_by_attribute( "double", "label", "linearExternalR" ) );
        auto r2 = readDouble( external.find_child_by_attribute( "double", "label", "quadraticExternalR" ) );
        std::array< double, 3 > polynomial = { r0.first, r1.first, r2.first };
        convertInverseEnergy( polynomial[1], r1.second.value() );
        convertInverseEnergySquared( polynomial[2], r2.second.value() );

        auto s0 = readDouble( external.find_child_by_attribute( "double", "label", "constantLogarithmicCoefficient" ) );
        auto s1 = readDouble( external.find_child_by_attribute( "double", "label", "linearLogarithmicCoefficient" ) );
        std::array< double, 2 > logarithmic = { s0.first, s1.first };
        convertInverseEnergy( logarithmic[1], s1.second.value() );

        auto lower = readDouble( external.find_child_by_attribute( "double", "label", "singularityEnergyBelow" ) );
        auto upper = readDouble( external.find_child_by_attribute( "double", "label", "singularityEnergyAbove" ) );
        convertEnergy( lower.first, lower.second.value() );
        convertEnergy( upper.first, upper.second.value() );
        return njoy::dryad::resonances::SammyBackground(
                 std::move( polynomial ), std::move( logarithmic ),
                 lower.first, upper.first );
      }
      else {

        Log::error( "Encountered an unknown external R-matrix type: \'{}\'", type.as_string() );
        throw std::exception();
      }
    }
    else {

      Log::error( "No type defined on the externalRMatrix node" );
      throw std::exception();
    }
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
