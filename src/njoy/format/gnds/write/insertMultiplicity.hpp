#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTMULTIPLICITY
#define NJOY_FORMAT_GNDS_WRITE_INSERTMULTIPLICITY

// system includes
#include <optional>
#include <string>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/TabulatedMultiplicity.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertConstant1d.hpp"
#include "njoy/format/gnds/write/insertPolynomial1d.hpp"
#include "njoy/format/gnds/write/insertTabulatedFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a multiplicity into a gnds node
   *
   *  @param[in,out] parent         the parent node
   *  @param[in]     option         the gnds write options
   *  @param[in]     multiplicity   the multiplicity
   *  @param[in]     min            the lower domain limit
   *  @param[in]     max            the upper domain limit
   *  @param[in]     label          the optional label for the node
   */
  inline pugi::xml_node
  insertMultiplicity( pugi::xml_node& parent,
                      const Options& options,
                      const std::variant< int, dryad::TabulatedMultiplicity, dryad::PolynomialMultiplicity >& multiplicity,
                      double min,
                      double max,
                      const std::optional< std::string >& label = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "multiplicity" );

    //! @todo this is where we would convert units if we really wanted to

    auto insert = tools::overload{

      [&] ( int value ) -> pugi::xml_node {

        return insertConstant1d( node, options, value, min, max,
                                 "incidentEnergy", "multiplicity", "eV", std::nullopt,
                                 label );
      },
      [&] ( const dryad::TabulatedMultiplicity& table ) -> pugi::xml_node {

        return insertTabulatedFunction( node, options, table.energies(), table.values(),
                                        table.boundaries(), table.interpolants(),
                                        "incidentEnergy", "multiplicity", "eV", std::nullopt,
                                        label );
      },
      [&] ( const dryad::PolynomialMultiplicity& series ) -> pugi::xml_node {

        return insertPolynomial1d( node, options, series.coefficients(),
                                   series.lowerEnergyLimit(), series.upperEnergyLimit(),
                                   "incidentEnergy", "multiplicity", "eV", std::nullopt,
                                   label );
      }
    };

    std::visit( insert, multiplicity );
    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
