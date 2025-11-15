// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace reconr {

  // declarations
  void wrapUnioniseCrossSections( python::module& );
  void wrapCalculateSummationCrossSections( python::module& );
} // medic namespace

void wrapReconr( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "reconr",
    "Linearisation, unionisation and resonance reconstruction"
  );

  // wrap components
  reconr::wrapUnioniseCrossSections( submodule );
  reconr::wrapCalculateSummationCrossSections( submodule );
}
