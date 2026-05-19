// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace medic {

  // declarations - pruning
  void wrapPruneCrossSection( python::module& );
  void wrapPruneCrossSections( python::module& );

  // declarations - covariance functions
  void wrapCovariance( python::module& );
} // medic namespace

void wrapMedic( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "medic",
    "Correcting and updating data"
  );

  // wrap components - pruning
  medic::wrapPruneCrossSection( submodule );
  medic::wrapPruneCrossSections( submodule );

  // wrap components - covariance functions
  medic::wrapCovariance( submodule );
}
