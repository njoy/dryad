// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/medic/pruneCrossSection.hpp"

// namespace aliases
namespace python = pybind11;

namespace medic {

  void wrapPruneCrossSection( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "prune_cross_section",
      &njoy::medic::pruneCrossSection,
      python::arg( "lower_energy" ),
      python::arg( "upper_energy" ),
      python::arg( "xs" ),
      "Prune cross section data\n\n"
      "Arguments:\n"
      "    lower_energy   the new lower energy limit\n"
      "    upper_energy   the new upper energy limit\n"
      "    xs             the cross section table to be modified"
    );
  }
} // medic namespace
