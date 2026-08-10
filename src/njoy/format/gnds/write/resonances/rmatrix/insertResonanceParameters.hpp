#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCEPARAMETERS
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCEPARAMETERS

// system includes
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertTable.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Insert resonance parameters into a gnds node
   *
   *  @param[in,out] parent                   the parent node
   *  @param[in]     option                   the gnds write options
   *  @param[in]     spingroup                the spin group with the parameters to be written out
   *  @param[in]     reducedWidthAmplitudes   use reduced width amplitudes
   */
  inline pugi::xml_node
  insertResonanceParameters( pugi::xml_node& parent,
                             const Options& options,
                             const dryad::resonances::SpinGroup& spingroup,
                             bool reducedWidthAmplitudes = true ) {

    pugi::xml_node node = parent.append_child( "resonanceParameters" );

    decltype(auto) table = spingroup.resonanceTable();

    std::size_t nrs = table.numberEnergies();
    std::size_t nch = table.numberChannels();

    std::vector< std::string > names( nch + 1 );
    std::vector< std::optional< std::string > > units( nch + 1 );
    std::vector< std::vector< double > > columns( nch + 1,
                                                  std::vector< double >( nrs ) );

    names[0] = "incidentEnergy";
    units[0] = "eV";
    columns[0] = table.energies();

    decltype(auto) widths = table.reducedWidthAmplitudes();
    for ( std::size_t i = 0; i < nch; ++i ) {

      names[i+1] = table.channels()[i].symbol() + " width";
      units[i+1] = reducedWidthAmplitudes ? "eV^1/2" : "eV";

      for ( std::size_t j = 0; j < nrs; ++j ) {

        if ( reducedWidthAmplitudes ) {

          columns[i+1][j] = widths[i][j];
        }
        else {

          double penetrability = spingroup.channels()[i].penetrability( columns[0][j] );
          double sign = widths[i][j] < 0. ? -1. : +1.;
          columns[i+1][j] = sign * 2. * penetrability * widths[i][j] * widths[i][j];
        }
      }
    }

    insertTable( node, options, names, units, columns );

    return node;
  }

} // rmatrix namespace
} // resonances namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
