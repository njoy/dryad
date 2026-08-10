#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTEXTERNALRMATRIX
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTEXTERNALRMATRIX

// system includes
#include <optional>
#include <string>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"
#include "njoy/dryad/resonances/TabulatedBackground.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertDouble.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Insert an external RMatrix into a gnds node
   *
   *  @param[in,out] parent       the parent node
   *  @param[in]     option       the gnds write options
   *  @param[in]     background   the external r matrix element
   */
  inline pugi::xml_node
  insertExternalRMatrix( pugi::xml_node& parent,
                         const Options& options,
                         const std::variant<
                                   dryad::resonances::FrohnerBackground,
                                   dryad::resonances::SammyBackground,
                                   dryad::resonances::TabulatedBackground >& background ) {

    pugi::xml_node node = parent.append_child( "externalRMatrix" );

    auto insert = tools::overload{

      [&] ( const dryad::resonances::FrohnerBackground& froehner ) -> pugi::xml_node {

        node.append_attribute( "type" ) = "Froehner";
        insertDouble( node, options, froehner.averageRadiationWidth(), "averageRadiationWidth", "eV" );
        insertDouble( node, options, froehner.distantLevelParameter(), "constantExternalR" );
        insertDouble( node, options, froehner.poleStrength(), "poleStrength" );
        insertDouble( node, options, froehner.lowerSingularity(), "singularityEnergyBelow", "eV" );
        insertDouble( node, options, froehner.upperSingularity(), "singularityEnergyAbove", "eV" );
        return node;
      },
      [&] ( const dryad::resonances::SammyBackground& sammy ) -> pugi::xml_node {

        node.append_attribute( "type" ) = "SAMMY";
        insertDouble( node, options, sammy.polynomialCoefficients()[0], "constantExternalR" );
        insertDouble( node, options, sammy.polynomialCoefficients()[1], "linearExternalR", "1/eV" );
        insertDouble( node, options, sammy.polynomialCoefficients()[2], "quadraticExternalR", "1/eV**2" );
        insertDouble( node, options, sammy.logarithmicCoefficients()[0], "constantLogarithmicCoefficient" );
        insertDouble( node, options, sammy.logarithmicCoefficients()[1], "linearLogarithmicCoefficient", "1/eV" );
        insertDouble( node, options, sammy.lowerSingularity(), "singularityEnergyBelow", "eV" );
        insertDouble( node, options, sammy.upperSingularity(), "singularityEnergyAbove", "eV" );
        return node;
      },
      [&] ( const dryad::resonances::TabulatedBackground& table ) -> pugi::xml_node {

        throw std::runtime_error( "GNDS does not support tabulated R matrix elements" );
      }
    };

    return std::visit( insert, background );
  }

} // rmatrix namespace
} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
