// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/medic/pruneCrossSections.hpp"

// namespace aliases
namespace python = pybind11;

namespace medic {

  void wrapPruneCrossSections( python::module& module ) {

    // type aliases

    // wrap the function
    module
    .def(

      "prune_cross_sections",
      &njoy::medic::pruneCrossSections,
      python::arg( "lower_energy" ),
      python::arg( "upper_energy" ),
      python::arg( "pt" ),
      "Prune cross section data\n\n"
      "Parameters\n"
      "----------\n"
      "    lower_energy : float\n"
      "        the new lower energy limit\n"
      "    upper_energy : float\n"
      "        the new upper energy limit\n"
      "    pt : njoy.dryad.ProjectileTarget\n"
      "        the projectile-target data to be modified"
    );
  }

} // medic namespace
