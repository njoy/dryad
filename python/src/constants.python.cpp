// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/constants.hpp"

// namespace aliases
namespace python = pybind11;

void wrapConstants( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "constants",
    "Physical and mathematical constants"
  );

  // math
  submodule.attr( "pi" ) = python::float_( njoy::constants::pi );

  // physics
  submodule.attr( "neutron_mass" ) = python::float_( njoy::constants::neutron_mass );
}
