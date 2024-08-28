// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace atomic {

  // declarations - enumerators
  void wrapTransitionType( python::module&, python::module& );

  // declarations - atomic data components
  void wrapElectronSubshellConfiguration( python::module&, python::module& );
}

void wrapAtomic( python::module& module, python::module& viewmodule ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "atomic",
    "Atomic relaxation data components"
  );

  // wrap components - enumerators
  atomic::wrapTransitionType( submodule, viewmodule );

  // declarations - atomic data components
  atomic::wrapElectronSubshellConfiguration( submodule, viewmodule );
}
