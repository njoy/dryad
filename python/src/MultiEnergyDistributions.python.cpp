// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/MultiEnergyDistributions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMultiEnergyDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::MultiEnergyDistributions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MultiEnergyDistributions"
  );
}
