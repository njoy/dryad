// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace resonances {

  // declarations - components
  void wrapResonanceParameters( python::module& );
}

void wrapResonances( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "resonances",
    "Resonance data"
  );

  resonances::wrapResonanceParameters( submodule );
}
